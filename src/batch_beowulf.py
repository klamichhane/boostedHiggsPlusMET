import os
import sys
from sys import argv
from datetime import datetime
import time

print "If running SB category, change the number of events for data"
#year = "2017"
year = sys.argv[1]
#que = ["AlphaSBHPNoVBF","AlphaSRHPNoVBF","AlphaSBHPVBF","AlphaSRHPVBF"]
#que = ["ZSBHPVBF","ZSBHPVBFfail","ZSBFPVBF","ZSBFPVBFfail"]
#que =  ["ZSRHPVBF","ZSRHPVBFfail","ZSRFPVBF","ZSRFPVBFfail"]
#que = ["AlphaSBFPVBFfail","AlphaSRFPVBFfail","AlphaSBHPVBFfail","AlphaSRHPVBFfail"]
#que = ["Baseline","ZSR","ZSRHP","ZSRHPVBFfail"]
#que = ["Baseline","ZSR","ZSRHP","ZSRHPVBF"]
que = ["ZSB"]
#que = ["ZSRHPVBFfail","ZSBHPVBFfail"]
#que = ["ZAlphaSRHPVBF","ZAlphaSBHPVBFfail","ZAlphaSRHPVBFfail"]
#que = ["ZAlphaSBFPVBF","ZAlphaSRFPVBF","ZAlphaSBFPVBFfail","ZAlphaSRFPVBFfail"]
#que = ["ZAlphaSBHPLooseVBF","ZAlphaSRHPLooseVBF","ZAlphaSBHPLooseVBFfail","ZAlphaSRHPLooseVBFfail"]

for i in range(len(que)):
    start = datetime.now()
    print "started {0} at: {1}".format(year,start)
    print "running {}".format(i)
    os.system("python runPlotObs_baseline_{0}.py {1} {0}".format(year,que[i]))
    end = datetime.now()
    print "started {0} {2} at: {1}".format(que[i],start,year)
    print "ended {0} {2} at: {1}".format(que[i],end,year)
    print "processed {0} {2} at: {1}".format(que[i],end-start,year)


print""
print "All {1} categories for {0} is done!!!".format(year,len(que))
print""
