from multiprocessing import Process
import os

#os.environ["DYLD_LIBRARY_PATH"] = "/Users/whitbeck/root_build/lib"

backgroundSamples=[#"QCD_200to300",
                   "ZJets_100to200",
                   "ZJets_200to400",
                   "ZJets_400to600",
                   "ZJets_600to800",
                   "ZJets_800to1200",
                   "ZJets_1200to2500",
                   "ZJets_2500toInf",
                   "WJets_100to200",
                   "WJets_200to400",
                   "WJets_400to600",
                   "WJets_600to800",
                   "WJets_800to1200",
                   "WJets_1200to2500",
                   "WJets_2500toInf",
                   "TT_600to800",
                   "TT_800to1200",
                   "TT_1200to2500",
                   "TT_2500toInf",
                   "TT_1LFromT", #KL
                   "TT_1LFromTbar", #KL
                   "TT_2L",   #KL
                   "ST_s-channel",
                   "ST_tW_antitop",
                   "ST_tW_top",
                   "Other_WWTo1L1Nu2Q",
                   "Other_WZTo1L3Nu",
                   "Other_ZZTo2L2Q",
                   "Other_TTWJetsToLNu",
                   "Other_TTWJetsToQQ",
                   "Other_TTGJets",
                   "Other_TTZToLLNuNu",
                   "Other_TTZToQQ",
]

signalSamples=["VBFG_1200",
              ]

dataSamples=["MET_2018A",
             "MET_2018B",
             "MET_2018C",
             "MET_2018D"
             ]

def runPlotObsBaseline(sel,bkg,sig,data):
    print '../bin/plotObs_baseline "{0}" "{1}" "{2}" "{3}"'.format(sel,bkg,sig,data)
    os.system('../bin/plotObs_baseline "{0}" "{1}" "{2}" "{3}"'.format(sel,bkg,sig,data))

processes=[]
for sample in backgroundSamples : 
    #p = Process(target=runPlotObsBaseline, args=("ZSBNoVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("ZNoSelection",sample,"","") )
    p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("ZSRHPVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSBHPVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF",sample,"","") )
    p.start()
    processes.append(p)

for sample in signalSamples : 
    #p = Process(target=runPlotObsBaseline, args=("ZSBNoVBF","",sample,"") )
    #p = Process(target=runPlotObsBaseline, args=("ZNoSelection","",sample,"") )
    p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF","",sample, "") )
    #p = Process(target=runPlotObsBaseline, args=("ZSRHPVBF","",sample, "") )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSBHPVBF","",sample, "") )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF","",sample, "") )
    p.start()
    processes.append(p)

for sample in dataSamples : 
    #p = Process(target=runPlotObsBaseline, args=("ZSBNoVBF","","",sample) )
    #p = Process(target=runPlotObsBaseline, args=("ZNoSelection","","",sample) )
    p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF","","", sample) )
    #p = Process(target=runPlotObsBaseline, args=("ZSRHPVBF","","", sample) )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSBHPVBF","","", sample) )
    #p = Process(target=runPlotObsBaseline, args=("AlphaSRHPVBF","","", sample) )
    p.start()
    processes.append(p)

for p in processes : 
    p.join()

#os.system("hadd -f plotObs_photon_baseline.root plotObs_photon_baseline_*.root")
#os.system("rm plotObs_photon_baseline_*.root")
2    
    


