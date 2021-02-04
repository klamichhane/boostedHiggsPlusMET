import ROOT as r
import os
from sys import argv

year = str(argv[1])

filetorun = "Unblind_prettyPlot_137fb.py"

cat = ["Baseline","ZSB","ZSR","ZSRHP","ZSRHPVBF","ZSRHPVBFfail","ZSRLP","ZSRLPVBF","ZSRLPVBFfail"]


for i in range(len(cat)):
    print" "
    print " running plots for category: "+cat[i]
    os.system("python {0} {1} {2}".format(filetorun,year,cat[i])) 
    print" "
