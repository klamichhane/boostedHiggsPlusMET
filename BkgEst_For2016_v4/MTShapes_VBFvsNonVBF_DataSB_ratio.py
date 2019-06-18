from sys import argv
import ROOT as r
import code

f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")

h1sbnovbf = f1.Get("ZMT2_ZSBHPNoVBF_Data")
h2sbnovbf = f1.Get("ZMT2_ZSBHPNoVBF_VBFG_1200")
h3sbnovbf = f1.Get("TotalBkg_SBHPNoVBF")
h4sbnovbf = f1.Get("Dom_Bkg_SBHPNoVBF")

h1sbvbf = f1.Get("ZMT2_ZSBHPVBF_Data")
h2sbvbf = f1.Get("ZMT2_ZSBHPVBF_VBFG_1200")
h3sbvbf = f1.Get("TotalBkg_SBHPVBF")
h4sbvbf = f1.Get("Dom_Bkg_SBHPVBF")

c = r.TCanvas("c","c",600,600)
topPad = r.TPad("topPad","topPad",0.,0.4,.99,.99);
botPad = r.TPad("botPad","botPad",0.,0.01,.99,.39);
botPad.SetBottomMargin(0.35);
botPad.SetTopMargin(0.02);
botPad.SetLeftMargin(0.15);
topPad.SetTopMargin(0.06);
topPad.SetBottomMargin(0.01);
topPad.SetLeftMargin(0.15);
topPad.Draw();
botPad.Draw();
topPad.cd();

#############################################
# Z SB HP No VBF: MT Shapes for 2016 Data  ##
#############################################

r.gPad.SetLogy(1)
#h1sbnovbf.SetTitle("2016 Data SB: HPVBF vs HPNoVBF")
h1sbnovbf.SetTitle("")
h1sbnovbf.GetYaxis().SetTitle("Events")
h1sbnovbf.SetMarkerStyle(20)
h1sbnovbf.SetMarkerColor(r.kBlue)
h1sbnovbf.SetLineColor(r.kBlue)
h1sbnovbf.GetYaxis().SetLabelFont(43);
h1sbnovbf.GetYaxis().SetLabelSize(24);
h1sbnovbf.GetYaxis().SetTitleFont(43);
h1sbnovbf.GetYaxis().SetTitleSize(24);
h1sbnovbf.GetYaxis().SetTitleOffset(1.7);

h1sbnovbf.GetXaxis().SetLabelFont(43);
h1sbnovbf.GetXaxis().SetLabelSize(24);
h1sbnovbf.GetXaxis().SetTitleFont(43);
h1sbnovbf.GetXaxis().SetTitleSize(24);
h1sbnovbf.GetXaxis().SetTitleOffset(1.7);

h1sbvbf.SetMarkerStyle(20)
h1sbvbf.SetMarkerColor(r.kBlack)
h1sbvbf.SetLineColor(r.kBlack)
h1sbnovbf.Draw("E1")
h1sbvbf.Draw("E1 same")

print "Data no vbf integral: {0}; vbf integral: {1}; ratio: {2}".format(h1sbnovbf.Integral(), h1sbvbf.Integral(), h1sbnovbf.Integral()/h1sbvbf.Integral())
   # For legend
l2 = r.TLegend(0.45,.74,.8,.92)
l2.SetFillColor(0)
l2.SetLineColor(r.kWhite)
l2.SetTextSize(0.055)

l2.AddEntry(h1sbnovbf,"SB HP NoVBF","p")
l2.AddEntry(h1sbvbf,"SB HP VBF","p")
l2.Draw()

txt4 = r.TText(.575,.575,"Data SB")
txt4.SetNDC()
txt4.SetTextSize(0.05)
txt4.SetTextColor(r.kOrange+10)
txt4.Draw("same")

CMStext = r.TText(.17,.95,"CMS")
CMStext.SetNDC()
CMStext.SetTextFont(61)
CMStext.SetTextSize(0.06)
CMStext.Draw()

SIMtext = r.TText(.28,.95,"preliminary")
SIMtext.SetNDC()
SIMtext.SetTextFont(52)
SIMtext.SetTextSize(0.06)
SIMtext.Draw()

LUMItext = r.TText(.60,.95,"13 TeV (35.8/fb)")
LUMItext.SetNDC()
LUMItext.SetTextFont(51)
LUMItext.SetTextSize(0.06)
LUMItext.Draw()

#########################################################
# Ratio of NoVBF/VBF for Data in SB  ##
#########################################################
botPad.cd()
#r.gPad.SetBottomMargin(0.15)
#r.gPad.SetLeftMargin(0.15)
h1sbnovbf1 = h1sbnovbf.Clone("h1sbnovbf1")
h1sbvbf1 = h1sbvbf.Clone("h1sbvbf1")
h1sbnovbf1.Divide(h1sbvbf1)
h1sbnovbf1.SetTitle("")
h1sbnovbf1.GetYaxis().SetTitle("NoVBF/VBF")
h1sbnovbf1.GetYaxis().SetRangeUser(0,60)
h1sbnovbf1.SetMarkerStyle(20)
h1sbnovbf1.SetMarkerColor(r.kBlack)
h1sbnovbf1.SetLineColor(r.kBlack)
h1sbnovbf1.GetYaxis().SetLabelFont(43);
h1sbnovbf1.GetYaxis().SetLabelSize(24);
h1sbnovbf1.GetYaxis().SetTitleFont(43);
h1sbnovbf1.GetYaxis().SetTitleSize(24);
h1sbnovbf1.GetYaxis().SetNdivisions(505);
h1sbnovbf1.GetYaxis().SetTitleOffset(1.7);
h1sbnovbf1.GetXaxis().SetLabelFont(43);
h1sbnovbf1.GetXaxis().SetLabelSize(24);
h1sbnovbf1.GetXaxis().SetTitleFont(43);
h1sbnovbf1.GetXaxis().SetTitleSize(24);
h1sbnovbf1.GetXaxis().SetTitleOffset(2.8)

h1sbnovbf1.Draw("E1")

c.SaveAs("DataSB_MTShapes_2016_v4.png")
