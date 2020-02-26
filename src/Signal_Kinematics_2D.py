import ROOT as r
from ROOT import *
import os
from sys import argv

cat = "VBF"
#cat = "ggF"

sample = "Graviton"
#sample = "Wprime"
#sample = "Radion"

f1 = r.TFile.Open("plotObs_ZNoSelection_baseline_ggFG_4500.root")
f2 = r.TFile.Open("plotObs_ZNoSelection_baseline_VBFG_4500.root")
f3 = r.TFile.Open("plotObs_ZNoSelection_baseline_ggFRad_4500.root")
f4 = r.TFile.Open("plotObs_ZNoSelection_baseline_VBFRad_4500.root")
f5 = r.TFile.Open("plotObs_ZNoSelection_baseline_VBFWp_4500.root")

histo = f2.Get("AK8EtavsZMT_ZNoSelection_VBFG_4500")
#histo = f5.Get("AK8EtavsZMT_ZNoSelection_VBFWp_4500")
#histo = f4.Get("AK8EtavsZMT_ZNoSelection_VBFRad_4500")

#histo = f3.Get("AK8EtavsZMT_ZNoSelection_ggFRad_4500")
#histo = f1.Get("AK8EtavsZMT_ZNoSelection_ggFG_4500")

c=r.TCanvas("c","c",500,500)
c.SetTopMargin(0.06)
c.SetLeftMargin(0.15)
c.SetRightMargin(0.15)
c.SetBottomMargin(0.15)

r.gPad.SetLogz(1)

histo.SetTitle("")
#histo.GetYaxis().SetTitle("Events")
#histo.GetYaxis().SetTitle("")
histo.GetYaxis().SetTitle(histo.GetYaxis().GetTitle())
histo.GetXaxis().SetTitle(histo.GetXaxis().GetTitle())
histo.GetYaxis().SetLabelFont(43);
histo.GetYaxis().SetLabelSize(24);
histo.GetYaxis().SetTitleFont(43);
histo.GetYaxis().SetTitleSize(24);
histo.GetYaxis().SetTitleOffset(1.3);
histo.GetYaxis().SetNdivisions(505);

histo.GetXaxis().SetLabelFont(43);
histo.GetXaxis().SetLabelSize(24);
histo.GetXaxis().SetTitleFont(43);
histo.GetXaxis().SetTitleSize(24);
histo.GetXaxis().SetTitleOffset(1.1);
histo.GetXaxis().SetNdivisions(505);

histo.Draw("colz")

CMStext = r.TText(.17,.95,"CMS")
CMStext.SetNDC()
CMStext.SetTextFont(61)
CMStext.SetTextSize(0.04)
CMStext.Draw()

SIMtext = r.TText(.28,.95,"preliminary")
SIMtext.SetNDC()
SIMtext.SetTextFont(52)
SIMtext.SetTextSize(0.04)
SIMtext.Draw()

#LUMItext = r.TText(.60,.95,"13 TeV ("+lumi+"/fb)")
LUMItext = r.TText(.6,.95,"13 TeV")
LUMItext.SetNDC()
LUMItext.SetTextFont(51)
LUMItext.SetTextSize(0.04)
LUMItext.Draw()

txt1 = r.TText(.55,.875,cat+" "+sample)
txt1.SetNDC()
txt1.SetTextSize(0.05)
txt1.SetTextColor(r.kOrange+10)
txt1.Draw()

c.SaveAs(cat+"_"+sample+"_2D.pdf")
