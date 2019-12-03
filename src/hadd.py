import os
import time

cat="AlphaSBHPVBF"

print "hadding "+cat
os.system("hadd AN_v0_Closure_LooseVbfFP/{0}_AN_v0_2016_v3.root AN_v0_Closure_LooseVbfFP/plotObs_{0}_baseline_*.root".format(cat))
time.sleep(20)
print "removing files for "+cat
os.system("rm AN_v0_Closure_LooseVbfFP/plotObs_{0}_baseline_*.root".format(cat))

