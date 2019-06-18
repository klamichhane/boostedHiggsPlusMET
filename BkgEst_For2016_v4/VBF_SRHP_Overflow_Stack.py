import ROOT as r
import sys


#f1 = r.TFile.Open("ForAlpha_n_BkgEst_2016_v4.root")
f1 = r.TFile.Open("../ForAlpha_n_BkgEst_FullRun2_SB_v4.root")
f2 = r.TFile.Open("../ForAlpha_n_BkgEst_FullRun2_SR_v4.root")
foutput_name = "VBF_SRHP_Overflow_FullRun2_v0.root"

h1 = f2.Get("SubBkgSR_HPVBF")
h2 = f2.Get("DomBkgSR_HPVBF")
#h3 = f2.Get("DataSB_HPVBF")
h4 = f2.Get("TotBkgSR_HPVBF")

r.gStyle.SetOptStat(0)
can = r.TCanvas("can","can",500,500)
can.SetTopMargin(0.06);
can.SetBottomMargin(0.15);
can.SetLeftMargin(0.15);

r.gPad.SetLogy(1)

def include_overflow(histo):
    temp=r.TH1F(histo.GetName()+"_inc_ovrflw",histo.GetTitle(),histo.GetNbinsX()+1,histo.GetBinLowEdge(1),histo.GetBinLowEdge(histo.GetNbinsX())+2*histo.GetBinWidth(histo.GetNbinsX()))
    for i in xrange(1,histo.GetNbinsX()+2):
        temp.SetBinContent(i,histo.GetBinContent(i))
        temp.SetBinError(i,histo.GetBinError(i))
    return temp

SubBkgSR_HPVBF_FullRun2 = include_overflow(h1)
DomBkgSR_HPVBF_FullRun2 = include_overflow(h2)
TotalBkgSR_HPVBF_FullRun2 = include_overflow(h4)

SubBkgSR_HPVBF_FullRun2.SetFillColor(r.kOrange)
SubBkgSR_HPVBF_FullRun2.SetLineColor(1)
DomBkgSR_HPVBF_FullRun2.SetFillColor(r.kGreen+1)
DomBkgSR_HPVBF_FullRun2.SetLineColor(1)


stack = r.THStack("stack","")
stack.Add(SubBkgSR_HPVBF_FullRun2)
stack.Add(DomBkgSR_HPVBF_FullRun2)
stack.Draw("histo")
stack.SetMaximum(1.5*DomBkgSR_HPVBF_FullRun2.GetMaximum())

stack.GetYaxis().SetTitle("Events")
stack.GetYaxis().SetLabelFont(43);
stack.GetYaxis().SetLabelSize(24);
stack.GetYaxis().SetTitleFont(43);
stack.GetYaxis().SetTitleSize(24);
stack.GetYaxis().SetTitleOffset(1.5);
stack.GetYaxis().SetNdivisions(505);

stack.GetXaxis().SetTitle(h2.GetXaxis().GetTitle())
stack.GetXaxis().SetLabelFont(43);
stack.GetXaxis().SetLabelSize(24);
stack.GetXaxis().SetTitleFont(43);
stack.GetXaxis().SetTitleSize(24);
stack.GetXaxis().SetTitleOffset(1.1);
stack.GetXaxis().SetNdivisions(505);


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

LUMItext = r.TText(.60,.95,"13 TeV (137/fb)")
LUMItext.SetNDC()
LUMItext.SetTextFont(51)
LUMItext.SetTextSize(0.04)
LUMItext.Draw()

# For legend
leg = r.TLegend(0.6,.7,.85,.92)
leg.SetNColumns(1)
#leg.SetNRows(2)
leg.SetFillColor(0)
leg.SetLineColor(r.kWhite)
leg.AddEntry(DomBkgSR_HPVBF_FullRun2,"Dom Bkg","f")
leg.AddEntry(SubBkgSR_HPVBF_FullRun2,"SubDom Bkg","f")
leg.Draw()

can.SaveAs("VBF_HPSR_MT_LogY.png")

fout = r.TFile(foutput_name,"RECREATE")
fout.cd()
SubBkgSR_HPVBF_FullRun2.Write() 
DomBkgSR_HPVBF_FullRun2.Write() 
TotalBkgSR_HPVBF_FullRun2.Write() 


f1.Close()



