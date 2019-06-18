import ROOT as r
import sys


def include_overflow(histo):
    temp=r.TH1F(histo.GetName()+"_inc_ovrflw",histo.GetTitle(),histo.GetNbinsX()+1,histo.GetBinLowEdge(1),histo.GetBinLowEdge(histo.GetNbinsX())+2*histo.GetBinWidth(histo.GetNbinsX()))
    for i in xrange(1,histo.GetNbinsX()+2):
        temp.SetBinContent(i,histo.GetBinContent(i))
        temp.SetBinError(i,histo.GetBinError(i))
    return temp


#f1 = r.TFile.Open("../../../PrivateSamples_2016/AllSig_ZSRHPVBF_515_v4_2016.root")
#f1 = r.TFile.Open("AllSig_ZSRHPVBF_515_v4_2016_revertpt_v1.root")
f1 = r.TFile.Open("ZSRHPVBF_VBFG_1200_afterHT_2016.root")
f2 = r.TFile.Open("ZSBHPVBF_VBFG_1200_afterHT_2016.root")
foutput_name = "LimitDebug_Rebin_2016_VBF_Sig_100GeV_NoSkim.root"

h2sr = f1.Get("ZMT2_ZSRHPVBF_VBFG_1200")
h2sb = f2.Get("ZMT2_ZSBHPVBF_VBFG_1200")

# Rebin the histogram to 100 GeV
h2sr1 = r.TH1F(h2sr)
h2sr1.Rebin(4)
h2sb1 = r.TH1F(h2sb)
h2sb1.Rebin(4)

SRHPVBF_1200 = include_overflow(h2sr1)
SBHPVBF_1200 = include_overflow(h2sb1)

print "SR: 100 GeV bin Integral: {0}".format(h2sr1.Integral())
print "SB: 100 GeV bin Integral: {0}".format(h2sb1.Integral())

print "SR Overflow: 100 GeV bin Integral: {0}".format(SRHPVBF_1200.Integral())
print "SB Overflow: 100 GeV bin Integral: {0}".format(SBHPVBF_1200.Integral())

fout = r.TFile(foutput_name,"RECREATE")
fout.cd()

SRHPVBF_1200.Write()
SBHPVBF_1200.Write()

f1.Close()
f2.Close()


