from sys import argv
import ROOT as r
import code

f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")
f2 = r.TFile.Open("Alpha_HP_VBFvsNoVBF_2016_v4.root")
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

hDataSBnovbf = f1.Get("ZMT2_ZSBHPNoVBF_Data")
hDataSBvbf = f1.Get("ZMT2_ZSBHPVBF_Data")
h4sbnovbf = f1.Get("Dom_Bkg_SBHPNoVBF")
h4sbvbf = f1.Get("Dom_Bkg_SBHPVBF")
hRsbnovbf = f1.Get("SubDom_Bkg_SBHPNoVBF")
hRsbvbf = f1.Get("SubDom_Bkg_SBHPVBF")
h4srnovbf = f1.Get("Dom_Bkg_SRHPNoVBF")
h4srvbf = f1.Get("Dom_Bkg_SRHPVBF")
hRsrnovbf = f1.Get("SubDom_Bkg_SRHPNoVBF")
hRsrvbf = f1.Get("SubDom_Bkg_SRHPVBF")
hAlphanovbf = f2.Get("h4Alphanovbf")
hAlphavbf = f2.Get("h4Alphavbf")

foutput_name = "BkgEst_HP_VBFvsNoVBF_2016_v4.root"

#######################################
# Alpha = SR/SB for Dominant Bkg  ##
#######################################
r.gPad.SetLogy(1)

# [(Data SB - Rare Bkg SB)*alpha] + Rare bkg in SR 

#######################################
# HP No VBF Category  ##
#######################################
hEstBkgNoVbf = hDataSBnovbf.Clone("hEstBkgNoVbf")
hEstBkgNoVbf.Add(hRsbnovbf,-1)
hEstBkgNoVbf.Multiply(hAlphanovbf)
hEstBkgNoVbf.Add(hRsrnovbf)

#######################################
# HP VBF Category  ##
#######################################
hEstBkgVbf = hDataSBvbf.Clone("hEstBkgVbf")
hEstBkgVbf.Add(hRsbvbf,-1)
hEstBkgVbf.Multiply(hAlphavbf)
hEstBkgVbf.Add(hRsrvbf)

print "estbkg for novbf, vbf, and ratio: {0}, {1}, {2}".format(hEstBkgNoVbf.Integral(), hEstBkgVbf.Integral(), hEstBkgNoVbf.Integral()/hEstBkgVbf.Integral())

#hEstBkgNoVbf.SetTitle("Estimated Bkg: HP VBF vs HP No VBF")
hEstBkgNoVbf.SetTitle("")
hEstBkgNoVbf.GetYaxis().SetTitle("Est. Bkg")
hEstBkgNoVbf.SetMarkerStyle(20)
hEstBkgNoVbf.SetMarkerColor(r.kBlue)
hEstBkgNoVbf.SetLineColor(r.kBlue)

hEstBkgNoVbf.GetYaxis().SetLabelFont(43);
hEstBkgNoVbf.GetYaxis().SetLabelSize(24);
hEstBkgNoVbf.GetYaxis().SetTitleFont(43);
hEstBkgNoVbf.GetYaxis().SetTitleSize(24);
hEstBkgNoVbf.GetYaxis().SetTitleOffset(1.7);

hEstBkgNoVbf.GetXaxis().SetLabelFont(43);
hEstBkgNoVbf.GetXaxis().SetLabelSize(24);
hEstBkgNoVbf.GetXaxis().SetTitleFont(43);
hEstBkgNoVbf.GetXaxis().SetTitleSize(24);
hEstBkgNoVbf.GetXaxis().SetTitleOffset(1.7);

hEstBkgVbf.SetMarkerStyle(20)
hEstBkgVbf.SetMarkerColor(r.kBlack)
hEstBkgVbf.SetLineColor(r.kBlack)
hEstBkgNoVbf.Draw("E1")
hEstBkgVbf.Draw("E1 same")

   # For legend
l1 = r.TLegend(0.45,.74,.8,.92)
l1.SetFillColor(0)
l1.SetLineColor(r.kWhite)
l1.SetTextSize(0.055)

l1.AddEntry(hEstBkgNoVbf,"N_{SR}^{predicted}: HP NoVBF","p")
l1.AddEntry(hEstBkgVbf,"N_{SR}^{predicted}: HP VBF","p")
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

################################
################################
botPad.cd()

h1novbf1 = hEstBkgNoVbf.Clone("h1novbf1")
h1vbf1 = hEstBkgVbf.Clone("h1vbf1")
h1novbf1.Divide(h1vbf1)
h1novbf1.SetTitle("")
h1novbf1.GetYaxis().SetTitle("NoVBF/VBF")
h1novbf1.GetYaxis().SetRangeUser(0,60)
h1novbf1.SetMarkerStyle(20)
h1novbf1.SetMarkerColor(r.kBlack)
h1novbf1.SetLineColor(r.kBlack)
h1novbf1.GetYaxis().SetLabelFont(43);
h1novbf1.GetYaxis().SetLabelSize(24);
h1novbf1.GetYaxis().SetTitleFont(43);
h1novbf1.GetYaxis().SetTitleSize(24);
h1novbf1.GetYaxis().SetNdivisions(505);
h1novbf1.GetYaxis().SetTitleOffset(1.7);
h1novbf1.GetXaxis().SetLabelFont(43);
h1novbf1.GetXaxis().SetLabelSize(24);
h1novbf1.GetXaxis().SetTitleFont(43);
h1novbf1.GetXaxis().SetTitleSize(24);
h1novbf1.GetXaxis().SetTitleOffset(2.8)

h1novbf1.Draw("E1")

c.SaveAs("BkgEst_VBFvsNoVBF_2016_v4_LogY_Ratio.png")

fout = r.TFile(foutput_name,"RECREATE")
fout.cd()
hEstBkgNoVbf.Write()
hEstBkgVbf.Write()


