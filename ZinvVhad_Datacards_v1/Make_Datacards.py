from sys import argv
import os
import ROOT
from ROOT import *

sig = str(argv[1]) # "ggFRad", "ggFWp", "ggFG", "VBFRad", "VBFWp", "VBFG"

#year = "137fb"
year = "2016"

if sig == "ggFG": h = ["1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", "4000", "4500"]
elif sig == "ggFWp": h = ["1000", "1200", "1400", "1600", "2000", "2500", "3000", "3500", "4000", "4500"] #1800 missing
else: h = ["800", "1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", 
           "4000", "4500", "5000", "5500", "6000", "6500", "7000", "7500", "8000"]

for i in h:
    print "Creating datacards for {0} M{1}:".format(sig,i)
    os.system("python Datacard.py {0} {1} {2}".format(i, sig, year))
    print " "
print 'Done: Creating datacards'
print " "
print 'Now start to Merge the Datacards:'


for i in h:
    print "Merging datacards for {0} M{1}:".format(sig,i)
    os.system("combineCards.py {0}_{1}/{0}_Card_M{2}_bin*_{1}.txt >{0}_{1}/{0}_merged_M{2}_{1}.txt".format(sig,year,i))
    print "Done Merging datacards for {0} M{1}:".format(sig,i)
    print " "
print 'Done: Creating & Merging Datacards'
print " "


