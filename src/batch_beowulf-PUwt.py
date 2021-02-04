import os
import sys
from sys import argv
from datetime import datetime
import time

year = sys.argv[1]
#que = ["ZSBLPVBF","ZSBLPVBFfail","ZSRLPVBF","ZSRLPVBFfail"]
#que = ["ZSBHPVBF","ZSBHPVBFfail","ZSRHPVBF","ZSRHPVBFfail"]
#que = ["ZSBHPVBF","ZSRHPVBF"]
#que = ["ZAlphaSBHPVBF","ZAlphaSRHPVBF","ZAlphaSBHPVBFfail","ZAlphaSRHPVBFfail"]
if year == "2016" or year=="2017":
    #que = ["ZSR", "ZSRHP","ZSRHPVBF", "ZSRHPVBFfail"]
    que = ["ZSB","ZSRLP","ZSRLPVBF","ZSRLPVBFfail"]
if year=="2018":
    que = ["Baseline","ZSR","ZSRHP","ZSRHPVBF", "ZSRHPVBFfail", "ZSB","ZSRLP","ZSRLPVBF","ZSRLPVBFfail"]
    #que = ["ZSB","ZSRLP","ZSRLPVBF","ZSRLPVBFfail"]

for i in range(len(que)):
    print "running {}".format(i)
    #os.system("python runPlotObs_baseline_2016.py {1} {0}".format(year,que[i]))
    os.system("python runPlotObs_baseline_{0}.py {1} {0}".format(year,que[i]))


print""
print "All {1} categories for {0} is done!!!".format(year,len(que))
print""
