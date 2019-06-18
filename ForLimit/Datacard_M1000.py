import ROOT as r
import sys
import code
import math

f1 = r.TFile.Open("../Overflow_Outputs_ForLimit_v1/LimitDebug_Rebin_2016_VBF_Bkg_100GeV_bin.root")
#f2 = r.TFile.Open("../Overflow_Outputs_ForLimit_v0/VBF_SBHP_Overflow_FullRun2_v0.root")
f3 = r.TFile.Open("../Overflow_Outputs_ForLimit_v1/LimitDebug_Rebin_2016_VBF_Sig_100GeV_NoSkim.root")
#f4 = r.TFile.Open("../Overflow_Outputs_ForLimit_v0/Sig_VBF_SBHP_Overflow_v0.root")


hSRbkg_sum = f1.Get('ZMT2_ZSRHPVBF_ZJets_inc_ovrflw')   # SR total bkg
hSRbkg_dom = f1.Get('ZMT2_ZSRHPVBF_ZJets_inc_ovrflw')        # SR Dom bkg  
hSRbkg_rare = f1.Get('ZMT2_ZSRHPVBF_TT_inc_ovrflw') # SR SubDom bkg

hSBbkg_sum = f1.Get('ZMT2_ZSBHPVBF_ZJets_inc_ovrflw')   # SB total bkg
hSBbkg_dom = f1.Get('ZMT2_ZSBHPVBF_ZJets_inc_ovrflw')        # SB Dom bkg 
hSBbkg_rare = f1.Get('ZMT2_ZSBHPVBF_TT_inc_ovrflw') # SB SubDom bkg

hSR_sig =    f3.Get('ZMT2_ZSRHPVBF_VBFG_1200_inc_ovrflw')  # Sig in SR
hSB_sig =    f3.Get('ZMT2_ZSBHPVBF_VBFG_1200_inc_ovrflw')  # Sig in SB
#hSB_sig =    f3.Get('ZMT2_ZSBHPVBF_VBFG_1000_inc_ovrflw')  # Sig in SB

histo = [hSR_sig, hSRbkg_dom, hSRbkg_rare, hSB_sig, hSBbkg_dom, hSBbkg_rare,  hSRbkg_sum, hSBbkg_sum]

nbins=0
for i in range(8):
    nbins = histo[i].GetNbinsX()
    #nbins = histo[i].GetXaxis().GetNbins()
    for j in xrange(1,nbins+2):
        bincontent = histo[i].GetBinContent(j)
        if bincontent < 0.00001:
            histo[i].SetBinContent(j,0.000001)

for j in xrange(1,nbins+2):
    fname="/uscms_data/d3/kxlpp1/SUSY/SUSY_OCT2018/Limit-Combine-Tool/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/datacards/pyDatacard/Binned_DataCard_v1/Limit_Debug/VBF/Card_MG1200_bin{0}.txt".format(int(histo[0].GetBinLowEdge(j)))
    #print fname
    with open(fname,'w') as f :

        f.write("imax 2  number of channels\n")
        f.write("jmax 2  number of backgrounds\n")
        f.write("kmax *  number of nuisance parameters (sources of systematic uncertainties)\n")
        f.write("bin signalRegion_{0} controlRegion_{0}\n".format(int(histo[0].GetBinLowEdge(j))))
        #f.write("observation {0} {1}\n".format(histo[6].GetBinContent(j), histo[7].GetBinContent(j)))
        f.write("observation {0} {1}\n".format((histo[1].GetBinContent(j)+histo[2].GetBinContent(j))*3.82, (histo[4].GetBinContent(j)+histo[5].GetBinContent(j))*3.82))
        f.write("bin       signalRegion_{0} signalRegion_{0} signalRegion_{0} controlRegion_{0} controlRegion_{0} controlRegion_{0}\n".format(int(histo[0].GetBinLowEdge(j))))
        f.write("process      sig                bkg             rare            sig                 bkg             rare\n")
        f.write("process       0                  1                2              0                   1                2\n")
        f.write("rate       {0}   {1}   {2}   {3}    {4}   {5}\n".format(
        (histo[0].GetBinContent(j)*3.82*0.001),  
        (histo[1].GetBinContent(j)*3.82),  
        (histo[2].GetBinContent(j)*3.82),  
        (histo[3].GetBinContent(j)*3.82*0.001), # 3.82: scaling to 137/fb and 0.0001 scaling Xsec to 1fb  
        (histo[4].GetBinContent(j)*3.82),  
        (histo[5].GetBinContent(j)*3.82) )) 
        f.write("#--------------------------\n")
        f.write("flat_{0} lnU - 100 - - 100 -\n".format(int(histo[0].GetBinLowEdge(j))))
        #f.write("bkgUnc_{0} lnN - 1.1 - - 0.9 -\n".format(int(histo[0].GetBinLowEdge(j))))
        #f.write("rareUnc_{0} lnN - - 1.2 - - 1.2\n".format(int(histo[0].GetBinLowEdge(j))))
        #f.write("sigUnc_{0} lnN 1.2 - - 1.2 - -".format(int(histo[0].GetBinLowEdge(j))))
        f.close()    



'''
{0} - bin's lower edge
{1} - signal yield for bin I in SR
{2} - background yield for bin I in SR
{3} - rare background yield for bin I in SR
{4} - signal yield for bin I in SB
{5} - background yield for bin I in SB
{6} - rare background yield for bin I in SB
{7} - total background in SR
{8} - total background in SB

'''

f1.Close()
#f2.Close()
f3.Close()
#f4.Close()


