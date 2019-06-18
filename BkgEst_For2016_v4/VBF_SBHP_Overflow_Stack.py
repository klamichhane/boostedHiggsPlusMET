import ROOT as r
import sys


#f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")
f1 = r.TFile.Open("../ForAlpha_n_BkgEst_FullRun2_SB_v4.root")
f2 = r.TFile.Open("../ForAlpha_n_BkgEst_FullRun2_SR_v4.root")
foutput_name = "VBF_SBHP_Overflow_FullRun2_v0.root"

h1 = f1.Get("SubBkgSB_HPVBF")
h2 = f1.Get("DomBkgSB_HPVBF")
h3 = f1.Get("DataSB_HPVBF")
h4 = f1.Get("TotBkgSB_HPVBF")

r.gStyle.SetOptStat(0)
can = r.TCanvas("can","can",500,500)
topPad = r.TPad("topPad","topPad",0.,0.4,.99,.99);
botPad = r.TPad("botPad","botPad",0.,0.01,.99,.39);
botPad.SetBottomMargin(0.35);
botPad.SetTopMargin(0.02);
botPad.SetLeftMargin(0.15);
topPad.SetLeftMargin(0.15);
topPad.SetTopMargin(0.06);
topPad.SetBottomMargin(0.01);
topPad.Draw();
botPad.Draw();
topPad.cd();

r.gPad.SetLogy(1)

def include_overflow(histo):
    temp=r.TH1F(histo.GetName()+"_inc_ovrflw",histo.GetTitle(),histo.GetNbinsX()+1,histo.GetBinLowEdge(1),histo.GetBinLowEdge(histo.GetNbinsX())+2*histo.GetBinWidth(histo.GetNbinsX()))
    for i in xrange(1,histo.GetNbinsX()+2):
        temp.SetBinContent(i,histo.GetBinContent(i))
        temp.SetBinError(i,histo.GetBinError(i))
    return temp

SubBkgSB_HPVBF_FullRun2 = include_overflow(h1)
DomBkgSB_HPVBF_FullRun2 = include_overflow(h2)
DataSB_HPVBF_FullRun2 = include_overflow(h3)
TotalBkgSB_HPVBF_FullRun2 = include_overflow(h4)

SubBkgSB_HPVBF_FullRun2.SetFillColor(r.kOrange)
SubBkgSB_HPVBF_FullRun2.SetLineColor(1)
DomBkgSB_HPVBF_FullRun2.SetFillColor(r.kGreen+1)
DomBkgSB_HPVBF_FullRun2.SetLineColor(1)

DataSB_HPVBF_FullRun2.SetMarkerStyle(8)

stack = r.THStack("stack","")
stack.Add(SubBkgSB_HPVBF_FullRun2)
stack.Add(DomBkgSB_HPVBF_FullRun2)
stack.Draw("histo")
DataSB_HPVBF_FullRun2.Draw("SAME,e1p")
stack.SetMaximum(1.5*DataSB_HPVBF_FullRun2.GetMaximum())

stack.GetYaxis().SetTitle("Events")
stack.GetYaxis().SetLabelFont(43);
stack.GetYaxis().SetLabelSize(24);
stack.GetYaxis().SetTitleFont(43);
stack.GetYaxis().SetTitleSize(24);
stack.GetYaxis().SetTitleOffset(1.5);
stack.GetYaxis().SetNdivisions(505);

stack.GetXaxis().SetLabelFont(43);
stack.GetXaxis().SetLabelSize(24);
stack.GetXaxis().SetTitleFont(43);
stack.GetXaxis().SetTitleSize(24);
stack.GetXaxis().SetTitleOffset(1.7);
stack.GetXaxis().SetNdivisions(505);

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

LUMItext = r.TText(.60,.95,"13 TeV (137/fb)")
LUMItext.SetNDC()
LUMItext.SetTextFont(51)
LUMItext.SetTextSize(0.06)
LUMItext.Draw()

# For legend
leg = r.TLegend(0.6,.7,.85,.92)
leg.SetNColumns(1)
#leg.SetNRows(2)
leg.SetFillColor(0)
leg.SetLineColor(r.kWhite)

leg.AddEntry(DomBkgSB_HPVBF_FullRun2,"Dom Bkg","f")
leg.AddEntry(SubBkgSB_HPVBF_FullRun2,"SubDom Bkg","f")
leg.AddEntry(DataSB_HPVBF_FullRun2,"Data","p")

leg.Draw()

botPad.cd()
ratio = r.TH1F(DataSB_HPVBF_FullRun2)
total = r.TH1F(TotalBkgSB_HPVBF_FullRun2)
#total = DomBkgSB_HPVBF_FullRun2.Clone("total")
#total.Add(SubBkgSB_HPVBF_FullRun2)

ratio.Divide(total)
ratio.SetMarkerStyle(8)

ratio.GetYaxis().SetRangeUser(0,2)
ratio.GetYaxis().SetTitle("Data/MC")
ratio.SetTitle("")
ratio.GetXaxis().SetTitle(h3.GetXaxis().GetTitle())
ratio.GetYaxis().SetLabelFont(43);
ratio.GetYaxis().SetLabelSize(24);
ratio.GetYaxis().SetTitleFont(43);
ratio.GetYaxis().SetTitleSize(24);
ratio.GetYaxis().SetNdivisions(505);
ratio.GetYaxis().SetTitleOffset(1.5);

ratio.GetXaxis().SetLabelFont(43);
ratio.GetXaxis().SetLabelSize(24);
ratio.GetXaxis().SetTitleFont(43);
ratio.GetXaxis().SetTitleSize(24);
ratio.GetXaxis().SetTitleOffset(2.8);
# Draw a horizontal line at 1 in ratio plot
nbins = ratio.GetNbinsX()
l = r.TLine(ratio.GetBinLowEdge(1),1.0,ratio.GetBinLowEdge(nbins+1),1.0);
l.SetLineColor(r.kRed);
l.SetLineWidth(2);
ratio.Draw()
l.Draw("same");

can.SaveAs("VBF_HPSB_MT_LogY.png")

fout = r.TFile(foutput_name,"RECREATE")
fout.cd()
SubBkgSB_HPVBF_FullRun2.Write() 
DomBkgSB_HPVBF_FullRun2.Write() 
DataSB_HPVBF_FullRun2.Write() 
TotalBkgSB_HPVBF_FullRun2.Write() 


f1.Close()



