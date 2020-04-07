from sys import argv
import os
import ROOT
from ROOT import *

#Running limits for individual category i.e either VBF or VBFfail

sig = str(argv[1]) # "ggFRad", "ggFWp", "ggFG", "VBFRad", "VBFWp", "VBFG"
year = "2016"
#year = "137fb"

if sig == "ggFG": h = ["1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", "4000", "4500"]
elif sig == "ggFWp": h = ["1000", "1200", "1400", "1600", "2000", "2500", "3000", "3500", "4000", "4500"] #1800 missing
else: h = ["800", "1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", "4000", "4500", "5000", "5500", "6000", "6500", "7000", "7500", "8000"]

print 'Now start to compute limits:'
for j in h:
    print "Calculating limits for {0} M{1}:".format(sig,j)
    os.system("combine -M Asymptotic {0}_{1}/{0}_merged_M{2}_{1}.txt -m {2} -n .{0}".format(sig,year,j))
    print "Done: Limits for {0} M{1}:".format(sig,j)
    print " "
    print 'Finally, limit root files to {0} directory:'.format(sig)
    os.system("mv higgsCombine.{0}.Asymptotic.mH*.root {0}_{1}/Root_Limit/".format(sig,year))

print 'Done: Calculating limits for all signals!!!'
print 'Done: Moving root files!!!'
print 'Finally, run LimitPlotter:'
