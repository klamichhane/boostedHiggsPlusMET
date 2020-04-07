#!/usr/bin/python
import ROOT as r
from ROOT import *
import sys
import os
from os.path import isfile, join

#sample = "Rad"
sample = "BulkG"
txt = sample + " with ggF sample"

if sample == "BulkG":
    sig1 = "ggFG"
    sig2 = "VBFG"
if sample == "Rad":
    sig1 = "ggFRad"
    sig2 = "VBFRad"

commondir = "/uscms_data/d3/kxlpp1/SUSY/SUSY_OCT2018/Limit-Combine-Tool/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/datacards/pyDatacard/Binned_DataCard_v1/"

limit_v0_dir_ggF = commondir+"AN_v0_Sep08/{0}_137fb/Root_Limit_Overflow_100GeV_varbin/".format(sig1)  
limit_v1_dir_ggF = commondir+"AN_v1_Feb19/{0}_137fb/Root_Limit_Overflow_100GeV_varbin/".format(sig1)  
limit_nlo_dir =  commondir+"AN_v1_NLO_Feb19/{0}_137fb/Root_Limit/".format(sig1)

filelist_v0_ggF1 = [f for f in os.listdir(limit_v0_dir_ggF) if isfile(join(limit_v0_dir_ggF, f)) if ".root" in f]
filelist_v1_ggF1 = [f for f in os.listdir(limit_v1_dir_ggF) if isfile(join(limit_v1_dir_ggF, f)) if ".root" in f]
filelist_nlo1  = [f for f in os.listdir(limit_nlo_dir)  if isfile(join(limit_nlo_dir, f)) if ".root" in f]

def NumberOfString(s):
  if 'H' in s[-9:-6]:
     return int(s[-8:-6])
  else:
     return int(s[-9:-6])

#meanexparraysorted    = [ x for x in sorted(filelist_v0_vbF,    key=lambda tup: NumberOfString(tup)) ]
filelist_v0_ggF = [ x for x in sorted(filelist_v0_ggF1,    key=lambda tup: NumberOfString(tup)) ]
filelist_v1_ggF = [ x for x in sorted(filelist_v1_ggF1,    key=lambda tup: NumberOfString(tup)) ]
filelist_nlo  = [ x for x in sorted(filelist_nlo1,    key=lambda tup: NumberOfString(tup)) ]

print""
print "file v0 ggF: {}".format(filelist_v0_ggF)
print""
print "file v1 ggF: {}".format(filelist_v1_ggF)
print""


expLimit_v0_ggF = []
expLimit_v1_ggF = []
expLimit_nlo = []

for filename in filelist_v0_ggF:
    infile=TFile(limit_v0_dir_ggF+"/"+filename,"READ")
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimit_v0_ggF.append(round(event.limit,3))

for filename in filelist_v1_ggF:
    infile=TFile(limit_v1_dir_ggF+"/"+filename,"READ")
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        #if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimitarray_1.append(round(event.limit*0.84,2)) #0.84 to takecare of muon in private sample.
        if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimit_v1_ggF.append(round(event.limit,3))

for filename in filelist_nlo:
    infile=TFile(limit_nlo_dir+"/"+filename,"READ")
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==2 and round(event.quantileExpected,2) == 0.5  : expLimit_nlo.append(round(event.limit,3))

print "limit v0 ggF: {}".format(expLimit_v0_ggF)
print""
print "limit v1 ggF: {}".format(expLimit_v1_ggF)
print""
print "limit nlo: {}".format(expLimit_nlo)
print""

cat = ["Mass","v0: ggF","v1: ggF","NLO"]

mp = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000]
mp_G = [1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]

print""
print ("Limit Investigation".center(55,'#'))
print""
print ("".center(55,'+'))
print (txt.center(55,'+'))
print ("".center(55,'+'))
print" {:<7s} & {:<8s} & {:<8s} & {:<8s} \\\\ ".format(cat[0],cat[1],cat[2],cat[3])
print ("".center(55,'+'))

if sample == "BulkG":
    for j in range(len(mp_G)):
        print" {:<7.1f} & {:<8.2f} & {:<8.2f} & {:<8.2f} \\\\ ".format(
        mp_G[j],expLimit_v0_ggF[j],expLimit_v1_ggF[j],expLimit_nlo[j]
    )
else:
    for i in range(len(mp)):
        print" {:<7.1f} & {:<8.2f} & {:<8.2f} & {:<8.2f} \\\\ ".format(
        mp[i],expLimit_v0_ggF[i],expLimit_v1_ggF[i],expLimit_nlo[i]
    )

print ("".center(55,'+'))
print ""




