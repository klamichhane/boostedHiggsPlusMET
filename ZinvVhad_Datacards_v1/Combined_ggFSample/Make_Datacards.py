from sys import argv
import os
import ROOT
from ROOT import *

sig = ["ggFRad","VBFRad"]
#sig = ["ggFWp","VBFWp"]
#sig = ["ggFG","VBFG"]

#year = "137fb"
year = "2016"

if sig[0] == "ggFG": h = ["1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", "4000", "4500"]
elif sig[0] == "ggFWp": h = ["1000", "1200", "1400", "1600", "2000", "2500", "3000", "3500", "4000", "4500"]
elif sig[0] == "ggFRad":
    h = ["800", "1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", 
         "4000", "4500", "5000", "5500", "6000", "6500", "7000", "7500", "8000"]

for j in sig:
    for i in h:
        print "Creating datacards for {0} M{1}:".format(j,i)
        os.system("python Datacard_Combo_ggF.py {0} {1} {2}".format(i, j, year))
        print " "
print 'Done: Creating datacards'
print " "
print 'Now start to Merge the Datacards:'


for j in sig:
    for i in h:
        print "Merging datacards for {0} M{1}:".format(j,i)
        os.system("combineCards.py "+j+"_"+year+"/"+j+"_Card_MG{0}_bin*_{1}.txt >".format(i,year)+j+"_"+year+"/"+j+"_{0}_merged_{1}.txt".format(i,year))
        print "Done Merging datacards for {0} M{1}:".format(j,i)
        print " "
print 'Done: Creating & Merging Datacards'
print " "


print 'Now Combine VBF and VBFfail cards:'

if len(sig)==2:
    for i in h:
        print "Merging VBF and VBFfail cards for M{}:".format(i)
        os.system("combineCards.py {2}_{1}/{2}_Card_MG{0}_bin*{1}.txt {3}_{1}/{3}_Card_MG{0}_bin*_{1}.txt > Combo_{2}_{1}/Combined_VBFnVBFfail_{2}_{0}_{1}.txt".format(i,year,sig[0],sig[1]))
        print "Done Merging datacards for M{}:".format(i)
        print " "
else: print "Running only 1 category!!!"


