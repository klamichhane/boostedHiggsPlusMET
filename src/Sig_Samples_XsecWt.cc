#include <iostream>
#include <vector>
#include <map>

//TString sig_samp ;
//double sig_xsec_wt = 0.0;

void Sig_Xsec_wt(TString & sig_samp, double& sig_xsec_wt){

    ///////////////// VBF Graviton Sample ///////////////////
    
    // 2016: VBFG
     if (sig_samp == "VBFG_800_MC2016")    sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1000_MC2016")   sig_xsec_wt = 1/48300.0;
     if (sig_samp == "VBFG_1200_MC2016")   sig_xsec_wt = 1/42200.0;
     if (sig_samp == "VBFG_1400_MC2016")   sig_xsec_wt = 1/46100.0;
     if (sig_samp == "VBFG_1600_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1800_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_2000_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_2500_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_3000_MC2016")   sig_xsec_wt = 1/48500.0;
     if (sig_samp == "VBFG_3500_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_4000_MC2016")   sig_xsec_wt = 1/48800.0;
     if (sig_samp == "VBFG_4500_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_5000_MC2016")   sig_xsec_wt = 1/48400.0;
     if (sig_samp == "VBFG_5500_MC2016")   sig_xsec_wt = 1/49400.0;
     if (sig_samp == "VBFG_6000_MC2016")   sig_xsec_wt = 1/49600.0;
     if (sig_samp == "VBFG_6500_MC2016")   sig_xsec_wt = 1/48500.0;
     if (sig_samp == "VBFG_7000_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_7500_MC2016")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_8000_MC2016")   sig_xsec_wt = 1/48200.0;
    
    //2017: VBFG
     if (sig_samp == "VBFG_800_MC2017")    sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1000_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1200_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1400_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1600_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_1800_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_2000_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_2500_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_3000_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_3500_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_4000_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_4500_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_5000_MC2017")   sig_xsec_wt = 1/46000.0;
     if (sig_samp == "VBFG_5500_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_6000_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_6500_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_7000_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_7500_MC2017")   sig_xsec_wt = 1/50000.0;
     if (sig_samp == "VBFG_8000_MC2017")   sig_xsec_wt = 1/48000.0;
    
    
    //2018: VBFG
    if (sig_samp == "VBFG_800_MC2018")    sig_xsec_wt = 1/50000.00; 
    if (sig_samp == "VBFG_1000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_1200_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_1400_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_1600_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_1800_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_2000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_2500_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_3000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_3500_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_4000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_4500_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_5000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_5500_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_6000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_6500_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_7000_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_7500_MC2018")   sig_xsec_wt = 1/50000.00;
    if (sig_samp == "VBFG_8000_MC2018")   sig_xsec_wt = 1/45000.00;
    
    
    ///////////////////////// VBF W prime Sample ///////////////////
    
    //2016: VBFWp
    if (sig_samp == "VBFWp_800_MC2016")    sig_xsec_wt = 1/49500.0;
    if (sig_samp == "VBFWp_1000_MC2016")   sig_xsec_wt = 1/48400.0;
    if (sig_samp == "VBFWp_1200_MC2016")   sig_xsec_wt = 1/49400.0;
    if (sig_samp == "VBFWp_1400_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1600_MC2016")   sig_xsec_wt = 1/49700.0;
    if (sig_samp == "VBFWp_1800_MC2016")   sig_xsec_wt = 1/47000.0;
    if (sig_samp == "VBFWp_2000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_2500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_3000_MC2016")   sig_xsec_wt = 1/49400.0;
    if (sig_samp == "VBFWp_3500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_4000_MC2016")   sig_xsec_wt = 1/47100.0;
    if (sig_samp == "VBFWp_4500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_5000_MC2016")   sig_xsec_wt = 1/49700.0;
    if (sig_samp == "VBFWp_5500_MC2016")   sig_xsec_wt = 1/48400.0;
    if (sig_samp == "VBFWp_6000_MC2016")   sig_xsec_wt = 1/48400.0;
    if (sig_samp == "VBFWp_6500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_7000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_7500_MC2016")   sig_xsec_wt = 1/49800.0;
    if (sig_samp == "VBFWp_8000_MC2016")   sig_xsec_wt = 1/49800.0;
    
    //2017: VBFWp
    if (sig_samp == "VBFWp_800_MC2017")    sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1200_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1400_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1600_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1800_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_2000_MC2017")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "VBFWp_2500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_3000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_3500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_4000_MC2017")   sig_xsec_wt = 1/47000.0;
    if (sig_samp == "VBFWp_4500_MC2017")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "VBFWp_5000_MC2017")   sig_xsec_wt = 1/49000.0;
    if (sig_samp == "VBFWp_5500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_6000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_6500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_7000_MC2017")   sig_xsec_wt = 1/49000.0;
    if (sig_samp == "VBFWp_7500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_8000_MC2017")   sig_xsec_wt = 1/50000.0;
    
    
    //2018: VBFWp
    if (sig_samp == "VBFWp_800_MC2018")    sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1200_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1400_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1600_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_1800_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_2000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_2500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_3000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_3500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_4000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_4500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_5000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_5500_MC2018")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "VBFWp_6000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_6500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_7000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_7500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFWp_8000_MC2018")   sig_xsec_wt = 1/48000.0;
    
    ///////////////////////// VBF Radion Sample ///////////////////
    
    //2016: VBFRad
    if (sig_samp == "VBFRad_800_MC2016")   sig_xsec_wt = 1/49800.0;
    if (sig_samp == "VBFRad_1000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1200_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1400_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1600_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1800_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_2000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_2500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_3000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_3500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_4000_MC2016")   sig_xsec_wt = 1/49800.0;
    if (sig_samp == "VBFRad_4500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_5000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_5500_MC2016")   sig_xsec_wt = 1/47900.0;
    if (sig_samp == "VBFRad_6000_MC2016")   sig_xsec_wt = 1/47600.0;
    if (sig_samp == "VBFRad_6500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_7000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_7500_MC2016")   sig_xsec_wt = 1/49000.0;
    if (sig_samp == "VBFRad_8000_MC2016")   sig_xsec_wt = 1/47200.0;
    
    //2017: VBFRad
    if (sig_samp == "VBFRad_800_MC2017")    sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1200_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1400_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1600_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1800_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_2000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_2500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_3000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_3500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_4000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_4500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_5000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_5500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_6000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_6500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_7000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_7500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_8000_MC2017")   sig_xsec_wt = 1/50000.0;
    
    
    //2018: VBFRad
    if (sig_samp == "VBFRad_800_MC2018")    sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1200_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1400_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1600_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_1800_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_2000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_2500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_3000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_3500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_4000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_4500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_5000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_5500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_6000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_6500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_7000_MC2018")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "VBFRad_7500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "VBFRad_8000_MC2018")   sig_xsec_wt = 1/50000.0;
    
    
    ///////////////////////// ggF Graviton Sample ///////////////////
    //2016: ggFG (these are exclusive samples) 
    if (sig_samp == "ggFG_800_MC2016")    sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_1000_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_1200_MC2016")   sig_xsec_wt = 1/95800.0 ;
    if (sig_samp == "ggFG_1400_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_1600_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_1800_MC2016")   sig_xsec_wt = 1/98800.0 ;
    if (sig_samp == "ggFG_2000_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_2500_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_3000_MC2016")   sig_xsec_wt = 1/99600.0 ;
    if (sig_samp == "ggFG_3500_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFG_4000_MC2016")   sig_xsec_wt = 1/99200.0 ;
    if (sig_samp == "ggFG_4500_MC2016")   sig_xsec_wt = 1/99800.0 ;    

    
    //2017: ggFG
    if (sig_samp == "ggFG_800_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1200_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1400_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1600_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1800_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_2000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_2500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_3000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_3500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_4000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_4500_MC2017")   sig_xsec_wt = 1/50000.0;
    
    //2018: ggFG //Samples not available Currently using 2017 samples
    if (sig_samp == "ggFG_800_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1200_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1400_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1600_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_1800_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_2000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_2500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_3000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_3500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_4000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFG_4500_MC2018")   sig_xsec_wt = 1/50000.0;
    
    
    ///////////////////////// ggF Wprime Sample ///////////////////
    // 2016: ggFWp (these are exclusive samples)
    if (sig_samp == "ggFWp_800_MC2016")    sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1000_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1200_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1400_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1600_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_2000_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_2500_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_3000_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_3500_MC2016")   sig_xsec_wt = 1/95400.0;
    if (sig_samp == "ggFWp_4000_MC2016")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_4500_MC2016")   sig_xsec_wt = 1/100000.0;
    
    //2017: ggFWp //Samples not available Currently using the 2016 sample
    if (sig_samp == "ggFWp_800_MC2017")    sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1000_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1200_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1400_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1600_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_2000_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_2500_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_3000_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_3500_MC2017")   sig_xsec_wt = 1/95400.0;
    if (sig_samp == "ggFWp_4000_MC2017")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_4500_MC2017")   sig_xsec_wt = 1/100000.0;
    
    //2018: ggFWp //Samples not available Currently using the 2016 sample
    if (sig_samp == "ggFWp_800_MC2018")    sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1000_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1200_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1400_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_1600_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_2000_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_2500_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_3000_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_3500_MC2018")   sig_xsec_wt = 1/95400.0;
    if (sig_samp == "ggFWp_4000_MC2018")   sig_xsec_wt = 1/100000.0;
    if (sig_samp == "ggFWp_4500_MC2018")   sig_xsec_wt = 1/100000.0;
    
    
    ///////////////////////// ggF Radion Sample ///////////////////
    
    //2016: ggFRad 
    if (sig_samp == "ggFRad_800_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_1000_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_1200_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_1400_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_1600_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_1800_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_2000_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_2500_MC2016")   sig_xsec_wt = 1/29800.0;
    if (sig_samp == "ggFRad_3000_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_3500_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_4000_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_4500_MC2016")   sig_xsec_wt = 1/30000.0;
    if (sig_samp == "ggFRad_5000_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_5500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_6000_MC2016")   sig_xsec_wt = 1/48200.0;
    if (sig_samp == "ggFRad_6500_MC2016")   sig_xsec_wt = 1/49900.0;
    if (sig_samp == "ggFRad_7000_MC2016")   sig_xsec_wt = 1/49812.0;
    if (sig_samp == "ggFRad_7500_MC2016")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_8000_MC2016")   sig_xsec_wt = 1/49800.0; 
    
    //2017: ggFRad
    if (sig_samp == "ggFRad_800_MC2017")    sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1200_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1400_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1600_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1800_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_2000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_2500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_3000_MC2017")   sig_xsec_wt = 1/43000.0;
    if (sig_samp == "ggFRad_3500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_4000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_4500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_5000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_5500_MC2017")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "ggFRad_6000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_6500_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_7000_MC2017")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_7500_MC2017")   sig_xsec_wt = 1/49000.0;
    if (sig_samp == "ggFRad_8000_MC2017")   sig_xsec_wt = 1/50000.0;
    
    
    //2018: ggFRad; 
    if (sig_samp == "ggFRad_800_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1200_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1400_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_1600_MC2018")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "ggFRad_1800_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_2000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_2500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_3000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_3500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_4000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_4500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_5000_MC2018")   sig_xsec_wt = 1/48000.0;
    if (sig_samp == "ggFRad_5500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_6000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_6500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_7000_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_7500_MC2018")   sig_xsec_wt = 1/50000.0;
    if (sig_samp == "ggFRad_8000_MC2018")   sig_xsec_wt = 1/48000.0;
    
}


