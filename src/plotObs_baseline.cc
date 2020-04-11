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

string year = "2017"; 
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
    if( selection_label == "Baseline"){
        selectionFunc = baselineCut;
    }else if( selection_label == "ZSR"){
        selectionFunc = ZSRCut;
    }else if( selection_label == "ZSRHP"){
        selectionFunc = ZSRHPCut;
    }else if( selection_label == "ZSRHPVBF"){
        selectionFunc = ZSRHPVBFCut;
    }else if( selection_label == "ZSRHPVBFfail"){
        selectionFunc = ZSRHPVBFfailCut;
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
  plot NJetsplot(*fillNJets<RA2bTree>,"NJets_"+selection_label,"n_{jets}",10,0.5,10.5); // Nj from tree
  plot NJets1plot(*fillNJets1<RA2bTree>,"NJets1_"+selection_label,"n_{jets}",10,0.5,10.5); // cent Nj(from tree) w/ pt > 30
  plot NJets2plot(*fillNJets2<RA2bTree>,"NJets2_"+selection_label,"n_{jets}",10,0.5,10.5); // jsize w/ pt>30
  plot NJets3plot(*fillCentralNJets<RA2bTree>,"NJetsCent_"+selection_label,"n_{jets}",10,0.5,10.5); // cent jsize w/ pt>30
  plot NAK8Jetsplot(*fillNAK8Jets<RA2bTree>,"NAK8Jets_"+selection_label,"nAK8_{jets}",10,0.5,10.5);
  plot NAK8Jets1plot(*fillNAK8Jets<RA2bTree>,"NAK8Jets1_"+selection_label,"nAK8_{jets}",4,0.5,4.5);
  plot NAK8Jets2plot(*fillCentralNAK8Jets<RA2bTree>,"NAK8JetsCent_"+selection_label,"nAK8_{jets}",4,0.5,4.5);
  plot madHT(*fillMadHT<RA2bTree>,"madHT_"+selection_label,"Madgraph HT",19,100,2000);  
  plot madHT1(*fillMadHT<RA2bTree>,"madHT1_"+selection_label,"Madgraph HT",120,100,3100);  
  plot MHTRatio(*fillMHTRatio<RA2bTree>,"MHT_HTRatio_"+selection_label,"MHT/HT",40,0,2);  
  plot MHTdPhivsHTRatioplot(*fillDeltaPhiMHT<RA2bTree>,*fillHTRatio<RA2bTree>,"HTRatiovsMHTdPhi_"+selection_label,"#Delta #phi(j1, MHT)","HT5/HT",35,0.,3.5,20,1.,3.);//0.1 bin
  plot MHTdPhi2vsHTRatioplot(*fillDeltaPhi2MHT<RA2bTree>,*fillHTRatio<RA2bTree>,"HTRatiovsMHTdPhi2_"+selection_label,"#Delta #phi(j2, MHT)","HT5/HT",35,0.,3.5,20,1.,3.);//0.1 bin
  plot MHTdPhi3vsHTRatioplot(*fillDeltaPhi3MHT<RA2bTree>,*fillHTRatio<RA2bTree>,"HTRatiovsMHTdPhi3_"+selection_label,"#Delta #phi(j3, MHT)","HT5/HT",35,0.,3.5,20,1.,3.);//0.1 bin
  plot MHTdPhi4vsHTRatioplot(*fillDeltaPhi4MHT<RA2bTree>,*fillHTRatio<RA2bTree>,"HTRatiovsMHTdPhi4_"+selection_label,"#Delta #phi(j4, MHT)","HT5/HT",35,0.,3.5,20,1.,3.);//0.1 bin
  plot METvsAK8Ptplot(*fillLeadingJetPt<RA2bTree>,*fillMET<RA2bTree>,"METvsAK8Pt_"+selection_label,"AK8 L1J p_{T} [GeV]","MET [GeV]",20,200.,1200.,20,200.,1200.);//50 GeV bin
  plot METvsAK4j1Ptplot(*fillJetPt1<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j1Pt_"+selection_label,"pt_{j1}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,0.,1000.);
  plot METvsAK4j2Ptplot(*fillJetPt2<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j2Pt_"+selection_label,"pt_{j2}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,0.,1000.);
  plot METvsAK4j3Ptplot(*fillJetPt3<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j3Pt_"+selection_label,"pt_{j3}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,0.,1000.);
  plot METvsAK4j4Ptplot(*fillJetPt4<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j4Pt_"+selection_label,"pt_{j4}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,0.,1000.);
 
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

  //plot AK4j1Phi_plot(*fillJetPhi1<RA2bTree>,"AK4j1Phi_"+selection_label,"#phi_{j1}^{AK4}","Events",40,-3.1415,3.1415);//0.1 bin
  plot AK4j1Phi_plot(*fillJetPhi1<RA2bTree>,"AK4j1Phi_"+selection_label,"#phi_{j1}^{AK4}",40,-3.1415,3.1415);//0.1 bin
  plot AK4j1Phi1_plot(*fillJetPhi1a<RA2bTree>,"AK4j1Phi1_"+selection_label,"#phi_{j1}^{AK4}",40,-3.1415,3.1415);//0.1 bin
  plot AK4j2Phi_plot(*fillJetPhi2<RA2bTree>,"AK4j2Phi_"+selection_label,"#phi_{j2}^{AK4}",40,-3.1415,3.1415);
  plot AK4j3Phi_plot(*fillJetPhi3<RA2bTree>,"AK4j3Phi_"+selection_label,"#phi_{j3}^{AK4}",40,-3.1415,3.1415);
  plot AK4j4Phi_plot(*fillJetPhi4<RA2bTree>,"AK4j4Phi_"+selection_label,"#phi_{j4}^{AK4}",40,-3.1415,3.1415);

  plot VBFj1NEMF_plot(*fillVBF_j1NEMF<RA2bTree>,"VBFj1NEMF_"+selection_label,"NEMF_{j1}^{VBF}",100,0.,1.); // 0.1
  plot VBFj2NEMF_plot(*fillVBF_j2NEMF<RA2bTree>,"VBFj2NEMF_"+selection_label,"NEMF_{j2}^{VBF}",100,0.,1.); // 0.1
  plot VBFj1NHEF_plot(*fillVBF_j1NHEF<RA2bTree>,"VBFj1NHEF_"+selection_label,"NHEF_{j1}^{VBF}",100,0.,1.); // 0.1
  plot VBFj2NHEF_plot(*fillVBF_j2NHEF<RA2bTree>,"VBFj2NHEF_"+selection_label,"NHEF_{j2}^{VBF}",100,0.,1.); // 0.1
  plot VBFj1CHEF_plot(*fillVBF_j1CHEF<RA2bTree>,"VBFj1CHEF_"+selection_label,"CHEF_{j1}^{VBF}",100,0.,1.); // 0.1
  plot VBFj2CHEF_plot(*fillVBF_j2CHEF<RA2bTree>,"VBFj2CHEF_"+selection_label,"CHEF_{j2}^{VBF}",100,0.,1.); // 0.1
  plot AK8j1NHEF_plot(*fillLeadingJetNHEF<RA2bTree>,"AK8j1NHEF_"+selection_label,"NHEF_{j1}^{AK8}",100,0.,1.); // 0.1
  plot AK8j1NEMF_plot(*fillLeadingJetNEMF<RA2bTree>,"AK8j1NEMF_"+selection_label,"NEMF_{j1}^{AK8}",100,0.,1.); // 0.1
  plot AK8j1CHEF_plot(*fillLeadingJetCHEF<RA2bTree>,"AK8j1CHEF_"+selection_label,"CHEF_{j1}^{AK8}",100,0.,1.); // 0.1
  plot AK4j1NEMF_plot(*fillJetNEMF1<RA2bTree>,"AK4j1NEMF_"+selection_label,"NEMF_{j1}^{AK4}",10,0.,1.); // 0.1
  plot AK4j1NEMF1_plot(*fillJetNEMF1a<RA2bTree>,"AK4j1NEMF1_"+selection_label,"NEMF_{j1}^{AK4}",10,0.,1.); // 0.1
  plot AK4j2NEMF_plot(*fillJetNEMF2<RA2bTree>,"AK4j2NEMF_"+selection_label,"NEMF_{j2}^{AK4}",10,0.,1.);
  plot AK4j3NEMF_plot(*fillJetNEMF3<RA2bTree>,"AK4j3NEMF_"+selection_label,"NEMF_{j3}^{AK4}",10,0.,1.);
  plot AK4j4NEMF_plot(*fillJetNEMF4<RA2bTree>,"AK4j4NEMF_"+selection_label,"NEMF_{j4}^{AK4}",10,0.,1.);

  plot AK4j1NHEF_plot(*fillJetNHEF1<RA2bTree>,"AK4j1NHEF_"+selection_label,"NHEF_{j1}^{AK4}",10,0.,1.); // 0.1
  plot AK4j1NHEF1_plot(*fillJetNHEF1a<RA2bTree>,"AK4j1NHEF1_"+selection_label,"NHEF_{j1}^{AK4}",10,0.,1.); // 0.1
  plot AK4j2NHEF_plot(*fillJetNHEF2<RA2bTree>,"AK4j2NHEF_"+selection_label,"NHEF_{j2}^{AK4}",10,0.,1.); // 0.1
  plot AK4j3NHEF_plot(*fillJetNHEF3<RA2bTree>,"AK4j3NHEF_"+selection_label,"NHEF_{j3}^{AK4}",10,0.,1.); // 0.1
  plot AK4j4NHEF_plot(*fillJetNHEF4<RA2bTree>,"AK4j4NHEF_"+selection_label,"NHEF_{j4}^{AK4}",10,0.,1.); // 0.1
    
  plot AK4j1CHEF_plot(*fillJetCHEF1<RA2bTree>,"AK4j1CHEF_"+selection_label,"CHEF_{j1}^{AK4}",10,0.,1.); // 0.1
  plot AK4j1CHEF1_plot(*fillJetCHEF1a<RA2bTree>,"AK4j1CHEF1_"+selection_label,"CHEF_{j1}^{AK4}",10,0.,1.); // 0.1
  plot AK4j2CHEF_plot(*fillJetCHEF2<RA2bTree>,"AK4j2CHEF_"+selection_label,"CHEF_{j2}^{AK4}",10,0.,1.); // 0.1
  plot AK4j3CHEF_plot(*fillJetCHEF3<RA2bTree>,"AK4j3CHEF_"+selection_label,"CHEF_{j3}^{AK4}",10,0.,1.); // 0.1
  plot AK4j4CHEF_plot(*fillJetCHEF4<RA2bTree>,"AK4j4CHEF_"+selection_label,"CHEF_{j4}^{AK4}",10,0.,1.); // 0.1

  plot AK4j1NHEFNEMF_plot(*fillJetNHEFNEMF1<RA2bTree>,"AK4j1NHEFNEMF_"+selection_label,"NHEFNEMF_{j1}^{AK4}",20,0.,2.); // 0.1
  plot AK4j2NHEFNEMF_plot(*fillJetNHEFNEMF2<RA2bTree>,"AK4j2NHEFNEMF_"+selection_label,"NHEFNEMF_{j2}^{AK4}",20,0.,2.); // 0.1
  plot AK4j3NHEFNEMF_plot(*fillJetNHEFNEMF3<RA2bTree>,"AK4j3NHEFNEMF_"+selection_label,"NHEFNEMF_{j3}^{AK4}",20,0.,2.); // 0.1
  plot AK4j4NHEFNEMF_plot(*fillJetNHEFNEMF4<RA2bTree>,"AK4j4NHEFNEMF_"+selection_label,"NHEFNEMF_{j4}^{AK4}",20,0.,2.); // 0.1

    // 2D plot for AK4 Objects:
   //plot AK4j1ptvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetPt1<RA2bTree>,"AK4j1ptvsEta_"+selection_label,"#eta_{j1}^{AK4}","pt_{j1}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j1ptvsEtaplot(*fillJetPt1<RA2bTree>,*fillJetEta1<RA2bTree>,"AK4j1EtavsPt_"+selection_label,"pt_{j1}^{AK4}","#eta_{j1}^{AK4} [GeV]",40,30.,1030.,100,-5.,5.);
  plot AK4j1PhivsEtaplot(*fillJetEta1<RA2bTree>,*fillJetPhi1<RA2bTree>,"AK4j1PhivsEta_"+selection_label,"#eta_{j1}^{AK4}","#phi_{j1}^{AK4}",100,-5.,5.,70,-3.5,3.5);
  plot AK4j1NEMFvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetNEMF1<RA2bTree>,"AK4j1NEMFvsEta_"+selection_label,"#eta_{j1}^{AK4}","NEMF_{j1}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j1NEMFvsPtplot(*fillJetPt1<RA2bTree>,*fillJetNEMF1<RA2bTree>,"AK4j1NEMFvsPt_"+selection_label,"pt_{j1}^{AK4} [GeV]","NEMF_{j1}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j1NHEFvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetNHEF1<RA2bTree>,"AK4j1NHEFvsEta_"+selection_label,"#eta_{j1}^{AK4}","NHEF_{j1}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j1NHEFvsPtplot(*fillJetPt1<RA2bTree>,*fillJetNHEF1<RA2bTree>,"AK4j1NHEFvsPt_"+selection_label,"pt_{j1}^{AK4} [GeV]","NHEF_{j1}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j1NHEFvsNEMFplot(*fillJetNEMF1<RA2bTree>,*fillJetNHEF1<RA2bTree>,"AK4j1NHEFvsNEMF_"+selection_label,"NEMF_{j1}^{AK4}","NHEF_{j1}^{AK4}",10,0.,1.,10,0.,1.);
  // j1 in eta 2.6 to 3.0
  plot AK4j1ptvsEta1plot(*fillJetPt1a<RA2bTree>,*fillJetEta1a<RA2bTree>,"AK4j1EtavsPt1_"+selection_label,"pt_{j1}^{AK4}","#eta_{j1}^{AK4} [GeV]",40,30.,1030.,100,-5.,5.);
  plot AK4j1PhivsEta1plot(*fillJetEta1a<RA2bTree>,*fillJetPhi1a<RA2bTree>,"AK4j1PhivsEta1_"+selection_label,"#eta_{j1}^{AK4}","#phi_{j1}^{AK4}",100,-5.,5.,70,-3.5,3.5);
  plot AK4j1NEMFvsEta1plot(*fillJetEta1a<RA2bTree>,*fillJetNEMF1a<RA2bTree>,"AK4j1NEMFvsEta1_"+selection_label,"#eta_{j1}^{AK4}","NEMF_{j1}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j1NEMFvsPt1plot(*fillJetPt1a<RA2bTree>,*fillJetNEMF1a<RA2bTree>,"AK4j1NEMFvsPt1_"+selection_label,"pt_{j1}^{AK4} [GeV]","NEMF_{j1}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j1NHEFvsEta1plot(*fillJetEta1a<RA2bTree>,*fillJetNHEF1a<RA2bTree>,"AK4j1NHEFvsEta1_"+selection_label,"#eta_{j1}^{AK4}","NHEF_{j1}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j1NHEFvsPt1plot(*fillJetPt1a<RA2bTree>,*fillJetNHEF1a<RA2bTree>,"AK4j1NHEFvsPt1_"+selection_label,"pt_{j1}^{AK4} [GeV]","NHEF_{j1}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j1NHEFvsNEMF1plot(*fillJetNEMF1a<RA2bTree>,*fillJetNHEF1a<RA2bTree>,"AK4j1NHEFvsNEMF1_"+selection_label,"NEMF_{j1}^{AK4}","NHEF_{j1}^{AK4}",10,0.,1.,10,0.,1.);
   //plot AK4j2ptvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetPt2<RA2bTree>,"AK4j2ptvsEta_"+selection_label,"#eta_{j2}^{AK4}","pt_{j2}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j2ptvsEtaplot(*fillJetPt2<RA2bTree>,*fillJetEta2<RA2bTree>,"AK4j2EtavsPt_"+selection_label,"pt_{j2}^{AK4}","#eta_{j2}^{AK4} [GeV]",40,30.,1030.,100,-5.,5.);
  plot AK4j2PhivsEtaplot(*fillJetEta2<RA2bTree>,*fillJetPhi2<RA2bTree>,"AK4j2PhivsEta_"+selection_label,"#eta_{j2}^{AK4}","#phi_{j2}^{AK4}",100,-5.,5.,70,-3.5,3.5);
  plot AK4j2NEMFvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetNEMF2<RA2bTree>,"AK4j2NEMFvsEta_"+selection_label,"#eta_{j2}^{AK4}","NEMF_{j2}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j2NEMFvsPtplot(*fillJetPt2<RA2bTree>,*fillJetNEMF2<RA2bTree>,"AK4j2NEMFvsPt_"+selection_label,"pt_{j2}^{AK4} [GeV]","NEMF_{j2}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j2NHEFvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetNHEF2<RA2bTree>,"AK4j2NHEFvsEta_"+selection_label,"#eta_{j2}^{AK4}","NHEF_{j2}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j2NHEFvsPtplot(*fillJetPt2<RA2bTree>,*fillJetNHEF2<RA2bTree>,"AK4j2NHEFvsPt_"+selection_label,"pt_{j2}^{AK4} [GeV]","NHEF_{j2}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j2NHEFvsNEMFplot(*fillJetNEMF2<RA2bTree>,*fillJetNHEF2<RA2bTree>,"AK4j2NHEFvsNEMF_"+selection_label,"NEMF_{j2}^{AK4}","NHEF_{j2}^{AK4}",10,0.,1.,10,0.,1.);

   //plot AK4j3ptvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetPt1<RA2bTree>,"AK4j1ptvsEta_"+selection_label,"#eta_{j1}^{AK4}","pt_{j1}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j3ptvsEtaplot(*fillJetPt3<RA2bTree>,*fillJetEta3<RA2bTree>,"AK4j3EtavsPt_"+selection_label,"pt_{j3}^{AK4}","#eta_{j3}^{AK4} [GeV]",40,30.,1030.,100,-5.,5.);
  plot AK4j3PhivsEtaplot(*fillJetEta3<RA2bTree>,*fillJetPhi3<RA2bTree>,"AK4j3PhivsEta_"+selection_label,"#eta_{j3}^{AK4}","#phi_{j3}^{AK4}",100,-5.,5.,70,-3.5,3.5);
  plot AK4j3NEMFvsEtaplot(*fillJetEta3<RA2bTree>,*fillJetNEMF3<RA2bTree>,"AK4j3NEMFvsEta_"+selection_label,"#eta_{j3}^{AK4}","NEMF_{j3}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j3NEMFvsPtplot(*fillJetPt3<RA2bTree>,*fillJetNEMF3<RA2bTree>,"AK4j3NEMFvsPt_"+selection_label,"pt_{j3}^{AK4} [GeV]","NEMF_{j3}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j3NHEFvsEtaplot(*fillJetEta3<RA2bTree>,*fillJetNHEF3<RA2bTree>,"AK4j3NHEFvsEta_"+selection_label,"#eta_{j3}^{AK4}","NHEF_{j3}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j3NHEFvsPtplot(*fillJetPt3<RA2bTree>,*fillJetNHEF3<RA2bTree>,"AK4j3NHEFvsPt_"+selection_label,"pt_{j3}^{AK4} [GeV]","NHEF_{j3}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j3NHEFvsNEMFplot(*fillJetNEMF3<RA2bTree>,*fillJetNHEF3<RA2bTree>,"AK4j3NHEFvsNEMF_"+selection_label,"NEMF_{j3}^{AK4}","NHEF_{j3}^{AK4}",10,0.,1.,10,0.,1.);

   //plot AK4j2ptvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetPt2<RA2bTree>,"AK4j2ptvsEta_"+selection_label,"#eta_{j2}^{AK4}","pt_{j2}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j4ptvsEtaplot(*fillJetPt4<RA2bTree>,*fillJetEta4<RA2bTree>,"AK4j4EtavsPt_"+selection_label,"pt_{j4}^{AK4}","#eta_{j4}^{AK4} [GeV]",40,30.,1030.,100,-5.,5.);
  plot AK4j4PhivsEtaplot(*fillJetEta4<RA2bTree>,*fillJetPhi4<RA2bTree>,"AK4j4PhivsEta_"+selection_label,"#eta_{j4}^{AK4}","#phi_{j4}^{AK4}",100,-5.,5.,70,-3.5,3.5);
  plot AK4j4NEMFvsEtaplot(*fillJetEta4<RA2bTree>,*fillJetNEMF4<RA2bTree>,"AK4j4NEMFvsEta_"+selection_label,"#eta_{j4}^{AK4}","NEMF_{j4}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j4NEMFvsPtplot(*fillJetPt4<RA2bTree>,*fillJetNEMF4<RA2bTree>,"AK4j4NEMFvsPt_"+selection_label,"pt_{j4}^{AK4} [GeV]","NEMF_{j4}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j4NHEFvsEtaplot(*fillJetEta4<RA2bTree>,*fillJetNHEF4<RA2bTree>,"AK4j4NHEFvsEta_"+selection_label,"#eta_{j4}^{AK4}","NHEF_{j4}^{AK4}",100,-5.,5.,10,0.,1.);
  plot AK4j4NHEFvsPtplot(*fillJetPt4<RA2bTree>,*fillJetNHEF4<RA2bTree>,"AK4j4NHEFvsPt_"+selection_label,"pt_{j4}^{AK4} [GeV]","NHEF_{j4}^{AK4}",40,30.,1030.,10,0.,1.);
  plot AK4j4NHEFvsNEMFplot(*fillJetNEMF4<RA2bTree>,*fillJetNHEF4<RA2bTree>,"AK4j4NHEFvsNEMF_"+selection_label,"NEMF_{j4}^{AK4}","NHEF_{j4}^{AK4}",10,0.,1.,10,0.,1.);

  plot METPhiplot(*fillMetPhi<RA2bTree>,"METPhi_"+selection_label,"MET #Phi",40,-3.1415,3.1415);
  plot METRatioplot(*fillPfCaloMetRatio<RA2bTree>,"METRatio_"+selection_label,"PfMET/Calo",20,0.,10.);//0.5
  //plot gendPhiplot(*dPhigenZinv<RA2bTree>,"dPhiGenMET_"+selection_label,"#Delta#Phi_{Z,MET}",20,0,3.1415);
  plot DeltaPhi1plot(*fillDeltaPhi1<RA2bTree>,"DeltaPhi1_"+selection_label,"#Delta#Phi_{1}",20,0,3.1415);
  plot DeltaPhi2plot(*fillDeltaPhi2<RA2bTree>,"DeltaPhi2_"+selection_label,"#Delta#Phi_{2}",20,0,3.1415);
  plot DeltaPhi3plot(*fillDeltaPhi3<RA2bTree>,"DeltaPhi3_"+selection_label,"#Delta#Phi_{3}",20,0,3.1415);
  plot DeltaPhi4plot(*fillDeltaPhi4<RA2bTree>,"DeltaPhi4_"+selection_label,"#Delta#Phi_{4}",20,0,3.1415);
  plot DeltaPhiAK8JMETplot(*fillDeltaPhiAK8JMET<RA2bTree>,"DeltaPhiAK8JMET_"+selection_label,"#Delta#Phi(AK8J1,MET)",20,0,3.1415);

  plot J1pt_Massplot(*fillLeadingJetMass<RA2bTree>,"J1pt_Mass_"+selection_label,"m_{J} [GeV]",54,30.,300.);//5 Gev bin
  plot J1_SDMassplot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]",54,30.,300.);//5 Gev bin
  plot J1_SDMass1plot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass1_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]",34,30.,200.);//5 Gev bin
  plot J1_SDMass2plot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass2_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]",8,65.,105.);//5 Gev bin
  plot J1_SDMass3plot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass3_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]",40,30,1030);//5 Gev bin
  plot J1_SDMass4plot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass4_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]",36,30,1830);//5 Gev bin
  // Turn on the line below for SR only
  plot BTagDeepCSVplot(*fillBTagsCSV<RA2bTree>,"BTagDeepCSV_"+selection_label,"BTag Deep CSV",20,0.,1.);//5 Gev bin
  plot J1pt_Mass1plot(*fillLeadingJetMass<RA2bTree>,"J1pt_Mass1_"+selection_label,"m_{J} [GeV]",14,50.,120.);//5 Gev bin
  plot J1pt_Tau21plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau21_"+selection_label,"AK8 J1 #tau_{21}",20,0.,1.); //0.05
  plot J1pt_Tau212plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau212_"+selection_label,"AK8 J1 #tau_{21}",1000,0.,1.); //0.04
  plot DDT_Tau21plot(*fillDDT<RA2bTree>,"DDT_Tau21_"+selection_label,"AK8 J1 DDT #tau_{21}",30,0.,1.2); //0.04
  plot Tau21vsJMassplot(*fillLeadingJetSDMass<RA2bTree>,*fillLeadingTau21<RA2bTree>,"Tau21vsJMass_"+selection_label,"AK8 J1 SoftDrop Mass [GeV]","AK8 J1 #tau_{21}",34,30.,200.,20,0.,1.);
  plot Tau21vsEtaplot(*fillLeadingJetEta<RA2bTree>,*fillLeadingTau21<RA2bTree>,"Tau21vsEta_"+selection_label,"AK8 J1 #eta ","AK8 J1 #tau_{21}",100,-5,5,20,0.,1.);
  plot Tau21vsNEMFplot(*fillLeadingJetNEMF<RA2bTree>,*fillLeadingTau21<RA2bTree>,"Tau21vsNEMF_"+selection_label,"AK8 J1 NEMF ","AK8 J1 #tau_{21}",100,0,1,20,0.,1.);
  plot Tau21vsCHEFplot(*fillLeadingJetCHEF<RA2bTree>,*fillLeadingTau21<RA2bTree>,"Tau21vsCHEF_"+selection_label,"AK8 J1 CHEF ","AK8 J1 #tau_{21}",100,0,1,20,0.,1.);

  plot GMassvsZMTplot(*fillGMass<RA2bTree>,*fillZMT<RA2bTree>,"GMassvsZMT_"+selection_label,"M [GeV]","MT [GeV]",25,500.,3000.,45,500.,5000.); // 100 GeV bin
  plot EtavsZMTplot(*fillZMT<RA2bTree>,*fillLeadingJetEta<RA2bTree>,"AK8EtavsZMT_"+selection_label,"MT [GeV]","AK8 J1 #eta",46,400.,5000.,60,-3.,3.); // 100 GeV bin
  plot GMassplot(*fillGMass<RA2bTree>,"GMass_"+selection_label,"M_{G} [GeV]",25,500.,3000.); // 100 GeV bin
  plot GMass1plot(*fillGMass<RA2bTree>,"GMass1_"+selection_label,"M_{G} [GeV]",70,0.,7000.); // 100 GeV bin
  plot GMass2plot(*fillGMass<RA2bTree>,"GMass2_"+selection_label,"M_{G} [GeV]",65,500.,7000.); // 100 GeV bin
  plot ZMTplot(*fillZMT<RA2bTree>,"ZMT_"+selection_label,"MT [GeV]",36,400.,4000.); // 100 GeV bin
  plot ZMT1plot(*fillZMT<RA2bTree>,"ZMT1_"+selection_label,"MT [GeV]",32,400.,2000.); //50 GeV bin
  plot ZMT3plot(*fillZMT<RA2bTree>,"ZMT3_"+selection_label,"MT [GeV]",52,400.,3000.); // 50 GeV bin
  plot ZMT31plot(*fillZMT<RA2bTree>,"ZMT31_"+selection_label,"MT [GeV]",23,400.,2700.); // 100 GeV bin ZSBFPVBF
  plot ZMT311plot(*fillZMT<RA2bTree>,"ZMT311_"+selection_label,"MT [GeV]",46,400.,2700.); // 50 GeV bin ZSBFPVBF
  plot ZMT312plot(*fillZMT<RA2bTree>,"ZMT312_"+selection_label,"MT [GeV]",92,400.,2700.); //25 GeV bin  ZSBFPVBF
  plot ZMT313plot(*fillZMT<RA2bTree>,"ZMT313_"+selection_label,"MT [GeV]",31,400.,3500.); // 100 GeV bin ZSBFPVBFfail
  plot ZMT314plot(*fillZMT<RA2bTree>,"ZMT314_"+selection_label,"MT [GeV]",62,400.,3500.); // 50 GeV bin ZSBFPVBFfail
  plot ZMT4plot(*fillZMT<RA2bTree>,"ZMT4_"+selection_label,"MT [GeV]",24,400.,1000.); // 25 GeV bin
  plot ZMT7plot(*fillZMT<RA2bTree>,"ZMT7_"+selection_label,"MT [GeV]",65,0.,6500.); // 100 GeV bin
  plot ZMT8plot(*fillZMT<RA2bTree>,"ZMT8_"+selection_label,"MT [GeV]",60,500.,6500.); // 100 GeV bin
  plot ZMT9plot(*fillZMT<RA2bTree>,"ZMT9_"+selection_label,"MT [GeV]",45,500.,5000.); // 100 GeV bin
  plot ZMT10plot(*fillZMT<RA2bTree>,"ZMT10_"+selection_label,"MT [GeV]",90,0.,9000.); // 100 GeV bin
  plot MTpTRatioplot(*fillMTpTRatio<RA2bTree>,"MTpTRatio_"+selection_label,"MT/pT",100,0.,3.); //0.04
  plot pTMTRatioplot(*fillpTMTRatio<RA2bTree>,"pTMTRatio_"+selection_label,"pT/MT",100,0.,1.); //0.04

  double edges_ggf[23]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2250,2400,2550,2700,2900};  
  double edges_vbf[16]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1850,2100};
  double edges_vbfhp137[20]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2250,2400};
  double edges_vbffailhp137[23]={400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2350,2550,2750,3000};
  double edges_ggf50[39]={400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2050,2100,2200,2400,2600,2900};  
  double edges_vbf50[29]={400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1850,2100};
  plot ZMT_ggFplot(*fillZMT<RA2bTree>,"ZMT_ggF_"+selection_label,"MT [GeV]",22,edges_ggf); 
  plot ZMT_vbFplot(*fillZMT<RA2bTree>,"ZMT_VBF_"+selection_label,"MT [GeV]",15,edges_vbf); 
  plot ZMT_vbFhpplot(*fillZMT<RA2bTree>,"ZMT_VBF137_"+selection_label,"MT [GeV]",19,edges_vbfhp137); 
  plot ZMT_vbFfailhpplot(*fillZMT<RA2bTree>,"ZMT_VBFfail137_"+selection_label,"MT [GeV]",22,edges_vbffailhp137); 
  plot ZMT_ggF50plot(*fillZMT<RA2bTree>,"ZMT_ggF50_"+selection_label,"MT [GeV]",38,edges_ggf50); 
  plot ZMT_vbF50plot(*fillZMT<RA2bTree>,"ZMT_VBF50_"+selection_label,"MT [GeV]",28,edges_vbf50); 

  plot J1pt_Ptplot(*fillLeadingJetPt<RA2bTree>,"AK8L1J_Pt_"+selection_label,"AK8 J1 p_{T} [GeV]",56,200.,3000.); //50 GeV bi n;
  plot J1pt_Pt1plot(*fillLeadingJetPt<RA2bTree>,"AK8L1J_Pt1_"+selection_label,"AK8 J1 p_{T} [GeV]",28,200.,1600.); //50 GeV bin;
  plot J1pt_Pt2plot(*fillLeadingJetPt<RA2bTree>,"AK8L1J_Pt2_"+selection_label,"AK8 J1 p_{T} [GeV]",24,200.,800.); //25 GeV bin;
  plot J1pt_Etaplot(*fillLeadingJetEta<RA2bTree>,"J1pt_Eta_"+selection_label,"AK8 J1 #eta",100,-5.,5.); //0.1 bin;
  plot J1pt_Phiplot(*fillLeadingJetPhi<RA2bTree>,"J1pt_Phi_"+selection_label,"AK8 J1 #Phi",40,-3.1415,3.1415); //0.1 bin;
  plot J1pt_Eta1plot(*fillLeadingJetEta<RA2bTree>,"J1pt_Eta1_"+selection_label,"AK8J1 #eta",60,-3.,3.); //0.1 bin;
  
  // for Boosted Deep AK8   
  plot DeepAK8_Wplot(*fillDeepAK8W<RA2bTree>,"DeepAK8_Wplot_"+selection_label,"Deep AK8 W",20,0.,1.); //0.05
  plot DeepAK8_W1plot(*fillDeepAK8W<RA2bTree>,"DeepAK8_W1plot_"+selection_label,"Deep AK8 W",200,0.,1.); //0.005
  plot DeepAK8_W2plot(*fillDeepAK8W<RA2bTree>,"DeepAK8_W2plot_"+selection_label,"Deep AK8 W",1000,0.,1.); //0.001
  plot DeepAK8_WDecorrelplot(*fillDeepAK8WDecorrel<RA2bTree>,"DeepAK8_WDecorrelplot_"+selection_label,"Deep AK8 W Decorrel",20,0.,1.); //0.04
  plot DeepAK8_Zplot(*fillDeepAK8Z<RA2bTree>,"DeepAK8_Zplot_"+selection_label,"Deep AK8 Z",20,0.,1.); //0.05
  plot DeepAK8_Z1plot(*fillDeepAK8Z<RA2bTree>,"DeepAK8_Z1plot_"+selection_label,"Deep AK8 Z",200,0.,1.); //0.005
  plot DeepAK8_Z2plot(*fillDeepAK8Z<RA2bTree>,"DeepAK8_Z2plot_"+selection_label,"Deep AK8 Z",1000,0.,1.); //0.001
  plot DeepAK8_ZhDecorrelplot(*fillDeepAK8ZDecorrel<RA2bTree>,"DeepAK8_ZhDecorrelplot_"+selection_label,"Deep AK8 Zh Decorrel",20,0.,1.); //0.04
    

//  plot WpMass_plot(*fillWpmass<RA2bTree>,"Wpmass_"+selection_label,"M_Wp [GeV]",100,0,6000);//100 GeV
  plot VBFmjj_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj_"+selection_label,"m_{jj}^{VBF} [GeV]",40,0,4000);//100 GeV
  plot VBFmjj1_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj1_"+selection_label,"m_{jj}^{VBF} [GeV]",50,0,2500);//50 GeV
  plot VBFmjj2_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj2_"+selection_label,"m_{jj}^{VBF} [GeV]",20,0,2000);//25 GeV
  plot VBFptjj_plot(*fillVBF_Ptjj<RA2bTree>,"VBFptjj_"+selection_label,"pt_{jj}^{VBF} [GeV]",40,0,2000);//50 GeV bin
  plot VBFptjj1_plot(*fillVBF_Ptjj<RA2bTree>,"VBFptjj1_"+selection_label,"pt_{jj}^{VBF} [GeV]",30,0,600);//25 GeV
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
  //plots.push_back(NgenZsplot);
  plots.push_back(NJetsplot);
  plots.push_back(NJets1plot);
  plots.push_back(NJets2plot);
  plots.push_back(NJets3plot);
  plots.push_back(NAK8Jetsplot); 
  plots.push_back(NAK8Jets1plot); 
  plots.push_back(NAK8Jets2plot); 
  plots.push_back(madHT);
  plots.push_back(madHT1);
  plots.push_back(MHTRatio);
  plots.push_back(MHTdPhivsHTRatioplot);
  plots.push_back(MHTdPhi2vsHTRatioplot);
  plots.push_back(MHTdPhi3vsHTRatioplot);
  plots.push_back(MHTdPhi4vsHTRatioplot);
  plots.push_back(METvsAK8Ptplot);
  plots.push_back(METvsAK4j1Ptplot);
  plots.push_back(METvsAK4j2Ptplot);
  plots.push_back(METvsAK4j3Ptplot);
  plots.push_back(METvsAK4j4Ptplot);

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

  plots.push_back(VBFj1NEMF_plot);
  plots.push_back(VBFj2NEMF_plot);
  plots.push_back(VBFj1NHEF_plot);
  plots.push_back(VBFj2NHEF_plot);
  plots.push_back(VBFj1CHEF_plot);
  plots.push_back(VBFj2CHEF_plot);
  plots.push_back(AK8j1NHEF_plot);
  plots.push_back(AK8j1NEMF_plot);
  plots.push_back(AK8j1CHEF_plot);
  plots.push_back(AK4j1NEMF_plot);
  plots.push_back(AK4j1NEMF1_plot);
  plots.push_back(AK4j2NEMF_plot);
  plots.push_back(AK4j3NEMF_plot);
  plots.push_back(AK4j4NEMF_plot);

  plots.push_back(AK4j1CHEF_plot);
  plots.push_back(AK4j1CHEF1_plot);
  plots.push_back(AK4j2CHEF_plot);
  plots.push_back(AK4j3CHEF_plot);
  plots.push_back(AK4j4CHEF_plot);

  plots.push_back(AK4j1NHEFNEMF_plot);
  plots.push_back(AK4j2NHEFNEMF_plot);
  plots.push_back(AK4j3NHEFNEMF_plot);
  plots.push_back(AK4j4NHEFNEMF_plot);

  plots.push_back(AK4j1NHEFvsNEMFplot);
  plots.push_back(AK4j1NHEFvsNEMF1plot);
  plots.push_back(AK4j2NHEFvsNEMFplot);
  plots.push_back(AK4j3NHEFvsNEMFplot);
  plots.push_back(AK4j4NHEFvsNEMFplot);

  plots.push_back(AK4j1NHEF_plot);
  plots.push_back(AK4j1NHEF1_plot);
  plots.push_back(AK4j2NHEF_plot);
  plots.push_back(AK4j3NHEF_plot);
  plots.push_back(AK4j4NHEF_plot);

  plots.push_back(AK4j1ptvsEtaplot);
  plots.push_back(AK4j1PhivsEtaplot);
  plots.push_back(AK4j1NEMFvsEtaplot);
  plots.push_back(AK4j1NEMFvsPtplot);
  plots.push_back(AK4j1NHEFvsEtaplot);
  plots.push_back(AK4j1NHEFvsPtplot);

  plots.push_back(AK4j1ptvsEta1plot);
  plots.push_back(AK4j1PhivsEta1plot);
  plots.push_back(AK4j1NEMFvsEta1plot);
  plots.push_back(AK4j1NEMFvsPt1plot);
  plots.push_back(AK4j1NHEFvsEta1plot);
  plots.push_back(AK4j1NHEFvsPt1plot);

  plots.push_back(AK4j2ptvsEtaplot  );
  plots.push_back(AK4j2PhivsEtaplot );
  plots.push_back(AK4j2NEMFvsEtaplot);
  plots.push_back(AK4j2NEMFvsPtplot );
  plots.push_back(AK4j2NHEFvsEtaplot);
  plots.push_back(AK4j2NHEFvsPtplot);

  plots.push_back(AK4j3ptvsEtaplot  );
  plots.push_back(AK4j3PhivsEtaplot );
  plots.push_back(AK4j3NEMFvsEtaplot);
  plots.push_back(AK4j3NEMFvsPtplot );
  plots.push_back(AK4j3NHEFvsEtaplot);
  plots.push_back(AK4j3NHEFvsPtplot);

  plots.push_back(AK4j4ptvsEtaplot  );
  plots.push_back(AK4j4PhivsEtaplot );
  plots.push_back(AK4j4NEMFvsEtaplot);
  plots.push_back(AK4j4NEMFvsPtplot );
  plots.push_back(AK4j4NHEFvsEtaplot);
  plots.push_back(AK4j4NHEFvsPtplot);

  plots.push_back(METPhiplot);
  plots.push_back(METRatioplot);
  //plots.push_back(gendPhiplot);
  plots.push_back(DeltaPhi1plot);
  plots.push_back(DeltaPhi2plot);
  plots.push_back(DeltaPhi3plot);
  plots.push_back(DeltaPhi4plot);
  plots.push_back(DeltaPhiAK8JMETplot);

  plots.push_back(J1pt_Massplot);
  plots.push_back(J1_SDMassplot);
  plots.push_back(J1_SDMass1plot);
  plots.push_back(J1_SDMass2plot);
  plots.push_back(J1_SDMass3plot);
  plots.push_back(J1_SDMass4plot);
  plots.push_back(J1pt_Mass1plot);
  plots.push_back(J1pt_Tau21plot);
  plots.push_back(J1pt_Tau212plot);
  plots.push_back(DDT_Tau21plot);
  plots.push_back(Tau21vsJMassplot);
  plots.push_back(Tau21vsEtaplot);
  plots.push_back(Tau21vsNEMFplot);
  plots.push_back(Tau21vsCHEFplot);
  plots.push_back(DeepAK8_Wplot);
  plots.push_back(DeepAK8_W1plot);
  plots.push_back(DeepAK8_W2plot);
  plots.push_back(DeepAK8_WDecorrelplot);
  plots.push_back(DeepAK8_Zplot);
  plots.push_back(DeepAK8_Z1plot);
  plots.push_back(DeepAK8_Z2plot);
  plots.push_back(DeepAK8_ZhDecorrelplot);

  plots.push_back(GMassvsZMTplot);  
  plots.push_back(EtavsZMTplot);  
  plots.push_back(GMassplot);
  plots.push_back(GMass1plot);
  plots.push_back(GMass2plot);
  plots.push_back(ZMTplot);
  plots.push_back(ZMT1plot);
  plots.push_back(ZMT3plot);
  plots.push_back(ZMT31plot);
  plots.push_back(ZMT311plot);
  plots.push_back(ZMT312plot);
  plots.push_back(ZMT313plot);
  plots.push_back(ZMT314plot);
  plots.push_back(ZMT4plot); 
  plots.push_back(ZMT7plot); 
  plots.push_back(ZMT8plot); 
  plots.push_back(ZMT9plot); 
  plots.push_back(ZMT10plot); 
  plots.push_back(MTpTRatioplot); 
  plots.push_back(pTMTRatioplot); 
    
  plots.push_back(ZMT_ggFplot);  
  plots.push_back(ZMT_vbFplot);  
  plots.push_back(ZMT_vbFhpplot);  
  plots.push_back(ZMT_vbFfailhpplot);  
  plots.push_back(ZMT_ggF50plot);  
  plots.push_back(ZMT_vbF50plot);  

  plots.push_back(J1pt_Ptplot);
  plots.push_back(J1pt_Pt1plot);
  plots.push_back(J1pt_Pt2plot);
  plots.push_back(J1pt_Etaplot);
  plots.push_back(J1pt_Phiplot);
  plots.push_back(J1pt_Eta1plot);

    
  //plots.push_back(WpMass_plot);
  plots.push_back(VBFmjj_plot);
  plots.push_back(VBFmjj1_plot);
  plots.push_back(VBFmjj2_plot);
  plots.push_back(VBFptjj_plot);
  plots.push_back(VBFptjj1_plot);
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
    TFile* outputFile = new TFile("AN_v1_NLO_files/"+year+"/plotObs_"+selection_label+"_"+skims.sampleName[iSample]+".root","RECREATE");
    
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
    }
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    double weight = 0.;
    double trigwt = 0.;
    
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(100,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
        filename = ntuple->fChain->GetFile()->GetName();
        if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;
    
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
        //trig wt
        trigwt = (TMath::Erf((ntuple->MET - p0) / p1) + 1) / 2. * p2;        
        weight = ntuple->Weight*lum*trigwt;

        // Prefiring wt for 2016 & 2017 only
        if (filename.Contains("MC2016") || filename.Contains("MC2017")){
            weight = ntuple->Weight*lum*ntuple->NonPrefiringProb*trigwt; 
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
    //TFile* outputFile = new TFile("plotObs_"+selection_label+"_baseline_"+skims.signalSampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_v1_NLO_files/"+year+"/plotObs_"+selection_label+"_"+skims.signalSampleName[iSample]+".root","RECREATE");

    sigSamples.push_back(ntuple);
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    double trigwt = 0.;

    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(100,numEvents) ; iEvt++ ){
      ntuple->GetEntry(iEvt);
      if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
      filename = ntuple->fChain->GetFile()->GetName();
      
      if(! selectionFunc(ntuple) ) continue;
      /*  
      if (filename.Contains("VBFG") || filename.Contains("ggFG") || filename.Contains("VBFRad") || filename.Contains("ggFRad")) {if(!genZmatched(ntuple)) continue; }
      if (filename.Contains("VBFWp") || filename.Contains("ggFWp")) {if(!genWpmatched(ntuple)) continue; }
      */  
      // HEM Veto  
      if(year=="2018"){  
            if((ntuple->EvtNum % 1000 > 1000*21.0/59.6) && (! passHEMjetVeto(ntuple, 30)))continue;
      }          

      // trig wt  
      trigwt = (TMath::Erf((ntuple->MET - p0) / p1) + 1) / 2. * p2;  
         
        
      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        TString sig_sample = skims.signalSampleName[iSample];    

        // based on 2018 samples for VBF
	    if ((sig_sample=="VBFG_800") || (sig_sample=="VBFWp_800") || (sig_sample=="VBFRad_800"))    //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_1000") || (sig_sample=="VBFWp_1000") || (sig_sample=="VBFRad_1000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); // wt for 48300 evts: 1pb/#evts
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_1200") || (sig_sample=="VBFWp_1200") || (sig_sample=="VBFRad_1200")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_1400") || (sig_sample=="VBFWp_1400") || (sig_sample=="VBFRad_1400")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_1600") || (sig_sample=="VBFWp_1600") || (sig_sample=="VBFRad_1600")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_1800") || (sig_sample=="VBFWp_1800") || (sig_sample=="VBFRad_1800")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_2000") || (sig_sample=="VBFWp_2000") || (sig_sample=="VBFRad_2000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_2500") || (sig_sample=="VBFWp_2500") || (sig_sample=="VBFRad_2500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_3000") || (sig_sample=="VBFWp_3000") || (sig_sample=="VBFRad_3000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_3500") || (sig_sample=="VBFWp_3500") || (sig_sample=="VBFRad_3500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_4000") || (sig_sample=="VBFWp_4000") || (sig_sample=="VBFRad_4000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_4500") || (sig_sample=="VBFWp_4500") || (sig_sample=="VBFRad_4500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_5000") || (sig_sample=="VBFWp_5000") || (sig_sample=="VBFRad_5000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_5500") || (sig_sample=="VBFRad_5500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if (sig_sample=="VBFWp_5500") //plots[iPlot].fillSignal(ntuple,lum*1*2.08333e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_6000") || (sig_sample=="VBFWp_6000") || (sig_sample=="VBFRad_6000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_6500") || (sig_sample=="VBFWp_6500") || (sig_sample=="VBFRad_6500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_7000") || (sig_sample=="VBFWp_7000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if (sig_sample=="VBFRad_7000") //plots[iPlot].fillSignal(ntuple,lum*1*2.08333e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFG_7500") || (sig_sample=="VBFWp_7500") || (sig_sample=="VBFRad_7500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if (sig_sample=="VBFG_8000") //plots[iPlot].fillSignal(ntuple,lum*1*2.222222e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="VBFWp_8000") || (sig_sample=="VBFRad_8000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 

        // based on 2017 samples for ggFG and ggFRad, for ggFWp it is based on 2016
	        //plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_800") || (sig_sample=="ggFRad_800"))   //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_1000") || (sig_sample=="ggFRad_1000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); // wt for 48300 evts: 1pb/#evts
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_1200") || (sig_sample=="ggFRad_1200")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_1400") || (sig_sample=="ggFRad_1400")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_1600") || (sig_sample=="ggFRad_1600")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_1800") || (sig_sample=="ggFRad_1800")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_2000") || (sig_sample=="ggFRad_2000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_2500") || (sig_sample=="ggFRad_2500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_3000") ) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if (sig_sample=="ggFRad_3000")  //plots[iPlot].fillSignal(ntuple,lum*1*2.325581395348837e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_3500") || (sig_sample=="ggFRad_3500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_4000") || (sig_sample=="ggFRad_4000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_4500") || (sig_sample=="ggFRad_4500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_5000") || (sig_sample=="ggFRad_5000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_5500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if (sig_sample=="ggFRad_5500") //plots[iPlot].fillSignal(ntuple,lum*1*2.08333e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_6000") || (sig_sample=="ggFRad_6000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_6500") || (sig_sample=="ggFRad_6500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_7000") || (sig_sample=="ggFRad_7000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_7500")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if (sig_sample=="ggFRad_7500") //plots[iPlot].fillSignal(ntuple,lum*1*2.0408163265306123e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 
	    if ((sig_sample=="ggFG_8000") || (sig_sample=="ggFRad_8000")) //plots[iPlot].fillSignal(ntuple,lum*1*2e-05*trigwt); 
	        plots[iPlot].fillSignal(ntuple,1); 

	    if ((sig_sample=="ggFWp_1000") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_1200") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_1400") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_1600") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	   //if ((sig_sample=="ggFWp_1800")) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_2000") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_2500") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_3000") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_3500") ) plots[iPlot].fillSignal(ntuple,lum*1*1.0482e-05*trigwt); //1/95400 evts 
	    if ((sig_sample=="ggFWp_4000") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
	    if ((sig_sample=="ggFWp_4500") ) plots[iPlot].fillSignal(ntuple,lum*1*1e-05*trigwt); 
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
    //TFile* outputFile = new TFile("plotObs_"+selection_label+"_baseline_"+skims.dataSampleName[iSample]+".root","RECREATE");
    TFile* outputFile = new TFile("AN_v1_NLO_files/"+year+"/plotObs_"+selection_label+"_"+skims.dataSampleName[iSample]+".root","RECREATE");
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
        
        if(filename.Contains("MET_2018")){
            if(!passHEMjetVeto(ntuple,30)) continue;
        }
      
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
