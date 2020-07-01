from multiprocessing import Process
import os
from sys import argv
from datetime import datetime
import time

start = datetime.now()

cat = argv[1]
year = argv[2]
print "started {0} {2} at: {1}".format(cat,start,year)


#os.environ["DYLD_LIBRARY_PATH"] = "/Users/whitbeck/root_build/lib"

print "If running 2016 & 2018: set tau21 HP value to: 0.35"

#os.system('make plotObs_baseline')

backgroundSamples=[#"QCD_200to300",
                   #"ZJets_100to200", "ZJets_200to400", "ZJets_400to600", "ZJets_600to800",
                   #"ZJets_800to1200", "ZJets_1200to2500", "ZJets_2500toInf",

                   #"WJets_100to200", "WJets_200to400", "WJets_400to600", "WJets_600to800",
                   #"WJets_800to1200", "WJets_1200to2500", "WJets_2500toInf",

                   #"TT_600to800", "TT_800to1200", "TT_1200to2500", "TT_2500toInf",
                   #"TT_1LFromT", "TT_1LFromTbar", "TT_2L",  
                   #"ST_s-channel", "ST_tW_antitop", "ST_tW_top",
                   ##"ST_t-channel_antitop", # remove for 2018
                   ##"ST_t-channel_top", # remove for 2018

                   ##"Other_WWTo2L2Nu", #remove for all years
                   ##"Other_WWZ", #remove for 2017 n 18
                   ##"Other_WZTo1L1Nu2Q", #remove for 2018
                   ##"Other_WZZ", #remove for 2018
                   ##"Other_ZZTo2Q2Nu", #remove for 2017 n 18
                   ##"Other_ZZZ", #remove for 2018
                   ##"Other_TTTT", #remove for 2018

                   #"Other_ZZTo2L2Q", "Other_WZTo1L3Nu", "Other_WWTo1L1Nu2Q", "Other_TTWJetsToLNu",
                   #"Other_TTWJetsToQQ", "Other_TTGJets", "Other_TTZToLLNuNu", "Other_TTZToQQ",
]

signalSamples=[#"ggFG_1000_MC2018",
               #"VBFG_1000_MC2018", 

               #"VBFG_800_MC2018", "VBFG_1000_MC2018", "VBFG_1200_MC2018", "VBFG_1400_MC2018", "VBFG_1600_MC2018", "VBFG_1800_MC2018", 
               #"VBFG_2000_MC2018","VBFG_2500_MC2018", "VBFG_3000_MC2018", "VBFG_3500_MC2018", "VBFG_4000_MC2018", "VBFG_4500_MC2018", 
               ###"VBFG_5000_MC2018","VBFG_5500_MC2018", "VBFG_6000_MC2018", "VBFG_6500_MC2018", "VBFG_7000_MC2018", "VBFG_7500_MC2018", "VBFG_8000_MC2018", 

               #"VBFRad_800_MC2018", "VBFRad_1000_MC2018", "VBFRad_1200_MC2018", "VBFRad_1400_MC2018", "VBFRad_1600_MC2018", "VBFRad_1800_MC2018", 
               #"VBFRad_2000_MC2018","VBFRad_2500_MC2018", "VBFRad_3000_MC2018", "VBFRad_3500_MC2018", "VBFRad_4000_MC2018", "VBFRad_4500_MC2018", 
               ###"VBFRad_5000_MC2018","VBFRad_5500_MC2018", "VBFRad_6000_MC2018", "VBFRad_6500_MC2018", "VBFRad_7000_MC2018", "VBFRad_7500_MC2018", "VBFRad_8000_MC2018", 

               ##"ggFG_800_MC2018", # n/a
               #"ggFG_1000_MC2018", "ggFG_1200_MC2018", "ggFG_1400_MC2018", "ggFG_1600_MC2018", "ggFG_1800_MC2018", 
               #"ggFG_2000_MC2018","ggFG_2500_MC2018", "ggFG_3000_MC2018", "ggFG_3500_MC2018", "ggFG_4000_MC2018", "ggFG_4500_MC2018", 
               ###"ggFG_5000_MC2018","ggFG_5500_MC2018", "ggFG_6000_MC2018", "ggFG_6500_MC2018", "ggFG_7000_MC2018", "ggFG_7500_MC2018", "ggFG_8000_MC2018", 

               #"ggFRad_800_MC2018", "ggFRad_1000_MC2018", "ggFRad_1200_MC2018", "ggFRad_1400_MC2018", "ggFRad_1600_MC2018", "ggFRad_1800_MC2018", 
               #"ggFRad_2000_MC2018","ggFRad_2500_MC2018", "ggFRad_3000_MC2018", "ggFRad_3500_MC2018", "ggFRad_4000_MC2018", "ggFRad_4500_MC2018", 
               ###"ggFRad_5000_MC2018","ggFRad_5500_MC2018", "ggFRad_6000_MC2018", "ggFRad_6500_MC2018", "ggFRad_7000_MC2018", "ggFRad_7500_MC2018", "ggFRad_8000_MC2018", 

               "VBFWp_800_MC2018", "VBFWp_1000_MC2018", "VBFWp_1200_MC2018", "VBFWp_1400_MC2018", "VBFWp_1600_MC2018", "VBFWp_1800_MC2018", 
               "VBFWp_2000_MC2018","VBFWp_2500_MC2018", "VBFWp_3000_MC2018", "VBFWp_3500_MC2018", "VBFWp_4000_MC2018", "VBFWp_4500_MC2018", 
               ##"VBFWp_5000_MC2018","VBFWp_5500_MC2018", "VBFWp_6000_MC2018", "VBFWp_6500_MC2018", "VBFWp_7000_MC2018", "VBFWp_7500_MC2018", "VBFWp_8000_MC2018", 

               "ggFWp_800_MC2018", "ggFWp_1000_MC2018", "ggFWp_1200_MC2018", "ggFWp_1400_MC2018", "ggFWp_1600_MC2018", #"ggFWp_1800_MC2018", 
               "ggFWp_2000_MC2018","ggFWp_2500_MC2018", "ggFWp_3000_MC2018", "ggFWp_3500_MC2018", "ggFWp_4000_MC2018", "ggFWp_4500_MC2018", 
               ##"ggFWp_5000_MC2018","ggFWp_5500_MC2018", "ggFWp_6000_MC2018", "ggFWp_6500_MC2018", "ggFWp_7000_MC2018", "ggFWp_7500_MC2018", "ggFWp_8000_MC2018", 


              ]

#if "ZSR" in cat or cat=="Baseline": dataSamples=[]
#else: dataSamples=["MET_2018A","MET_2018B","MET_2018C","MET_2018D"]
dataSamples=[]

def runPlotObsBaseline(sel,bkg,sig,data):
    print '../bin/plotObs_baseline "{0}" "{1}" "{2}" "{3}"'.format(sel,bkg,sig,data)
    os.system('../bin/plotObs_baseline "{0}" "{1}" "{2}" "{3}"'.format(sel,bkg,sig,data))

processes=[]
for sample in backgroundSamples : 
    p = Process(target=runPlotObsBaseline, args=(str(cat),sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF",sample,"","") )
    p.start()
    processes.append(p)

for sample in signalSamples : 
    p = Process(target=runPlotObsBaseline, args=(str(cat),"",sample,"") )
    #p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF","",sample, "") )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF","",sample, "") )
    p.start()
    processes.append(p)

for sample in dataSamples : 
    p = Process(target=runPlotObsBaseline, args=(str(cat),"","",sample) )
    #p = Process(target=runPlotObsBaseline, args=("ZSRHPVBF","","",sample) )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF","","",sample) )
    p.start()
    processes.append(p)

for p in processes : 
    p.join()

end = datetime.now()


print""
##time.sleep(20)
#print "hadding "+cat
#os.system("hadd -f AN_v1_NLO_files/{1}/{0}_AN_v1_{1}.root AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year))
#print "removing files for "+cat
#os.system("rm AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year))

print""
print "started {0} {2} at: {1}".format(cat,start,year)
print "ended {0} {2} at: {1}".format(cat,end,year)
print "processed {0} {2} at: {1}".format(cat,end-start,year)
print""

#for signal:
print "hadding "+cat
#os.system("hadd -f AN_v1_NLO_files/{1}/Sig_{2}_{0}_{1}_Unweighted.root AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year,sig))
os.system("hadd -f AN_v1_NLO_files/{1}/Sig_{0}_{1}_v2.root AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year))
print "removing files for "+cat
os.system("rm AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year))
print ""

2    
    


