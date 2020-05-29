import ROOT as r
import os
import sys
from sys import argv
from array import array
import math


sample = sys.argv[1]
year = sys.argv[2]
#sample = "ggFG", "VBFG"

skimDir = "/home/whitbeck/raid/temp/SusyRA2Analysis2015/Skims_TTU_Jul19/Run2ProductionV17/Sig_Samples/"

if sample == "ggFG" or sample == "VBFG": sam = "mG"
if sample == "ggFRad" or sample == "VBFRad": sam = "mRad"
if sample == "ggFWp" or sample == "VBFWp": sam = "mWp"

mpfull = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000]
mpcomm = [800,1000,5000, 5500, 6000, 6500, 7000, 7500, 8000]
mp = []
if sample == "VBFG" and year == "2016": mp = [800,1000,1200,1400,1600,1800,2000,3000,3500,4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000]
elif sample == "VBFWp" and year == "2016": mp = mpcomm 
elif sample == "VBFRad" and year == "2016": mp = [1200,5000, 5500, 6000, 6500, 7000, 7500]
elif sample == "ggFWp" and year == "2016": mp = [800, 1000, 1200, 1400, 1600, 2000, 2500, 3000, 3500, 4000, 4500]
elif sample == "ggFG" and year == "2017": mp = [1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500]
elif sample == "ggFRad" and year == "2018": mp = [1000, 4500]
else: mp = mpfull 

if year == "2016": label = "v3_MC2016"
elif year == "2017": label = "v14_MC2017"
elif year == "2018": label = "v15_MC2018"

#tree_VBFRad_mRad6500_v15_MC2018.root
evtProc = []

info = "{0} {1}".format(sample,year)
print ""
print (info.center(30,'+'))
print ("".center(30,'+'))
print "{:<15s}{:<13s}".format("Mass","nEvtProc")
print ("".center(30,'+'))
for i in mp:
    f1 = r.TFile.Open(skimDir+"tree_{0}_{1}{2}_{3}.root".format(sample,sam,i,label))
    h = f1.Get("nEventProc")
    evtProc.append(h.Integral())
    #print "{:<15.1f}{:<13.2f}".format(i,h.Integral())
    print '''if (sig_samp == "{0}_{1}_MC{2}")   sig_xsec_wt = 1/{3};'''.format(sample,i,year,h.Integral())
    f1.Close()

print ("".center(30,'+'))
print ""
print "EvtProc array: {}".format(evtProc)


