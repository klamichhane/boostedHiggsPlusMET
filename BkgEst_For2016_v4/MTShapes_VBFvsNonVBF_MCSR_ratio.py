from sys import argv
import ROOT as r
import code

f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")

h2srnovbf = f1.Get("ZMT2_ZSRHPNoVBF_VBFG_1200")
h3srnovbf = f1.Get("TotalBkg_SRHPNoVBF")
h4srnovbf = f1.Get("Dom_Bkg_SRHPNoVBF")

h2srvbf = f1.Get("ZMT2_ZSRHPVBF_VBFG_1200")
h3srvbf = f1.Get("TotalBkg_SRHPVBF")
h4srvbf = f1.Get("Dom_Bkg_SRHPVBF")

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
#h3srnovbf.SetTitle("MC SR: HPVBF vs HPNoVBF")
h3srnovbf.SetTitle("")
h3srnovbf.GetYaxis().SetTitle("Events")
h3srnovbf.SetMarkerStyle(20)
h3srnovbf.SetMarkerColor(r.kBlue)
h3srnovbf.SetLineColor(r.kBlue)
h3srnovbf.GetYaxis().SetLabelFont(43);
h3srnovbf.GetYaxis().SetLabelSize(24);
h3srnovbf.GetYaxis().SetTitleFont(43);
h3srnovbf.GetYaxis().SetTitleSize(24);
h3srnovbf.GetYaxis().SetTitleOffset(1.7);

h3srnovbf.GetXaxis().SetLabelFont(43);
h3srnovbf.GetXaxis().SetLabelSize(24);
h3srnovbf.GetXaxis().SetTitleFont(43);
h3srnovbf.GetXaxis().SetTitleSize(24);
h3srnovbf.GetXaxis().SetTitleOffset(1.7);

h3srvbf.SetMarkerStyle(20)
h3srvbf.SetMarkerColor(r.kBlack)
h3srvbf.SetLineColor(r.kBlack)
h3srnovbf.Draw("E1")
h3srvbf.Draw("E1 same")

print "Data no vbf integral: {0}; vbf integral: {1}; ratio: {2}".format(h3srnovbf.Integral(), h3srvbf.Integral(), h3srnovbf.Integral()/h3srvbf.Integral())
   # For legend
l2 = r.TLegend(0.45,.74,.8,.92)
l2.SetFillColor(0)
l2.SetLineColor(r.kWhite)
l2.SetTextSize(0.055)

l2.AddEntry(h3srnovbf,"SR HP NoVBF","p")
l2.AddEntry(h3srvbf,"SR HP VBF","p")
l2.Draw()

txt4 = r.TText(.575,.575,"MC SR")
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
h3srnovbf1 = h3srnovbf.Clone("h3srnovbf1")
h3srvbf1 = h3srvbf.Clone("h3srvbf1")
h3srnovbf1.Divide(h3srvbf1)
h3srnovbf1.SetTitle("")
h3srnovbf1.GetYaxis().SetTitle("NoVBF/VBF")
h3srnovbf1.GetYaxis().SetRangeUser(0,60)
h3srnovbf1.SetMarkerStyle(20)
h3srnovbf1.SetMarkerColor(r.kBlack)
h3srnovbf1.SetLineColor(r.kBlack)
h3srnovbf1.GetYaxis().SetLabelFont(43);
h3srnovbf1.GetYaxis().SetLabelSize(24);
h3srnovbf1.GetYaxis().SetTitleFont(43);
h3srnovbf1.GetYaxis().SetTitleSize(24);
h3srnovbf1.GetYaxis().SetNdivisions(505);
h3srnovbf1.GetYaxis().SetTitleOffset(1.7);
h3srnovbf1.GetXaxis().SetLabelFont(43);
h3srnovbf1.GetXaxis().SetLabelSize(24);
h3srnovbf1.GetXaxis().SetTitleFont(43);
h3srnovbf1.GetXaxis().SetTitleSize(24);
h3srnovbf1.GetXaxis().SetTitleOffset(2.8)

h3srnovbf1.Draw("E1")

c.SaveAs("MCSR_MTShapes_2016_v4.png")
