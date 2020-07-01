import os
import sys
from sys import argv
from datetime import datetime
import time

#year = "2017"
year = sys.argv[1]
#que = ["ZSB"]
#que = ["ZSB","ZSBHP","ZSBHPVBF","ZSBHPVBFfail","ZSR","ZSRHP","ZSRHPVBF","ZSRHPVBFfail"]
#que = ["Baseline","ZSB","ZSBHP","ZSBHPVBF","ZSBHPVBFfail","ZSR","ZSRHP","ZSRHPVBF","ZSRHPVBFfail"]
#que = ["Baseline","ZSB","ZSBHPVBF","ZSBHPVBFfail","ZSR","ZSRHPVBF","ZSRHPVBFfail"]
#que = ["ZSBHP"]
que = ["ZSBHPVBF","ZSBHPVBFfail","ZSRHPVBF","ZSRHPVBFfail"]
#que = ["ZAlphaSBHPVBF","ZAlphaSRHPVBF","ZAlphaSBHPVBFfail","ZAlphaSRHPVBFfail"]
#que = ["ZAlphaSBHPLooseVBF","ZAlphaSRHPLooseVBF","ZAlphaSBHPLooseVBFfail","ZAlphaSRHPLooseVBFfail"]

for i in range(len(que)):
    start = datetime.now()
    print "running {}".format(i)
    os.system("python runPlotObs_baseline_{0}.py {1} {0}".format(year,que[i]))
    end = datetime.now()
    print "started {0} {2} at: {1}".format(que[i],start,year)
    print "ended {0} {2} at: {1}".format(que[i],end,year)
    print "processed {0} {2} at: {1}".format(que[i],end-start,year)
    print""


print""
print "All {1} categories for {0} is done!!!".format(year,len(que))
print""
