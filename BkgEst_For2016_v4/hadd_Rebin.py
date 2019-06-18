import ROOT as r
from ROOT import *
import sys

def include_overflow(histo):
    temp=r.TH1F(histo.GetName()+"_inc_ovrflw",histo.GetTitle(),histo.GetNbinsX()+1,histo.GetBinLowEdge(1),histo.GetBinLowEdge(histo.GetNbinsX())+2*histo.GetBinWidth(histo.GetNbinsX()))
    for i in xrange(1,histo.GetNbinsX()+2):
        temp.SetBinContent(i,histo.GetBinContent(i))
        temp.SetBinError(i,histo.GetBinError(i))
    return temp

f1 = r.TFile.Open("ZSRHPVBF_515_v4_2016_pt30GeV_Output.root")
f2 = r.TFile.Open("ZSBHPVBF_515_v4_2016_pt30GeV_v2_Output.root")
foutname = "LimitDebug_Rebin_2016_VBF_Bkg_25GeV_bin.root"

######################
### for SR VBF ######
#####################

h1 = f1.Get("ZMT2_ZSRHPVBF_ZJets")
h2 = f1.Get("ZMT2_ZSRHPVBF_WJets")
h3 = f1.Get("ZMT2_ZSRHPVBF_TT")
h4 = f1.Get("ZMT2_ZSRHPVBF_Other")
h5 = f1.Get("ZMT2_ZSRHPVBF_Single top")

SR_Dom = r.TH1F(h1)
SR_Dom.Add(h2)
SR_Rare = r.TH1F(h3)
SR_Rare.Add(h4)
SR_Rare.Add(h5)

print "integral of Dom: {0}, rare: {1}".format(SR_Dom.Integral(),SR_Rare.Integral())

## Rebin plotting with Overflow bin
hdomsr = r.TH1F(SR_Dom)
hraresr = r.TH1F(SR_Rare)
SR_Dom_Rebin = include_overflow(hdomsr)
SR_Rare_Rebin = include_overflow(hraresr)

print "Rebinned integral of Dom: {0}, rare: {1}".format(SR_Dom_Rebin.Integral(),SR_Rare_Rebin.Integral())

######################
### for SB VBF ######
#####################

h11 = f2.Get("ZMT2_ZSBHPVBF_ZJets")
h21 = f2.Get("ZMT2_ZSBHPVBF_WJets")
h31 = f2.Get("ZMT2_ZSBHPVBF_TT")
h41 = f2.Get("ZMT2_ZSBHPVBF_Other")
h51 = f2.Get("ZMT2_ZSBHPVBF_Single top")

print "SR: Integral\n"
print "SR Zj: {0}\n".format(h1.Integral())
print "SR Wj: {0}\n".format(h2.Integral())
print "SR TT: {0}\n".format(h3.Integral())
print "SR Oth: {0}\n".format(h4.Integral())
print "SR St: {0}\n".format(h5.Integral())
print ""
print "SB: Integral\n"
print "SB Zj: {0}\n".format(h11.Integral())
print "SB Wj: {0}\n".format(h21.Integral())
print "SB TT: {0}\n".format(h31.Integral())
print "SB Oth: {0}\n".format(h41.Integral())
print "SB St: {0}\n".format(h51.Integral())

SB_Dom = r.TH1F(h11)
SB_Dom.Add(h21)
SB_Rare = r.TH1F(h31)
SB_Rare.Add(h41)
SB_Rare.Add(h51)

print ""
print "integral of Dom: {0}, rare: {1}".format(SB_Dom.Integral(),SB_Rare.Integral())

## Rebin plotting with Overflow bin
hdomsb = r.TH1F(SB_Dom)
hraresb = r.TH1F(SB_Rare)
SB_Dom_Rebin = include_overflow(hdomsb)
SB_Rare_Rebin = include_overflow(hraresb)

print "Rebinned integral of Dom: {0}, rare: {1}".format(SB_Dom_Rebin.Integral(),SB_Rare_Rebin.Integral())

fout = r.TFile(foutname,"RECREATE")
fout.cd()

SR_Dom_Rebin.Write()
SR_Rare_Rebin.Write()
SB_Dom_Rebin.Write()
SB_Rare_Rebin.Write()


f1.Close()
f2.Close()
