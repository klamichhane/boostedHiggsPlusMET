#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <cassert>
#include "plotterUtils.cc"
//#include "skimSamples_2016.cc"
#include "skimSamples_2017.cc"
//#include "skimSamples_2018.cc"
#include "definitions.h"
#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"

using namespace std;

int MAX_EVENTS = 99999999;

void process(string selection_label,
	     string backgroundSample,
	     string signalSample,
	     string dataSample){

    if(year=="2016") {lum=35815.165; p0=1.21277e+02; p1=8.77679e+01;p2=9.94172e-01;}
    if(year=="2017") {lum=41486.136; p0=1.61724e+02; p1=6.91644e+01; p2=9.89446e-01;}
    if(year=="2018") {lum=59546.381; p0=1.70454e+02; p1=6.64100e+01; p2=9.89298e-01;}
    cout<<"year: "<<year<<" lumi: "<<lum<<endl;

  // set up selectors
    bool (*selectionFunc)(RA2bTree*);
    if( selection_label == "ZSRHPVBF"){
        selectionFunc = ZSRHPVBFVBF;
    }else if( selection_label == "ZSRHPVBFfail"){
        selectionFunc = ZSRHPVBFfail;
    }else{
        assert(0);
    }

  // set up background samples
    vector<TString> backgroundSamples;
    if( backgroundSample != "" ){
        backgroundSamples.push_back(TString(backgroundSample));
    }

  // setup signal samples
    vector<TString> signalSamples;
    if( signalSample != "" ){
        signalSamples.push_back(TString(signalSample));
    }

  // setup data samples
    vector<TString> dataSamples;
    if( dataSample != "" ){
        dataSamples.push_back(TString(dataSample));
    }
    skimSamples skims(skimSamples::kSignal,backgroundSamples,signalSamples,dataSamples);
  
  // begin plotting sutff
  gROOT->ProcessLine(".L tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");
  
  typedef plot<RA2bTree> plot;

  double edges_ggf1[22]={500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2250,2400,2550,2700,2900};  
  double edges_vbf1[16]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1850,2100};
  plot ZMT_ggFplot(*fillZMT<RA2bTree>,"ZMT_ggF_"+selection_label,"MT [GeV]",21,edges_ggf1); 
  plot ZMT_vbFplot(*fillZMT<RA2bTree>,"ZMT_VBF_"+selection_label,"MT [GeV]",15,edges_vbf1); 
// For PDF and Scale wt:

  vector<plot> plots;
  plots.push_back(ZMT_ggFplot);  
  plots.push_back(ZMT_vbFplot);  

  // background MC samples
  for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
    RA2bTree* ntuple = skims.ntuples[iSample];
    isMC_ = true;
    TFile* outputFile = new TFile("AN_v0_Sep08/plotObs_"+selection_label+"_baseline_"+skims.sampleName[iSample]+".root","RECREATE");
    
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
    }
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    double weight = 0., pdfwt=0., scalewt=0.;
    
    double edges_ggf[22]={500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2250,2400,2550,2700,2900};  
    double edges_vbf[16]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1850,2100};
    TH2* h_PDF_ggf = new TH2F("h_PDF_ggf","PDF",21,edges_ggf,101,0,101); 
    TH2* h_PDF_vbf = new TH2F("h_PDF_vbf","PDF",15,edges_vbf,101,0,101); 
    TH2* h_Scale_ggf = new TH2F("h_Scale_ggf","Scale",21,edges_ggf,9,0,9); 
    TH2* h_Scale_vbf = new TH2F("h_Scale_vbf","Scale",15,edges_vbf,9,0,9); 

    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
        filename = ntuple->fChain->GetFile()->GetName();
        if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;
    
        // Prefiring wt for 2016 & 2017 only
        if(! selectionFunc(ntuple) ) continue;
        weight = ntuple->Weight*lumi*ntuple->NonPrefiringProb;   //weight = ntuple->Weight*lumii*customPUweights(ntuple);

        // PDF and Scale Weights
        double MT = 0.0;
        if(ntuple->JetsAK8->size()==0) MT=-99999.;
        else{
            double AK8Pt = ntuple->JetsAK8->at(0).Pt();
            double AK8Phi = ntuple->JetsAK8->at(0).Phi();
            double MET = ntuple->MET;
            double METPhi = ntuple->METPhi;
            MT = ZMT(AK8Pt, AK8Phi, MET, METPhi);
        }

        //------ PDF Weights ----------//
        for(int i=0; i<ntuple->PDFweights->size(); i++){
            pdfwt = weight*ntuple->PDFweights->at(i);
            h_PDF_ggf->Fill(MT,i,pdfwt);
            h_PDF_vbf->Fill(MT,i,pdfwt);
        }
        //------ Scale Weights ----------//
        for(int j=0; j<ntuple->ScaleWeights->size(); j++){
            scalewt = weight*ntuple->ScaleWeights->at(j);
            h_Scale_ggf->Fill(MT,j,scalewt);
            h_Scale_vbf->Fill(MT,j,scalewt);
        }

      // ------------ end weights -------------
      //cout << "event passed all selections" << endl;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
	        plots[iPlot].fill(ntuple,weight);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    h_PDF_ggf->Write();
    h_PDF_vbf->Write();
    h_Scale_ggf->Write();
    h_Scale_vbf->Write();
    outputFile->Close();
 }// end loop over bkg samples
    
  // Signal samples
  vector<RA2bTree*> sigSamples;
  for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
    RA2bTree* ntuple = skims.signalNtuples[iSample];
    isMC_ = true;
    TFile* outputFile = new TFile("AN_v0_Sep08/plotObs_"+selection_label+"_baseline_"+skims.signalSampleName[iSample]+".root","RECREATE");

    sigSamples.push_back(ntuple);
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);

    double weight = 0., pdfwt=0., scalewt=0.;

    double edges_ggf[22]={500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2250,2400,2550,2700,2900};  
    double edges_vbf[16]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1850,2100};
    TH2* h_PDF_ggf = new TH2F("h_PDF_ggf","PDF",21,edges_ggf,101,0,101); 
    TH2* h_PDF_vbf = new TH2F("h_PDF_vbf","PDF",15,edges_vbf,101,0,101); 
    TH2* h_Scale_ggf = new TH2F("h_Scale_ggf","Scale",21,edges_ggf,9,0,9); 
    TH2* h_Scale_vbf = new TH2F("h_Scale_vbf","Scale",15,edges_vbf,9,0,9); 

    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
      ntuple->GetEntry(iEvt);
      if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;

      if(! selectionFunc(ntuple) ) continue;

         // PDF and Scale Weights
        double MT = 0.0;
        if(ntuple->JetsAK8->size()==0) MT=-99999.;
        else{
            double AK8Pt = ntuple->JetsAK8->at(0).Pt();
            double AK8Phi = ntuple->JetsAK8->at(0).Phi();
            double MET = ntuple->MET;
            double METPhi = ntuple->METPhi;
            MT = ZMT(AK8Pt, AK8Phi, MET, METPhi);
        }

        //------ PDF Weights ----------//
        weight = lumi*1*2e-05;
        for(int i=0; i<ntuple->PDFweights->size(); i++){
            pdfwt = weight*ntuple->PDFweights->at(i);
            h_PDF_ggf->Fill(MT,i,pdfwt);
            h_PDF_vbf->Fill(MT,i,pdfwt);
        }
        //------ Scale Weights ----------//
        for(int j=0; j<ntuple->ScaleWeights->size(); j++){
            scalewt = weight*ntuple->ScaleWeights->at(j);
            h_Scale_ggf->Fill(MT,j,scalewt);
            h_Scale_vbf->Fill(MT,j,scalewt);
        }
// end of pdf and scale wt for signal

      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        TString sig_sample = skims.signalSampleName[iSample];    
	    //if (skims.signalSampleName[iSample]=="VBFG_1400") 

        // based on 2018 samples for VBF
	    if ((sig_sample=="VBFG_800") || (sig_sample=="VBFWp_800") || (sig_sample=="VBFRad_800")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_1000") || (sig_sample=="VBFWp_1000") || (sig_sample=="VBFRad_1000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); // wt for 48300 evts: 1pb/#evts
	        // plots[iPlot].fillSignal(ntuple,lumi*1*0.0000207); //for VBFG 2016 for 48300 evts: 1pb/#evts
	    if ((sig_sample=="VBFG_1200") || (sig_sample=="VBFWp_1200") || (sig_sample=="VBFRad_1200")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_1400") || (sig_sample=="VBFWp_1400") || (sig_sample=="VBFRad_1400")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_1600") || (sig_sample=="VBFWp_1600") || (sig_sample=="VBFRad_1600")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_1800") || (sig_sample=="VBFWp_1800") || (sig_sample=="VBFRad_1800")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_2000") || (sig_sample=="VBFWp_2000") || (sig_sample=="VBFRad_2000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_2500") || (sig_sample=="VBFWp_2500") || (sig_sample=="VBFRad_2500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_3000") || (sig_sample=="VBFWp_3000") || (sig_sample=="VBFRad_3000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_3500") || (sig_sample=="VBFWp_3500") || (sig_sample=="VBFRad_3500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_4000") || (sig_sample=="VBFWp_4000") || (sig_sample=="VBFRad_4000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_4500") || (sig_sample=="VBFWp_4500") || (sig_sample=="VBFRad_4500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_5000") || (sig_sample=="VBFWp_5000") || (sig_sample=="VBFRad_5000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_5500") || (sig_sample=="VBFRad_5500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if (sig_sample=="VBFWp_5500") 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2.08333e-05); 
	    if ((sig_sample=="VBFG_6000") || (sig_sample=="VBFWp_6000") || (sig_sample=="VBFRad_6000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_6500") || (sig_sample=="VBFWp_6500") || (sig_sample=="VBFRad_6500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="VBFG_7000") || (sig_sample=="VBFWp_7000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if (sig_sample=="VBFRad_7000") 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2.08333e-05); 
	    if ((sig_sample=="VBFG_7500") || (sig_sample=="VBFWp_7500") || (sig_sample=="VBFRad_7500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if (sig_sample=="VBFG_8000") 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2.222222e-05); 
	    if ((sig_sample=="VBFWp_8000") || (sig_sample=="VBFRad_8000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 

        // based on 2017 samples for ggF
	    if ((sig_sample=="ggFG_800") || (sig_sample=="ggFWp_800") || (sig_sample=="ggFRad_800")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_1000") || (sig_sample=="ggFWp_1000") || (sig_sample=="ggFRad_1000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); // wt for 48300 evts: 1pb/#evts
	    if ((sig_sample=="ggFG_1200") || (sig_sample=="ggFWp_1200") || (sig_sample=="ggFRad_1200")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_1400") || (sig_sample=="ggFWp_1400") || (sig_sample=="ggFRad_1400")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_1600") || (sig_sample=="ggFWp_1600") || (sig_sample=="ggFRad_1600")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_1800") || (sig_sample=="ggFWp_1800") || (sig_sample=="ggFRad_1800")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_2000") || (sig_sample=="ggFWp_2000") || (sig_sample=="ggFRad_2000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_2500") || (sig_sample=="ggFWp_2500") || (sig_sample=="ggFRad_2500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_3000") || (sig_sample=="ggFWp_3000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if (sig_sample=="ggFRad_3000") 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2.325581395348837e-05); 
	    if ((sig_sample=="ggFG_3500") || (sig_sample=="ggFWp_3500") || (sig_sample=="ggFRad_3500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_4000") || (sig_sample=="ggFWp_4000") || (sig_sample=="ggFRad_4000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_4500") || (sig_sample=="ggFWp_4500") || (sig_sample=="ggFRad_4500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_5000") || (sig_sample=="ggFWp_5000") || (sig_sample=="ggFRad_5000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_5500") || (sig_sample=="ggFWp_5500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if (sig_sample=="ggFRad_5500") 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2.08333e-05); 
	    if ((sig_sample=="ggFG_6000") || (sig_sample=="ggFWp_6000") || (sig_sample=="ggFRad_6000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_6500") || (sig_sample=="ggFWp_6500") || (sig_sample=="ggFRad_6500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_7000") || (sig_sample=="ggFWp_7000") || (sig_sample=="ggFRad_7000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if ((sig_sample=="ggFG_7500") || (sig_sample=="ggFWp_7500")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	    if (sig_sample=="ggFRad_7500") 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2.0408163265306123e-05); 
	    if ((sig_sample=="ggFG_8000") || (sig_sample=="ggFWp_8000") || (sig_sample=="ggFRad_8000")) 
	        plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    
    h_PDF_ggf->Write();
    h_PDF_vbf->Write();
    h_Scale_ggf->Write();
    h_Scale_vbf->Write();
    outputFile->Close();
  }// end loop over samples


  // Data samples
  for( int iSample = 0 ; iSample < skims.dataNtuple.size() ; iSample++){
    RA2bTree* ntuple = skims.dataNtuple[iSample];
    //TFile* outputFile = new TFile("plotObs_"+selection_label+"_baseline_"+skims.dataSampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_v0_Sep08/plotObs_"+selection_label+"_baseline_"+skims.dataSampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("Test_Files_Jul29/plotObs_"+selection_label+"_baseline_"+skims.dataSampleName[iSample]+".root","RECREATE");
	  
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,skims.dataSampleName[iSample]);
    }
    
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    cout << "data MET: " << numEvents << endl;
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(0,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        //cout<<"Run Num: "<<ntuple->RunNum<<endl;
        if( iEvt % 100000 == 0 ) cout << "data_MET: " << iEvt << "/" << min(MAX_EVENTS,numEvents) << endl;

        if(! selectionFunc(ntuple) ) continue;
        //if(! selectionFunc(ntuple, false) ) continue;
        //HEM Veto
       // if(!passHEMjetVeto(ntuple,30)) continue;

        if( !signalTriggerCut(ntuple) ) continue;
      
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
	        plots[iPlot].fillData(ntuple);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        //if (plots[iPlot].is2Dhist) continue;
        plots[iPlot].Write();
    }// end loop over plots
    
    outputFile->Close();
  }// end loop over samples

}// end process


int main(int argc, char** argv){

  string signal_label,background_label,data_label;
  string selection_label;
  if( argc > 5 )
    MAX_EVENTS = atoi(argv[5]);
  else
    MAX_EVENTS = 99999999;
  if( argc > 4 )
    data_label = argv[4];
  else
    data_label="";
  if( argc > 3 )
    signal_label = argv[3];
  else
    signal_label = "";
  if( argc > 2 )
    background_label = argv[2];
  else
    background_label = "ZJets_400to600";
  if( argc > 1 )
    selection_label = argv[1];
  else
    selection_label = "ZSBNoVBF";

  process(selection_label,
	  background_label,
	  signal_label,
	  data_label);
  
}
