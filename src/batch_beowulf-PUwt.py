import os
import sys
from sys import argv
from datetime import datetime
import time

year = sys.argv[1]
que = ["ZSBHPVBF","ZSBHPVBFfail","ZSRHPVBF","ZSRHPVBFfail"]

for i in range(len(que)):
    print "running {}".format(i)
    os.system("python runPlotObs_baseline_2016.py {1} {0}".format(year,que[i]))


print""
print "All {1} categories for {0} is done!!!".format(year,len(que))
print""
