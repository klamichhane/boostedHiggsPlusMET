import ROOT as r
from ROOT import *
import os
from sys import argv

cat = "VBF"
#cat = "ggF"
#obj = "MET"
#obj = "pT"
obj = "MT"
#obj = "Eta"

f1 = r.TFile.Open("plotObs_ZNoSelection_baseline_ggFG_4500.root")
f2 = r.TFile.Open("plotObs_ZNoSelection_baseline_VBFG_4500.root")
f3 = r.TFile.Open("plotObs_ZNoSelection_baseline_ggFRad_4500.root")
f4 = r.TFile.Open("plotObs_ZNoSelection_baseline_VBFRad_4500.root")
f5 = r.TFile.Open("plotObs_ZNoSelection_baseline_VBFWp_4500.root")

ggF_G = f1.Get("MET_ZNoSelection_ggFG_4500")
ggF_Rad = f3.Get("MET_ZNoSelection_ggFRad_4500")

# MET, AK8L1J_Pt, J1pt_Eta1, ZMT9

VBF_Rad = f4.Get("ZMT9_ZNoSelection_VBFRad_4500")
VBF_Wp  = f5.Get("ZMT9_ZNoSelection_VBFWp_4500")
VBF_G   = f2.Get("ZMT9_ZNoSelection_VBFG_4500")

#ytitle = "MET [GeV]"

def legend_setup():
    leg = r.TLegend(0.68,.74,.88,.92)
    leg.SetLineColor(r.kWhite)
    leg.SetTextFont(51)
    leg.SetTextSize(0.04)
    return leg 


c=r.TCanvas("c","c",500,500)
c.SetTopMargin(0.06)
c.SetLeftMargin(0.15)
c.SetBottomMargin(0.15)

#VBF_G.SetMaximum(2*max(VBF_G.GetMaximum(),VBF_Rad.GetMaximum()))
VBF_Rad.SetTitle("")
#VBF_Rad.GetYaxis().SetTitle("Events")
VBF_Rad.GetYaxis().SetTitle("")
#VBF_Rad.GetYaxis().SetTitle(VBF_Rad.GetYaxis().GetTitle())
VBF_Rad.GetXaxis().SetTitle(VBF_Rad.GetXaxis().GetTitle())
#VBF_Rad.GetXaxis().SetTitle(vbf_sb_vj.GetXaxis().GetTitle())
VBF_Rad.SetMarkerStyle(20)
VBF_Rad.SetMarkerColor(r.kBlack)
VBF_Rad.SetLineColor(r.kBlack)
VBF_Rad.GetYaxis().SetLabelFont(43);
VBF_Rad.GetYaxis().SetLabelSize(24);
VBF_Rad.GetYaxis().SetTitleFont(43);
VBF_Rad.GetYaxis().SetTitleSize(24);
VBF_Rad.GetYaxis().SetTitleOffset(1.3);
VBF_Rad.GetYaxis().SetNdivisions(505);

VBF_Rad.GetXaxis().SetLabelFont(43);
VBF_Rad.GetXaxis().SetLabelSize(24);
VBF_Rad.GetXaxis().SetTitleFont(43);
VBF_Rad.GetXaxis().SetTitleSize(24);
VBF_Rad.GetXaxis().SetTitleOffset(1.1);
VBF_Rad.GetXaxis().SetNdivisions(505);

VBF_G.SetLineColor(r.kBlack);
VBF_Wp.SetLineColor(r.kBlue);
VBF_Rad.SetLineColor(r.kRed);
VBF_G.SetLineWidth(2);
VBF_Wp.SetLineWidth(2);
VBF_Rad.SetLineWidth(2);

VBF_G.Scale(1/VBF_G.Integral())
VBF_Wp.Scale(1/VBF_Wp.Integral())
VBF_Rad.Scale(1/VBF_Rad.Integral())

if obj != "MT":
    VBF_G.Rebin(2)
    VBF_Wp.Rebin(2)
    VBF_Rad.Rebin(2)

VBF_Rad.SetMaximum(1.5*(VBF_Rad.GetMaximum()))

VBF_Rad.Draw("histo")
VBF_Wp.Draw("histo same")
VBF_G.Draw("histo same")

leg2 = legend_setup()
leg2.AddEntry(VBF_Rad,"Spin 0","l")
leg2.AddEntry(VBF_Wp,"Spin 1","l")
leg2.AddEntry(VBF_G,"Spin 2","l")
leg2.Draw()

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
LUMItext = r.TText(.60,.95,"13 TeV")
LUMItext.SetNDC()
LUMItext.SetTextFont(51)
LUMItext.SetTextSize(0.04)
LUMItext.Draw()

c.SaveAs(cat+"_"+obj+".pdf")
