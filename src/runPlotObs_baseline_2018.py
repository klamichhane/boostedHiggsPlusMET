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

os.system('make plotObs_baseline')

backgroundSamples=[
#                   "ZJets_100to200", "ZJets_200to400", "ZJets_400to600", "ZJets_600to800",
#                   "ZJets_800to1200", "ZJets_1200to2500", "ZJets_2500toInf",
#                   "WJets_100to200", "WJets_200to400", "WJets_400to600", "WJets_600to800",
#                   "WJets_800to1200", "WJets_1200to2500", "WJets_2500toInf",
#
#                   "TT_600to800", "TT_800to1200", "TT_1200to2500", "TT_2500toInf",
#                   "TT_1LFromT", "TT_1LFromTbar", "TT_2L",  
#                   "ST_s-channel", "ST_tW_antitop", "ST_tW_top",
#                   "ST_t-channel_antitop", "ST_t-channel_top", 
#
#                   #"Other_WWTo2L2Nu", #remove for all years
#                   "Other_WZ", 
#                   "Other_WZTo1L1Nu2Q", "Other_WZTo1L3Nu", # now using incl. sample for WZ
#                   "Other_ZZTo2Q2Nu", #remove for 2017 n 18
#                   "Other_WWZ", "Other_WZZ", "Other_ZZZ", "Other_TTTT", #newly ntuplized
#                   "Other_ZZTo2L2Q", "Other_WWTo1L1Nu2Q", "Other_TTWJetsToLNu",
#                   "Other_TTWJetsToQQ", "Other_TTGJets", "Other_TTZToLLNuNu", "Other_TTZToQQ",
]

signalSamples=[#"ggFG_1200",
               #"ggFWp_3500", 
#               "VBFG_1000", 
#               "VBFG_2000", 
#               "VBFG_4500", 
#               "ggFG_1000", 
#               "ggFG_2000", 
#               "ggFG_4500", 

               #"VBFG_800", "VBFG_1000", "VBFG_1200", "VBFG_1400", "VBFG_1600", "VBFG_1800", 
               #"VBFG_2000","VBFG_2500", "VBFG_3000", "VBFG_3500", "VBFG_4000", "VBFG_4500", 
               #"VBFG_5000","VBFG_5500", "VBFG_6000", "VBFG_6500", "VBFG_7000", "VBFG_7500", "VBFG_8000", 

               #"VBFRad_800", "VBFRad_1000", "VBFRad_1200", "VBFRad_1400", "VBFRad_1600", "VBFRad_1800", 
               #"VBFRad_2000","VBFRad_2500", "VBFRad_3000", "VBFRad_3500", "VBFRad_4000", "VBFRad_4500", 
               #"VBFRad_5000","VBFRad_5500", "VBFRad_6000", "VBFRad_6500", "VBFRad_7000", "VBFRad_7500", "VBFRad_8000", 

               ##"ggFG_800", "ggFG_1000", "ggFG_1200", "ggFG_1400", "ggFG_1600", "ggFG_1800", 
               ##"ggFG_2000","ggFG_2500", "ggFG_3000", "ggFG_3500", "ggFG_4000", "ggFG_4500", 

               #"ggFRad_800", "ggFRad_1000", "ggFRad_1200", "ggFRad_1400", "ggFRad_1600", "ggFRad_1800", 
               #"ggFRad_2000","ggFRad_2500", "ggFRad_3000", "ggFRad_3500", "ggFRad_4000", "ggFRad_4500", 
               #"ggFRad_5000","ggFRad_5500", "ggFRad_6000", "ggFRad_6500", "ggFRad_7000", "ggFRad_7500", "ggFRad_8000", 

               #"VBFWp_800", "VBFWp_1000", "VBFWp_1200", "VBFWp_1400", "VBFWp_1600", "VBFWp_1800", 
               #"VBFWp_2000","VBFWp_2500", "VBFWp_3000", "VBFWp_3500", "VBFWp_4000", "VBFWp_4500", 
               #"VBFWp_5000","VBFWp_5500", "VBFWp_6000", "VBFWp_6500", "VBFWp_7000", "VBFWp_7500", "VBFWp_8000", 

               ##"ggFWp_800", "ggFWp_1000", "ggFWp_1200", "ggFWp_1400", "ggFWp_1600", #"ggFWp_1800", 
               ##"ggFWp_2000","ggFWp_2500", "ggFWp_3000", "ggFWp_3500", "ggFWp_4000", "ggFWp_4500", 


              ]

#if "ZSR" in cat or cat=="Baseline": dataSamples=[]
#else: dataSamples=["MET_2018A","MET_2018B","MET_2018C","MET_2018D"]
dataSamples=["MET_2018A","MET_2018B","MET_2018C","MET_2018D"]
#dataSamples=[]

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
#time.sleep(20)
print "hadding "+cat
#os.system("hadd -f AN_ORv1_files/{1}_ORv1/{0}_AN_v1_{1}.root AN_ORv1_files/{1}_ORv1/plotObs_{0}_*.root".format(cat,year))
#os.system("hadd -f AN_ORv1_files/Systematics_LP/{1}/{0}_AN_v1_{1}.root AN_ORv1_files/Systematics_LP/{1}/plotObs_{0}_*.root".format(cat,year))
#print "removing files for "+cat
#os.system("rm AN_ORv1_files/Systematics_LP/{1}/plotObs_{0}_*.root".format(cat,year))
#os.system("rm AN_ORv1_files/{1}_ORv1/plotObs_{0}_*.root".format(cat,year))

#os.system("hadd -f AN_Unblind_v1_files/{1}_UB_v1/{0}_AN_v1_{1}.root AN_Unblind_v1_files/{1}_UB_v1/plotObs_{0}_*.root".format(cat,year))
#print "removing files for "+cat
#os.system("rm AN_Unblind_v1_files/{1}_UB_v1/plotObs_{0}_*.root".format(cat,year))

print""
print "started {0} {2} at: {1}".format(cat,start,year)
print "ended {0} {2} at: {1}".format(cat,end,year)
print "processed {0} {2} at: {1}".format(cat,end-start,year)
print""

##for signal:
#print "hadding "+cat
##os.system("hadd -f AN_ORv1_files/{1}_ORv1/Sig_{2}_{0}_{1}_Unweighted.root AN_ORv1_files/{1}_ORv1/plotObs_{0}_*.root".format(cat,year,sig))
#os.system("hadd -f AN_ORv1_files/{1}_ORv1/Sig_{0}_{1}.root AN_ORv1_files/{1}_ORv1/plotObs_{0}_*.root".format(cat,year))
#print "removing files for "+cat
#os.system("rm AN_ORv1_files/{1}_ORv1/plotObs_{0}_*.root".format(cat,year))
#print ""
#os.system("hadd -f AN_Unblind_v1_files/{1}_UB_v1/Sig_{0}_{1}.root AN_Unblind_v1_files/{1}_UB_v1/plotObs_{0}_*.root".format(cat,year))
#print "removing files for "+cat
#os.system("rm AN_Unblind_v1_files/{1}_UB_v1/plotObs_{0}_*.root".format(cat,year))

2    
    


