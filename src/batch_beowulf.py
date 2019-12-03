import os
import sys
from sys import argv
from datetime import datetime
import time

year = "2016"
que = ["AlphaSBHPNoVBF","AlphaSRHPNoVBF","AlphaSBHPVBF","AlphaSRHPVBF"]

for i in range(len(que)):
    start = datetime.now()
    print "started {0} at: {1}".format(year,start)
    print "running {}".format(i)
    os.system("python runPlotObs_baseline_{0}.py {1}".format(year,que[i]))
    end = datetime.now()
    print "started {0} {2} at: {1}".format(que[i],start,year)
    print "ended {0} {2} at: {1}".format(que[i],end,year)
    print "processed {0} {2} at: {1}".format(que[i],end-start,year)


print""
print "All 4 categories for {0} is done!!!".format(year)
print""
