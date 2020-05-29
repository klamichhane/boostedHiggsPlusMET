import ROOT as r
import os
from sys import argv

norm = "SB"

year = str(argv[1])

filetorun = ""

if norm == "SR":
    cat = ["ZSRHPVBF","ZSRHPVBFfail"]
    filetorun = "NoRatio_prettyPlot_137fb-PUtest.py"
elif norm == "SB":
    cat = ["ZSBHPVBF","ZSBHPVBFfail"] 
    filetorun = "NoNorm_prettyPlot_137fb-PUtest.py"

for i in range(len(cat)):
    print" "
    print " running plots for category: "+cat[i]
    os.system("python {0} {1} {2}".format(filetorun,year,cat[i])) #for NoNorm
