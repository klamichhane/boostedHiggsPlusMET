from sys import argv
import ROOT as r
import code

f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")

h4sbnovbf = f1.Get("Dom_Bkg_SBHPNoVBF")
h4sbvbf = f1.Get("Dom_Bkg_SBHPVBF")
h4srnovbf = f1.Get("Dom_Bkg_SRHPNoVBF")
h4srvbf = f1.Get("Dom_Bkg_SRHPVBF")
foutput_name = "Alpha_HP_VBFvsNoVBF_2016_v4.root"

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



#######################################
# Alpha = SR/SB for Dominant Bkg  ##
#######################################

h4Alphanovbf = h4srnovbf.Clone("h4Alphanovbf") # Dom bkg SRHPNoVBF
h4Alphavbf = h4srvbf.Clone("h4Alphavbf") # Dom bkg SRHPVBF

h4Alphanovbf.Divide(h4sbnovbf)
h4Alphavbf.Divide(h4sbvbf)

hAlphanovbf1 = h4Alphanovbf.Clone("h4Alphanovbf1")
hAlphavbf1 = h4Alphavbf.Clone("h4Alphavbf1")
#h4Alphavbf.SetTitle("Alpha: HP VBF vs HP No VBF")
h4Alphanovbf.SetTitle("")
h4Alphanovbf.GetYaxis().SetTitle("Alpha: (N_{SR}/N_{SB})^{Vjet}")
h4Alphanovbf.SetMarkerStyle(20)
h4Alphanovbf.SetMarkerColor(r.kBlue)
h4Alphanovbf.SetLineColor(r.kBlue)
h4Alphanovbf.GetYaxis().SetLabelFont(43);
h4Alphanovbf.GetYaxis().SetLabelSize(24);
h4Alphanovbf.GetYaxis().SetTitleFont(43);
h4Alphanovbf.GetYaxis().SetTitleSize(24);
h4Alphanovbf.GetYaxis().SetTitleOffset(1.7);

h4Alphanovbf.GetXaxis().SetLabelFont(43);
h4Alphanovbf.GetXaxis().SetLabelSize(24);
h4Alphanovbf.GetXaxis().SetTitleFont(43);
h4Alphanovbf.GetXaxis().SetTitleSize(24);
h4Alphanovbf.GetXaxis().SetTitleOffset(1.7);


h4Alphavbf.SetMarkerStyle(20)
h4Alphavbf.SetMarkerColor(r.kBlack)
h4Alphavbf.SetLineColor(r.kBlack)
h4Alphanovbf.Draw("E1")
h4Alphavbf.Draw("E1 same")

   # For legend
l1 = r.TLegend(0.6,.74,.8,.92)
l1.SetFillColor(0)
l1.SetLineColor(r.kWhite)
l1.SetTextSize(0.055)

l1.AddEntry(h4Alphanovbf,"HP NoVBF","p")
l1.AddEntry(h4Alphavbf,"HP VBF","p")
l1.Draw()

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

###############################
# Ratio of alpha for no-vbf/vbf
botPad.cd()
hAlphanovbf1.Divide( hAlphavbf1)
hAlphanovbf1.SetTitle("")
hAlphanovbf1.GetYaxis().SetRangeUser(0,2)
hAlphanovbf1.GetYaxis().SetTitle("#alpha^{NoVBF}/#alpha^{VBF}")
hAlphanovbf1.SetMarkerStyle(20)
hAlphanovbf1.SetMarkerColor(r.kBlack)
hAlphanovbf1.SetLineColor(r.kBlack)
hAlphanovbf1.GetYaxis().SetLabelFont(43);
hAlphanovbf1.GetYaxis().SetLabelSize(24);
hAlphanovbf1.GetYaxis().SetTitleFont(43);
hAlphanovbf1.GetYaxis().SetTitleSize(24);
hAlphanovbf1.GetYaxis().SetNdivisions(505);
hAlphanovbf1.GetYaxis().SetTitleOffset(1.7);
hAlphanovbf1.GetXaxis().SetLabelFont(43);
hAlphanovbf1.GetXaxis().SetLabelSize(24);
hAlphanovbf1.GetXaxis().SetTitleFont(43);
hAlphanovbf1.GetXaxis().SetTitleSize(24);
hAlphanovbf1.GetXaxis().SetTitleOffset(2.8)


hAlphanovbf1.Draw("E1")

l = r.TLine(400,1.0,1500,1.0)
l.SetLineColor(r.kRed)
l.SetLineWidth(2)
l.Draw("same")

c.SaveAs("Alpha_VBFvsNoVBF_2016_v4.png")

fout = r.TFile(foutput_name,"RECREATE")
fout.cd()
h4Alphavbf.Write()
h4Alphanovbf.Write()


