#include "TChain.h"
#include "RA2bTree.cc"
#include "TString.h"

#include <iostream>
#include <vector>
#include <map>

static const TString BASE_DIR_DATA = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims/Run2ProductionV17/";
static const TString BASE_DIR = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims_TTU_Jul19/Run2ProductionV17/";
static const TString BASE_DIR_SIG = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims_TTU_Jul19/Run2ProductionV17/Sig_Samples/";
//static const TString BASE_DIR_SIG = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims/Run2ProductionV16/VBF_G_V2/";
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

        fileNames["ZJets_100to200"]   = "tree_ZJetsToNuNu_HT-100to200_MC2017.root";
        fileNames["ZJets_200to400"]   = "tree_ZJetsToNuNu_HT-200to400_MC2017.root";
        fileNames["ZJets_400to600"]   = "tree_ZJetsToNuNu_HT-400to600_MC2017.root";
        fileNames["ZJets_600to800"]   = "tree_ZJetsToNuNu_HT-600to800_MC2017.root";
        fileNames["ZJets_800to1200"]  = "tree_ZJetsToNuNu_HT-800to1200_MC2017.root";
        fileNames["ZJets_1200to2500"] = "tree_ZJetsToNuNu_HT-1200to2500_MC2017.root";
        fileNames["ZJets_2500toInf"]  = "tree_ZJetsToNuNu_HT-2500toInf_MC2017.root";


        fileNames["WJets_100to200"]   = "tree_WJetsToLNu_HT-100to200_MC2017.root";
        fileNames["WJets_200to400"]   = "tree_WJetsToLNu_HT-200to400_MC2017.root";
        fileNames["WJets_400to600"]   = "tree_WJetsToLNu_HT-400to600_MC2017.root";
        fileNames["WJets_600to800"]   = "tree_WJetsToLNu_HT-600to800_MC2017.root";
        fileNames["WJets_800to1200"]  = "tree_WJetsToLNu_HT-800to1200_MC2017.root";
        fileNames["WJets_1200to2500"] = "tree_WJetsToLNu_HT-1200to2500_MC2017.root";
        fileNames["WJets_2500toInf"]  = "tree_WJetsToLNu_HT-2500toInf_MC2017.root";

        fileNames["TT_600to800"] = "tree_TTJets_HT-600to800_MC2017.root";
        fileNames["TT_800to1200"] = "tree_TTJets_HT-800to1200_MC2017.root";
        fileNames["TT_1200to2500"] = "tree_TTJets_HT-1200to2500_MC2017.root";
        fileNames["TT_2500toInf"] = "tree_TTJets_HT-2500toInf_MC2017.root";
        fileNames["TT_1LFromT"] = "tree_TTJets_SingleLeptFromT_MC2017.root";
        fileNames["TT_1LFromTbar"] = "tree_TTJets_SingleLeptFromTbar_MC2017.root";
        fileNames["TT_2L"] = "tree_TTJets_DiLept_MC2017.root";
        // KL added the last 3 in TT section: tree_TTJets_SingleLeptFromT_MC2017.root, 
        // tree_TTJets_SingleLeptFromTbar_MC2017.root & tree_TTJets_DiLept_MC2017.root

	    fileNames["ST_s-channel"] = "tree_ST_s-channel_MC2017.root";
	    fileNames["ST_t-channel_antitop"] = "tree_ST_t-channel_antitop_MC2017.root";
	    fileNames["ST_t-channel_top"] = "tree_ST_t-channel_top_MC2017.root";
	    fileNames["ST_tW_antitop"] = "tree_ST_tW_antitop_MC2017.root";
	    fileNames["ST_tW_top"] = "tree_ST_tW_top_MC2017.root";


        fileNames["Other_WWTo1L1Nu2Q"] = "tree_WWTo1L1Nu2Q_MC2017.root";
        //fileNames["Other_WWTo2L2Nu"] = "tree_WWTo2L2Nu_MC2017.root"; //n/a for all years
        fileNames["Other_WWZ"] = "tree_WWZ_MC2017.root"; //using 2016 sample
        fileNames["Other_WZTo1L1Nu2Q"] = "tree_WZTo1L1Nu2Q_MC2017.root"; // for 16 n 17
        fileNames["Other_WZTo1L3Nu"] = "tree_WZTo1L3Nu_MC2017.root";
        fileNames["Other_WZZ"] = "tree_WZZ_MC2017.root"; // for 16 n 17
        fileNames["Other_ZZTo2L2Q"] = "tree_ZZTo2L2Q_MC2017.root";
        fileNames["Other_ZZTo2Q2Nu"] = "tree_ZZTo2Q2Nu_MC2017.root"; // using 2016 sample
        fileNames["Other_ZZZ"] = "tree_ZZZ_MC2017.root"; // for 16 n 17
        fileNames["Other_TTTT"] = "tree_TTTT_MC2017.root"; // for 16 n 17
        fileNames["Other_TTWJetsToLNu"] = "tree_TTWJetsToLNu_MC2017.root";
        fileNames["Other_TTWJetsToQQ"] = "tree_TTWJetsToQQ_MC2017.root";
        fileNames["Other_TTGJets"] = "tree_TTGJets_MC2017.root";
        fileNames["Other_TTZToLLNuNu"] = "tree_TTZToLLNuNu_MC2017.root";
        fileNames["Other_TTZToQQ"] = "tree_TTZToQQ_MC2017.root";
      
	    fileNames["MET_2017B"] = "tree_MET_2017B.root";
	    fileNames["MET_2017C"] = "tree_MET_2017C.root";
        fileNames["MET_2017D"] = "tree_MET_2017D.root";
        fileNames["MET_2017E"] = "tree_MET_2017E.root";
        fileNames["MET_2017F"] = "tree_MET_2017F.root";

        //fileNames["VBFG_1000"] = "tree_VBF_ZZ_mG1000.root";
        fileNames["VBFG_800_MC2017"] = "tree_VBFG_mG800_v14_MC2017.root";
        fileNames["VBFG_1000_MC2017"] = "tree_VBFG_mG1000_v14_MC2017.root";
        fileNames["VBFG_1200_MC2017"] = "tree_VBFG_mG1200_v14_MC2017.root";
        fileNames["VBFG_1400_MC2017"] = "tree_VBFG_mG1400_v14_MC2017.root";
        fileNames["VBFG_1600_MC2017"] = "tree_VBFG_mG1600_v14_MC2017.root";
        fileNames["VBFG_1800_MC2017"] = "tree_VBFG_mG1800_v14_MC2017.root";
        fileNames["VBFG_2000_MC2017"] = "tree_VBFG_mG2000_v14_MC2017.root";
        fileNames["VBFG_2500_MC2017"] = "tree_VBFG_mG2500_v14_MC2017.root";
        fileNames["VBFG_3000_MC2017"] = "tree_VBFG_mG3000_v14_MC2017.root";
        fileNames["VBFG_3500_MC2017"] = "tree_VBFG_mG3500_v14_MC2017.root";
        fileNames["VBFG_4000_MC2017"] = "tree_VBFG_mG4000_v14_MC2017.root";
        fileNames["VBFG_4500_MC2017"] = "tree_VBFG_mG4500_v14_MC2017.root";
        fileNames["VBFG_5000_MC2017"] = "tree_VBFG_mG5000_v14_MC2017.root";
        fileNames["VBFG_5500_MC2017"] = "tree_VBFG_mG5500_v14_MC2017.root";
        fileNames["VBFG_6000_MC2017"] = "tree_VBFG_mG6000_v14_MC2017.root";
        fileNames["VBFG_6500_MC2017"] = "tree_VBFG_mG6500_v14_MC2017.root";
        fileNames["VBFG_7000_MC2017"] = "tree_VBFG_mG7000_v14_MC2017.root";
        fileNames["VBFG_7500_MC2017"] = "tree_VBFG_mG7500_v14_MC2017.root";
        fileNames["VBFG_8000_MC2017"] = "tree_VBFG_mG8000_v14_MC2017.root";

        fileNames["VBFRad_800_MC2017"] = "tree_VBFRad_mRad800_v14_MC2017.root";
        fileNames["VBFRad_1000_MC2017"] = "tree_VBFRad_mRad1000_v14_MC2017.root";
        fileNames["VBFRad_1200_MC2017"] = "tree_VBFRad_mRad1200_v14_MC2017.root";
        fileNames["VBFRad_1400_MC2017"] = "tree_VBFRad_mRad1400_v14_MC2017.root";
        fileNames["VBFRad_1600_MC2017"] = "tree_VBFRad_mRad1600_v14_MC2017.root";
        fileNames["VBFRad_1800_MC2017"] = "tree_VBFRad_mRad1800_v14_MC2017.root";
        fileNames["VBFRad_2000_MC2017"] = "tree_VBFRad_mRad2000_v14_MC2017.root";
        fileNames["VBFRad_2500_MC2017"] = "tree_VBFRad_mRad2500_v14_MC2017.root";
        fileNames["VBFRad_3000_MC2017"] = "tree_VBFRad_mRad3000_v14_MC2017.root";
        fileNames["VBFRad_3500_MC2017"] = "tree_VBFRad_mRad3500_v14_MC2017.root";
        fileNames["VBFRad_4000_MC2017"] = "tree_VBFRad_mRad4000_v14_MC2017.root";
        fileNames["VBFRad_4500_MC2017"] = "tree_VBFRad_mRad4500_v14_MC2017.root";
        fileNames["VBFRad_5000_MC2017"] = "tree_VBFRad_mRad5000_v14_MC2017.root";
        fileNames["VBFRad_5500_MC2017"] = "tree_VBFRad_mRad5500_v14_MC2017.root";
        fileNames["VBFRad_6000_MC2017"] = "tree_VBFRad_mRad6000_v14_MC2017.root";
        fileNames["VBFRad_6500_MC2017"] = "tree_VBFRad_mRad6500_v14_MC2017.root";
        fileNames["VBFRad_7000_MC2017"] = "tree_VBFRad_mRad7000_v14_MC2017.root";
        fileNames["VBFRad_7500_MC2017"] = "tree_VBFRad_mRad7500_v14_MC2017.root";
        fileNames["VBFRad_8000_MC2017"] = "tree_VBFRad_mRad8000_v14_MC2017.root";

        fileNames["VBFWp_800_MC2017"]  = "tree_VBFWp_mWp800_v14_MC2017.root";
        fileNames["VBFWp_1000_MC2017"] = "tree_VBFWp_mWp1000_v14_MC2017.root";
        fileNames["VBFWp_1200_MC2017"] = "tree_VBFWp_mWp1200_v14_MC2017.root";
        fileNames["VBFWp_1400_MC2017"] = "tree_VBFWp_mWp1400_v14_MC2017.root";
        fileNames["VBFWp_1600_MC2017"] = "tree_VBFWp_mWp1600_v14_MC2017.root";
        fileNames["VBFWp_1800_MC2017"] = "tree_VBFWp_mWp1800_v14_MC2017.root";
        fileNames["VBFWp_2000_MC2017"] = "tree_VBFWp_mWp2000_v14_MC2017.root";
        fileNames["VBFWp_2500_MC2017"] = "tree_VBFWp_mWp2500_v14_MC2017.root";
        fileNames["VBFWp_3000_MC2017"] = "tree_VBFWp_mWp3000_v14_MC2017.root";
        fileNames["VBFWp_3500_MC2017"] = "tree_VBFWp_mWp3500_v14_MC2017.root";
        fileNames["VBFWp_4000_MC2017"] = "tree_VBFWp_mWp4000_v14_MC2017.root";
        fileNames["VBFWp_4500_MC2017"] = "tree_VBFWp_mWp4500_v14_MC2017.root";
        fileNames["VBFWp_5000_MC2017"] = "tree_VBFWp_mWp5000_v14_MC2017.root";
        fileNames["VBFWp_5500_MC2017"] = "tree_VBFWp_mWp5500_v14_MC2017.root";
        fileNames["VBFWp_6000_MC2017"] = "tree_VBFWp_mWp6000_v14_MC2017.root";
        fileNames["VBFWp_6500_MC2017"] = "tree_VBFWp_mWp6500_v14_MC2017.root";
        fileNames["VBFWp_7000_MC2017"] = "tree_VBFWp_mWp7000_v14_MC2017.root";
        fileNames["VBFWp_7500_MC2017"] = "tree_VBFWp_mWp7500_v14_MC2017.root";
        fileNames["VBFWp_8000_MC2017"] = "tree_VBFWp_mWp8000_v14_MC2017.root";

        fileNames["ggFG_800_MC2017"] = "tree_ggFG_mG800_v14_MC2017.root";
        fileNames["ggFG_1000_MC2017"] = "tree_ggFG_mG1000_v14_MC2017.root";
        fileNames["ggFG_1200_MC2017"] = "tree_ggFG_mG1200_v14_MC2017.root";
        fileNames["ggFG_1400_MC2017"] = "tree_ggFG_mG1400_v14_MC2017.root";
        fileNames["ggFG_1600_MC2017"] = "tree_ggFG_mG1600_v14_MC2017.root";
        fileNames["ggFG_1800_MC2017"] = "tree_ggFG_mG1800_v14_MC2017.root";
        fileNames["ggFG_2000_MC2017"] = "tree_ggFG_mG2000_v14_MC2017.root";
        fileNames["ggFG_2500_MC2017"] = "tree_ggFG_mG2500_v14_MC2017.root";
        fileNames["ggFG_3000_MC2017"] = "tree_ggFG_mG3000_v14_MC2017.root";
        fileNames["ggFG_3500_MC2017"] = "tree_ggFG_mG3500_v14_MC2017.root";
        fileNames["ggFG_4000_MC2017"] = "tree_ggFG_mG4000_v14_MC2017.root";
        fileNames["ggFG_4500_MC2017"] = "tree_ggFG_mG4500_v14_MC2017.root";

        fileNames["ggFRad_800_MC2017"] = "tree_ggFRad_mRad800_v14_MC2017.root";
        fileNames["ggFRad_1000_MC2017"] = "tree_ggFRad_mRad1000_v14_MC2017.root";
        fileNames["ggFRad_1200_MC2017"] = "tree_ggFRad_mRad1200_v14_MC2017.root";
        fileNames["ggFRad_1400_MC2017"] = "tree_ggFRad_mRad1400_v14_MC2017.root";
        fileNames["ggFRad_1600_MC2017"] = "tree_ggFRad_mRad1600_v14_MC2017.root";
        fileNames["ggFRad_1800_MC2017"] = "tree_ggFRad_mRad1800_v14_MC2017.root";
        fileNames["ggFRad_2000_MC2017"] = "tree_ggFRad_mRad2000_v14_MC2017.root";
        fileNames["ggFRad_2500_MC2017"] = "tree_ggFRad_mRad2500_v14_MC2017.root";
        fileNames["ggFRad_3000_MC2017"] = "tree_ggFRad_mRad3000_v14_MC2017.root";
        fileNames["ggFRad_3500_MC2017"] = "tree_ggFRad_mRad3500_v14_MC2017.root";
        fileNames["ggFRad_4000_MC2017"] = "tree_ggFRad_mRad4000_v14_MC2017.root";
        fileNames["ggFRad_4500_MC2017"] = "tree_ggFRad_mRad4500_v14_MC2017.root";
        fileNames["ggFRad_5000_MC2017"] = "tree_ggFRad_mRad5000_v14_MC2017.root";
        fileNames["ggFRad_5500_MC2017"] = "tree_ggFRad_mRad5500_v14_MC2017.root";
        fileNames["ggFRad_6000_MC2017"] = "tree_ggFRad_mRad6000_v14_MC2017.root";
        fileNames["ggFRad_6500_MC2017"] = "tree_ggFRad_mRad6500_v14_MC2017.root";
        fileNames["ggFRad_7000_MC2017"] = "tree_ggFRad_mRad7000_v14_MC2017.root";
        fileNames["ggFRad_7500_MC2017"] = "tree_ggFRad_mRad7500_v14_MC2017.root";
        fileNames["ggFRad_8000_MC2017"] = "tree_ggFRad_mRad8000_v14_MC2017.root";

        fileNames["ggFWp_800_MC2017"] =  "tree_ggFWp_mWp800_v3_MC2016.root";
        fileNames["ggFWp_1000_MC2017"] = "tree_ggFWp_mWp1000_v3_MC2016.root";
        fileNames["ggFWp_1200_MC2017"] = "tree_ggFWp_mWp1200_v3_MC2016.root";
        fileNames["ggFWp_1400_MC2017"] = "tree_ggFWp_mWp1400_v3_MC2016.root";
        fileNames["ggFWp_1600_MC2017"] = "tree_ggFWp_mWp1600_v3_MC2016.root";
        //fileNames["ggFWp_1800_MC2017"] = "tree_ggFWp_mWp1800_v3_MC2016.root";
        fileNames["ggFWp_2000_MC2017"] = "tree_ggFWp_mWp2000_v3_MC2016.root";
        fileNames["ggFWp_2500_MC2017"] = "tree_ggFWp_mWp2500_v3_MC2016.root";
        fileNames["ggFWp_3000_MC2017"] = "tree_ggFWp_mWp3000_v3_MC2016.root";
        fileNames["ggFWp_3500_MC2017"] = "tree_ggFWp_mWp3500_v3_MC2016.root";
        fileNames["ggFWp_4000_MC2017"] = "tree_ggFWp_mWp4000_v3_MC2016.root";
        fileNames["ggFWp_4500_MC2017"] = "tree_ggFWp_mWp4500_v3_MC2016.root";

	for( auto name : backgrounds ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    //temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    //temp->Add(BASE_DIR_DATA+skimType+"/"+fileNames[name]);	  
	    temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    ntuples.push_back(new RA2bTree(temp));
	    sampleName.push_back(name);
	  }

	}	    

	for( auto name : signals ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    //TChain* temp = new TChain("TreeMaker2/PreSelection");
        //VBFG1000 = new TChain("TreeMaker2/PreSelection");
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
