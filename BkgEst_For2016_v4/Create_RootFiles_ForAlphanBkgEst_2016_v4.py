from sys import argv
import ROOT as r
import code

f1 = r.TFile.Open("ZSBHPNoVBF_515_v4_2016_Output.root")
f2 = r.TFile.Open("ZSBHPVBF_515_v4_2016_Output.root")
f3 = r.TFile.Open("ZSRHPNoVBF_515_v4_2016_Output.root")
f4 = r.TFile.Open("ZSRHPVBF_515_v4_2016_Output.root")
foutput_name = "ForAlpha_n_BkgEst_2016_v4.root"

############################
# ZSB HP No VBF Category  ##
############################

h1 = f1.Get("ZMT2_ZSBHPNoVBF_Data")
h2 = f1.Get("ZMT2_ZSBHPNoVBF_VBFG_1200")
h3 = f1.Get("ZMT2_ZSBHPNoVBF_Single top")
h4 = f1.Get("ZMT2_ZSBHPNoVBF_TT")
h5 = f1.Get("ZMT2_ZSBHPNoVBF_Other")
h6 = f1.Get("ZMT2_ZSBHPNoVBF_WJets")
h7 = f1.Get("ZMT2_ZSBHPNoVBF_ZJets")

SubDom_Bkg_SBHPNoVBF = h3.Clone("SubDom_Bkg_SBHPNoVBF")
Dom_Bkg_SBHPNoVBF = h6.Clone("Dom_Bkg_SBHPNoVBF")

SubDom_Bkg_SBHPNoVBF.Add(h4)
SubDom_Bkg_SBHPNoVBF.Add(h5)
Dom_Bkg_SBHPNoVBF.Add(h7)

TotalBkg_SBHPNoVBF = SubDom_Bkg_SBHPNoVBF.Clone("TotalBkg_SBHPNoVBF")
TotalBkg_SBHPNoVBF.Add(Dom_Bkg_SBHPNoVBF)

############################
#   ZSB HP VBF Category  ##
############################

h1sbvbf = f2.Get("ZMT2_ZSBHPVBF_Data")
h2sbvbf = f2.Get("ZMT2_ZSBHPVBF_VBFG_1200")
h3sbvbf = f2.Get("ZMT2_ZSBHPVBF_Single top")
h4sbvbf = f2.Get("ZMT2_ZSBHPVBF_TT")
h5sbvbf = f2.Get("ZMT2_ZSBHPVBF_Other")
h6sbvbf = f2.Get("ZMT2_ZSBHPVBF_WJets")
h7sbvbf = f2.Get("ZMT2_ZSBHPVBF_ZJets")

SubDom_Bkg_SBHPVBF = h3sbvbf.Clone("SubDom_Bkg_SBHPVBF")
Dom_Bkg_SBHPVBF = h6sbvbf.Clone("Dom_Bkg_SBHPVBF")

SubDom_Bkg_SBHPVBF.Add(h4sbvbf)
SubDom_Bkg_SBHPVBF.Add(h5sbvbf)
Dom_Bkg_SBHPVBF.Add(h7sbvbf)

TotalBkg_SBHPVBF = SubDom_Bkg_SBHPVBF.Clone("TotalBkg_SBHPVBF")
TotalBkg_SBHPVBF.Add(Dom_Bkg_SBHPVBF)

c = r.TCanvas("c","c")
SubDom_Bkg_SBHPNoVBF.Draw("histo")

#############################
#   ZSR HP No VBF Category ##
#############################

h2srnovbf = f3.Get("ZMT2_ZSRHPNoVBF_VBFG_1200")
h3srnovbf = f3.Get("ZMT2_ZSRHPNoVBF_Single top")
h4srnovbf = f3.Get("ZMT2_ZSRHPNoVBF_TT")
h5srnovbf = f3.Get("ZMT2_ZSRHPNoVBF_Other")
h6srnovbf = f3.Get("ZMT2_ZSRHPNoVBF_WJets")
h7srnovbf = f3.Get("ZMT2_ZSRHPNoVBF_ZJets")

SubDom_Bkg_SRHPNoVBF = h3srnovbf.Clone("SubDom_Bkg_SRHPNoVBF")
Dom_Bkg_SRHPNoVBF = h6srnovbf.Clone("Dom_Bkg_SRHPNoVBF")

SubDom_Bkg_SRHPNoVBF.Add(h4srnovbf)
SubDom_Bkg_SRHPNoVBF.Add(h5srnovbf)
Dom_Bkg_SRHPNoVBF.Add(h7srnovbf)

TotalBkg_SRHPNoVBF = SubDom_Bkg_SRHPNoVBF.Clone("TotalBkg_SRHPNoVBF")
TotalBkg_SRHPNoVBF.Add(Dom_Bkg_SRHPNoVBF)

#############################
#   ZSR HP VBF Category ##
#############################

h2srvbf = f4.Get("ZMT2_ZSRHPVBF_VBFG_1200")
h3srvbf = f4.Get("ZMT2_ZSRHPVBF_Single top")
h4srvbf = f4.Get("ZMT2_ZSRHPVBF_TT")
h5srvbf = f4.Get("ZMT2_ZSRHPVBF_Other")
h6srvbf = f4.Get("ZMT2_ZSRHPVBF_WJets")
h7srvbf = f4.Get("ZMT2_ZSRHPVBF_ZJets")

SubDom_Bkg_SRHPVBF = h3srvbf.Clone("SubDom_Bkg_SRHPVBF")
Dom_Bkg_SRHPVBF = h6srvbf.Clone("Dom_Bkg_SRHPVBF")

SubDom_Bkg_SRHPVBF.Add(h4srvbf)
SubDom_Bkg_SRHPVBF.Add(h5srvbf)
Dom_Bkg_SRHPVBF.Add(h7srvbf)

TotalBkg_SRHPVBF = SubDom_Bkg_SRHPVBF.Clone("TotalBkg_SRHPVBF")
TotalBkg_SRHPVBF.Add(Dom_Bkg_SRHPVBF)

###################################
# Output file from all Category  ##
###################################

fout = r.TFile(foutput_name,"RECREATE")
fout.cd()
# Z SB HP No VBF
SubDom_Bkg_SBHPNoVBF.Write()
Dom_Bkg_SBHPNoVBF.Write()
h1.Write() # Data 
h2.Write() # sig
TotalBkg_SBHPNoVBF.Write()
#Z SB HP VBF
SubDom_Bkg_SBHPVBF.Write()
Dom_Bkg_SBHPVBF.Write()
h1sbvbf.Write()
h2sbvbf.Write()
TotalBkg_SBHPVBF.Write()
#Z SR HP No VBF
SubDom_Bkg_SRHPNoVBF.Write() 
Dom_Bkg_SRHPNoVBF.Write()
h2srnovbf.Write()
TotalBkg_SRHPNoVBF.Write()
#Z SR HP VBF
SubDom_Bkg_SRHPVBF.Write() 
Dom_Bkg_SRHPVBF.Write()
h2srvbf.Write()
TotalBkg_SRHPVBF.Write()



