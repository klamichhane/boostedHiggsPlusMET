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
#include "Sig_Samples_XsecWt.cc"
#include "plotterUtils.cc"
//#include "skimSamples_2016.cc"
#include "definitions.h"
#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"
#include "btag/BTagCorrector.h"

//string year = "2016"; 
double lum = 0.0;
double p0, p1, p2;

using namespace std;

int MAX_EVENTS = 99999999;
void process(string selection_label,
	     string backgroundSample,
	     string signalSample,
	     string dataSample){
    
    if(year=="2016") {lum=35815.165;} 
    if(year=="2017") {lum=41486.136;} 
    if(year=="2018") {lum=59546.381;} 
    cout<<"year: "<<year<<" lumi: "<<lum<<endl;

  // set up selectors
    bool (*selectionFunc)(RA2bTree*);
    if( selection_label == "Baseline"){
        selectionFunc = baselineCut;
    }else if( selection_label == "BaselineHP"){
        selectionFunc = baselineHPCut;
    }else if( selection_label == "ZSR"){
        selectionFunc = ZSRCut;
    }else if( selection_label == "ZSRHP"){
        selectionFunc = ZSRHPCut;
    }else if( selection_label == "ZSRHPVBF"){
        selectionFunc = ZSRHPVBFCut;
    }else if( selection_label == "ZSRHPVBFfail"){
        selectionFunc = ZSRHPVBFfailCut;
    }else if( selection_label == "ZSRLP"){
        selectionFunc = ZSRLPCut;
    }else if( selection_label == "ZSRLPVBF"){
        selectionFunc = ZSRLPVBFCut;
    }else if( selection_label == "ZSRLPVBFfail"){
        selectionFunc = ZSRLPVBFfailCut;
    }else if( selection_label == "ZSRFP"){
        selectionFunc = ZSRFPCut;
    }else if( selection_label == "ZSRFPVBF"){
        selectionFunc = ZSRFPVBFCut;
    }else if( selection_label == "ZSRFPVBFfail"){
        selectionFunc = ZSRFPVBFfailCut;
    }else if( selection_label == "ZSRHPLooseVBF"){
        selectionFunc = ZSRHPLooseVBFCut;
    }else if( selection_label == "ZSRHPLooseVBFfail" ){
        selectionFunc = ZSRHPLooseVBFfailCut;
    }else if( selection_label == "ZSRFPLooseVBF" ){
        selectionFunc = ZSRFPLooseVBFCut;
    }else if( selection_label == "ZSRFPLooseVBFfail" ){
        selectionFunc = ZSRFPLooseVBFfailCut;
    }else if( selection_label == "ZSB" ){
        selectionFunc = ZSBCut;
    }else if( selection_label == "ZSBHP"){
        selectionFunc = ZSBHPCut;
    }else if( selection_label == "ZSBHPVBF"){
        selectionFunc = ZSBHPVBFCut;
    }else if( selection_label == "ZSBHPVBFfail"){
        selectionFunc = ZSBHPVBFfailCut;
    }else if( selection_label == "ZSBLP"){
        selectionFunc = ZSBLPCut;
    }else if( selection_label == "ZSBLPVBF"){
        selectionFunc = ZSBLPVBFCut;
    }else if( selection_label == "ZSBLPVBFfail"){
        selectionFunc = ZSBLPVBFfailCut;
    }else if( selection_label == "ZSBFP"){
        selectionFunc = ZSBFPCut;
    }else if( selection_label == "ZSBFPVBF"){
        selectionFunc = ZSBFPVBFCut;
    }else if( selection_label == "ZSBFPVBFfail"){
        selectionFunc = ZSBFPVBFfailCut;
    }else if( selection_label == "ZSBHPLooseVBF"){
        selectionFunc = ZSBHPLooseVBFCut;
    }else if( selection_label == "ZSBHPLooseVBFfail" ){
        selectionFunc = ZSBHPLooseVBFfailCut;
    }else if( selection_label == "ZSBFPLooseVBF" ){
        selectionFunc = ZSBFPLooseVBFCut;
    }else if( selection_label == "ZSBFPLooseVBFfail" ){
        selectionFunc = ZSBFPLooseVBFfailCut;

    }else if( selection_label == "ZAlphaSBHPVBF" ){
        selectionFunc = ZAlphaSBHPVBFCut;
    }else if( selection_label == "ZAlphaSRHPVBF" ){
        selectionFunc = ZAlphaSRHPVBFCut;
    }else if( selection_label == "ZAlphaSBHPVBFfail" ){
        selectionFunc = ZAlphaSBHPVBFfailCut;
    }else if( selection_label == "ZAlphaSRHPVBFfail" ){
        selectionFunc = ZAlphaSRHPVBFfailCut;

    }else if( selection_label == "ZAlphaSBLPVBF" ){
        selectionFunc = ZAlphaSBLPVBFCut;
    }else if( selection_label == "ZAlphaSRLPVBF" ){
        selectionFunc = ZAlphaSRLPVBFCut;
    }else if( selection_label == "ZAlphaSBLPVBFfail" ){
        selectionFunc = ZAlphaSBLPVBFfailCut;
    }else if( selection_label == "ZAlphaSRLPVBFfail" ){
        selectionFunc = ZAlphaSRLPVBFfailCut;

    }else if( selection_label == "ZAlphaSBFPVBF" ){
        selectionFunc = ZAlphaSBFPVBFCut;
    }else if( selection_label == "ZAlphaSRFPVBF" ){
        selectionFunc = ZAlphaSRFPVBFCut;
    }else if( selection_label == "ZAlphaSBFPVBFfail" ){
        selectionFunc = ZAlphaSBFPVBFfailCut;
    }else if( selection_label == "ZAlphaSRFPVBFfail" ){
        selectionFunc = ZAlphaSRFPVBFfailCut;

    }else if( selection_label == "ZAlphaSBHPLooseVBF" ){
        selectionFunc = ZAlphaSBHPLooseVBFCut;
    }else if( selection_label == "ZAlphaSRHPLooseVBF" ){
        selectionFunc = ZAlphaSRHPLooseVBFCut;
    }else if( selection_label == "ZAlphaSBHPLooseVBFfail" ){
        selectionFunc = ZAlphaSBHPLooseVBFfailCut;
    }else if( selection_label == "ZAlphaSRHPLooseVBFfail" ){
        selectionFunc = ZAlphaSRHPLooseVBFfailCut;
    }else if( selection_label == "NoSelection" ){
        selectionFunc = acceptanceCut;
    }else if( selection_label == "VBSBaseline" ){
        selectionFunc = VBSBaselineCut;
    }else if( selection_label == "VBSVBF" ){
        selectionFunc = VBSVBFCut;

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
  plot Oneplot(*fillOne<RA2bTree>,"One_"+selection_label,"Bkg_composition",1,0.5,1.5);//1 bin
  plot NVtxplot(*fillNVtx<RA2bTree>,"NVtx_"+selection_label,"NVtx",80,0.5,80.5);//1 bin
  plot NVtx1plot(*fillNVtx<RA2bTree>,"NVtx1_"+selection_label,"NVtx",50,0.5,50.5);//1 bin
  plot METplot(*fillMET<RA2bTree>,"MET_"+selection_label,"MET [GeV]",56,200.,3000.);//50 GeV bin
  plot MET1plot(*fillMET<RA2bTree>,"MET1_"+selection_label,"MET [GeV]",20,200.,1200.);//50 GeV bin
  plot MET2plot(*fillMET<RA2bTree>,"MET2_"+selection_label,"MET [GeV]",24,200.,800.);//25 GeV bin
  plot HTplot(*fillHT<RA2bTree>,"HT_"+selection_label,"H_{T} [GeV]",75,300,3300.); // 100 GeV bin

  //plot NgenZsplot(*getNumGenZs<RA2bTree>,"NgenZs_"+selection_label,"n_{genZs}",5,-0.5,4.5); // N genZs from tree
  //plot genZMTplot(*FillGenZMT<RA2bTree>,"genZMT_"+selection_label,"gen MT [GeV]",100,0.,5000.);
  plot NJetsplot(*fillNJets<RA2bTree>,"NJets_"+selection_label,"n_{jets}",10,0.5,10.5); // Nj from tree
  plot genZpTplot(*FillGenZPt<RA2bTree>,"genZpT_"+selection_label,"gen Z p_{T} [GeV]",100,0.,3000.);
  plot genWpTplot(*FillGenWPt<RA2bTree>,"genWpT_"+selection_label,"gen W p_{T} [GeV]",100,0.,3000.);
  plot genZEtaplot(*FillGenZEta<RA2bTree>,"genZEta_"+selection_label,"gen Z #eta ",100,-5.,5.);
  plot genWEtaplot(*FillGenWEta<RA2bTree>,"genWEta_"+selection_label,"gen W #eta ",100,-5.,5.);
  plot genWpMTplot(*FillGenWpMT<RA2bTree>,"genWpMT_"+selection_label,"gen MT [GeV]",100,0.,5000.);
  plot ZMTplot(*fillZMT<RA2bTree>,"ZMT_"+selection_label,"MT [GeV]",36,400.,4000.); // 100 GeV bin
  plot ZMT7plot(*fillZMT<RA2bTree>,"ZMT7_"+selection_label,"MT [GeV]",65,0.,6500.); // 100 GeV bin  
 
     // AK4 Jets plots: pt, eta, phi, Nemf
  plot AK4j1pt_plot(*fillJetPt1<RA2bTree>,"AK4j1pt_"+selection_label,"pt_{j1}^{AK4} [GeV]",40,0,1000);//25 GeV bin
  plot AK4j1pt1_plot(*fillJetPt1a<RA2bTree>,"AK4j1pt1_"+selection_label,"pt_{j1}^{AK4} [GeV]",40,0,1000);//25 GeV bin
  plot AK4j2pt_plot(*fillJetPt2<RA2bTree>,"AK4j2pt_"+selection_label,"pt_{j2}^{AK4} [GeV]",40,0,1000);
  plot AK4j3pt_plot(*fillJetPt3<RA2bTree>,"AK4j3pt_"+selection_label,"pt_{j3}^{AK4} [GeV]",40,0,1000);
  plot AK4j4pt_plot(*fillJetPt4<RA2bTree>,"AK4j4pt_"+selection_label,"pt_{j4}^{AK4} [GeV]",24,0,600);

  plot AK4j1Eta_plot(*fillJetEta1<RA2bTree>,"AK4j1Eta_"+selection_label,"#eta_{j1}^{AK4}",100,-5.,5.); // 0.1 bin
  plot AK4j1Eta1_plot(*fillJetEta1a<RA2bTree>,"AK4j1Eta1_"+selection_label,"#eta_{j1}^{AK4}",100,-5.,5.); // 0.1 bin
  plot AK4j2Eta_plot(*fillJetEta2<RA2bTree>,"AK4j2Eta_"+selection_label,"#eta_{j2}^{AK4}",100,-5.,5.);
  plot AK4j3Eta_plot(*fillJetEta3<RA2bTree>,"AK4j3Eta_"+selection_label,"#eta_{j3}^{AK4}",100,-5.,5.);
  plot AK4j4Eta_plot(*fillJetEta4<RA2bTree>,"AK4j4Eta_"+selection_label,"#eta_{j4}^{AK4}",100,-5.,5.);

  plot AK4j1Phi_plot(*fillJetPhi1<RA2bTree>,"AK4j1Phi_"+selection_label,"#phi_{j1}^{AK4}",40,-3.1415,3.1415);//0.1 bin
  plot AK4j1Phi1_plot(*fillJetPhi1a<RA2bTree>,"AK4j1Phi1_"+selection_label,"#phi_{j1}^{AK4}",40,-3.1415,3.1415);//0.1 bin
  plot AK4j2Phi_plot(*fillJetPhi2<RA2bTree>,"AK4j2Phi_"+selection_label,"#phi_{j2}^{AK4}",40,-3.1415,3.1415);
  plot AK4j3Phi_plot(*fillJetPhi3<RA2bTree>,"AK4j3Phi_"+selection_label,"#phi_{j3}^{AK4}",40,-3.1415,3.1415);
  plot AK4j4Phi_plot(*fillJetPhi4<RA2bTree>,"AK4j4Phi_"+selection_label,"#phi_{j4}^{AK4}",40,-3.1415,3.1415);

 // plot VBFgendR1vsdR2plot(*VBF_gendR1<RA2bTree>,*VBF_gendR2<RA2bTree>,"VBFgendR1vsdR2_"+selection_label,"dR(genj,j1^{VBF})","dR(genj,j2^{VBF})",10,0.,1.,10,0.,1.);
 // plot VBFgendR1vsdR21plot(*VBF_gendR1<RA2bTree>,*VBF_gendR2<RA2bTree>,"VBFgendR1vsdR21_"+selection_label,"dR(genj,j1^{VBF})","dR(genj,j2^{VBF})",100,0.,10.,100,0.,10.);
 // plot VBFgendR1plot(*VBF_gendR1<RA2bTree>,"VBFgendR1_"+selection_label,"dR(genj,j1^{VBF})",10,0.,1.);
 // plot VBFgendR11plot(*VBF_gendR1<RA2bTree>,"VBFgendR11_"+selection_label,"dR(genj,j1^{VBF})",100,0.,10.);
 // plot VBFgendR2plot(*VBF_gendR2<RA2bTree>,"VBFgendR2_"+selection_label,"dR(genj,j2^{VBF})",10,0.,1.);
 // plot VBFgendR21plot(*VBF_gendR2<RA2bTree>,"VBFgendR21_"+selection_label,"dR(genj,j2^{VBF})",100,0.,10.);

  plot VBFmjj_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj_"+selection_label,"m_{jj}^{VBF} [GeV]",40,0,4000);//100 GeV
  plot VBFmjj1_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj1_"+selection_label,"m_{jj}^{VBF} [GeV]",50,0,2500);//50 GeV
  plot VBFmjj2_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj2_"+selection_label,"m_{jj}^{VBF} [GeV]",20,0,2000);//25 GeV
  //plot VBFptjj_plot(*fillVBF_Ptjj<RA2bTree>,"VBFptjj_"+selection_label,"pt_{jj}^{VBF} [GeV]",40,0,2000);//50 GeV bin
  //plot VBFptjj1_plot(*fillVBF_Ptjj<RA2bTree>,"VBFptjj1_"+selection_label,"pt_{jj}^{VBF} [GeV]",30,0,600);//25 GeV
  plot VBFj1pt_plot(*fillVBF_j1Pt<RA2bTree>,"VBFj1pt_"+selection_label,"pt_{j1}^{VBF} [GeV]",40,0,1000);//25 GeV
  plot VBFj1pt1_plot(*fillVBF_j1Pt<RA2bTree>,"VBFj1pt1_"+selection_label,"pt_{j1}^{VBF} [GeV]",40,0,400);// 10 GeV bin
  plot VBFj2pt_plot(*fillVBF_j2Pt<RA2bTree>,"VBFj2pt_"+selection_label,"pt_{j2}^{VBF} [GeV]",40,0,1000);// 25 GeV
  plot VBFj2pt1_plot(*fillVBF_j2Pt<RA2bTree>,"VBFj2pt1_"+selection_label,"pt_{j2}^{VBF} [GeV]",30,0,300);// 10 GeV bin
  plot VBFdEta_plot(*fillVBF_dEta<RA2bTree>,"VBFdEta_"+selection_label,"#Delta#eta^{VBF}",90,0,9); //0.1 from 0.2
  plot VBFdEta1_plot(*fillVBF_dEta<RA2bTree>,"VBFdEta1_"+selection_label,"#Delta#eta^{VBF}",45,0,9); //0.2 from 0.2
  plot VBFdPhi_plot(*fillVBF_dPhi<RA2bTree>,"VBFdPhi_"+selection_label,"#Delta#Phi VBF(j1,j2)",20,0,3.1415);
  plot VBFj1Eta_plot(*fillVBF_j1Eta<RA2bTree>,"VBFj1Eta_"+selection_label,"#eta_{j1}^{VBF}",50,-5.,5.);
  plot VBFj1Eta1_plot(*fillVBF_j1Eta<RA2bTree>,"VBFj1Eta1_"+selection_label,"#eta_{j1}^{VBF}",100,-5.,5.);
  plot VBFj1Eta2_plot(*fillVBF_j1Eta<RA2bTree>,"VBFj1Eta2_"+selection_label,"#eta_{j1}^{VBF}",25,-5.,5.);
  plot VBFj2Eta_plot(*fillVBF_j2Eta<RA2bTree>,"VBFj2Eta_"+selection_label,"#eta_{j2}^{VBF}",50,-5.,5.);
  plot VBFj2Eta1_plot(*fillVBF_j2Eta<RA2bTree>,"VBFj2Eta1_"+selection_label,"#eta_{j2}^{VBF}",100,-5.,5.);
  plot VBFj2Eta2_plot(*fillVBF_j2Eta<RA2bTree>,"VBFj2Eta2_"+selection_label,"#eta_{j2}^{VBF}",25,-5.,5.);
  plot VBFj1Phi_plot(*fillVBF_j1Phi<RA2bTree>,"VBFj1Phi_"+selection_label,"#Phi_{j1}^{VBF}",40,-3.1415,3.1415);
  plot VBFj2Phi_plot(*fillVBF_j2Phi<RA2bTree>,"VBFj2Phi_"+selection_label,"#Phi_{j2}^{VBF}",40,-3.1415,3.1415);
  plot VBFj1j2Eta_plot(*fillVBF_j1j2Eta<RA2bTree>,"VBFj1j2Eta_"+selection_label,"#eta_{j1.j2}^{VBF}",100,-25,25);// 0.5
  plot VBFj1j2Eta1_plot(*fillVBF_j1j2Eta<RA2bTree>,"VBFj1j2Eta1_"+selection_label,"#eta_{j1.j2}^{VBF}",50,-25,25);// 0.5


  vector<plot> plots;
  //plots.push_back(HEMFracplot);

  plots.push_back(Oneplot);
  plots.push_back(NVtxplot);
  plots.push_back(NVtx1plot);
  plots.push_back(METplot);
  plots.push_back(MET1plot);
  plots.push_back(MET2plot);
  plots.push_back(HTplot);

  plots.push_back(NJetsplot);
  plots.push_back(genZpTplot);
  plots.push_back(genWpTplot);
  plots.push_back(genZEtaplot);
  plots.push_back(genWEtaplot);
  plots.push_back(genWpMTplot);
  plots.push_back(ZMTplot);
  plots.push_back(ZMT7plot);

  plots.push_back(AK4j1pt_plot);
  plots.push_back(AK4j1pt1_plot);
  plots.push_back(AK4j2pt_plot);
  plots.push_back(AK4j3pt_plot);
  plots.push_back(AK4j4pt_plot);

  plots.push_back(AK4j1Eta_plot);
  plots.push_back(AK4j1Eta1_plot);
  plots.push_back(AK4j2Eta_plot);
  plots.push_back(AK4j3Eta_plot);
  plots.push_back(AK4j4Eta_plot);

  plots.push_back(AK4j1Phi_plot);
  plots.push_back(AK4j1Phi1_plot);
  plots.push_back(AK4j2Phi_plot);
  plots.push_back(AK4j3Phi_plot);
  plots.push_back(AK4j4Phi_plot);  

  //plots.push_back(VBFgendR1vsdR2plot);
  //plots.push_back(VBFgendR1vsdR21plot);
  //plots.push_back(VBFgendR1plot);
  //plots.push_back(VBFgendR11plot);
  //plots.push_back(VBFgendR2plot);
  //plots.push_back(VBFgendR21plot);
  
  plots.push_back(VBFmjj_plot);
  plots.push_back(VBFmjj1_plot);
  plots.push_back(VBFmjj2_plot);
  //plots.push_back(VBFptjj_plot);
  //plots.push_back(VBFptjj1_plot);
  plots.push_back(VBFj1pt_plot);
  plots.push_back(VBFj1pt1_plot);
  plots.push_back(VBFj2pt_plot);
  plots.push_back(VBFj2pt1_plot);
  plots.push_back(VBFdEta_plot);
  plots.push_back(VBFdEta1_plot);
  plots.push_back(VBFdPhi_plot);
  plots.push_back(VBFj1Eta_plot);
  plots.push_back(VBFj1Eta1_plot);
  plots.push_back(VBFj1Eta2_plot);
  plots.push_back(VBFj2Eta_plot);
  plots.push_back(VBFj2Eta1_plot);
  plots.push_back(VBFj2Eta2_plot);
  plots.push_back(VBFj1Phi_plot);
  plots.push_back(VBFj2Phi_plot);
  plots.push_back(VBFj1j2Eta_plot);
  plots.push_back(VBFj1j2Eta1_plot);


  // background MC samples
  for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
    RA2bTree* ntuple = skims.ntuples[iSample];
     isMC_ = true;
    //TFile* outputFile = new TFile("AN_ORv1_files/"+year+"_ORv1/plotObs_"+selection_label+"_"+skims.sampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_ORv1_files/Systematics_LP/"+year+"/plotObs_"+selection_label+"_"+skims.sampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_Unblind_v1_files/"+year+"_UB_v1/plotObs_"+selection_label+"_"+skims.sampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_ARC_v1_files/"+year+"_ARC_v1/plotObs_"+selection_label+"_"+skims.sampleName[iSample]+".root","RECREATE");
    
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
    }
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    //TString bkg_sample = skims.sampleName[iSample];    

    double weight = 0.;
/*    BTagCorrector btagcorr; // for btag scale factor systematics.    
    TFile *currFile;
    double  deepCSVvalue = 0.0;

    currFile = ntuple->fChain->GetFile();
        //btagcorr.SetBtagSFunc(1); // for up variation; turn this on in addition to SetEffs(currFile) line.
        //btagcorr.SetMistagSFunc(1); // for Mistag up variation
    btagcorr.SetEffs(currFile);
    if(year == "2016") {
        btagcorr.SetCalib("btag/DeepCSV_Moriond17_B_H_mod.csv");
        deepCSVvalue = 0.6321;
    }
	if(year == "2017"){
        btagcorr.SetCalib("btag/DeepCSV_94XSF_V3_B_F_mod.csv");
        deepCSVvalue = 0.4941;
    }
	if(year == "2018"){
        btagcorr.SetCalib("btag/DeepCSV_102XSF_V1_mod.csv");
        deepCSVvalue = 0.4184;
    }
*/
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(100,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
        filename = ntuple->fChain->GetFile()->GetName();
        if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;
    
        //std::cout<<filename<<std::endl;

        // HEM Veto
        if(! selectionFunc(ntuple) ) continue;
        if (filename.Contains("MC2018")){
            if((ntuple->EvtNum % 1000 > 1000*21.0/59.6) && (! passHEMjetVeto(ntuple, 30)))continue;
        }
        // to avoid the peak at MT with Wjets 200-400 for 2018
        if (filename.Contains("WJetsToLNu_HT-200to400_MC2018") && selection_label == "ZSRHPVBF"){
            std::cout<<"Remember, there is a hack in 2018 Wjets 200-400 sample; removing the one spike at high MT tail."<<std::endl;
            if(fillZMT(ntuple) > 1900.)continue;
        }

        weight = ntuple->Weight * lum * customTrigWeights(ntuple) * customPUweights(ntuple);
        // scaling to 137/fb and correcting the BR for the VBS WZ sample.
        weight *= (137.0/35.8) * 4.08; // scaling to 137/fb and correcting the BR for the VBS WZ sample.
        
        // tau21 sf
        double tau21 = 1.0; 
        //if (purity == "HP"){tau21 = tau21HPScaleFactor(ntuple);} 
        //else if (purity == "LP"){tau21 = tau21LPScaleFactor(ntuple);} 
        //else tau21 = 1.0;

        if ((selection_label == "ZSBHP") || (selection_label == "ZSBHPVBF") || (selection_label == "ZSBHPVBFfail") || (selection_label == "ZSRHP") || (selection_label == "ZSRHPVBF") || (selection_label == "ZSRHPVBFfail")) {tau21 = tau21HPScaleFactor(ntuple);}
        else if ((selection_label == "ZSBLP") || (selection_label == "ZSBLPVBF") || (selection_label == "ZSBLPVBFfail") || (selection_label == "ZSRLP") || (selection_label == "ZSRLPVBF") || (selection_label == "ZSRLPVBFfail")) {tau21 = tau21LPScaleFactor(ntuple);}
        else tau21 = 1.0;

        if ( ! ( filename.Contains("_ZJetsTo")  || filename.Contains("_WJetsTo")) ){ weight *= tau21; }

        // tau21 pt Extrapolation systematics:
         /*   double tauwt = customTau21pTExtrapUp(ntuple);
              double tauwt = customTau21pTExtrapDown(ntuple);
              weight *= tauwt; // with tau21 pT Extrapolation */

        // Prefiring wt for 2016 & 2017 only
        if (filename.Contains("MC2016") || filename.Contains("MC2017")){
            weight *= ntuple->NonPrefiringProb; 
        }
        
        //NLO wt for WJets and ZJets Sample, 2017 & 2018 from BU group.
        if ( (year=="2016") && filename.Contains("_ZJetsTo")){        
             //weight *= ZJetsNLOWeights(ntuple);
             weight *= ZJetsNLOWeightsEwk16(ntuple); //Ewk in 2016 is QCD+Ewk
        }
        if ( (year=="2016") && filename.Contains("_WJetsTo")){        
             //weight *= WJetsNLOWeights(ntuple);
             weight *= WJetsNLOWeightsEwk16(ntuple);
        }
        if ( (year=="2017" || year=="2018") && filename.Contains("_ZJetsTo")){        
             weight *= ZJetsNLOWeightsQCD1718(ntuple);
             weight *= ZJetsNLOWeightsEwk1718(ntuple);
        }
        if ( (year=="2017" || year == "2018") && filename.Contains("_WJetsTo")){        
             weight *= WJetsNLOWeightsQCD1718(ntuple);
             weight *= WJetsNLOWeightsEwk1718(ntuple);
        }
      // ------------ b-tag sf weights -------------
     /*   double corrbtag = 1.0;
        corrbtag = btagcorr.GetSimpleCorrection(ntuple->Jets,ntuple->Jets_hadronFlavor,ntuple->Jets_HTMask,ntuple->Jets_bJetTagDeepCSVBvsAll,deepCSVvalue);
        weight = weight * corrbtag;
     */   
      // ------------ end b-tag weights -------------
      // end of btag-sf for MC bkgs
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
    //TFile* outputFile = new TFile("AN_ORv1_files/"+year+"_ORv1/plotObs_"+selection_label+"_"+skims.signalSampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_ORv1_files/Systematics_LP/"+year+"/plotObs_"+selection_label+"_"+skims.signalSampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_Unblind_v1_files/"+year+"_UB_v1/plotObs_"+selection_label+"_"+skims.signalSampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_ARC_v1_files/"+year+"_ARC_v1/plotObs_"+selection_label+"_"+skims.signalSampleName[iSample]+".root","RECREATE");

    sigSamples.push_back(ntuple);
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    double weight = 0.;
    ///*
    BTagCorrector btagcorr; // for btag scale factor systematics.    
    TFile *currFile;
    double deepCSVvalue = 0.0;
        // Signal sample btag -sf stuffs....
    currFile = ntuple->fChain->GetFile();
        //btagcorr.SetBtagSFunc(1); // for up variation
        //btagcorr.SetMistagSFunc(1); // for Mistag up variation
    
    btagcorr.SetEffs(currFile);
    if(year == "2016") { 
        btagcorr.SetCalib("btag/DeepCSV_Moriond17_B_H_mod.csv");
        deepCSVvalue = 0.6321;
    }
    if(year == "2017"){
        btagcorr.SetCalib("btag/DeepCSV_94XSF_V3_B_F_mod.csv");
        deepCSVvalue = 0.4941;
    }
    if(year == "2018"){
        btagcorr.SetCalib("btag/DeepCSV_102XSF_V1_mod.csv");
        deepCSVvalue = 0.4184;
    }
        
    TFile *Evtprocfile = (TFile*)ntuple->fChain->GetFile();
    TH1F *hEvtProc = (TH1F*)Evtprocfile->Get("nEventProc");
    double EvtProcessed = hEvtProc->GetBinContent(1);
    delete Evtprocfile;
   //*/    

    filename = ntuple->fChain->GetFile()->GetName();
    TString sig_sample = skims.signalSampleName[iSample];    
    //double sigxsecwt;    
    //Sig_Xsec_wt(sig_sample, sigxsecwt);
    //std::cout<<"sig sample: "<< sig_sample<<" filename: "<<filename<<"       wt: "<<sigxsecwt<<endl;

    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(100,numEvents) ; iEvt++ ){
      ntuple->GetEntry(iEvt);

      if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
      
      if(! selectionFunc(ntuple) ) continue;

        //if (filename.Contains("VBFG") || filename.Contains("ggFG") || filename.Contains("VBFRad") || filename.Contains("ggFRad")) {if(!genZmatched(ntuple)) continue; }
        //if (filename.Contains("VBFWp") || filename.Contains("ggFWp")) {if(!genWpmatched(ntuple)) continue; }

      // HEM Veto  
      if(year=="2018"){ if((ntuple->EvtNum % 1000 > 1000*21.0/59.6) && (! passHEMjetVeto(ntuple, 30)))continue;}          

      double tau21 = 1.0; 
      //if (purity == "HP"){tau21 = tau21HPScaleFactor(ntuple);} 
      //if (purity == "LP"){tau21 = tau21LPScaleFactor(ntuple);} 
      if ((selection_label == "ZSBHP") || (selection_label == "ZSBHPVBF") || (selection_label == "ZSBHPVBFfail") || (selection_label == "ZSRHP") || (selection_label == "ZSRHPVBF") || (selection_label == "ZSRHPVBFfail")) {tau21 = tau21HPScaleFactor(ntuple);}
      else if ((selection_label == "ZSBLP") || (selection_label == "ZSBLPVBF") || (selection_label == "ZSBLPVBFfail") || (selection_label == "ZSRLP") || (selection_label == "ZSRLPVBF") || (selection_label == "ZSRLPVBFfail")) {tau21 = tau21LPScaleFactor(ntuple);}
      else tau21 = 1.0;
      //std::cout<<"tau21sf: "<<tau21<<endl; 
      //weight = lum * sigxsecwt * customTrigWeights(ntuple) * customPUweights(ntuple) * tau21ScaleFactor(ntuple); 
      weight = lum * (1/EvtProcessed) * customTrigWeights(ntuple) * customPUweights(ntuple) *  tau21; 
      //weight = lum * (1/double(numEvents)) * customPUweights(ntuple) *  tau21; 

        // tau21 pt Extrapolation systematics:
         /*   double tauwt = customTau21pTExtrapUp(ntuple);
              double tauwt = customTau21pTExtrapDown(ntuple);
              weight *= tauwt; // with tau21 pT Extrapolation  */

      //Pre-firing weights
      if (year=="2016" || year=="2017"){ weight *= ntuple->NonPrefiringProb;}
       //std::cout<<"wt2: "<<weight<<endl; 
        
        // Signal sample btag -sf stuffs....
        double corrbtag = 1.0;
        corrbtag = btagcorr.GetSimpleCorrection(ntuple->Jets,ntuple->Jets_hadronFlavor,ntuple->Jets_HTMask,ntuple->Jets_bJetTagDeepCSVBvsAll,deepCSVvalue);
        weight = weight * corrbtag;
      // end of btag-sf for MC bkgs

      if (year=="2016" && filename.Contains("ggFG")){ weight *= 0.279644;} // 2016 ggFG is excl. sample so applied BR to make it inclusive. 
      //if (year=="2016" && filename.Contains("ggFWp")){ weight *= 0.13482;} // 2016 ggFWp is excl. sample so applied BR to make it inclusive. 
      if (filename.Contains("ggFWp")){ weight *= 0.13482;} // 2016 ggFWp is excl. sample so applied BR to make it inclusive. 
       // W to had BR (67.41 +/- 0.27) % Z to had BR (69.911 +/- 0.056) %; to nunu (20.00 +/- 0.055) %       

      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        if (filename.Contains("VBF") || filename.Contains("ggF") ) plots[iPlot].fillSignal(ntuple,weight); 
        //if (filename.Contains("VBF") || filename.Contains("ggF") ) plots[iPlot].fillSignal(ntuple,1); 
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    
    outputFile->Close();
  }// end loop over samples


  // Data samples
  for( int iSample = 0 ; iSample < skims.dataNtuple.size() ; iSample++){
    isMC_ = false;
    RA2bTree* ntuple = skims.dataNtuple[iSample];
    //TFile* outputFile = new TFile("AN_ORv1_files/"+year+"_ORv1/plotObs_"+selection_label+"_"+skims.dataSampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_ORv1_files/Systematics_LP/"+year+"/plotObs_"+selection_label+"_"+skims.dataSampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_Unblind_v1_files/"+year+"_UB_v1/plotObs_"+selection_label+"_"+skims.dataSampleName[iSample]+".root","RECREATE");
    //TFile* outputFile = new TFile("AN_Unblind_v1_files/"+year+"_UB_v1/plotObs_"+selection_label+"_VBFdEta5p0"+skims.dataSampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_ARC_v1_files/"+year+"_ARC_v1/plotObs_"+selection_label+"_VBFdEta5p0"+skims.dataSampleName[iSample]+".root","RECREATE");
	TString filename;  
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,skims.dataSampleName[iSample]);
    }
    
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    cout << "data MET: " << numEvents << endl;
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(100,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        //cout<<"Run Num: "<<ntuple->RunNum<<endl;
        if( iEvt % 100000 == 0 ) cout << "data_MET: " << iEvt << "/" << min(MAX_EVENTS,numEvents) << endl;

        if(! selectionFunc(ntuple) ) continue;
        if( !signalTriggerCut(ntuple) ) continue;

        //HEM Veto
        filename = ntuple->fChain->GetFile()->GetName();
        if(filename.Contains("MET_2018")){if(!passHEMjetVeto(ntuple,30)) continue;}
      
        // print info for events with hight MT in HP VBF regions
       /* 
       if (fillZMT(ntuple) > 1000.0){ 
            cout<<" "<<endl;
            cout<<"{\"filename\": \""<<filename<<"\","<<endl;
            cout<<"\"year\": "<<year<<","<<endl;
            cout<<"\"Run\": "<<ntuple->RunNum<<", \"Evt\": "<<ntuple->EvtNum<<", \"LumiBlock\": "<<ntuple->LumiBlockNum<<","<<endl;
            cout<<"\"MT\": "<<fillZMT(ntuple)<<", \"MET\": "<<ntuple->MET<<", \"METPhi\": "<<ntuple->METPhi<<","<<endl; 
            cout<<"\"AK8J1Mass\": "<<AK8PUPPISoftdropCorrMass(ntuple)<<", \"AK8J1pT\": "<<fillLeadingJetPt(ntuple)<<", \"Eta\": "<<fillLeadingJetEta(ntuple)<<", \"AK8J1Phi\": "<<fillLeadingJetPhi(ntuple)<<","<<endl; 
            cout<<"\"AK8J1tau21\": "<<fillLeadingTau21(ntuple)<<", \"VBFfwdmjj\": "<<fillVBF_Mjj(ntuple)<<", \"VBFdEta\": "<<fillVBF_dEta(ntuple)<<","<<endl; 
            cout<<"\"VBFj1pt\": "<<fillVBF_j1Pt(ntuple)<<", \"VBFj1eta\": "<<fillVBF_j1Eta(ntuple)<<", \"VBFj1phi\": "<<fillVBF_j1Phi(ntuple)<<","<<endl; 
            cout<<"\"VBFj2pt\": "<<fillVBF_j2Pt(ntuple)<<", \"VBFj2eta\": "<<fillVBF_j2Eta(ntuple)<<", \"VBFj2phi\": "<<fillVBF_j2Phi(ntuple)<<","<<endl; 
            cout<<"}, "<<endl;
            cout<<" "<<endl;
       }
      */  
 
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
	        plots[iPlot].fillData(ntuple);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
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
