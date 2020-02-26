import ROOT as r
import os
from sys import argv

#norm = "Norm"
#norm = "NoNorm"
norm = "SR"

#year = "2018"
year = str(argv[1])

filetorun = ""

if norm == "SR":
    cat = ["ZSR","ZSRHP","ZSRHPVBF","ZSRHPVBFfail","ZSRFPVBF","ZSRFPVBFfail"] # for SR
    filetorun = "prettyPlot_NoRatio_137fb.py"
elif norm == "Norm":
    cat = ["ZSB","ZSBHP","ZSBHPVBF","ZSBHPVBFfail","ZSBFPVBF","ZSBFPVBFfail"] #for Norm
    filetorun = "prettyPlot_137fb.py"
elif norm == "NoNorm":
    cat = ["ZSBHPVBF","ZSBHPVBFfail","ZSBFPVBF","ZSBFPVBFfail"] #for NoNorm
    filetorun = "NoNorm_prettyPlot_137fb.py"


for i in range(len(cat)):
    print" "
    print " running plots for category: "+cat[i]
    #os.system("python prettyPlot_NoRatio_137fb.py {0} {1}".format(year,cat[i])) #for SR
    #os.system("python prettyPlot_137fb.py {0} {1}".format(year,cat[i])) #for Norm
    #os.system("python NoNorm_prettyPlot_137fb.py {0} {1}".format(year,cat[i])) #for NoNorm
    #os.system("python {2} {0} {1}".format(year,cat[i]),filetorun) #for NoNorm
    os.system("python {0} {1} {2}".format(filetorun,year,cat[i])) #for NoNorm
