import os,sys

#mkdir -p AN_Unblind_v1_plots/ZSB/2016

location = "AN_Unblind_v1_plots/"

year = ["2016","2017","2018","137fb"] 

cat = ["ZSB","ZSR","ZSRHP","ZSRHPVBF","ZSRHPVBFfail","ZSRLP","ZSRLPVBF","ZSRLPVBFfail"]

for i in cat:
    for j in year:
        os.system("mkdir -p {0}{1}/{2}".format(location,i,j))


