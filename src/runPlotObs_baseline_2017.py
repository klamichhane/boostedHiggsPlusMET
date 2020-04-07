from multiprocessing import Process
import os
from sys import argv
from datetime import datetime
import time

#start = datetime.now()

cat = argv[1]
year = argv[2]
print "started {0} {1}".format(cat,year)
#print "started {0} {2} at: {1}".format(cat,start,year)

#os.environ["DYLD_LIBRARY_PATH"] = "/Users/whitbeck/root_build/lib"
#print "If running 2016 & 2018: set tau21 HP value to: 0.35"
#os.system('make plotObs_baseline')

backgroundSamples=[##"QCD_200to300",
                   #"ZJets_100to200",
                   #"ZJets_200to400",
                   #"ZJets_400to600",
                   #"ZJets_600to800",
                   #"ZJets_800to1200",
                   #"ZJets_1200to2500",
                   #"ZJets_2500toInf",
                   #"WJets_100to200",
                   #"WJets_200to400",
                   #"WJets_400to600",
                   #"WJets_600to800",
                   #"WJets_800to1200",
                   #"WJets_1200to2500",
                   #"WJets_2500toInf",
                   #"TT_600to800",
                   #"TT_800to1200",
                   #"TT_1200to2500",
                   #"TT_2500toInf",
                   #"TT_1LFromT", #KL
                   #"TT_1LFromTbar", #KL
                   #"TT_2L",   #KL
                   #"ST_s-channel",
                   #"ST_t-channel_antitop", # remove for 2018
                   #"ST_t-channel_top", # remove for 2018
                   #"ST_tW_antitop",
                   #"ST_tW_top",

                   ##"Other_WWTo2L2Nu", #remove for all years
                   #"Other_WWTo1L1Nu2Q",
                   #"Other_WWZ", #remove for 2017 n 18
                   #"Other_WZTo1L1Nu2Q", #remove for 2018
                   #"Other_WZTo1L3Nu",
                   #"Other_WZZ", #remove for 2018
                   #"Other_ZZTo2L2Q",
                   #"Other_ZZTo2Q2Nu", #remove for 2017 n 18
                   #"Other_ZZZ", #remove for 2018
                   #"Other_TTTT", #remove for 2018
                   #"Other_TTWJetsToLNu",
                   #"Other_TTWJetsToQQ",
                   #"Other_TTGJets",
                   #"Other_TTZToLLNuNu",
                   #"Other_TTZToQQ",
]

sig = "ggFRad"

signalSamples=[#"VBFG_1000",
               #"ggFG_1000", 
               #"VBFWp_800", 
               "ggFWp_1000", 
               "ggFWp_1200", 
               "ggFWp_1400", 
               "ggFWp_1600", 
               #"ggFWp_1800", 
               "ggFWp_2000", 
               "ggFWp_2500", 
               "ggFWp_3000", 
               "ggFWp_3500", 
               "ggFWp_4000", 
               "ggFWp_4500", 
               #"VBFWp_5000", 
               #"VBFWp_5500", 
               #"VBFWp_6000", 
               #"VBFWp_6500", 
               #"VBFWp_7000", 
               #"VBFWp_7500", 
               #"VBFWp_8000", 
              ]

dataSamples=[]
#if "ZSR" in cat or cat=="Baseline":
#    dataSamples=[]
#else: dataSamples=["MET_2017B","MET_2017C","MET_2017D","MET_2017E","MET_2017F"]

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
    #p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF","","", sample) )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF","","",sample) )
    p.start()
    processes.append(p)

for p in processes : 
    p.join()

#end = datetime.now()

#print "started {0} 2017 at: {1}".format(cat,start)
#print "ended {0} 2017 at: {1}".format(cat,end)
#print "processed {0} 2017 at: {1}".format(cat,end-start)

print""
##time.sleep(20)
#print "hadding "+cat
#os.system("hadd -f AN_v1_NLO_files/{1}/{0}_AN_v1_{1}.root AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year))
#print "removing files for "+cat
#os.system("rm AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year))

#for signal:
#print "hadding "+cat
#os.system("hadd -f AN_v1_NLO_files/{1}/Sig_{2}_{0}_{1}_Unweighted.root AN_v1_NLO_files/{1}/plotObs_{0}_*.root".format(cat,year,sig))
#print "removing files for "+cat
#os.system("rm AN_v1_files/{1}/plotObs_{0}_*.root".format(cat,year))
#print ""
2    
    


