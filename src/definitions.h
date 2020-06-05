#include "TLorentzVector.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TString.h"
#include <iostream>
#include "paramTest.cc"

std::vector<TLorentzVector> dummy;

//string year = "2016"; 

// constants
// ==============================================
double bbtagCut = 0.3;

TFile* trigWtRatioFile = new TFile("Systematics/Trigger/Ratio_TriggerEff_SESM.root");
TH1D* trigWtRatioHist_16 = (TH1D*) trigWtRatioFile->Get("Ratio_eff_16");
TH1D* trigWtRatioHist_17 = (TH1D*) trigWtRatioFile->Get("Ratio_eff_17");
TH1D* trigWtRatioHist_18 = (TH1D*) trigWtRatioFile->Get("Ratio_eff_18");

TFile* puWeightFile_16 = new TFile("../data/PileupHistograms_2016_69mb_pm5.root");
TFile* puWeightFile_17 = new TFile("../data/PileupHistograms_2017_69mb_pm5.root");
TFile* puWeightFile_18 = new TFile("../data/PileupHistograms_2018_69mb_pm5.root");

//TH1F* puWeightHist_16 = (TH1F*) puWeightFile_16->Get("pu_weights_down");
//TH1F* puWeightHist_17 = (TH1F*) puWeightFile_17->Get("pu_weights_down");
//TH1F* puWeightHist_18 = (TH1F*) puWeightFile_18->Get("pu_weights_down");

TH1F* puWeightHist_16 = (TH1F*) puWeightFile_16->Get("pu_weights_central");
TH1F* puWeightHist_17 = (TH1F*) puWeightFile_17->Get("pu_weights_central");
TH1F* puWeightHist_18 = (TH1F*) puWeightFile_18->Get("pu_weights_central");

//TH1F* puWeightHist_16 = (TH1F*) puWeightFile_16->Get("pu_weights_up");
//TH1F* puWeightHist_17 = (TH1F*) puWeightFile_17->Get("pu_weights_up");
//TH1F* puWeightHist_18 = (TH1F*) puWeightFile_18->Get("pu_weights_up");

// - - - - - - weights for WJets, GJets, - - - - - - - - 
// - - - - - - and ZJets NLO Pt distribution - - - - - - 
TFile* NLOWeightFile = new TFile("../data/kfactors.root");
TH1F* WJets_NLO = (TH1F*) NLOWeightFile->Get("WJets_012j_NLO/nominal");
TH1F* WJets_LO = (TH1F*) NLOWeightFile->Get("WJets_LO/inv_pt");
TH1F* ZJets_NLO = (TH1F*) NLOWeightFile->Get("ZJets_01j_NLO/nominal");
TH1F* ZJets_LO = (TH1F*) NLOWeightFile->Get("ZJets_LO/inv_pt");

TH1F* ZJets_Ewk16 = (TH1F*) NLOWeightFile->Get("EWKcorr/Z");
TH1F* WJets_Ewk16 = (TH1F*) NLOWeightFile->Get("EWKcorr/W");
// - - - - - - W and ZJets EWK NLO kfactor from Boston group - - - - - - 
TFile* EwkZNLOFile = new TFile("../data/merged_kfactors_zjets_fromBU.root");
TFile* EwkWNLOFile = new TFile("../data/merged_kfactors_wjets_fromBU.root");

TH1F* ZJets_Ewk = (TH1F*) EwkZNLOFile->Get("kfactor_monojet_ewk");
TH1F* WJets_Ewk = (TH1F*) EwkWNLOFile->Get("kfactor_monojet_ewk");
// =====================================================================
TFile* file = new TFile("../data/puppiCorr_2016.root");

TF1* puppisd_corrGEN      = (TF1*)file->Get("puppiJECcorr_gen");
TF1* puppisd_corrRECO_cen = (TF1*)file->Get("puppiJECcorr_reco_0eta1v3");
TF1* puppisd_corrRECO_for = (TF1*)file->Get("puppiJECcorr_reco_1v3eta2v5");
// =====================================================================

double CalcdPhi( double phi1 , double phi2 ){
  double dPhi = phi1-phi2;
  if( dPhi < -TMath::Pi() ) 
    dPhi += 2*TMath::Pi() ;
  if( dPhi > TMath::Pi() )
    dPhi -= 2*TMath::Pi() ;
  return fabs(dPhi);
  //return dPhi;

}


double CalcDeltaR( double eta1, double phi1 , double eta2, double phi2 ){
    float dEta = (eta1-eta2);
    float dPhi = CalcdPhi(phi1, phi2);
    return sqrt((dEta*dEta) + (dPhi * dPhi));
}

double ZMT(double pt1, double phi1, double pt2, double phi2){
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pt1,0,phi1,0);
    v2.SetPtEtaPhiM(pt2,0,phi2,0);
    return (v1+v2).M();
}

template<typename ntupleType>void ntupleBranchStatus(ntupleType* ntuple){
  ntuple->fChain->SetBranchStatus("*",0);
  ntuple->fChain->SetBranchStatus("RunNum",1);
  ntuple->fChain->SetBranchStatus("EvtNum",1);
  ntuple->fChain->SetBranchStatus("Muons",1);
  ntuple->fChain->SetBranchStatus("NMuons",1);
  ntuple->fChain->SetBranchStatus("Electrons",1);
  ntuple->fChain->SetBranchStatus("Photons",1);
  ntuple->fChain->SetBranchStatus("Photons_hasPixelSeed",1);
  ntuple->fChain->SetBranchStatus("Photons_fullID",1);
  ntuple->fChain->SetBranchStatus("NElectrons",1);
  ntuple->fChain->SetBranchStatus("iso*Tracks",1);
  ntuple->fChain->SetBranchStatus("DeltaPhi1",1);
  ntuple->fChain->SetBranchStatus("DeltaPhi2",1);
  ntuple->fChain->SetBranchStatus("DeltaPhi3",1);
  ntuple->fChain->SetBranchStatus("DeltaPhi4",1);
  ntuple->fChain->SetBranchStatus("TriggerNames",1);
  ntuple->fChain->SetBranchStatus("TriggerPass",1);
  ntuple->fChain->SetBranchStatus("MHT",1);
  ntuple->fChain->SetBranchStatus("madHT",1);
  ntuple->fChain->SetBranchStatus("HT*",1);
  ntuple->fChain->SetBranchStatus("NJets",1);
  ntuple->fChain->SetBranchStatus("BTags*",1);
  ntuple->fChain->SetBranchStatus("MET*",1);
  ntuple->fChain->SetBranchStatus("METPhi",1);
  ntuple->fChain->SetBranchStatus("HTclean",1);
  ntuple->fChain->SetBranchStatus("NJetsclean",1);
  ntuple->fChain->SetBranchStatus("NJets",1);
  ntuple->fChain->SetBranchStatus("BTagsclean",1);
  ntuple->fChain->SetBranchStatus("METclean",1);
  ntuple->fChain->SetBranchStatus("METPhiclean",1);
  ntuple->fChain->SetBranchStatus("JetsAK8*",1);
  ntuple->fChain->SetBranchStatus("Jets",1);
  ntuple->fChain->SetBranchStatus("JetsAK8_neutralEmEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("JetsAK8_chargedHadronEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("JetsAK8_neutralHadronEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("Jets_neutralEmEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("Jets_neutralHadronEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("Weight",1);
  ntuple->fChain->SetBranchStatus("PDFweights",1); // for PDFweights
  ntuple->fChain->SetBranchStatus("ScaleWeights",1); //for ScaleWeights
  ntuple->fChain->SetBranchStatus("pu*",1);
  ntuple->fChain->SetBranchStatus("TrueNumInteractions",1);
  ntuple->fChain->SetBranchStatus("*Filter",1);
  ntuple->fChain->SetBranchStatus("HEMDPhiVetoFilter",1);
  ntuple->fChain->SetBranchStatus("HEMVetoFilter",1);
  
  ntuple->fChain->SetBranchStatus("CaloMET",1);
  ntuple->fChain->SetBranchStatus("PFCaloMETRatio",1);
  ntuple->fChain->SetBranchStatus("NVtx",1);
  ntuple->fChain->SetBranchStatus("NumInteractions",1);
  ntuple->fChain->SetBranchStatus("nAllVertices",1);
  ntuple->fChain->SetBranchStatus("JetID*",1);
  ntuple->fChain->SetBranchStatus("madHT",1);
  ntuple->fChain->SetBranchStatus("NJetsISR",1);
  ntuple->fChain->SetBranchStatus("madMinDeltaRStatus",1);
  ntuple->fChain->SetBranchStatus("madMinPhotonDeltaR",1);
  ntuple->fChain->SetBranchStatus("ZCandidates",1);
  ntuple->fChain->SetBranchStatus("GenParticles*",1);
  ntuple->fChain->SetBranchStatus("NonPrefiringProb",1);
  ntuple->fChain->SetBranchStatus("NonPrefiringProbUp",1);
  ntuple->fChain->SetBranchStatus("NonPrefiringProbDown",1);
  ntuple->fChain->SetBranchStatus("HTRatioDPhiFilter",1);
  ntuple->fChain->SetBranchStatus("HTRatioDPhiTightFilter",1);
    
}

/***************************************************************/
/* - - - - - - - - - - - - gen-level cuts - - - - - - - - - -  */
/***************************************************************/

template<typename ntupleType> double FillGenWPt(ntupleType* ntuple){
    //cout << "FillGenWPt:" << endl;
    if( ntuple->GenParticles == NULL ) return -999.;
    double pt = -999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 ){
            //std::cout << "pt: " << ntuple->GenParticles->at(p).Pt() << std::endl;
            pt = ntuple->GenParticles->at(p).Pt();
        }
    }
    return pt; 
}

template<typename ntupleType> double FillGenZPt(ntupleType* ntuple){
    //cout << "FillGenZPt:" << endl;
    if( ntuple->GenParticles == NULL ) return -999.;
    double pt = -999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 ){
            //std::cout << "pt: " << ntuple->GenParticles->at(p).Pt() << std::endl;
            pt = ntuple->GenParticles->at(p).Pt();
        }
    }
    return pt; 
}

template<typename ntupleType> bool genWmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( abs(ntuple->GenParticles_PdgId->at(i)) == 24 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4)
            return true;
    }
    return false;
}

template<typename ntupleType> bool genTmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( abs(ntuple->GenParticles_PdgId->at(i)) == 6 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4)
            return true;
    }
    return false;
}

template<typename ntupleType> bool genWpmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        int pid = abs(ntuple->GenParticles_PdgId->at(i));
        int parent = abs(ntuple->GenParticles_ParentId->at(i));
        if( (pid == 1 || pid ==2 || pid == 3 || pid ==4 || pid ==5) && parent == 24 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<=0.8)
            return true;
    }
    return false;
}

template<typename ntupleType> bool genZmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        int pid = abs(ntuple->GenParticles_PdgId->at(i));
        int parent = abs(ntuple->GenParticles_ParentId->at(i));
        if( (pid == 1 || pid ==2 || pid == 3 || pid ==4 || pid ==5) && parent == 23 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<=0.8)
        //if( (pid == 1 || pid ==2 || pid == 3 || pid ==4 || pid ==5) && parent != 23 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<=0.8)
        //if( (pid == 21) && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<=0.8)
            return true;
    }
    return false;
}

template<typename ntupleType> double dPhigenZinv(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -999.0;
    double dphi = 99.0;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        int pid = abs(ntuple->GenParticles_PdgId->at(i));
        int parent = abs(ntuple->GenParticles_ParentId->at(i));
        if( (pid == 12 || pid ==14 || pid == 16) && parent == 23){ 
            int j = abs(ntuple->GenParticles_ParentIdx->at(i));
            double p1 = ntuple->GenParticles->at(j).Phi();
            double p2 = ntuple->METPhi;
            dphi = CalcdPhi(p1,p2);
        //return dphi;
        }
    }
    return dphi;
}

template<typename ntupleType> double getNumGenZs(ntupleType* ntuple){
    int numZs=0;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( (ntuple->GenParticles_PdgId->at(i) == 23) && (ntuple->GenParticles_Status->at(i) == 62)){ 
            numZs++;
        }    
    }
    //std::cout<<"num zs: "<< numZs<<std::endl;
    return numZs;
}

/***************************************************************/
/* - - - - - - - - - - - - custom weights - - - - - - - - - -  */
/***************************************************************/

template<typename ntupleType> double WJetsNLOWeights(ntupleType* ntuple){
    double Wpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 )
            Wpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Wpt>150. && Wpt<1250.){
        double LO = WJets_LO->GetBinContent( WJets_LO->FindBin(Wpt) );
        double NLO = WJets_NLO->GetBinContent( WJets_NLO->FindBin(Wpt) );
        return (LO==0?0.:NLO/LO/1.21);
    }else if( Wpt >= 1250.){
        double LO =  WJets_LO->GetBinContent(  WJets_LO->GetNbinsX() );
        double NLO = WJets_NLO->GetBinContent( WJets_NLO->GetNbinsX());
        return (LO==0?0.:NLO/LO/1.21);
    }else
        return WJets_NLO->GetBinContent(1)/WJets_LO->GetBinContent(1)/1.21;
}

template<typename ntupleType> double ZJetsNLOWeights(ntupleType* ntuple){
    double Zpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 )
            Zpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Zpt>150. && Zpt < 1250.){
        double LO = ZJets_LO->GetBinContent( ZJets_LO->FindBin(Zpt) );
        double NLO = ZJets_NLO->GetBinContent( ZJets_NLO->FindBin(Zpt) );
        return (LO==0?0.:NLO/LO/1.23);
    }else if( Zpt >= 1250.){
        double LO = ZJets_LO->GetBinContent( ZJets_LO->GetNbinsX());
        double NLO = ZJets_NLO->GetBinContent( ZJets_NLO->GetNbinsX());
        return (LO==0?0.:NLO/LO/1.23);
    }else
        return ZJets_NLO->GetBinContent(1)/ZJets_LO->GetBinContent(1)/1.23;
}

template<typename ntupleType> double ZJetsNLOWeightsEwk16(ntupleType* ntuple){
    double Zpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 )
            Zpt = ntuple->GenParticles->at(p).Pt();
    }
    // k-factor histogram goes from 150 to 1250 GeV, and has 24 bins
    if( Zpt > 150. && Zpt < 1250.){
        double LO = ZJets_LO->GetBinContent( ZJets_LO->FindBin(Zpt) );
        double NLO = ZJets_Ewk16->GetBinContent( ZJets_Ewk16->FindBin(Zpt) );
        return (LO==0?0.:NLO/LO/1.23);
    }else if( Zpt >= 1250.){
        double LO = ZJets_LO->GetBinContent( ZJets_LO->GetNbinsX());
        double NLO = ZJets_Ewk16->GetBinContent( ZJets_Ewk16->GetNbinsX());
        return (LO==0?0.:NLO/LO/1.23);
    }else
        return ZJets_Ewk16->GetBinContent(1)/ZJets_LO->GetBinContent(1)/1.23;
}

template<typename ntupleType> double WJetsNLOWeightsEwk16(ntupleType* ntuple){
    double Wpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 )
            Wpt = ntuple->GenParticles->at(p).Pt();
    }
    // k-factor histogram goes from 150 to 1250 GeV, and has 24 bins
    if( Wpt > 150. && Wpt < 1250.){
        double LO = WJets_LO->GetBinContent( WJets_LO->FindBin(Wpt) );
        double NLO = WJets_Ewk16->GetBinContent( WJets_Ewk16->FindBin(Wpt) );
        return (LO==0?0.:NLO/LO/1.21);
    }else if( Wpt >= 1250.){
        double LO = WJets_LO->GetBinContent( WJets_LO->GetNbinsX() );
        double NLO = WJets_Ewk16->GetBinContent( WJets_Ewk16->GetNbinsX() );
        return (LO==0?0.:NLO/LO/1.21);
    }else
        return WJets_Ewk16->GetBinContent(1)/WJets_Ewk16->GetBinContent(1)/1.21;
}
// New NLO weights from Boston group:
// https://github.com/bu-cms/bucoffea/blob/master/bucoffea/monojet/definitions.py#L606-L626
// https://github.com/bu-cms/bucoffea/tree/master/bucoffea/data/sf/theory

//def fitfun(x, a, b, c): return a * np.exp(-b * x) + c

double NLOfitfun( double vpt, double a , double b, double c){
    return (a*exp(-b*vpt)+c); //return a * np.exp(-b * x) + c 
}

template<typename ntupleType> double ZJetsNLOWeightsQCD1718(ntupleType* ntuple){
    double Zpt=1.0;
    double Z_kfactor = 1.0;

    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( (abs(ntuple->GenParticles_PdgId->at(p)) == 23) && (ntuple->GenParticles_Status->at(p) == 62)){
            Zpt = ntuple->GenParticles->at(p).Pt();
            //ntuple->GenParticles_Status->at(p) == 62;
            //std::cout<<"status of Z: "<<ntuple->GenParticles_Status->at(p)<<endl; //got status 62,1,1 for 3 Zs. 
        }
    }
    if( Zpt>150. ){
        Z_kfactor = NLOfitfun(Zpt,1.434,2.210e-3,0.443); //fitfun(gen_v_pt, 1.434, 2.210e-3, 0.443)
        return (Z_kfactor);
        //return (Z_kfactor/1.23);
    }else
        return 1.0;
}

template<typename ntupleType> double WJetsNLOWeightsQCD1718(ntupleType* ntuple){
    double Wpt=1.0;
    double W_kfactor = 1.0;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 )
            Wpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Wpt>150. ){
        W_kfactor = NLOfitfun(Wpt,1.053, 3.163e-3, 0.746); //fitfun(gen_v_pt, 1.053, 3.163e-3, 0.746)
        return W_kfactor;
        //return (W_kfactor/1.21);
    }else
        return 1.0;
}

template<typename ntupleType> double ZJetsNLOWeightsEwk1718(ntupleType* ntuple){
    double Zpt=-999.;
    double Z_kfactor = 1.0;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 )
            Zpt = ntuple->GenParticles->at(p).Pt();
    }
    // k-factor histogram goes from 150 to 1250 GeV, and has 24 bins
    if( Zpt > 150. && Zpt < 1250.){
        Z_kfactor = ZJets_Ewk->GetBinContent(ZJets_Ewk->FindBin(Zpt) );
        return Z_kfactor;
    }else if( Zpt >= 1250.){
        Z_kfactor = ZJets_Ewk->GetBinContent(ZJets_Ewk->GetNbinsX());
        return Z_kfactor;
    }else
        return (ZJets_Ewk->GetBinContent(1));
}

template<typename ntupleType> double WJetsNLOWeightsEwk1718(ntupleType* ntuple){
    double Wpt=-999.;
    double W_kfactor = 1.0;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 )
            Wpt = ntuple->GenParticles->at(p).Pt();
    }
    // k-factor histogram goes from 150 to 1250 GeV, and has 24 bins
    if( Wpt > 150. && Wpt < 1250.){
        W_kfactor = WJets_Ewk->GetBinContent(WJets_Ewk->FindBin(Wpt) );
        return W_kfactor;
    }else if( Wpt >= 1250.){
        W_kfactor = WJets_Ewk->GetBinContent(WJets_Ewk->GetNbinsX()); //setting the last bin content for the bins > 1250.
        return W_kfactor;
    }else
        return (WJets_Ewk->GetBinContent(1));
}

//////////// Puppi SoftDrop Mass Correction //////////////////////////////////////////////////////
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetWtagging#PUPPI_softdrop_mass_corrections
// 2016: https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetWtagging#PUPPI_softdrop_mass_corrections
/////////////////////////////////////////////////////////////////////////////////////////////////
//puppipt and puppieta are the puppi AK8 L1J pt and eta.

float getPUPPIwt2016(float puppipt, float puppieta){

    float genCorr  = 1.;
    float recoCorr = 1.;
    float totalWeight = 1.;

    genCorr =  puppisd_corrGEN->Eval( puppipt );
    if( fabs(puppieta)  <= 1.3 ){
      recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
    }
    else{
      recoCorr = puppisd_corrRECO_for->Eval( puppipt );
    }
    
    totalWeight = genCorr * recoCorr;

    return totalWeight;
}


template<typename ntupleType> double AK8PUPPISoftdropCorrMass(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0 || (ntuple->JetsAK8_subjets->at(0)).size()==0) return -99999.;

    TLorentzVector puppi_softdrop, subjet1, subjet2;

    for( unsigned int i = 0 ; i < (ntuple->JetsAK8_subjets->at(0)).size() ; i++ ){
        subjet1.SetPtEtaPhiM( (ntuple->JetsAK8_subjets->at(0))[0].Pt(), (ntuple->JetsAK8_subjets->at(0))[0].Eta(), (ntuple->JetsAK8_subjets->at(0))[0].Phi(), (ntuple->JetsAK8_subjets->at(0))[0].M()); 
        subjet2.SetPtEtaPhiM( (ntuple->JetsAK8_subjets->at(0))[1].Pt(), (ntuple->JetsAK8_subjets->at(0))[1].Eta(), (ntuple->JetsAK8_subjets->at(0))[1].Phi(), (ntuple->JetsAK8_subjets->at(0))[1].M());
        puppi_softdrop = subjet1+subjet2;    
    }

    float AK8jetPt = ntuple->JetsAK8->at(0).Pt();
    float AK8jetEta = ntuple->JetsAK8->at(0).Eta();
    float puppiCorr = getPUPPIwt2016(AK8jetPt, AK8jetEta);
    double Corrected_Mass = puppi_softdrop.M() * puppiCorr;
    return (Corrected_Mass);
}


template<typename ntupleType> double AK8PUPPISoftdropCorrMassCent(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return -99999.;
  if( fabs(ntuple->JetsAK8->at(0).Eta())<1.3)
       return AK8PUPPISoftdropCorrMass(ntuple);
   else
       return -999.; 
}

template<typename ntupleType> double AK8PUPPISoftdropCorrMassFwd(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return -99999.;
  if( (fabs(ntuple->JetsAK8->at(0).Eta()) > 1.3) && (fabs(ntuple->JetsAK8->at(0).Eta()) < 2.5))
       return AK8PUPPISoftdropCorrMass(ntuple);
   else
       return -999.; 
}

template<typename ntupleType> double fillLeadingJetPtCent(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  if( fabs(ntuple->JetsAK8->at(0).Eta())<1.3) 
    return ntuple->JetsAK8->at(0).Pt();
  else
       return -999.; 
}

template<typename ntupleType> double fillLeadingJetPtFwd(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  if( (fabs(ntuple->JetsAK8->at(0).Eta()) > 1.3) && (fabs(ntuple->JetsAK8->at(0).Eta()) < 2.5))
    return ntuple->JetsAK8->at(0).Pt();
  else
       return -999.; 
}
//////////////////// end of soft drop corrn ////////////////////

template<typename ntupleType> double customPUweights(ntupleType* ntuple){
    int nVtx = ntuple->TrueNumInteractions;
    //puWeightHist_16
    //return puWeightHist->GetBinContent(puWeightHist->GetXaxis()->FindBin(min(ntuple->TrueNumInteractions,puWeightHist->GetBinLowEdge(puWeightHist->GetNbinsX()+1))));
    if (year == "2016") return puWeightHist_16->GetBinContent(puWeightHist_16->GetXaxis()->FindBin(min(ntuple->TrueNumInteractions,puWeightHist_16->GetBinLowEdge(puWeightHist_16->GetNbinsX()+1))));
    else if (year == "2017") return puWeightHist_17->GetBinContent(puWeightHist_17->GetXaxis()->FindBin(min(ntuple->TrueNumInteractions,puWeightHist_17->GetBinLowEdge(puWeightHist_17->GetNbinsX()+1))));
    else if (year == "2018") return puWeightHist_18->GetBinContent(puWeightHist_18->GetXaxis()->FindBin(min(ntuple->TrueNumInteractions,puWeightHist_18->GetBinLowEdge(puWeightHist_18->GetNbinsX()+1))));
    else return 1.0;
}

template<typename ntupleType> double customTrigWeights(ntupleType* ntuple){
    double p0, p1, p2;
    if(year=="2016") {p0=1.21277e+02; p1=8.77679e+01; p2=9.94172e-01;}
    if(year=="2017") {p0=1.61724e+02; p1=6.91644e+01; p2=9.89446e-01;}
    if(year=="2018") {p0=1.70454e+02; p1=6.64100e+01; p2=9.89298e-01;}

    double trigwt = (TMath::Erf((ntuple->MET - p0) / p1) + 1) / 2. * p2;
    return trigwt;
}

template<typename ntupleType> double trigWtRatio(ntupleType* ntuple){
    double MET = ntuple->MET;
    double ratio = 1.0;
    if( MET > 200. && MET < 1000.){
        if (year == "2016"){ratio = trigWtRatioHist_16->GetBinContent(trigWtRatioHist_16->FindBin(MET) );}
        if (year == "2017"){ratio = trigWtRatioHist_17->GetBinContent(trigWtRatioHist_17->FindBin(MET) );}
        if (year == "2018"){ratio = trigWtRatioHist_18->GetBinContent(trigWtRatioHist_18->FindBin(MET) );}
        return ratio;
    }else if( MET >= 1000.){
        if (year == "2016"){ratio = trigWtRatioHist_16->GetBinContent(trigWtRatioHist_16->GetNbinsX());} //setting the last bin content for the bins > 1000.
        if (year == "2017"){ratio = trigWtRatioHist_17->GetBinContent(trigWtRatioHist_17->GetNbinsX());} 
        if (year == "2018"){ratio = trigWtRatioHist_18->GetBinContent(trigWtRatioHist_18->GetNbinsX());} 
        return ratio;
    }else return 1.0;
}

template<typename ntupleType> double customTrigWeightsUp(ntupleType* ntuple){
    double upVar;
    upVar = customTrigWeights(ntuple) * trigWtRatio(ntuple);
    if (upVar < 1.0) return upVar; 
    else return 1.0;
}

template<typename ntupleType> double customTrigWeightsDown(ntupleType* ntuple){
    double downVar;
    downVar = customTrigWeights(ntuple)/trigWtRatio(ntuple);
    if (downVar < 1.0) return downVar; 
    else return 1.0;
}

template<typename ntupleType> double tau21pTExtrapolation(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return 1.0;
    double factor;
    double pt = (ntuple->JetsAK8->at(0).Pt()) / 200.0;
    factor = 1 + (0.085 * log(pt));
    return factor ;
}

template<typename ntupleType> double customTau21pTExtrapUp(ntupleType* ntuple){
    return tau21pTExtrapolation(ntuple) ;
}

template<typename ntupleType> double customTau21pTExtrapDown(ntupleType* ntuple){
    return (1/tau21pTExtrapolation(ntuple));
}

//https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetWtagging#tau21_0_35_HP_0_35_tau21_0_75_LP
template<typename ntupleType> double tau21ScaleFactor(ntupleType* ntuple){
    double sf; // for HP working points of 0.35
    if(year=="2016") {sf = 0.99;}
    if(year=="2017") {sf = 0.957;}
    if(year=="2018") {sf = 0.964;}

    return sf;
}

enum ISRweightType {kNom,kUp,kDn};
template<typename ntupleType> double ISRweights(ntupleType* ntuple, ISRweightType wType = kNom ){

    double wanted_w_isr=1.;
    double wanted_sys_isr[2]={1.,1.};

    TString sample = ntuple->fChain->GetFile()->GetName();

    // these are taken from here:
    // https://github.com/manuelfs/babymaker/blob/3a57e1bace6c52832fe40e401cf37bc6b50923c3/bmaker/genfiles/src/change_weights.cxx#L156-L175
    // via Manuel Franco Sevilla
    if(sample.Contains("TTJets_HT-600to800")) {
        wanted_w_isr = 0.7838;
        wanted_sys_isr[0] = 0.8965;
        wanted_sys_isr[1] = 0.6604;
    }else if(sample.Contains("TTJets_HT-800to1200")) {
        wanted_w_isr = 0.7600;
        wanted_sys_isr[0] = 0.8851;
        wanted_sys_isr[1] = 0.6230;
    }else if(sample.Contains("TTJets_HT-1200to2500")) {
        wanted_w_isr = 0.7365;
        wanted_sys_isr[0] = 0.8739;
        wanted_sys_isr[1] = 0.5861;
    }else if(sample.Contains("TTJets_HT-2500toInf")) {
        wanted_w_isr = 0.7254;
        wanted_sys_isr[0] = 0.8686;
        wanted_sys_isr[1] = 0.5687;
    }else{ //  if(sample.Contains("TTJets_SingleLept") or sample.Contains("TTJets_DiLept") ){
        // these numbers should really only be applied to the inclusive sample
        wanted_w_isr = 1.071;
        wanted_sys_isr[0] = 1.071;
        wanted_sys_isr[1] = 1.071;
    }
    
    double D;
    if( wType == kNom ) D = wanted_w_isr;
    else D = wanted_sys_isr[wType-1];

    double w[6]={0.920,0.821,0.715,0.662,0.561,0.511};
    if( ntuple->NJetsISR == 0 )
        return D;
    else if( ntuple->NJetsISR >= 6 )
        return w[5]*D;
    else 
        return w[ntuple->NJetsISR]*D;
}

// Zpt = dimuon pt; calculate this to calculate the energy scale later = t1muMET/Zpt; t1mumet= pfmet -Zpt
double Zpt(double pt1, double eta1, double phi1, double e1, double pt2, double eta2, double phi2, double e2){
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiE(pt1,eta1,phi1,e1);
    v2.SetPtEtaPhiE(pt2,eta2,phi2,e2);
    return (v1+v2).Pt();
}

double Zmass(double pt1, double eta1, double phi1, double e1, double pt2, double eta2, double phi2, double e2){
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiE(pt1,eta1,phi1,e1);
    v2.SetPtEtaPhiE(pt2,eta2,phi2,e2);
    return (v1+v2).M();
}

template<typename ntupleType> double fillWpmass(ntupleType* ntuple){
    std::cout<<"Wp mass check: "<<std::endl;
    if (ntuple->GenParticles->size()==0) return 0.;
    double Wpt = 0.00;
    double WEta = 0.00;
    double WPhi = 0.00;
    double Wm = 0.00;
    double Zpt = 0.00;
    double ZEta = 0.00;
    double ZPhi = 0.00;
    double Zm = 0.00;
    //std::cout<<"Gen size: "<<ntuple->GenParticles->size()<<std::endl;
    for (int i=0; i<(ntuple->GenParticles->size()); i++){    
    //std::cout<<"Gen size: "<<ntuple->GenParticles->size()<<std::endl;
        if(abs(ntuple->GenParticles_PdgId->at(i)) == 24){ 
            Wpt   = ntuple->GenParticles->at(i).Pt();
            WEta  = ntuple->GenParticles->at(i).Eta();
            WPhi  = ntuple->GenParticles->at(i).Phi();
            Wm = ntuple->GenParticles->at(i).Energy();
        }
    std::cout<<"Gen size: "<<ntuple->GenParticles->size()<<std::endl;
        if(abs(ntuple->GenParticles_PdgId->at(i)) == 23){
            Zpt   = ntuple->GenParticles->at(i).Pt();
            ZEta  = ntuple->GenParticles->at(i).Eta();
            ZPhi  = ntuple->GenParticles->at(i).Phi();
            Zm = ntuple->GenParticles->at(i).Energy();
        }
    }
    //std::cout<<"Gen size: "<<ntuple->GenParticles->size()<<std::endl;
    double Wpmass = Zmass(Wpt, WEta, WPhi, Wm, Zpt, ZEta, ZPhi, Zm);
//    std::cout<<"Wp mass: "<<Wpmass<<std::endl;
    return Wpmass; 

}

// Ecal Debug
template<typename ntupleType> double fillJetPt1a(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta)>=2.6 && fabs(eta)<=3.0 && pt>30)
        return ntuple->Jets->at(0).Pt();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetEta1a(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta)>=2.6 && fabs(eta)<=3.0 && pt>30)
        return ntuple->Jets->at(0).Eta();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetPhi1a(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta)>=2.6 && fabs(eta)<=3.0 && pt>30)
        return ntuple->Jets->at(0).Phi();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNEMF1a(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta)>=2.6 && fabs(eta)<=3.0 && pt>30)
        return ntuple->Jets_neutralEmEnergyFraction->at(0);
    else 
        return -999.;
}



template<typename ntupleType> double fillJetNHEF1a(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta) >= 2.6 && fabs(eta)<=3.0 && pt>30)
        return ntuple->Jets_neutralHadronEnergyFraction->at(0);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetCHEF1a(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta) >= 2.6 && fabs(eta)<=3.0 && pt>30)
        return ntuple->Jets_chargedHadronEnergyFraction->at(0);
    else 
        return -999.;
}

// End of Ecal Debug
////////////////////////////////////////////////////////////
// - - - - - - - - EVENT LEVEL VARIABLES - - - - - - - -  //
////////////////////////////////////////////////////////////

template<typename ntupleType> double fillJetPt1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && pt>30)
        return ntuple->Jets->at(0).Pt();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetEta1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    //double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    //if( ntuple->Jets->size() >= 1 && fabs(eta)>=2.6 && fabs(eta)<=3.0 && pt>30)
    //if( ntuple->Jets->size() >= 1 && fabs(eta) > 3.0 && pt>30)
    if( ntuple->Jets->size() >= 1 && pt>30)
        return ntuple->Jets->at(0).Eta();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetPhi1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && fabs(eta)<2.6 && pt>30)
        return ntuple->Jets->at(0).Phi();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNEMF1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && pt>30)
        return ntuple->Jets_neutralEmEnergyFraction->at(0);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetNHEF1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && pt>30)
        return ntuple->Jets_neutralHadronEnergyFraction->at(0);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetCHEF1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && pt>30)
        return ntuple->Jets_chargedHadronEnergyFraction->at(0);
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNHEFNEMF1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double eta = ntuple->Jets->at(0).Eta();
    double pt = ntuple->Jets->at(0).Pt();
    if( ntuple->Jets->size() >= 1 && pt>30)
        return (ntuple->Jets_neutralHadronEnergyFraction->at(0) + ntuple->Jets_neutralEmEnergyFraction->at(0));
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && pt>30)
        return ntuple->Jets->at(1).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetEta2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && pt>30)
        return ntuple->Jets->at(1).Eta();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetPhi2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double eta = ntuple->Jets->at(1).Eta();
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && fabs(eta)<2.6 && pt>30)
        return ntuple->Jets->at(1).Phi();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNEMF2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double eta = ntuple->Jets->at(1).Eta();
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && pt>30)
        return ntuple->Jets_neutralEmEnergyFraction->at(1);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetNHEF2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double eta = ntuple->Jets->at(1).Eta();
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && pt>30)
        return ntuple->Jets_neutralHadronEnergyFraction->at(1);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetCHEF2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double eta = ntuple->Jets->at(1).Eta();
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && pt>30)
        return ntuple->Jets_chargedHadronEnergyFraction->at(1);
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNHEFNEMF2(ntupleType* ntuple){
    if( ntuple->Jets->size() <2 ) return -9999.;
    double eta = ntuple->Jets->at(1).Eta();
    double pt = ntuple->Jets->at(1).Pt();
    if( ntuple->Jets->size() >= 2 && pt>30)
        return (ntuple->Jets_neutralHadronEnergyFraction->at(1) + ntuple->Jets_neutralEmEnergyFraction->at(1));
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && pt>30)
        return ntuple->Jets->at(2).Pt();
    else 
        return -999.;
}


template<typename ntupleType> double fillJetEta3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && pt>30)
        return ntuple->Jets->at(2).Eta();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPhi3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double eta = ntuple->Jets->at(2).Eta();
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && fabs(eta)<2.6 && pt>30)
        return ntuple->Jets->at(2).Phi();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNEMF3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double eta = ntuple->Jets->at(2).Eta();
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && pt>30)
        return ntuple->Jets_neutralEmEnergyFraction->at(2);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetNHEF3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double eta = ntuple->Jets->at(2).Eta();
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && pt>30)
        return ntuple->Jets_neutralHadronEnergyFraction->at(2);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetCHEF3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double eta = ntuple->Jets->at(2).Eta();
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && pt>30)
        return ntuple->Jets_chargedHadronEnergyFraction->at(2);
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNHEFNEMF3(ntupleType* ntuple){
    if( ntuple->Jets->size() <3 ) return -9999.;
    double eta = ntuple->Jets->at(2).Eta();
    double pt = ntuple->Jets->at(2).Pt();
    if( ntuple->Jets->size() >= 3 && pt>30)
        return (ntuple->Jets_neutralHadronEnergyFraction->at(2) + ntuple->Jets_neutralEmEnergyFraction->at(2));
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double pt = ntuple->Jets->at(3).Pt();
    if( ntuple->Jets->size() >= 4 && pt>30)
        return ntuple->Jets->at(3).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetEta4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double pt = ntuple->Jets->at(3).Pt();
    if( ntuple->Jets->size() >= 4 && pt>30)
        return ntuple->Jets->at(3).Eta();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetPhi4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double eta = ntuple->Jets->at(3).Eta();
    double pt = ntuple->Jets->at(3).Pt();
    if( ntuple->Jets->size() >= 4 && fabs(eta)<2.6 && pt>30)
        return ntuple->Jets->at(3).Phi();
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNEMF4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double eta = ntuple->Jets->at(3).Eta();
    double pt = ntuple->Jets->at(3).Pt();
    if( ntuple->Jets->size() >= 4 && pt>30)
        return ntuple->Jets_neutralEmEnergyFraction->at(3);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetNHEF4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double eta = ntuple->Jets->at(3).Eta();
    double pt = ntuple->Jets->at(3).Pt();
    if( ntuple->Jets->size() >= 4 && pt>30)
        return ntuple->Jets_neutralHadronEnergyFraction->at(3);
    else 
        return -999.;
}

template<typename ntupleType> double fillJetCHEF4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double eta = ntuple->Jets->at(3).Eta();
    double pt = ntuple->Jets->at(3).Pt();
    //if( ntuple->Jets->size() >= 4 && fabs(eta) > 3.0 && pt>30)
    if( ntuple->Jets->size() >= 4 && pt>30)
        return ntuple->Jets_chargedHadronEnergyFraction->at(3);
    else 
        return -999.;
}
template<typename ntupleType> double fillJetNHEFNEMF4(ntupleType* ntuple){
    if( ntuple->Jets->size() <4 ) return -9999.;
    double eta = ntuple->Jets->at(3).Eta();
    double pt = ntuple->Jets->at(3).Pt();
    if( ntuple->Jets->size() >= 4 && pt>30)
        return (ntuple->Jets_neutralHadronEnergyFraction->at(3) + ntuple->Jets_neutralEmEnergyFraction->at(3));
    else 
        return -999.;
}

// End of AK4 fill list

template<typename ntupleType> double fillNVtx(ntupleType* ntuple){
  return ntuple->NVtx;
}

template<typename ntupleType> double fillMadHT(ntupleType* ntuple){
  return ntuple->madHT;
}

template<typename ntupleType> double fillMetPhi(ntupleType* ntuple){
  return ntuple->METPhi;
}

template<typename ntupleType> double fillPfCaloMetRatio(ntupleType* ntuple){
  return (ntuple->MET/ntuple->CaloMET);
}

template<typename ntupleType> double fillDeltaPhi1(ntupleType* ntuple){
  //return ntuple->DeltaPhi1;
  if( ntuple->Jets->size() == 0 || ntuple->Jets->at(0).Pt()<30) return 999.;  
  double phi1 = ntuple->Jets->at(0).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi1 = CalcdPhi(phi1, phi2);  
  return Dphi1;
}

template<typename ntupleType> double fillDeltaPhi2(ntupleType* ntuple){
  //return ntuple->DeltaPhi2;
  if( ntuple->Jets->size() <2 || ntuple->Jets->at(1).Pt()<30 ) return 999.;  
  double phi1 = ntuple->Jets->at(1).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi2 = CalcdPhi(phi1, phi2);  
  return Dphi2;
}

template<typename ntupleType> double fillDeltaPhi3(ntupleType* ntuple){
  //return ntuple->DeltaPhi3;
  if( ntuple->Jets->size() < 3 || ntuple->Jets->at(2).Pt()<30) return 999.;  
  double phi1 = ntuple->Jets->at(2).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi3 = CalcdPhi(phi1, phi2);  
  return Dphi3;
}

template<typename ntupleType> double fillDeltaPhi4(ntupleType* ntuple){
  //return ntuple->DeltaPhi4;
  if( ntuple->Jets->size() < 4 || ntuple->Jets->at(3).Pt()<30) return 999.;  
  double phi1 = ntuple->Jets->at(3).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi4 = CalcdPhi(phi1, phi2);  
  return Dphi4;
}

template<typename ntupleType> double fillDeltaPhiMHT(ntupleType* ntuple){
  return ntuple->DeltaPhi1;
}

template<typename ntupleType> double fillDeltaPhi2MHT(ntupleType* ntuple){
  return ntuple->DeltaPhi2;
}

template<typename ntupleType> double fillDeltaPhi3MHT(ntupleType* ntuple){
  return ntuple->DeltaPhi3;
}

template<typename ntupleType> double fillDeltaPhi4MHT(ntupleType* ntuple){
  return ntuple->DeltaPhi4;
}

template<typename ntupleType> double fillHT(ntupleType* ntuple){
  return ntuple->HT;
}

template<typename ntupleType> double fillHTRatio(ntupleType* ntuple){
  return (ntuple->HT5/ntuple->HT);
}

template<typename ntupleType> double fillMHTRatio(ntupleType* ntuple){
  return (ntuple->MHT/ntuple->HT);
}

template<typename ntupleType> double fillMHT(ntupleType* ntuple){
  return ntuple->MHT;
}

template<typename ntupleType> double fillMET(ntupleType* ntuple){
  return ntuple->MET;
  //return ntuple->METUp->at(5);
}

template<typename ntupleType> double fillOne(ntupleType* ntuple){
  return 1.;
}


template<typename ntupleType> double fillNAK8Jets(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -999.;
    return ntuple->JetsAK8->size();
}

template<typename ntupleType> double fillNJets(ntupleType* ntuple){
  return ntuple->NJets;
}

template<typename ntupleType> double fillNJets1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -999.;
    else{
        int nj = 0.;
        double jeta = 0.0;
        double jpt = 0.0;
        for( int q = 0 ; q < ntuple->Jets->size() ; q++ ){
            jeta = ntuple->Jets->at(q).Eta();
            jpt = ntuple->Jets->at(q).Pt();
            if(jpt>30 && abs(jeta)<=2.4){
                nj = ntuple->NJets;
            }
        }
        return nj;
    }
}

template<typename ntupleType> double fillCentralNJets(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -999.;
    else{
        int nj = 0.;
        double jeta = 0.0;
        double jpt = 0.0;
        for( int q = 0 ; q < ntuple->Jets->size() ; q++ ){
            jeta = ntuple->Jets->at(q).Eta();
            jpt = ntuple->Jets->at(q).Pt();
            if(abs(jeta)<=2.4 && jpt>30){
                nj++;
            }
        }
        return nj;
    }
}

template<typename ntupleType> double fillCentralNAK8Jets(ntupleType* ntuple){
    if( (ntuple->JetsAK8->size() == 0) && (ntuple->Jets->size() == 0)) return -999.;
    else{
        int nj = 0;
        double jeta = 0.0;
        for( int i = 0 ; i < ntuple->JetsAK8->size() ; i++ ){
            jeta = ntuple->JetsAK8->at(i).Eta();
            if(abs(jeta)<=2.4){
                nj++;
            }
        }
        return nj;
    }
}

template<typename ntupleType> double fillLeadingJetSDMass(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return -99999.;
  return ntuple->JetsAK8_softDropMass->at(0);
}

template<typename ntupleType> double fillLeadingJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8->at(0).Pt();
}

template<typename ntupleType> double fillLeadingJetEta(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8->at(0).Eta();
}

template<typename ntupleType> double fillLeadingJetNEMF(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8_neutralEmEnergyFraction->at(0);
}

template<typename ntupleType> double fillLeadingJetNHEF(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8_neutralHadronEnergyFraction->at(0);
}

template<typename ntupleType> double fillLeadingJetCHEF(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8_chargedHadronEnergyFraction->at(0);
}

template<typename ntupleType> double fillLeadingJetPhi(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8->at(0).Phi();
}

template<typename ntupleType> double fillLeadingTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
}

////////////////////////////////////////
// Graviton Mass Reconstruction  //
//////////////////////////////////////

double Gmass(double pt1, double eta1, double phi1, double mass1, double pt2, double eta2, double phi2, double mass2){
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pt1,eta1,phi1,mass1);
    v2.SetPtEtaPhiM(pt2,eta2,phi2,mass2);
    return (v1+v2).M();
}

template<typename ntupleType> double fillGMass(ntupleType* ntuple){
     if( ntuple->JetsAK8->size() == 0 ) return -99999.;
     double AK8Pt = ntuple->JetsAK8->at(0).Pt();
     double AK8Eta = ntuple->JetsAK8->at(0).Eta();
     double AK8Phi = ntuple->JetsAK8->at(0).Phi();
     double AK8Mass = ntuple->JetsAK8_prunedMass->at(0);
     double MET = ntuple->MET;
     double METEta = -AK8Eta;
     double METPhi = ntuple->METPhi;
     double ZMass = 91.0;
     return Gmass(AK8Pt, AK8Eta, AK8Phi, AK8Mass, MET, METEta, METPhi, ZMass);
}

/////////////////////////////////////////////
// Filters Cut //
/////////////////////////////////////////////

template<typename ntupleType> bool FiltersCut(ntupleType* ntuple){
    return (ntuple->HBHENoiseFilter==1 && 
            ntuple->HBHEIsoNoiseFilter==1 && 
            ntuple->eeBadScFilter==1 &&
            //ntuple->ecalBadCalibFilter==1 && //New 
            ntuple->EcalDeadCellTriggerPrimitiveFilter == 1 && 
            ntuple->NVtx>0 && 
            ntuple->MET/ntuple->CaloMET < 5. &&
            //ntuple->METUp->at(5)/ntuple->CaloMET < 5. &&
            //ntuple->PFCaloMETRatio < 5. &&
            ntuple->BadPFMuonFilter == 1 &&
            ntuple->BadChargedCandidateFilter == 1 &&
            ntuple->globalSuperTightHalo2016Filter==1 &&
            ntuple->JetID == 1
            );
}

// photon veto cut
template<typename ntupleType> bool PhotonCut(ntupleType* ntuple){
    int NumPhotons=0;
    for(unsigned p=0; p < ntuple->Photons->size(); ++p){
        if ((ntuple->Photons_hasPixelSeed->at(p)==0.) && (ntuple->Photons_fullID->at(p)) && (ntuple->Photons->at(p).Pt()>100)) ++NumPhotons;
    }
    return NumPhotons == 0;
}

template<typename ntupleType> bool MHTHTRatioCut(ntupleType* ntuple){
  return (ntuple->MHT/ntuple->HT)<=1.0 ; 
}

// to get event factor for MC samples to reduce HEM issue events.
template<typename ntupleType> double fillHEMTest1(ntupleType* ntuple){
    if( ntuple->Jets->size() == 0 ) return -9999.;
    double pt = ntuple->Jets->at(0).Pt();
    if( pt>30){
        double x = ntuple->Jets->at(0).Phi();
        int x1 = int(x*1000000);
        int x2 = x1%1000;
        return x2;
    }
    else 
        return -999.;
}

// HT Ratio Private
template<typename ntupleType> bool HTRatioCut(ntupleType* ntuple){
  double HT5 = ntuple->HT5/ntuple->HT;  
  //return ( (HT5<1.2) || (ntuple->DeltaPhi1 >= ((1.67*HT5)-1.67)));// 0% loss in sig 
  //return ( (HT5<1.2) || ((ntuple->DeltaPhi1) >= ((2.7*HT5)-2.17)));// 2.25% loss 
  //return ( (HT5<1.2) || ((ntuple->DeltaPhi1) >= ((3.6*HT5)-2.8)));// 6.7% loss 
  //return ( (HT5<1.2) || ((ntuple->DeltaPhi1) >= ((1.76*HT5)-1.64))); //0.1% 
  //return ( (HT5<1.3) || ((ntuple->DeltaPhi1) >= ((2.7*HT5)-1.64))); // 4.6% loss 
  //return ( (HT5<1.3) || ((ntuple->DeltaPhi1) >= ((3.5*HT5)-1.76))); 
  return ( (HT5<1.2) || ((fillDeltaPhi1(ntuple)) >= ((2.64*HT5)-2.64))); // 0.56% loss in sig 
  //return ( (HT5<1.2) || ((ntuple->DeltaPhi1) >= ((2.64*HT5)-2.64))); // 0.56% loss in sig 
}


template<typename ntupleType> bool HEMRunFilterCut(ntupleType* ntuple, bool MC_HEM=false){
  //if (MC_HEM) return ((fillHEMTest1(ntuple)<649) || ntuple->HEMDPhiVetoFilter==1);
  if (MC_HEM) return (ntuple->HEMDPhiVetoFilter==1);
  else
    return ((ntuple->RunNum < 319077) || (ntuple->HEMDPhiVetoFilter==1));   
}

/***********************************HEM veto  **********************************************/
 int StartHEM = 319077;
 bool isMC_, Run_number;
 double METPhi,JetPhi,DeltaPhi;

 bool passHEMjetVeto(RA2bTree* ntuple, double ptThresh = 30) {
    if (!isMC_ && ntuple->RunNum < StartHEM) return true;
    METPhi = ntuple->METPhi;

   for (int p = 0; p < ntuple->Jets->size(); p++){
       JetPhi = ntuple->Jets->at(p).Phi();
       DeltaPhi = CalcdPhi(JetPhi,METPhi);
       if (-3.2 <= ntuple->Jets->at(p).Eta() && ntuple->Jets->at(p).Eta() <= -1.2 &&
           -1.77 <= ntuple->Jets->at(p).Phi() && ntuple->Jets->at(p).Phi() <= -0.67 &&
           ntuple->Jets->at(p).Pt() > ptThresh && abs(DeltaPhi) < 0.5)
            return false;
    }
    return true;
};

template<typename ntupleType> bool DeltaPhi1Cut(ntupleType* ntuple){
  return fillDeltaPhi1(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhi2Cut(ntupleType* ntuple){
  return fillDeltaPhi2(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhi3Cut(ntupleType* ntuple){
  return fillDeltaPhi3(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhi4Cut(ntupleType* ntuple){
  return fillDeltaPhi4(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhiCuts(ntupleType* ntuple){
    return ( DeltaPhi1Cut(ntuple) &&
             DeltaPhi2Cut(ntuple) &&
             DeltaPhi3Cut(ntuple) &&
             DeltaPhi4Cut(ntuple) ) ;
}             

template<typename ntupleType> bool AK8JetPtCut(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;    
    return ( ntuple->JetsAK8->at(0).Pt() > 200.
           && fabs(ntuple->JetsAK8->at(0).Eta())<2.5
           && ntuple->JetsAK8_neutralEmEnergyFraction->at(0)<0.9 
           && ntuple->JetsAK8_chargedHadronEnergyFraction->at(0)>0.05 
         );
}

template<typename ntupleType> bool METCut(ntupleType* ntuple){
  return ( ntuple->MET > 200.);
  //return ( ntuple->METUp->at(5) > 200.);
}
template<typename ntupleType> bool DeltaPhiAK8JMETCut(ntupleType* ntuple){
  if( ntuple->JetsAK8->size() == 0 ) return false;    
  double DeltaPhiAK8JMET=CalcdPhi(ntuple->JetsAK8->at(0).Phi(), ntuple->METPhi);
  return DeltaPhiAK8JMET>2.0;
}

template<typename ntupleType> double fillDeltaPhiAK8JMET(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  double DeltaPhiAK8JMET=CalcdPhi(ntuple->JetsAK8->at(0).Phi(), ntuple->METPhi);
  return DeltaPhiAK8JMET;
}

template<typename ntupleType> bool ZMTCut(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
     double AK8Pt = ntuple->JetsAK8->at(0).Pt();
     double AK8Phi = ntuple->JetsAK8->at(0).Phi();
     double MET = ntuple->MET;
     double METPhi = ntuple->METPhi;
     double MT = ZMT(AK8Pt, AK8Phi, MET, METPhi);
     return (MT > 800.0 && MT<1200);
}

template<typename ntupleType> double fillZMT(ntupleType* ntuple){
     if(ntuple->JetsAK8->size()==0) return-99999.;
     double AK8Pt = ntuple->JetsAK8->at(0).Pt();
     double AK8Phi = ntuple->JetsAK8->at(0).Phi();
     double MET = ntuple->MET;
     //double MET = ntuple->METUp->at(5);
     double METPhi = ntuple->METPhi;
     return ZMT(AK8Pt, AK8Phi, MET, METPhi);
     //return sqrt( 2*AK8Pt*MET * ( 1 - cos( DeltaPhiAK8JMETCut(ntuple)) ) );
}

template<typename ntupleType> double fillMTpTRatio(ntupleType* ntuple){
     if(ntuple->JetsAK8->size()==0) return-99999.;
     double AK8Pt = ntuple->JetsAK8->at(0).Pt();
     double AK8Phi = ntuple->JetsAK8->at(0).Phi();
     double MET = ntuple->MET;
     double METPhi = ntuple->METPhi;
     double MT = ZMT(AK8Pt, AK8Phi, MET, METPhi);
     return (MT/AK8Pt);
}

template<typename ntupleType> double fillpTMTRatio(ntupleType* ntuple){
     if(ntuple->JetsAK8->size()==0) return-99999.;
     double AK8Pt = ntuple->JetsAK8->at(0).Pt();
     double AK8Phi = ntuple->JetsAK8->at(0).Phi();
     double MET = ntuple->MET;
     double METPhi = ntuple->METPhi;
     double MT = ZMT(AK8Pt, AK8Phi, MET, METPhi);
     return (AK8Pt/MT);
}

// DDT = tau21 + 0.082*log(m*m/pt)
template<typename ntupleType> double fillDDT(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -99999.;
    double tau21 = ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
    double m = AK8PUPPISoftdropCorrMass(ntuple);
    //double m = ntuple->JetsAK8_softDropMass->at(0);
    double m2 = m*m;
    double p = ntuple->JetsAK8->at(0).Pt(); 
  return (tau21+(0.082*log(m2/p)));
}

////////////////////////////
// Deep AK8 Discriminator //
///////////////////////////

template<typename ntupleType> double fillDeepAK8W(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -99999.;
    return (ntuple->JetsAK8_wDiscriminatorDeep->at(0));
}

template<typename ntupleType> double fillDeepAK8WDecorrel(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -99999.;
    return (ntuple->JetsAK8_wDiscriminatorDeepDecorrel->at(0));
}

template<typename ntupleType> double fillDeepAK8Z(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -99999.;
    return (ntuple->JetsAK8_zDiscriminatorDeep->at(0));
}

template<typename ntupleType> double fillDeepAK8ZDecorrel(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -99999.;
    return (ntuple->JetsAK8_zhDiscriminatorDeepDecorrel->at(0));
}

// For ECAL Eta Debug
template<typename ntupleType> bool EcalNEMFCut(ntupleType* ntuple){
     if(ntuple->Jets->size()==0) return false;
     for (unsigned int ij =0; ij<ntuple->Jets->size(); ij++){
         double eta = ntuple->Jets->at(ij).Eta();
         double pt = ntuple->Jets->at(ij).Pt();
         if ((pt<50.0) && ((fabs(eta)>=2.6) && fabs(eta)<=3.0)) return false;
     }
     return true;
 }

////////////////////////////////////////
// VBF JET   //
//////////////////////////////////////

// skip Z jets function
template<typename ntupleType> vector<TLorentzVector>  skipZjets(ntupleType* ntuple, int iJ=0){
    vector<TLorentzVector> skipZ_jets;
    if (ntuple->JetsAK8->size()<1 && ntuple->Jets->size()<2) return skipZ_jets; 
    for( unsigned int iak4 = 0 ; iak4 < ntuple->Jets->size() ; iak4++ ){
        if(!((ntuple->JetsAK8->at(iJ).DeltaR(ntuple->Jets->at(iak4)) < 0.8 ) && 
            (ntuple->JetsAK8->at(iJ).Pt()>200 && (ntuple->JetsAK8_NsubjettinessTau2->at(iJ)/ntuple->JetsAK8_NsubjettinessTau1->at(iJ)<0.75) &&
            AK8PUPPISoftdropCorrMass(ntuple) < 300 && AK8PUPPISoftdropCorrMass(ntuple) > 30
            //ntuple->JetsAK8_softDropMass->at(iJ)<300 && ntuple->JetsAK8_softDropMass->at(iJ)>30
            ))){
            skipZ_jets.push_back(TLorentzVector(ntuple->Jets->at(iak4)));
        }// end if block to make sure there is a valid Ztag
    }// end for loop over ak4 jets
   return skipZ_jets;
} 

template<typename ntupleType> vector<TLorentzVector>  cleanedVBFjets(ntupleType* ntuple, int iJ=0){
    vector<TLorentzVector> cleaned_jets=skipZjets(ntuple,iJ);
    vector<TLorentzVector> vj(2);
    vj[0].SetPtEtaPhiM(1.0,-99.,-99.,0.);
    vj[1].SetPtEtaPhiM(1.0,99.,99.,0.);

    int nj = cleaned_jets.size() ;
    if (nj<2) return vj;
    double MassMax = 0.0;
    for( unsigned int iak4 = 0 ; iak4 < nj; iak4++ ){
        if (cleaned_jets[iak4].Pt()<30) continue;
        for( unsigned int jak4 = iak4+1; jak4 < nj; jak4++ ){        
            if (cleaned_jets[jak4].Pt()<30) continue;
            TLorentzVector vjA, vjB;
            vjA.SetPtEtaPhiM(cleaned_jets[iak4].Pt(), cleaned_jets[iak4].Eta(), 
                             cleaned_jets[iak4].Phi(),cleaned_jets[iak4].M());
            vjB.SetPtEtaPhiM(cleaned_jets[jak4].Pt(), cleaned_jets[jak4].Eta(),
                             cleaned_jets[jak4].Phi(),cleaned_jets[jak4].M());
            double jetABMass = (vjA+vjB).M();                       
            if (jetABMass > MassMax){
                MassMax = jetABMass;
                vj[0] = vjA;
                vj[1] = vjB;
            }
        }// end for loop over jak4 jets
    }// end for loop over iak4 jets
  return vj;
} 

// for vbf j matched to ak4 j
template<typename ntupleType> vector<int> VBF_ak4indx(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    vector<int> indx(2); indx[0]=-9999; indx[1]=-9999;
    float dRak4vbf1 = 999999.;
    float dRak4vbf2 = 999999.;
    for( unsigned int nj = 0; nj < ntuple->Jets->size(); nj++ ){
        float dR = ntuple->Jets->at(nj).DeltaR(vbf_jets[0]);
        if (dRak4vbf1>dR) {
            indx[0]=nj;
           dRak4vbf1=dR;
        }
        dR = ntuple->Jets->at(nj).DeltaR(vbf_jets[1]);
        if (dRak4vbf2>dR) {
            indx[1]=nj;
           dRak4vbf2=dR;
        }
    }
   return (indx);
}

template<typename ntupleType> double fillVBF_j1NEMF(ntupleType* ntuple){
    vector<int> i = VBF_ak4indx(ntuple);
    if (i[0]>=0 && ntuple->Jets->at(i[0]).Pt() >30.0) 
        return  (ntuple->Jets_neutralEmEnergyFraction->at(i[0]));
    else
        return -9999.;
}
template<typename ntupleType> double fillVBF_j2NEMF(ntupleType* ntuple){
    vector<int> i = VBF_ak4indx(ntuple);
    if (i[1]>=0 && ntuple->Jets->at(i[1]).Pt() >30.0) 
        return  (ntuple->Jets_neutralEmEnergyFraction->at(i[1]));
    else
        return -9999.;
}

template<typename ntupleType> double fillVBF_j1NHEF(ntupleType* ntuple){
    vector<int> i = VBF_ak4indx(ntuple);
    if (i[0]>=0 && ntuple->Jets->at(i[0]).Pt() >30.0) 
        return  (ntuple->Jets_neutralHadronEnergyFraction->at(i[0]));
    else
        return -9999.;
}
template<typename ntupleType> double fillVBF_j2NHEF(ntupleType* ntuple){
    vector<int> i = VBF_ak4indx(ntuple);
    if (i[1]>=0 && ntuple->Jets->at(i[1]).Pt() >30.0) 
        return  (ntuple->Jets_neutralHadronEnergyFraction->at(i[1]));
    else
        return -9999.;
}

template<typename ntupleType> double fillVBF_j1CHEF(ntupleType* ntuple){
    vector<int> i = VBF_ak4indx(ntuple);
    if (i[0]>=0 && ntuple->Jets->at(i[0]).Pt() >30.0) 
        return  (ntuple->Jets_chargedHadronEnergyFraction->at(i[0]));
    else
        return -9999.;
}
template<typename ntupleType> double fillVBF_j2CHEF(ntupleType* ntuple){
    vector<int> i = VBF_ak4indx(ntuple);
    if (i[1]>=0 && ntuple->Jets->at(i[1]).Pt() >30.0) 
        return  (ntuple->Jets_chargedHadronEnergyFraction->at(i[1]));
    else
        return -9999.;
}

template<typename ntupleType> double fillVBF_Mjj(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
        TLorentzVector temp(vbf_jets[0]);
        temp+=vbf_jets[1];
    if (vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0) 
        return temp.M();
    else
        return 0.;
}

template<typename ntupleType> double fillVBF_Ptjj(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    TLorentzVector temp(vbf_jets[0]);
    temp+=vbf_jets[1];
    if (vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0) 
        return temp.Pt();
    else
        return -999.;
}

template<typename ntupleType> double fillVBF_dEta(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0) 
        return  fabs(vbf_jets[0].Eta()-vbf_jets[1].Eta());
    else
        return 0.;
}

template<typename ntupleType> double fillVBF_dPhi(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0) 
        return CalcdPhi(vbf_jets[0].Phi(), vbf_jets[1].Phi());
    else
        return -1.;
}

template<typename ntupleType> double fillVBF_j1Eta(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[0].Pt()>30.0) 
        return  vbf_jets[0].Eta();
    else
        return -999.;
}

template<typename ntupleType> double fillVBF_j2Eta(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[1].Pt()>30.0) 
        return  vbf_jets[1].Eta();
    else
        return -999.;
}

template<typename ntupleType> double fillVBF_j1Phi(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[0].Pt()>30.0) 
        return  vbf_jets[0].Phi();
    else
        return -999.;
}

template<typename ntupleType> double fillVBF_j2Phi(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[1].Pt()>30.0) 
        return  vbf_jets[1].Phi();
    else
        return -999.;
}
template<typename ntupleType> double fillVBF_j1j2Eta(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0) 
        return (vbf_jets[0].Eta()*vbf_jets[1].Eta());
    else
        return -999.;
}

template<typename ntupleType> double fillVBF_j1Pt(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[0].Pt()>30.0) 
        return  vbf_jets[0].Pt();
    else
        return -999.;
}

template<typename ntupleType> double fillVBF_j2Pt(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    if (vbf_jets[1].Pt()>30.0) 
        return  vbf_jets[1].Pt();
    else
        return -999.;
}

template<typename ntupleType> bool VBFCut(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    return ( fillVBF_dEta(ntuple)>4.0 &&
             fillVBF_Mjj(ntuple)>500.0 &&
             fillVBF_j1j2Eta(ntuple)<0 &&
             vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0);
}             

template<typename ntupleType> bool LooseVBFCut(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    return ( fillVBF_dEta(ntuple)>3.0 &&
             fillVBF_Mjj(ntuple)>300.0 &&
             fillVBF_j1j2Eta(ntuple)<0 &&
             vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0);
}

template<typename ntupleType> bool VBFFailCut(ntupleType* ntuple){
    return !VBFCut(ntuple);
}

template<typename ntupleType> bool LooseVBFFailCut(ntupleType* ntuple){
    return !LooseVBFCut(ntuple);
}

template<typename ntupleType> bool VBFdEtaDebugCuts(ntupleType* ntuple){
    vector<TLorentzVector> vbf_jets = cleanedVBFjets(ntuple,0);
    return ( fillVBF_dEta(ntuple)>=5.0 &&
             fillVBF_dEta(ntuple)<=6.0 &&
             vbf_jets[0].Pt()>30.0 && vbf_jets[1].Pt()>30.0);
}             

// End of VBF JET   //

template<typename ntupleType> bool AK8JetSideBandCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
    //double mJ = ntuple->JetsAK8_softDropMass->at(0);
    double mJ = AK8PUPPISoftdropCorrMass(ntuple);
    return ( ( mJ > 30. && mJ < 65.) || ( mJ > 135. && mJ < 300.) );
}

template<typename ntupleType> bool AlphaSideBandCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
    //double mJ = ntuple->JetsAK8_softDropMass->at(0);
    double mJ = AK8PUPPISoftdropCorrMass(ntuple);
    //return ( (mJ > 30. && mJ < 55.) || (mJ > 135. && mJ < 150.));
    return ( (mJ > 30. && mJ < 55.) || (mJ > 135. && mJ < 300.));
}

template<typename ntupleType> bool AlphaSRCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
    //double mJ = ntuple->JetsAK8_softDropMass->at(0);
    double mJ = AK8PUPPISoftdropCorrMass(ntuple);
    return (mJ > 55. && mJ < 65.);
}

template<typename ntupleType> bool AK8JetSRCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
    //double mJ = ntuple->JetsAK8_softDropMass->at(0);
    double mJ = AK8PUPPISoftdropCorrMass(ntuple);
    return (  mJ > 65. && mJ < 105.);
}

template<typename ntupleType> bool LowTau21DebugCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
  return (
         (ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0))<0.15
         );
}


template<typename ntupleType> bool FullPurityCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
  return (
         (ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0))<0.75
         );
}
/*
template<typename ntupleType> bool HighPurityCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
  return (
         (ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0))<0.35
         );
}
*/
template<typename ntupleType> bool HighPurityCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
    double tau21 = (ntuple->JetsAK8_NsubjettinessTau2->at(0))/(ntuple->JetsAK8_NsubjettinessTau1->at(0));
    //if (year == "2017") return (tau21 < 0.45);
    //else return (tau21 < 0.35);
    return (tau21 < 0.35);
}

template<typename ntupleType> bool LowPurityCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
    double tau21 = (ntuple->JetsAK8_NsubjettinessTau2->at(0))/(ntuple->JetsAK8_NsubjettinessTau1->at(0));
    if (year == "2017") return (tau21 > 0.45 && tau21 < 0.75);
    else return (tau21 > 0.35 && tau21 < 0.75);
}

/*
template<typename ntupleType> bool LowPurityCut(ntupleType* ntuple){
    if(ntuple->JetsAK8->size()==0) return false;
  return (
         (ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0))>0.35 &&
         (ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0))<0.75
        );} */

// Extra selection for debugging
  
template<typename ntupleType> bool DebugCut(ntupleType* ntuple ){
  return (   genWpmatched(ntuple) //for Wp signal
             //genZmatched(ntuple) // for G and Rad to ZZ signal
             //ZMTCut(ntuple)
             //VBFdEtaDebugCuts(ntuple)
             //EcalNEMFCut(ntuple)
         ); 
}

// 1) Baseline selection without VBF cut
template<typename ntupleType> bool baselineCut(ntupleType* ntuple){
  return (  METCut(ntuple) 
	        && AK8JetPtCut(ntuple) 
            &&  DeltaPhiCuts(ntuple) 
            &&  PhotonCut(ntuple) // photon veto
            &&  ntuple->NMuons==0 
            &&  ntuple->NElectrons==0 
            &&  ntuple->BTagsDeepCSV==0 
            &&  ntuple->isoElectronTracks==0 && ntuple->isoMuonTracks==0 && ntuple->isoPionTracks==0 
            &&  HTRatioCut(ntuple)
	        &&  FiltersCut(ntuple)
            //&&  DebugCut(ntuple) //for Wp signal
         );
}
    
// 2) SR Baseline i.e. Puppi SD Mass [65,105] GeV  
template<typename ntupleType> bool ZSRCut(ntupleType* ntuple ){
  return (baselineCut(ntuple) && 
          AK8JetSRCut(ntuple)); 
}

// 3) Baseline + Z SR+ HP without  VBF cut 
template<typename ntupleType> bool ZSRHPCut(ntupleType* ntuple){
  return (  ZSRCut(ntuple) && 
            HighPurityCut(ntuple));
}

// 6) Baseline + Z SR + HP + VBF cut 
template<typename ntupleType> bool ZSRHPVBFCut(ntupleType* ntuple){
  return ( ZSRHPCut(ntuple) && 
           VBFCut(ntuple));
}

// 7) Baseline + Z SR + HP + failVBF cut 
template<typename ntupleType> bool ZSRHPVBFfailCut(ntupleType* ntuple){
  return ( ZSRHPCut(ntuple) && 
           VBFFailCut(ntuple));
}

// 7) Baseline + Z SR+ FP 
template<typename ntupleType> bool ZSRFPCut(ntupleType* ntuple){
  return (  ZSRCut(ntuple) && 
            FullPurityCut(ntuple));
}

// 8) Baseline + Z SR + FP + VBF cut 
template<typename ntupleType> bool ZSRFPVBFCut(ntupleType* ntuple){
  return ( ZSRFPCut(ntuple) &&
           VBFCut(ntuple));
}

// 9) Baseline + Z SR + FP + failVBF cut 
template<typename ntupleType> bool ZSRFPVBFfailCut(ntupleType* ntuple){
  return ( ZSRFPCut(ntuple) &&
           VBFFailCut(ntuple));
}

// 8A) Baseline + Z SR + HP + LooseVBF cut 
template<typename ntupleType> bool ZSRHPLooseVBFCut(ntupleType* ntuple){
  return ( ZSRHPCut(ntuple) &&
           LooseVBFCut(ntuple));
}

// 9A) Baseline + Z SR + HP + failLooseVBF cut 
template<typename ntupleType> bool ZSRHPLooseVBFfailCut(ntupleType* ntuple){
  return ( ZSRHPCut(ntuple) &&
           LooseVBFFailCut(ntuple));
}

// 8AA) Baseline + Z SR + FP + LooseVBF cut 
template<typename ntupleType> bool ZSRFPLooseVBFCut(ntupleType* ntuple){
  return ( ZSRFPCut(ntuple) &&
           LooseVBFCut(ntuple));
}

// 9AA) Baseline + Z SR + FP + failLooseVBF cut 
template<typename ntupleType> bool ZSRFPLooseVBFfailCut(ntupleType* ntuple){
  return ( ZSRFPCut(ntuple) &&
           LooseVBFFailCut(ntuple));
}

// ###### Side Band ##############

// 10) Z side band baseline selection ([30,65][>135,300])
template<typename ntupleType> bool ZSBCut(ntupleType* ntuple){
  return ( baselineCut(ntuple) &&
           AK8JetSideBandCut(ntuple) ); 
}

// Z side band HP(tau21<0.35) selection
// https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging#2016_scale_factors_and_correctio

// 11) Z sideband high purity
template<typename ntupleType> bool ZSBHPCut(ntupleType* ntuple){
  return (ZSBCut(ntuple) &&
          HighPurityCut(ntuple));            
}

// 12) Z sideband High purity with VBF cut
template<typename ntupleType> bool ZSBHPVBFCut(ntupleType* ntuple){
  return ( ZSBHPCut(ntuple) && 
           VBFCut(ntuple));
}

// 13) Z sideband High purity with VBFfail cut
template<typename ntupleType> bool ZSBHPVBFfailCut(ntupleType* ntuple){
  return ( ZSBHPCut(ntuple) && 
           VBFFailCut(ntuple));
}

// 14) Baseline + Z SB+ FP 
template<typename ntupleType> bool ZSBFPCut(ntupleType* ntuple){
  return (  ZSBCut(ntuple) && 
            FullPurityCut(ntuple));
}

// 15) Baseline + Z SB + FP + VBF cut 
template<typename ntupleType> bool ZSBFPVBFCut(ntupleType* ntuple){
  return ( ZSBFPCut(ntuple) &&
           VBFCut(ntuple));
}

// 16) Baseline + Z SB + FP + failVBF cut 
template<typename ntupleType> bool ZSBFPVBFfailCut(ntupleType* ntuple){
  return ( ZSBFPCut(ntuple) &&
           VBFFailCut(ntuple));
}

// 15A) Baseline + Z SB + HP + LooseVBF cut 
template<typename ntupleType> bool ZSBHPLooseVBFCut(ntupleType* ntuple){
  return ( ZSBHPCut(ntuple) &&
           LooseVBFCut(ntuple));
}

// 16A) Baseline + Z SB + HP + failLooseVBF cut 
template<typename ntupleType> bool ZSBHPLooseVBFfailCut(ntupleType* ntuple){
  return ( ZSBHPCut(ntuple) &&
           LooseVBFFailCut(ntuple));
}

// 15AA) Baseline + Z SB + FP + LooseVBF cut 
template<typename ntupleType> bool ZSBFPLooseVBFCut(ntupleType* ntuple){
  return ( ZSBFPCut(ntuple) &&
           LooseVBFCut(ntuple));
}

// 16AA) Baseline + Z SB + FP + failLooseVBF cut 
template<typename ntupleType> bool ZSBFPLooseVBFfailCut(ntupleType* ntuple){
  return ( ZSBFPCut(ntuple) &&
           LooseVBFFailCut(ntuple));
}


//############################################
// ######## Alpha Closure test Part ################
//############################################

template<typename ntupleType> bool ZAlphaSBCut(ntupleType* ntuple){
  return ( baselineCut(ntuple) &&
          AlphaSideBandCut(ntuple));
}

template<typename ntupleType> bool ZAlphaSRCut(ntupleType* ntuple){
  return ( baselineCut(ntuple) &&
          AlphaSRCut(ntuple) );
}

template<typename ntupleType> bool ZAlphaSBHPVBFCut(ntupleType* ntuple){
  return ( ZAlphaSBCut(ntuple) &&
          HighPurityCut(ntuple) &&
          VBFCut(ntuple));            
}

template<typename ntupleType> bool ZAlphaSBHPVBFfailCut(ntupleType* ntuple){
  return ( ZAlphaSBCut(ntuple) &&
          HighPurityCut(ntuple) &&
          VBFFailCut(ntuple));            
}

template<typename ntupleType> bool ZAlphaSBFPVBFCut(ntupleType* ntuple){
  return ( ZAlphaSBCut(ntuple) &&
          FullPurityCut(ntuple) &&
          VBFCut(ntuple));            
}

template<typename ntupleType> bool ZAlphaSBFPVBFfailCut(ntupleType* ntuple){
  return ( ZAlphaSBCut(ntuple) &&
          FullPurityCut(ntuple) &&
          VBFFailCut(ntuple));            
}

template<typename ntupleType> bool ZAlphaSBHPLooseVBFCut(ntupleType* ntuple){
  return ( ZAlphaSBCut(ntuple) &&
          HighPurityCut(ntuple) &&
          LooseVBFCut(ntuple));            
}

template<typename ntupleType> bool ZAlphaSBHPLooseVBFfailCut(ntupleType* ntuple){
  return ( ZAlphaSBCut(ntuple) &&
          HighPurityCut(ntuple) &&
          LooseVBFFailCut(ntuple));            
}

template<typename ntupleType> bool ZAlphaSRHPVBFCut(ntupleType* ntuple){
  return ( ZAlphaSRCut(ntuple) &&
          HighPurityCut(ntuple) &&
          VBFCut(ntuple));
}

template<typename ntupleType> bool ZAlphaSRHPVBFfailCut(ntupleType* ntuple){
  return ( ZAlphaSRCut(ntuple) &&
          HighPurityCut(ntuple) &&
          VBFFailCut(ntuple));
}

template<typename ntupleType> bool ZAlphaSRFPVBFCut(ntupleType* ntuple){
  return ( ZAlphaSRCut(ntuple) &&
          FullPurityCut(ntuple) &&
          VBFCut(ntuple));
}

template<typename ntupleType> bool ZAlphaSRFPVBFfailCut(ntupleType* ntuple){
  return ( ZAlphaSRCut(ntuple) &&
          FullPurityCut(ntuple) &&
          VBFFailCut(ntuple));
}

template<typename ntupleType> bool ZAlphaSRHPLooseVBFCut(ntupleType* ntuple){
  return ( ZAlphaSRCut(ntuple) &&
          HighPurityCut(ntuple) &&
          LooseVBFCut(ntuple));
}

template<typename ntupleType> bool ZAlphaSRHPLooseVBFfailCut(ntupleType* ntuple){
  return ( ZAlphaSRCut(ntuple) &&
          HighPurityCut(ntuple) &&
          LooseVBFFailCut(ntuple));
}

// end of Alhpha Closure part


/////////////////////////////////////////////////
// - - - - - - - Trigger Cuts - - - - - - - -  //
/////////////////////////////////////////////////
template<typename ntupleType> bool signalTriggerCut(ntupleType* ntuple){
    return (ntuple->TriggerPass->at(110) == 1 || ntuple->TriggerPass->at(112) == 1 || 
           ntuple->TriggerPass->at(116) == 1 || ntuple->TriggerPass->at(118) == 1 || 
           ntuple->TriggerPass->at(120) == 1 || ntuple->TriggerPass->at(124) == 1 
           /* // below are METNoMU triggers 
           || ntuple->TriggerPass->at(126) == 1 || ntuple->TriggerPass->at(128) == 1 || 
           ntuple->TriggerPass->at(131) == 1 || ntuple->TriggerPass->at(133) == 1 || 
           ntuple->TriggerPass->at(135) == 1 || ntuple->TriggerPass->at(136) == 1 
           */ ); 

}
