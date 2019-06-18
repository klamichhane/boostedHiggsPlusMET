from sys import argv
import ROOT as r
import code

f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")
f2 = r.TFile.Open("BkgEst_HP_VBFvsNoVBF_2016_v4.root")
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
r.gPad.SetLogy(1)

hT= f1.Get("TotalBkg_SRHPVBF")
hE= f2.Get("hEstBkgVbf")

print "estbkg, mc, and ratio: {0}, {1}, {2}".format(hE.Integral(), hT.Integral(), hE.Integral()/hT.Integral())

#hE.SetTitle("HP VBF: Estimated vs total bkg")
hE.SetTitle("")
#hE.SetMaximum(20.0*max(hE.GetMaximum(), hT.GetMaximum))
hE.SetMaximum(20.0*hE.GetMaximum())
#hE.SetMinimum(0.000001)
#hT.SetMinimum(0.000001)
hE.GetYaxis().SetTitle("Events")
hE.SetMarkerStyle(20)
hE.SetMarkerColor(r.kBlack)
hE.SetLineColor(r.kBlack)
hE.GetYaxis().SetLabelFont(43);
hE.GetYaxis().SetLabelSize(24);
hE.GetYaxis().SetTitleFont(43);
hE.GetYaxis().SetTitleSize(24);
hE.GetYaxis().SetTitleOffset(1.7);

hE.GetXaxis().SetLabelFont(43);
hE.GetXaxis().SetLabelSize(24);
hE.GetXaxis().SetTitleFont(43);
hE.GetXaxis().SetTitleSize(24);
hE.GetXaxis().SetTitleOffset(1.7);

hT.SetMarkerStyle(20)
hT.SetMarkerColor(r.kRed)
hT.SetLineColor(r.kRed)
hE.Draw("E1")
hT.Draw("E1 same")

   # For legend
l1 = r.TLegend(0.45,.74,.8,.92)
l1.SetFillColor(0)
l1.SetLineColor(r.kWhite)
l1.SetTextSize(0.055)

l1.AddEntry(hE,"N_{SR}^{predicted}: HP VBF","p")
l1.AddEntry(hT,"N_{SR}^{MC bkg}: HP VBF","p")
l1.Draw()

#txt1 = r.TText(.55,.65,"Ratio = 1.05")
#txt1.SetNDC()
#txt1.SetTextFont(51)
#txt1.SetTextSize(0.055)
#txt1.Draw()

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

##################################
##################################
botPad.cd()

Ratio = hE.Clone("Ratio")
RatMC = hT.Clone("MC")

Ratio.Divide(RatMC)
Ratio.SetTitle("")
Ratio.GetYaxis().SetRangeUser(0,2)
Ratio.GetYaxis().SetTitle("Data^{Pred}/MC")
Ratio.SetMarkerStyle(20)
Ratio.SetMarkerColor(r.kBlack)
Ratio.SetLineColor(r.kBlack)

Ratio.GetYaxis().SetLabelFont(43);
Ratio.GetYaxis().SetLabelSize(24);
Ratio.GetYaxis().SetTitleFont(43);
Ratio.GetYaxis().SetTitleSize(24);
Ratio.GetYaxis().SetNdivisions(505);
Ratio.GetYaxis().SetTitleOffset(1.7);
Ratio.GetXaxis().SetLabelFont(43);
Ratio.GetXaxis().SetLabelSize(24);
Ratio.GetXaxis().SetTitleFont(43);
Ratio.GetXaxis().SetTitleSize(24);
Ratio.GetXaxis().SetTitleOffset(2.8)

Ratio.Draw("E1")

l = r.TLine(400,1.0,1500,1.0)
l.SetLineColor(r.kRed)
l.SetLineWidth(2)
l.Draw("same")

c.SaveAs("BkgEst_VBF_2016_v4_LogY.png")

