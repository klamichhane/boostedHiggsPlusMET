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

string year = "2017"; //change the sample files above also 
double lum = 0.0;
double p0, p1, p2;

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
    if( selection_label == "ZNoSelection"){
        selectionFunc = baselineCutNoVBF;
    }else if( selection_label == "baselineVBF" ){
        selectionFunc = baselineCut;
    }else if( selection_label == "ZSRNoVBF"){
        selectionFunc = ZSignalRegionCutNoVBF;
    }else if( selection_label == "ZSRVBF"){
        selectionFunc = ZSignalRegionCut;
    }else if( selection_label == "ZSRHPNoVBF"){
        selectionFunc = ZSignalRegionHPCutNoVBF;
    }else if( selection_label == "ZSRHPVBF"){
        selectionFunc = ZSignalRegionHPCut;
    }else if( selection_label == "ZSBNoVBF" ){
        selectionFunc = ZSidebandnoVBFCut;
    }else if( selection_label == "ZSBVBF" ){
        selectionFunc = ZSidebandCut;
    }else if( selection_label == "ZSBHPNoVBF" ){
        selectionFunc = ZSidebandHPCutnoVBF;
    }else if( selection_label == "ZSBHPVBF" ){
        selectionFunc = ZSidebandHPCut;
    }else if( selection_label == "AlphaSBHPNoVBF" ){
        selectionFunc = ZAlphaSBHPnoVBF;
    }else if( selection_label == "AlphaSBHPVBF" ){
        selectionFunc = ZAlphaSBHPVBF;
    }else if( selection_label == "AlphaSBHPVBFfail" ){
        selectionFunc = ZAlphaSBHPVBFfail;
    }else if( selection_label == "AlphaSBFPVBF" ){
        selectionFunc = ZAlphaSBFPVBF;
    }else if( selection_label == "AlphaSBFPVBFfail" ){
        selectionFunc = ZAlphaSBFPVBFfail;
    }else if( selection_label == "AlphaSBHPLooseVBF" ){
        selectionFunc = ZAlphaSBHPLooseVBF;
    }else if( selection_label == "AlphaSBHPLooseVBFfail" ){
        selectionFunc = ZAlphaSBHPLooseVBFfail;
    }else if( selection_label == "AlphaSBFPLooseVBF" ){
        selectionFunc = ZAlphaSBFPLooseVBF;
    }else if( selection_label == "AlphaSBFPLooseVBFfail" ){
        selectionFunc = ZAlphaSBFPLooseVBFfail;

    }else if( selection_label == "AlphaSRHPNoVBF" ){
        selectionFunc = ZAlphaSRHPnoVBF;
    }else if( selection_label == "AlphaSRHPVBF" ){
        selectionFunc = ZAlphaSRHPVBF;
    }else if( selection_label == "AlphaSRHPVBFfail" ){
        selectionFunc = ZAlphaSRHPVBFfail;
    }else if( selection_label == "AlphaSRFPVBF" ){
        selectionFunc = ZAlphaSRFPVBF;
    }else if( selection_label == "AlphaSRFPVBFfail" ){
        selectionFunc = ZAlphaSRFPVBFfail;
    }else if( selection_label == "AlphaSRHPLooseVBF" ){
        selectionFunc = ZAlphaSRHPLooseVBF;
    }else if( selection_label == "AlphaSRHPLooseVBFfail" ){
        selectionFunc = ZAlphaSRHPLooseVBFfail;
    }else if( selection_label == "AlphaSRFPLooseVBF" ){
        selectionFunc = ZAlphaSRFPLooseVBF;
    }else if( selection_label == "AlphaSRFPLooseVBFfail" ){
        selectionFunc = ZAlphaSRFPLooseVBFfail;
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

  //plot HEMFracplot(*fillHEMTest1<RA2bTree>,"HEMFrac_"+selection_label,"HEM Frac",50,-0.5,999.5);//1 bin
  plot NVtxplot(*fillNVtx<RA2bTree>,"NVtx_"+selection_label,"NVtx",80,0.5,80.5);//1 bin
  plot MET1plot(*fillMET<RA2bTree>,"MET1_"+selection_label,"MET [GeV]",20,200.,1200.);//50 GeV bin
  plot HTplot(*fillHT<RA2bTree>,"HT_"+selection_label,"H_{T} [GeV]",75,300,3300.); // 100 GeV bin
  plot NJetsplot(*fillNJets<RA2bTree>,"NJets_"+selection_label,"n_{jets}",10,0.5,10.5); // Nj from tree
  plot NAK8Jets1plot(*fillNAK8Jets<RA2bTree>,"NAK8Jets1_"+selection_label,"nAK8_{jets}",4,0.5,4.5);
  plot madHT(*fillMadHT<RA2bTree>,"madHT_"+selection_label,"Madgraph HT",19,100,2000);  
 
  plot J1_SDMassplot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]",54,30.,300.);//5 Gev bin

  plot ZMTplot(*fillZMT<RA2bTree>,"ZMT_"+selection_label,"MT [GeV]",40,400.,4000.); // 100 GeV bin
  plot ZMT1plot(*fillZMT<RA2bTree>,"ZMT1_"+selection_label,"MT [GeV]",32,400.,2000.); //50 GeV bin
  plot ZMT2plot(*fillZMT<RA2bTree>,"ZMT2_"+selection_label,"MT [GeV]",44,400.,1500.); // 25 GeV bin
  plot ZMT3plot(*fillZMT<RA2bTree>,"ZMT3_"+selection_label,"MT [GeV]",52,400.,3000.); // 50 GeV bin
  plot ZMT31plot(*fillZMT<RA2bTree>,"ZMT31_"+selection_label,"MT [GeV]",22,500.,2700.); // 100 GeV bin
  plot ZMT311plot(*fillZMT<RA2bTree>,"ZMT311_"+selection_label,"MT [GeV]",44,500.,2700.); // 50 GeV bin
  plot ZMT312plot(*fillZMT<RA2bTree>,"ZMT312_"+selection_label,"MT [GeV]",88,500.,2700.); //25 GeV bin
  plot ZMT313plot(*fillZMT<RA2bTree>,"ZMT313_"+selection_label,"MT [GeV]",42,500.,4700.); // 100 GeV bin
  plot ZMT4plot(*fillZMT<RA2bTree>,"ZMT4_"+selection_label,"MT [GeV]",24,400.,1000.); // 25 GeV bin
  plot ZMT41plot(*fillZMT<RA2bTree>,"ZMT41_"+selection_label,"MT [GeV]",20,500.,1000.); // 25 GeV bin
  plot ZMT5plot(*fillZMT<RA2bTree>,"ZMT5_"+selection_label,"MT [GeV]",40,0.,1000.); // 25 GeV bin
  plot ZMT6plot(*fillZMT<RA2bTree>,"ZMT6_"+selection_label,"MT [GeV]",30,0.,1500.); // 50 GeV bin
  plot ZMT7plot(*fillZMT<RA2bTree>,"ZMT7_"+selection_label,"MT [GeV]",40,0.,2000.); // 50 GeV bin

  double edges_ggf[22]={500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2250,2400,2550,2700,2900};  
  double edges_vbf[16]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1850,2100};
  double edges_ggf50[39]={500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2050,2100,2150,2250,2400,2550,2700,2900};  
  double edges_vbf50[29]={400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1850,2100};
  double edges_ggf25[37]={500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000,
                          1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1600,1700,1800,2000,2500,2900};  
  double edges_vbf25[27]={400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775, 800, 
                          850, 900, 950, 1000,1100,1200,1400,1600,1800,2100};
  plot ZMT_ggFplot(*fillZMT<RA2bTree>,"ZMT_ggF_"+selection_label,"MT [GeV]",21,edges_ggf); 
  plot ZMT_vbFplot(*fillZMT<RA2bTree>,"ZMT_VBF_"+selection_label,"MT [GeV]",15,edges_vbf); 
  plot ZMT_ggF50plot(*fillZMT<RA2bTree>,"ZMT_ggF50_"+selection_label,"MT [GeV]",38,edges_ggf50); 
  plot ZMT_vbF50plot(*fillZMT<RA2bTree>,"ZMT_VBF50_"+selection_label,"MT [GeV]",28,edges_vbf50); 
  plot ZMT_ggF25plot(*fillZMT<RA2bTree>,"ZMT_ggF25_"+selection_label,"MT [GeV]",36,edges_ggf25); 
  plot ZMT_vbF25plot(*fillZMT<RA2bTree>,"ZMT_VBF25_"+selection_label,"MT [GeV]",26,edges_vbf25); 

  plot J1pt_Pt1plot(*fillLeadingJetPt<RA2bTree>,"AK8L1J_Pt1_"+selection_label,"AK8 J1 p_{T} [GeV]",28,200.,1600.); //50 GeV bin;
  plot J1pt_Phiplot(*fillLeadingJetPhi<RA2bTree>,"J1pt_Phi_"+selection_label,"AK8 J1 #Phi",40,-3.1415,3.1415); //0.1 bin;
  plot J1pt_Eta1plot(*fillLeadingJetEta<RA2bTree>,"J1pt_Eta1_"+selection_label,"AK8J1 #eta",60,-3.,3.); //0.1 bin;
  plot J1pt_Tau21plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau21_"+selection_label,"AK8 J1 #tau_{21}",20,0.,1.); //0.05  

  vector<plot> plots;
  //plots.push_back(HEMFracplot);

  plots.push_back(NVtxplot);
  plots.push_back(MET1plot);
  plots.push_back(HTplot);
  plots.push_back(NJetsplot);
  plots.push_back(NAK8Jets1plot); 
  plots.push_back(madHT);

  plots.push_back(J1_SDMassplot);

  plots.push_back(ZMTplot);
  plots.push_back(ZMT1plot);
  plots.push_back(ZMT2plot);
  plots.push_back(ZMT3plot);
  plots.push_back(ZMT31plot);
  plots.push_back(ZMT311plot);
  plots.push_back(ZMT312plot);
  plots.push_back(ZMT313plot);
  plots.push_back(ZMT4plot); 
  plots.push_back(ZMT41plot); 
  plots.push_back(ZMT5plot); 
  plots.push_back(ZMT6plot); 
  plots.push_back(ZMT7plot); 
    
  plots.push_back(ZMT_ggFplot);  
  plots.push_back(ZMT_vbFplot);  
  plots.push_back(ZMT_ggF50plot);  
  plots.push_back(ZMT_vbF50plot);  
  plots.push_back(ZMT_ggF25plot);  
  plots.push_back(ZMT_vbF25plot);  

  plots.push_back(J1pt_Pt1plot);
  plots.push_back(J1pt_Phiplot);
  plots.push_back(J1pt_Eta1plot);
  plots.push_back(J1pt_Tau21plot);  

  // background MC samples
  for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
    RA2bTree* ntuple = skims.ntuples[iSample];
     isMC_ = true;
    //TFile* outputFile = new TFile("AN_v0_Sep08/plotObs_"+selection_label+"_baseline_"+skims.sampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_v0_Closure_VBF_trigwt/plotObs_"+selection_label+"_baseline_"+skims.sampleName[iSample]+".root","RECREATE");
    
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
    }
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    double weight = 0.;
    double trigwt = 0.;    

    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(0,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
        filename = ntuple->fChain->GetFile()->GetName();
        if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;
    

        // HEM Veto
        if(! selectionFunc(ntuple) ) continue;
        if (filename.Contains("MC2018")){
            if ( ntuple->EvtNum % 1000 < 1000*21.0/59.6) continue;
            if(! passHEMjetVeto(ntuple, 30) ) continue;
        }
        
        trigwt = (TMath::Erf((ntuple->MET - p0) / p1) + 1) / 2. * p2;

        // Prefiring wt for 2016 & 2017 only
        if (filename.Contains("MC2016") || filename.Contains("MC2017")){
            weight = ntuple->Weight*lum*ntuple->NonPrefiringProb*trigwt;   //weight = ntuple->Weight*lumii*customPUweights(ntuple);
            //weight = ntuple->Weight*lumi*ntuple->NonPrefiringProb;   //weight = ntuple->Weight*lumii*customPUweights(ntuple);
        }
        //else weight = ntuple->Weight*lumi;
        else weight = ntuple->Weight*lum*trigwt;
      // ------------ end weights -------------

      //cout << "event passed all selections" << endl;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
	        plots[iPlot].fill(ntuple,weight);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    outputFile->Close();
 }// end loop over samples
    
  // Signal samples
  vector<RA2bTree*> sigSamples;
  for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
    RA2bTree* ntuple = skims.signalNtuples[iSample];
    isMC_ = true;
    TFile* outputFile = new TFile("AN_v0_Closure_VBF_trigwt/plotObs_"+selection_label+"_baseline_"+skims.signalSampleName[iSample]+".root","RECREATE");

    sigSamples.push_back(ntuple);
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);

    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(0,numEvents) ; iEvt++ ){
      ntuple->GetEntry(iEvt);
      if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;

      if(! selectionFunc(ntuple) ) continue;

      // HEM Veto  
      if(year=="2018"){  
        //cout<<"evtnum1: "<<ntuple->EvtNum<<endl;
        if ((ntuple->EvtNum % 1000) < (1000*21.0/59.6)) continue;
        //cout<<"evtnum2: "<<ntuple->EvtNum<<endl;
        if(!passHEMjetVeto(ntuple,30)) continue;  
      }          

      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        TString sig_sample = skims.signalSampleName[iSample];    

        // based on 2018 samples for VBF
	    if ((sig_sample=="VBFG_800") || (sig_sample=="VBFWp_800") || (sig_sample=="VBFRad_800")) 
	        //plots[iPlot].fillSignal(ntuple,lumi*1*2e-05); 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_1000") || (sig_sample=="VBFWp_1000") || (sig_sample=="VBFRad_1000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); // wt for 48300 evts: 1pb/#evts
	        // plots[iPlot].fillSignal(ntuple,lum*1*0.0000207); //for VBFG 2016 for 48300 evts: 1pb/#evts
	    if ((sig_sample=="VBFG_1200") || (sig_sample=="VBFWp_1200") || (sig_sample=="VBFRad_1200")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_1400") || (sig_sample=="VBFWp_1400") || (sig_sample=="VBFRad_1400")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_1600") || (sig_sample=="VBFWp_1600") || (sig_sample=="VBFRad_1600")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_1800") || (sig_sample=="VBFWp_1800") || (sig_sample=="VBFRad_1800")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_2000") || (sig_sample=="VBFWp_2000") || (sig_sample=="VBFRad_2000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_2500") || (sig_sample=="VBFWp_2500") || (sig_sample=="VBFRad_2500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_3000") || (sig_sample=="VBFWp_3000") || (sig_sample=="VBFRad_3000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_3500") || (sig_sample=="VBFWp_3500") || (sig_sample=="VBFRad_3500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_4000") || (sig_sample=="VBFWp_4000") || (sig_sample=="VBFRad_4000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_4500") || (sig_sample=="VBFWp_4500") || (sig_sample=="VBFRad_4500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_5000") || (sig_sample=="VBFWp_5000") || (sig_sample=="VBFRad_5000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_5500") || (sig_sample=="VBFRad_5500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if (sig_sample=="VBFWp_5500") 
	        plots[iPlot].fillSignal(ntuple,lum*1*2.08333e-05); 
	    if ((sig_sample=="VBFG_6000") || (sig_sample=="VBFWp_6000") || (sig_sample=="VBFRad_6000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_6500") || (sig_sample=="VBFWp_6500") || (sig_sample=="VBFRad_6500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="VBFG_7000") || (sig_sample=="VBFWp_7000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if (sig_sample=="VBFRad_7000") 
	        plots[iPlot].fillSignal(ntuple,lum*1*2.08333e-05); 
	    if ((sig_sample=="VBFG_7500") || (sig_sample=="VBFWp_7500") || (sig_sample=="VBFRad_7500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if (sig_sample=="VBFG_8000") 
	        plots[iPlot].fillSignal(ntuple,lum*1*2.222222e-05); 
	    if ((sig_sample=="VBFWp_8000") || (sig_sample=="VBFRad_8000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 

        // based on 2017 samples for ggF
	    if ((sig_sample=="ggFG_800") || (sig_sample=="ggFWp_800") || (sig_sample=="ggFRad_800")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_1000") || (sig_sample=="ggFWp_1000") || (sig_sample=="ggFRad_1000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); // wt for 48300 evts: 1pb/#evts
	    if ((sig_sample=="ggFG_1200") || (sig_sample=="ggFWp_1200") || (sig_sample=="ggFRad_1200")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_1400") || (sig_sample=="ggFWp_1400") || (sig_sample=="ggFRad_1400")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_1600") || (sig_sample=="ggFWp_1600") || (sig_sample=="ggFRad_1600")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_1800") || (sig_sample=="ggFWp_1800") || (sig_sample=="ggFRad_1800")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_2000") || (sig_sample=="ggFWp_2000") || (sig_sample=="ggFRad_2000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_2500") || (sig_sample=="ggFWp_2500") || (sig_sample=="ggFRad_2500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_3000") || (sig_sample=="ggFWp_3000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if (sig_sample=="ggFRad_3000") 
	        plots[iPlot].fillSignal(ntuple,lum*1*2.325581395348837e-05); 
	    if ((sig_sample=="ggFG_3500") || (sig_sample=="ggFWp_3500") || (sig_sample=="ggFRad_3500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_4000") || (sig_sample=="ggFWp_4000") || (sig_sample=="ggFRad_4000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_4500") || (sig_sample=="ggFWp_4500") || (sig_sample=="ggFRad_4500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_5000") || (sig_sample=="ggFWp_5000") || (sig_sample=="ggFRad_5000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_5500") || (sig_sample=="ggFWp_5500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if (sig_sample=="ggFRad_5500") 
	        plots[iPlot].fillSignal(ntuple,lum*1*2.08333e-05); 
	    if ((sig_sample=="ggFG_6000") || (sig_sample=="ggFWp_6000") || (sig_sample=="ggFRad_6000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_6500") || (sig_sample=="ggFWp_6500") || (sig_sample=="ggFRad_6500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_7000") || (sig_sample=="ggFWp_7000") || (sig_sample=="ggFRad_7000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if ((sig_sample=="ggFG_7500") || (sig_sample=="ggFWp_7500")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
	    if (sig_sample=="ggFRad_7500") 
	        plots[iPlot].fillSignal(ntuple,lum*1*2.0408163265306123e-05); 
	    if ((sig_sample=="ggFG_8000") || (sig_sample=="ggFWp_8000") || (sig_sample=="ggFRad_8000")) 
	        plots[iPlot].fillSignal(ntuple,lum*1*2e-05); 
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    
    outputFile->Close();
  }// end loop over samples


  // Data samples
  for( int iSample = 0 ; iSample < skims.dataNtuple.size() ; iSample++){
    RA2bTree* ntuple = skims.dataNtuple[iSample];
    TFile* outputFile = new TFile("AN_v0_Closure_VBF_trigwt/plotObs_"+selection_label+"_baseline_"+skims.dataSampleName[iSample]+".root","RECREATE");
	TString filename;  
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
        //HEM Veto
        filename = ntuple->fChain->GetFile()->GetName();
        if(filename.Contains("MET_2018")){
            if(!passHEMjetVeto(ntuple,30)) continue;
        }
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
