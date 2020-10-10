import os
from sys import argv

year = argv[1]
cut = argv[2]
wt = argv[3]

print "moving : "+"AN_ORv1_files/{0}_ORv11/Sig_{1}_{0}.root     AN_ORv1_files/{0}_ORv11/Sig_{1}_{0}_{2}.root".format(year,cut,wt)

os.system("mv AN_ORv1_files/{0}_ORv11/Sig_{1}_{0}.root AN_ORv1_files/{0}_ORv11/Sig_{1}_{0}_{2}.root".format(year,cut,wt))
