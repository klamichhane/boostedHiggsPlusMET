import sys
import os
import ROOT
from ROOT import *

#Running limits for VBF and VBFfail combined category

#sig = ["VBFRad", "VBFWp", "VBFG"]
sig = ["VBFWp", "VBFG"]
year = "137fb"
h = ["800", "1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", "4000", "4500", "5000", "5500", "6000", "6500", "7000", "7500", "8000"]

print 'Now start to compute limits:'
for i in sig:
    for j in h:
        print "Calculating limits for {0} M{1}:".format(i,j)
        os.system("combine -M Asymptotic Combo_{0}_{2}/Combined_VBFnVBFfail_{0}_{1}_{2}.txt -m {1} -n .{0}".format(i,j,year))
        print "Done: Limits for {0} M{1}:".format(i,j)
        print " "
    print 'Finally, moving limit root files to {0} directory:'.format(i)
    os.system("mv higgsCombine.{0}.Asymptotic.mH*.root Combo_{0}_{1}/Root_Limit/".format(i,year))

print 'Done: Calculating limits for all signals!!!'
print 'Done: Moving root files!!!'
print 'Finally, run LimitPlotter in Plots_Limit dir'
#os.system("python LimitPlotter_NoVBF.py {0} {1}".format(sig, year))
