#include "TChain.h"
#include "RA2bTree.cc"
#include "TString.h"

#include <iostream>
#include <vector>
#include <map>

static const TString BASE_DIR_DATA = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims/Run2ProductionV17/";
static const TString BASE_DIR = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims_TTU_Jul19/Run2ProductionV17/";
static const TString BASE_DIR_SIG = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims_TTU_Jul19/Run2ProductionV17/Sig_Samples/";
//static const TString BASE_DIR_SIG = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims/Run2ProductionV17/VBF_NoSkim";
static const bool RE_MINIAOD = false;

class skimSamples{

public :

    enum region {kSignal,kLDP,kPhoton,kPhotonLoose,kPhotonLDP,kPhotonLDPLoose,kDYe,kDYm,kDYeLDP,kDYmLDP,kNumRegions};
    TString regionNames[kNumRegions]={"signal","LDP","photon","photonLoose","photonLDP","photonLDPLoose","DYe","DYm","DYeLDP","DYmLDP"};  
  
    map<TString,TString> fileNames;

    std::vector<RA2bTree*> ntuples,signalNtuples;
    std::vector<RA2bTree*> dataNtuple;
    std::vector<TString> sampleName, signalSampleName;
    std::vector<TString> dataSampleName;

    TString skimType;
   
    skimSamples(region r, vector<TString> backgrounds, vector<TString> signals, vector<TString> datas){

        skimType="";
        if( r == kSignal )
            skimType="tree_signal/";
        if( r == kLDP )
            skimType="tree_LDP/";
        if( r == kPhoton )
            skimType="tree_GJet_CleanVars/";
	if( r == kPhotonLDP )
            skimType="tree_GJetLDP_CleanVars/";
        if( r == kPhotonLoose )
            skimType="tree_GJetLoose_CleanVars/";
        if( r == kPhotonLDPLoose )
            skimType="tree_GJetLooseLDP_CleanVars/";
        if( r == kDYm )
            skimType="tree_DYm_CleanVars";
        if( r == kDYmLDP )
            skimType="tree_DYmLDP_CleanVars";
        if( r == kDYe )
            skimType="tree_DYe_CleanVars";
        if( r == kDYeLDP )
            skimType="tree_DYeLDP_CleanVars";

        ///////////////////////////////////////////////////////////////////////
        // - - - - - - - - - - BACKGROUND INPUTS - - - - - - - - - - - - - - //
        ///////////////////////////////////////////////////////////////////////

        fileNames["ZJets_100to200"]   = "tree_ZJetsToNuNu_HT-100to200_MC2016.root";
        fileNames["ZJets_200to400"]   = "tree_ZJetsToNuNu_HT-200to400_MC2016.root";
        fileNames["ZJets_400to600"]   = "tree_ZJetsToNuNu_HT-400to600_MC2016.root";
        fileNames["ZJets_600to800"]   = "tree_ZJetsToNuNu_HT-600to800_MC2016.root";
        fileNames["ZJets_800to1200"]  = "tree_ZJetsToNuNu_HT-800to1200_MC2016.root";
        fileNames["ZJets_1200to2500"] = "tree_ZJetsToNuNu_HT-1200to2500_MC2016.root";
        fileNames["ZJets_2500toInf"]  = "tree_ZJetsToNuNu_HT-2500toInf_MC2016.root";

        fileNames["WJets_100to200"]   = "tree_WJetsToLNu_HT-100to200_MC2016.root";
        fileNames["WJets_200to400"]   = "tree_WJetsToLNu_HT-200to400_MC2016.root";
        fileNames["WJets_400to600"]   = "tree_WJetsToLNu_HT-400to600_MC2016.root";
        fileNames["WJets_600to800"]   = "tree_WJetsToLNu_HT-600to800_MC2016.root";
        fileNames["WJets_800to1200"]  = "tree_WJetsToLNu_HT-800to1200_MC2016.root";
        fileNames["WJets_1200to2500"] = "tree_WJetsToLNu_HT-1200to2500_MC2016.root";
        fileNames["WJets_2500toInf"]  = "tree_WJetsToLNu_HT-2500toInf_MC2016.root";

        fileNames["TT_600to800"] = "tree_TTJets_HT-600to800_MC2016.root";
        fileNames["TT_800to1200"] = "tree_TTJets_HT-800to1200_MC2016.root";
        fileNames["TT_1200to2500"] = "tree_TTJets_HT-1200to2500_MC2016.root";
        fileNames["TT_2500toInf"] = "tree_TTJets_HT-2500toInf_MC2016.root";
        fileNames["TT_1LFromT"] = "tree_TTJets_SingleLeptFromT_MC2016.root";
        fileNames["TT_1LFromTbar"] = "tree_TTJets_SingleLeptFromTbar_MC2016.root";
        fileNames["TT_2L"] = "tree_TTJets_DiLept_MC2016.root";
        // KL added the last 3 in TT section: tree_TTJets_SingleLeptFromT_MC2017.root, 
        // tree_TTJets_SingleLeptFromTbar_MC2017.root & tree_TTJets_DiLept_MC2017.root

	    fileNames["ST_s-channel"] = "tree_ST_s-channel_MC2016.root";
	    fileNames["ST_t-channel_antitop"] = "tree_ST_t-channel_antitop_MC2016.root";
	    fileNames["ST_t-channel_top"] = "tree_ST_t-channel_top_MC2016.root";
	    fileNames["ST_tW_antitop"] = "tree_ST_tW_antitop_MC2016.root";
	    fileNames["ST_tW_top"] = "tree_ST_tW_top_MC2016.root";

        fileNames["Other_WWTo1L1Nu2Q"] = "tree_WWTo1L1Nu2Q_MC2016.root";
        //fileNames["Other_WWTo2L2Nu"] = "tree_WWTo2L2Nu_MC2016.root"; //n/a for all years
        fileNames["Other_WWZ"] = "tree_WWZ_MC2016.root"; //for 2016 only
        fileNames["Other_WZTo1L1Nu2Q"] = "tree_WZTo1L1Nu2Q_MC2016.root"; // for 16 n 17
        fileNames["Other_WZTo1L3Nu"] = "tree_WZTo1L3Nu_MC2016.root";
        fileNames["Other_WZZ"] = "tree_WZZ_MC2016.root"; // for 16 n 17
        fileNames["Other_ZZTo2L2Q"] = "tree_ZZTo2L2Q_MC2016.root";
        fileNames["Other_ZZTo2Q2Nu"] = "tree_ZZTo2Q2Nu_MC2016.root"; // for 2016 only
        fileNames["Other_ZZZ"] = "tree_ZZZ_MC2016.root"; // for 16 n 17
        fileNames["Other_TTTT"] = "tree_TTTT_MC2016.root"; // for 16 n 17
        fileNames["Other_TTWJetsToLNu"] = "tree_TTWJetsToLNu_MC2016.root";
        fileNames["Other_TTWJetsToQQ"] = "tree_TTWJetsToQQ_MC2016.root";
        fileNames["Other_TTGJets"] = "tree_TTGJets_MC2016.root";
        fileNames["Other_TTZToLLNuNu"] = "tree_TTZToLLNuNu_MC2016.root";
        fileNames["Other_TTZToQQ"] = "tree_TTZToQQ_MC2016.root";
      
        fileNames["MET_2016B"] = "tree_MET_2016B.root";
        fileNames["MET_2016C"] = "tree_MET_2016C.root";
        fileNames["MET_2016D"] = "tree_MET_2016D.root";
        fileNames["MET_2016E"] = "tree_MET_2016E.root";
        fileNames["MET_2016F"] = "tree_MET_2016F.root";
        fileNames["MET_2016G"] = "tree_MET_2016G.root";
        fileNames["MET_2016H"] = "tree_MET_2016H.root";

        fileNames["VBFG_1000"] = "tree_VBFG_mG1000_v3_MC2016.root";
        fileNames["VBFG_2000"] = "tree_VBFG_mG2000_v15_MC2018.root";
        fileNames["VBFG_1200"] = "tree_VBFG_mG1200_v15_MC2018.root";
        fileNames["VBFG_1400"] = "tree_VBFG_mG1400_v15_MC2018.root";
        fileNames["VBFG_1600"] = "tree_VBFG_mG1600_v15_MC2018.root";
        fileNames["VBFG_1800"] = "tree_VBFG_mG1800_v15_MC2018.root";
        fileNames["VBFG_2500"] = "tree_VBFG_mG2500_v15_MC2018.root";
        fileNames["VBFG_3000"] = "tree_VBFG_mG3000_v15_MC2018.root";
        fileNames["VBFG_3500"] = "tree_VBFG_mG3500_v15_MC2018.root";
        fileNames["VBFG_4000"] = "tree_VBFG_mG4000_v15_MC2018.root";
        fileNames["VBFG_4500"] = "tree_VBFG_mG4500_v15_MC2018.root";

        fileNames["VBFRad_1000"] = "tree_VBFRad_mRad1000_v15_MC2018.root";
        fileNames["VBFRad_4500"] = "tree_VBFRad_mRad4500_v15_MC2018.root";

        fileNames["VBFWp_1000"] = "tree_VBFWp_mWp1000_v3_MC2016.root";
        fileNames["VBFWp_4500"] = "tree_VBFWp_mWp4500_v15_MC2018.root";

        fileNames["ggFRad_1000"] = "tree_ggFRad_mRad1000_v15_MC2018.root";
        fileNames["ggFRad_4500"] = "tree_ggFRad_mRad4500_v15_MC2018.root";


        fileNames["ggFG_1000"] = "tree_ggFG_mG1000_v14_MC2017.root";
        fileNames["ggFG_2000"] = "tree_ggFG_mG2000_v14_MC2017.root";
        fileNames["ggFG_1200"] = "tree_ggFG_mG1200_v14_MC2017.root";
        fileNames["ggFG_1400"] = "tree_ggFG_mG1400_v14_MC2017.root";
        fileNames["ggFG_1600"] = "tree_ggFG_mG1600_v14_MC2017.root";
        fileNames["ggFG_1800"] = "tree_ggFG_mG1800_v14_MC2017.root";
        fileNames["ggFG_2500"] = "tree_ggFG_mG2500_v14_MC2017.root";
        fileNames["ggFG_3000"] = "tree_ggFG_mG3000_v14_MC2017.root"; 
        fileNames["ggFG_3500"] = "tree_ggFG_mG3500_v14_MC2017.root";
        fileNames["ggFG_4000"] = "tree_ggFG_mG4000_v14_MC2017.root";
        fileNames["ggFG_4500"] = "tree_ggFG_mG4500_v14_MC2017.root";

	for( auto name : backgrounds ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    //temp->Add(BASE_DIR_DATA+skimType+"/"+fileNames[name]);	  
	    ntuples.push_back(new RA2bTree(temp));
	    sampleName.push_back(name);
	  }

	}	    

	for( auto name : signals ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    //TChain* temp = new TChain("TreeMaker2/PreSelection");
	    //temp->Add(BASE_DIR_SIG+skimType+"/"+fileNames[name]);	  
	    temp->Add(BASE_DIR_SIG+"/"+fileNames[name]);	  
	    //temp->Add(BASE_DIR_DATA+skimType+"/"+fileNames[name]);	  
	    signalNtuples.push_back(new RA2bTree(temp));
	    signalSampleName.push_back(name);
	  }

	}	    

	for( auto name : datas ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    //temp->Add(BASE_DIR_DATA+skimType+"/"+fileNames[name]);	  
	    dataNtuple.push_back(new RA2bTree(temp));
	    dataSampleName.push_back(name);
	  }

	}	    
       
    };

    void dumpRegions(){
        cout << "index  name" << endl;
        for( int iReg = 0 ; iReg < kNumRegions ; iReg++ ){
            cout << iReg << "      " << regionNames[iReg] << endl;
        }
    };

    RA2bTree* findNtuple(TString name){
        for( int iSam = 0 ; iSam < sampleName.size() ; iSam++ ){
            if( sampleName[iSam] == name )
                return ntuples[iSam] ;
        }
        for( int iSam = 0 ; iSam < signalSampleName.size() ; iSam++ ){
            if( signalSampleName[iSam] == name )
                return signalNtuples[iSam] ;
        }
        return NULL;
    };

};
