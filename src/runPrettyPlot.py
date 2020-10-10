import ROOT as r
import os
from sys import argv

norm = "SR"
#norm = "SB"

#norm = "Alpha"

year = str(argv[1])

filetorun = ""

if norm == "SR":
    #cat = ["Baseline","ZSR","ZSRHP","ZSRHPVBF","ZSRHPVBFfail"] # for SR
    cat = ["ZSRLPVBF","ZSRLPVBFfail"] # for SR
    filetorun = "NoRatio_prettyPlot_137fb.py"
elif norm == "SB":
    #cat = ["ZSBHPVBF","ZSBHPVBFfail","ZSBFPVBF","ZSBFPVBFfail"] #for NoNorm
    #cat = ["ZSB","ZSBHP","ZSBHPVBF","ZSBHPVBFfail"] #for NoNorm
    cat = ["ZSBLPVBF","ZSBLPVBFfail"] # for SR
    filetorun = "NoNorm_prettyPlot_137fb.py"

elif norm == "Alpha":
    cat = ["ZAlphaSBHPVBF","ZAlphaSBHPVBFfail","ZAlphaSRHPVBF","ZAlphaSRHPVBFfail"] #for NoNorm
    #cat = ["ZAlphaSBHPVBF","ZAlphaSBHPVBFfail","ZAlphaSBFPVBF","ZAlphaSBFPVBFfail","ZAlphaSBHPLooseVBF","ZAlphaSBHPLooseVBFfail",
    #       "ZAlphaSRHPVBF","ZAlphaSRHPVBFfail","ZAlphaSRFPVBF","ZAlphaSRFPVBFfail","ZAlphaSRHPLooseVBF","ZAlphaSRHPLooseVBFfail"] #for NoNorm
    filetorun = "prettyPlot_Alpha.py"

for i in range(len(cat)):
    print" "
    print " running plots for category: "+cat[i]
    #os.system("python prettyPlot_NoRatio_137fb.py {0} {1}".format(year,cat[i])) #for SR
    os.system("python {0} {1} {2}".format(filetorun,year,cat[i])) #for NoNorm
