#!/usr/bin/python
import ROOT as r
from ROOT import *
import sys
import os
from os.path import isfile, join

#sample = "Rad"
#sample = "Wp"
sample = "BulkG"
txt = sample + " with VBF sample"

if sample == "BulkG":
    sig1 = "ggFG"
    sig2 = "VBFG"
if sample == "Rad":
    sig1 = "ggFRad"
    sig2 = "VBFRad"
if sample == "Wp":
    sig1 = "ggFWp"
    sig2 = "VBFWp"

commondir = "/uscms_data/d3/kxlpp1/SUSY/SUSY_OCT2018/Limit-Combine-Tool/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/datacards/pyDatacard/Binned_DataCard_v1/"

#limit_v0_dir_ggF = commondir+"AN_v0_Sep08/{0}_137fb/Root_Limit_Overflow_100GeV_varbin/".format(sig1)  
limit_v0_dir_vbF = commondir+"AN_v0_Sep08/{0}_137fb/Root_Limit_Overflow_100GeV_varbin/".format(sig2)  
#limit_v1_dir_ggF = commondir+"AN_v1_Feb19/{0}_137fb/Root_Limit_Overflow_100GeV_varbin/".format(sig1)  
limit_v1_dir_vbF = commondir+"AN_v1_Feb19/{0}_137fb/Root_Limit_Overflow_100GeV_varbin/".format(sig2)  
limit_nlo_dir =  commondir+"AN_v1_NLO_Feb19/{0}_137fb/Root_Limit/".format(sig2)  
#limit_nlo_dir =  commondir+"AN_v1_NLO_Feb19/Combined_VBFSample/{0}_Combo_137fb/Root_Limit/".format(sample)  

#filelist_v0_ggF1 = [f for f in os.listdir(limit_v0_dir_ggF) if isfile(join(limit_v0_dir_ggF, f)) if ".root" in f]
filelist_v0_vbF1 = [f for f in os.listdir(limit_v0_dir_vbF) if isfile(join(limit_v0_dir_vbF, f)) if ".root" in f]
#filelist_v1_ggF1 = [f for f in os.listdir(limit_v1_dir_ggF) if isfile(join(limit_v1_dir_ggF, f)) if ".root" in f]
filelist_v1_vbF1 = [f for f in os.listdir(limit_v1_dir_vbF) if isfile(join(limit_v1_dir_vbF, f)) if ".root" in f]
filelist_nlo1  = [f for f in os.listdir(limit_nlo_dir)  if isfile(join(limit_nlo_dir, f)) if ".root" in f]

def NumberOfString(s):
  if 'H' in s[-9:-6]:
     return int(s[-8:-6])
  else:
     return int(s[-9:-6])

#meanexparraysorted    = [ x for x in sorted(filelist_v0_vbF,    key=lambda tup: NumberOfString(tup)) ]
#filelist_v0_ggF = [ x for x in sorted(filelist_v0_ggF1,    key=lambda tup: NumberOfString(tup)) ]
filelist_v0_vbF = [ x for x in sorted(filelist_v0_vbF1,    key=lambda tup: NumberOfString(tup)) ]    
#filelist_v1_ggF = [ x for x in sorted(filelist_v1_ggF1,    key=lambda tup: NumberOfString(tup)) ]
filelist_v1_vbF = [ x for x in sorted(filelist_v1_vbF1,    key=lambda tup: NumberOfString(tup)) ]
filelist_nlo  = [ x for x in sorted(filelist_nlo1,    key=lambda tup: NumberOfString(tup)) ]

print""
print "file v0 vbF: {}".format(filelist_v0_vbF)
print""
print "file v1 vbF: {}".format(filelist_v1_vbF)
print""


expLimit_v0_ggF = []
expLimit_v0_vbF = []
expLimit_v1_ggF = []
expLimit_v1_vbF = []
expLimit_nlo = []

for filename in filelist_v0_vbF:
    infile=TFile(limit_v0_dir_vbF+"/"+filename,"READ")
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimit_v0_vbF.append(round(event.limit,3))

for filename in filelist_v1_vbF:
    infile=TFile(limit_v1_dir_vbF+"/"+filename,"READ")
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimit_v1_vbF.append(round(event.limit,3))

for filename in filelist_nlo:
    infile=TFile(limit_nlo_dir+"/"+filename,"READ")
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimit_nlo.append(round(event.limit,3))

print""
print "limit v0 vbF: {}".format(expLimit_v0_vbF)
print""
print "limit v1 vbF: {}".format(expLimit_v1_vbF)
print""
print "limit nlo: {}".format(expLimit_nlo)

cat = ["Mass","v0: vbF","v1: vbF","NLO"]

mp = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000]

print""
print ("Limit Investigation".center(50,'#'))
#print (sample.center(80,'+'))
print""
print ("".center(50,'+'))
print (txt.center(50,'+'))
print ("".center(50,'+'))
print" {:<7s} & {:<8s} & {:<8s} & {:<12s} \\\\ ".format(cat[0],cat[1],cat[2],cat[3])
print ("".center(50,'+'))

#if sample == "BulkG":
if sample == "ggFG":
    print "wrong category, maybe you should run it at Combined_ggFSample dir."
else:
    for i in range(len(mp)):
        print" {:<7.1f} & {:<8.2f} & {:<8.2f} & {:<12.2f} \\\\ ".format(
        #print"||{:<7.1f}||{0:<8.2f}||{1:<7s}||{2:<7s}||{3:<7s}||{4:<9s}|| ".format(
        mp[i],expLimit_v0_vbF[i],expLimit_v1_vbF[i],expLimit_nlo[i]
    )

print ("".center(50,'+'))
print ""




