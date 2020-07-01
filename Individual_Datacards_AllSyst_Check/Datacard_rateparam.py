import ROOT as r
import sys
import os
import math

mass=sys.argv[1]
sample=sys.argv[2] # VBFG, VBFWp, VBFRad, ggFG, ggFWp, ggFRad
year=sys.argv[3] # 137fb, 2016, 2017, 2018
purity = "HP"


#if sample=="VBFG" or sample=="VBFWp" or sample=="VBFRad":
if "VBF" in sample:
    cat = "VBF"; cat1 = "VBF"; binning = "VBF137"        
elif "ggF" in sample:
    cat = "VBFfail"; cat1 = "ggF"; binning = "VBFfail137"        

print "his: {0}; his1: {1}".format(cat,cat1)

if "VBF" in sample: sample1=sample
if "VBFG" in sample: spin = "VBFS2"
if "VBFWp" in sample: spin = "VBFS1"
if "VBFRad" in sample: spin = "VBFS0"
elif "ggFG" in sample: sample1 = "VBFfailG"; spin = "ggFS2"
elif "ggFWp" in sample: sample1 = "VBFfailWp"; spin = "ggFS1"
elif "ggFRad" in sample: sample1 = "VBFfailRad"; spin = "ggFS0"

if year=="137fb":  scale = 3.3012 # currently using sig sample from 2017, so scaling to respective year (lumi).
elif year=="2016": scale = 0.863
elif year=="2017": scale = 1.0
elif year=="2018": scale = 1.434


f1 = r.TFile.Open("../ForLimit/EstBkg_"+purity+cat+"_"+year+"_varbin.root")
f2 = r.TFile.Open("../ForLimit/Signal_"+sample+"_"+"ZSR"+purity+cat+"_"+binning+"_AN_v1_varbin_2017.root")
f3 = r.TFile.Open("../ForLimit/Signal_"+sample+"_"+"ZSB"+purity+cat+"_"+binning+"_AN_v1_varbin_2017.root")
f4= r.TFile.Open("../ForLimit/SystUnc_PDFscaleBG_JECJERall.root")
if "VBF" in sample: 
    frare_vbf = r.TFile.Open("../ForLimit/Rarebkg_allSystUnc_137fb_HP_VBF.root")
    fsig_vbf = r.TFile.Open("../ForLimit/Signal_allSystUnc_137fb_HP_VBF.root")
if "ggF" in sample: 
    frare_vbf = r.TFile.Open("../ForLimit/Rarebkg_allSystUnc_137fb_HP_ggF.root")
    fsig_vbf = r.TFile.Open("../ForLimit/Signal_allSystUnc_137fb_HP_ggF.root")

print "f1 EstBkg: {}".format(f1)
print "f2 Sig SR: {}".format(f2)
print "f3 Sig SB: {}".format(f3)
print "f4 Unc   : {}".format(f4)
print "f5 rare vbf Unc   : {}".format(frare_vbf)
#print "f6 rare vbf Unc   : {}".format(frare_ggf)

hSRbkg_est = f1.Get('EstBkg'); hSRbkg_dom = f1.Get('Dom_SR'); hSRbkg_rare = f1.Get('Rare_SR') # SR SubDom bkg
# Est bkg in SR                     # SR Dom bkg                    # SR SubDom bkg

hSBbkg_data = f1.Get('Data_SB'); hSBbkg_dom = f1.Get('Dom_SB'); hSBbkg_rare = f1.Get('Rare_SB') # SB SubDom bkg
# SB Data                               # SB Dom bkg                # SB SubDom bkg

hSR_sig =    f2.Get('ZMT_{0}_ZSR{1}{2}_{3}_{4}_inc_ovrflw'.format(binning,purity,cat,sample,mass))  # Sig in SR
hSB_sig =    f3.Get('ZMT_{0}_ZSB{1}{2}_{3}_{4}_inc_ovrflw'.format(binning,purity,cat,sample,mass))  # Sig in SR

rare_uncs_name = ["Lumi_uncRare", "Vtag_tau21_sf_uncRare", "Pileup_uncRare", "bveto_uncRare", 
                  "Prefiring_uncRare", "Unclusturedenergy_uncRare", "JMR_uncRare", "Vtag_pt_extrap_uncRare", 
                  "JMSup_uncRare", "JMSdown_uncRare", "Triggerup_uncRare", "Triggerdown_uncRare"]
rare_uncs_name1 = ["ScaleUncRareShape", "ScaleUncRareNorm", "PDFUncRareShape", "PDFUncRareNorm", "JECuncRare", "JERuncRare"]

jer = "JERuncAlpha" if "VBF" in sample else "JERuncAplha"
alpha_pdf = f4.Get("PDFuncAlpha_{0}_HP".format(cat1))
alpha_scale = f4.Get("ScaleuncAlpha_{0}_HP".format(cat1))
alpha_jec = f4.Get("JECuncAlpha_{0}".format(cat1))
alpha_jer = f4.Get("{0}_{1}".format(jer,cat1))
sig_jec_jer = f4.Get("SigJECJER")

rare_uncs_vbf_sr = []; rare_uncs_vbf_cr = []
for i in range(len(rare_uncs_name)): 
    h_sr_vbf = frare_vbf.Get("{0}_{1}_SR".format(rare_uncs_name[i],cat1))
    h_cr_vbf = frare_vbf.Get("{0}_{1}_CR".format(rare_uncs_name[i],cat1))
    rare_uncs_vbf_sr.append(h_sr_vbf)
    rare_uncs_vbf_cr.append(h_cr_vbf)

rare_uncs_vbf_sr1 = []; rare_uncs_vbf_cr1 = []
for j in range(len(rare_uncs_name1)):
    h_sr_vbf1 = f4.Get("{0}_{1}_SR".format(rare_uncs_name1[j],cat1))
    h_cr_vbf1 = f4.Get("{0}_{1}_CR".format(rare_uncs_name1[j],cat1))
    rare_uncs_vbf_sr1.append(h_sr_vbf1)
    rare_uncs_vbf_cr1.append(h_cr_vbf1)
    
#print "rare_uncs_vbf_sr1: {}".format(rare_uncs_vbf_sr1)
#print ""
#print "rare_uncs_vbf_cr1: {}".format(rare_uncs_vbf_cr1)

sig_uncs_name = ["Lumi_uncSig", "Vtag_tau21_sf_uncSig", "Pileup_uncSig", "bveto_uncSig", 
                  "Prefiring_uncSig", "Unclusturedenergy_uncSig", "JMR_uncSig", 
                  "JMSup_uncSig", "JMSdown_uncSig", "Triggerup_uncSig", "Triggerdown_uncSig",
                  "Tau21ptExtup_uncSig",  "Tau21ptExtdown_uncSig"]

sig_uncs_vbf_sr = []; sig_uncs_vbf_cr = []
for i in range(len(sig_uncs_name)): 
    h_sr_vbf2 = fsig_vbf.Get("{0}_{1}_SR".format(sig_uncs_name[i],cat1))
    h_cr_vbf2 = fsig_vbf.Get("{0}_{1}_CR".format(sig_uncs_name[i],cat1))
    sig_uncs_vbf_sr.append(h_sr_vbf2)
    sig_uncs_vbf_cr.append(h_cr_vbf2)

sig_jec_up_sr = sig_jec_jer.GetBinContent(sig_jec_jer.GetXaxis().FindBin("JECup_{0}_{1}_SR".format(spin,cat1)))
sig_jec_up_cr = sig_jec_jer.GetBinContent(sig_jec_jer.GetXaxis().FindBin("JECup_{0}_{1}_CR".format(spin,cat1)))
sig_jec_do_sr = sig_jec_jer.GetBinContent(sig_jec_jer.GetXaxis().FindBin("JECdown_{0}_{1}_SR".format(spin,cat1)))
sig_jec_do_cr = sig_jec_jer.GetBinContent(sig_jec_jer.GetXaxis().FindBin("JECdown_{0}_{1}_CR".format(spin,cat1)))
sig_jer_sr = sig_jec_jer.GetBinContent(sig_jec_jer.GetXaxis().FindBin("JERup_{0}_{1}_SR".format(spin,cat1))) # jer is same for up and down var.
sig_jer_cr = sig_jec_jer.GetBinContent(sig_jec_jer.GetXaxis().FindBin("JERup_{0}_{1}_CR".format(spin,cat1)))

#print ""
#print ""
#print "sig_uncs_vbf_sr: {}".format(sig_uncs_vbf_sr)
#print ""
#print "sig_uncs_vbf_cr: {}".format(sig_uncs_vbf_cr)
#histo = [hSR_sig, hSRbkg_dom, hSRbkg_rare, hSB_sig, hSBbkg_dom, hSBbkg_rare,  hSRbkg_est, hSBbkg_data, hPDF_HP, hScale_HP]
#           0         1            2         3          4           5           6           7             8         9      
#for l in range(len(histo)): print "histo[i]: {}".format(histo[l].GetName())

#sig_uncs_name = ["Lumi","Vtag_tau21_sf","Pileup","bveto","Prefiring","Unclusturedenergy","JMR","JMSup","JMSdown","Triggerup","Triggerdown","Tau21ptExtup", "Tau21ptExtdown"]
#                   0         1             2       3         4             5               6      7        8         9             10            11               12  

nbins = hSRbkg_est.GetNbinsX() 
print "nbins: {}".format(nbins)

carddir = os.getcwd()+"/"+sample1+"_"+year+"/"
if not os.path.exists(carddir): os.system("mkdir -p {0}Root_Limit_{1}/".format(carddir,sample1))
for j in xrange(1,nbins+1):
    fname = carddir+sample1+"_Card_M{0}_bin{1}_{2}.txt".format(mass,int(hSR_sig.GetBinLowEdge(j)),year)
    sRcat = "S{}".format(j)
    cRcat = "C{}".format(j)
    with open(fname,'w') as f :
        f.write("imax 2  number of channels\n")
        f.write("jmax 2  number of backgrounds\n")
        f.write("kmax *  number of nuisance parameters (sources of systematic uncertainties)\n")
        f.write("#S: signal region, C: control region or sideband, number is bin number\n")
        f.write("bin         {0}        {1}\n".format(sRcat,cRcat,cat))
        f.write("observation {0}        {1}\n".format(round(hSRbkg_est.GetBinContent(j),6), round(hSBbkg_data.GetBinContent(j),4)))
        f.write("bin         {0}        {0}     {0}     {1}     {1}     {1}\n".format(sRcat,cRcat,cat))
        f.write("process     {0}        {1}     {2}     {0}     {1}     {2}\n".format('sig','bkg','rare'))
        f.write("process     {0}        {1}     {2}     {0}     {1}     {2}\n".format('0','1','2'))
        f.write("rate        {0}        {1}     {2}     {3}     {4}     {5}\n".format(
        round((hSR_sig.GetBinContent(j)*0.001*scale),6), # 0.001 scaling Xsec to 1fb  
        round((hSRbkg_dom.GetBinContent(j)),6),  
        round((hSRbkg_rare.GetBinContent(j)),6),  
        round((hSB_sig.GetBinContent(j)*0.001*scale),6), 
        round((hSBbkg_dom.GetBinContent(j)),6),  
        round((hSBbkg_rare.GetBinContent(j)),6) )) 
        f.write("#--------------------------\n")
        f.write("rateparam_{0} rateParam {1} bkg 1  [1e-5,10]\n".           format(j,cRcat))
        f.write("rateparam_{0} rateParam {1} bkg 1  [1e-5,10]\n".           format(j,sRcat))
        f.write("{1} lnN - {2} - - - -\n".format(j, alpha_pdf.GetTitle(), round(alpha_pdf.GetBinContent(j),4)))
        f.write("{1} lnN - {2} - - - -\n".format(j, alpha_scale.GetTitle(), round(alpha_scale.GetBinContent(j),4)))
        f.write("{1} lnN - {2} - - - -\n".format(j, alpha_jec.GetTitle(), round(alpha_jec.GetBinContent(j),4)))
        f.write("{1} lnN - {2} - - - -\n".format(j, alpha_jer.GetTitle(), round(alpha_jer.GetBinContent(j),4)))

#sig_uncs_name = ["Lumi","Vtag_tau21_sf","Pileup","bveto","Prefiring","Unclusturedenergy","JMR","JMSup","JMSdown","Triggerup","Triggerdown","Tau21ptExtup", "Tau21ptExtdown"]
#                   0         1             2       3         4             5               6      7        8         9             10            11               12  
       # new addition for rare uncs. 
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[0].GetTitle(),round(rare_uncs_vbf_sr[0].GetBinContent(j),4), round(rare_uncs_vbf_cr[0].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[0].GetBinContent(j),4), round(sig_uncs_vbf_cr[0].GetBinContent(j),4))) #lumi
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[1].GetTitle(),round(rare_uncs_vbf_sr[1].GetBinContent(j),4), round(rare_uncs_vbf_cr[1].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[1].GetBinContent(j),4), round(sig_uncs_vbf_cr[1].GetBinContent(j),4))) #tau21sf
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[2].GetTitle(),round(rare_uncs_vbf_sr[2].GetBinContent(j),4), round(rare_uncs_vbf_cr[2].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[2].GetBinContent(j),4), round(sig_uncs_vbf_cr[2].GetBinContent(j),4))) #pileup
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[3].GetTitle(),round(rare_uncs_vbf_sr[3].GetBinContent(j),4), round(rare_uncs_vbf_cr[3].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[3].GetBinContent(j),4), round(sig_uncs_vbf_cr[3].GetBinContent(j),4))) #bveto
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[4].GetTitle(),round(rare_uncs_vbf_sr[4].GetBinContent(j),4), round(rare_uncs_vbf_cr[4].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[4].GetBinContent(j),4), round(sig_uncs_vbf_cr[4].GetBinContent(j),4))) #prefiring
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[5].GetTitle(),round(rare_uncs_vbf_sr[5].GetBinContent(j),4), round(rare_uncs_vbf_cr[5].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[5].GetBinContent(j),4), round(sig_uncs_vbf_cr[5].GetBinContent(j),4))) #unlcustured en
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr[6].GetTitle(),round(rare_uncs_vbf_sr[6].GetBinContent(j),4), round(rare_uncs_vbf_cr[6].GetBinContent(j),4), 
                                                                                        round(sig_uncs_vbf_sr[6].GetBinContent(j),4), round(sig_uncs_vbf_cr[6].GetBinContent(j),4))) #JMR
        f.write("{1} lnN {4}/{6} - {2} {5}/{7} - {3}\n".format(j,rare_uncs_vbf_sr[7].GetTitle(),round(rare_uncs_vbf_sr[7].GetBinContent(j),4), round(rare_uncs_vbf_cr[7].GetBinContent(j),4),
                   round(sig_uncs_vbf_sr[11].GetBinContent(sig_uncs_vbf_sr[11].FindBin(float(mass))),4),  round(sig_uncs_vbf_cr[11].GetBinContent(sig_uncs_vbf_cr[11].FindBin(float(mass))),4),  
                   round(sig_uncs_vbf_sr[12].GetBinContent(sig_uncs_vbf_sr[12].FindBin(float(mass))),4),  round(sig_uncs_vbf_cr[12].GetBinContent(sig_uncs_vbf_cr[12].FindBin(float(mass))),4))) #tau21 pt extrap
        f.write("{1} lnN {8}/{6} - {4}/{2} {9}/{7} - {5}/{3}\n".format(j,rare_uncs_vbf_sr[8].GetTitle(),round(rare_uncs_vbf_sr[8].GetBinContent(j),4), round(rare_uncs_vbf_cr[8].GetBinContent(j),4),
                                                                                                        round(rare_uncs_vbf_sr[9].GetBinContent(j),4), round(rare_uncs_vbf_cr[9].GetBinContent(j),4),  
                                                                                                        round(sig_uncs_vbf_sr[7].GetBinContent(j),4),  round(sig_uncs_vbf_cr[7].GetBinContent(j),4),  
                                                                                                        round(sig_uncs_vbf_sr[8].GetBinContent(j),4),  round(sig_uncs_vbf_cr[8].GetBinContent(j),4))) #JMS UP/Down
        f.write("{1} lnN {6}/{8} - {4}/{2} {7}/{9} - {5}/{3}\n".format(j,rare_uncs_vbf_sr[10].GetTitle(), round(rare_uncs_vbf_sr[10].GetBinContent(j),4), round(rare_uncs_vbf_cr[10].GetBinContent(j),4),
                                                                                                          round(rare_uncs_vbf_sr[11].GetBinContent(j),4), round(rare_uncs_vbf_cr[11].GetBinContent(j),4),
                                                                                                          round(sig_uncs_vbf_sr[9].GetBinContent(j),4),   round(sig_uncs_vbf_cr[9].GetBinContent(j),4),
                                                                                                          round(sig_uncs_vbf_sr[10].GetBinContent(j),4),  round(sig_uncs_vbf_cr[10].GetBinContent(j),4))) #trigger up/down 

        #rare_uncs_name1 = ["ScaleUncRareShape", "ScaleUncRareNorm", "PDFUncRareShape", "PDFUncRareNorm", "JECuncRare", "JERuncRare"]
        f.write("{1} lnN - - {2} - - {3}\n".format(j,rare_uncs_vbf_sr1[0].GetTitle(),round(rare_uncs_vbf_sr1[0].GetBinContent(j),4), round(rare_uncs_vbf_cr1[0].GetBinContent(j),4))) #scale shape
        f.write("{1} lnN - - {2} - - {3}\n".format(j,rare_uncs_vbf_sr1[1].GetTitle(),round(rare_uncs_vbf_sr1[1].GetBinContent(j),4), round(rare_uncs_vbf_cr1[1].GetBinContent(j),4))) #scale norm
        f.write("{1} lnN - - {2} - - -\n".  format(j,rare_uncs_vbf_sr1[2].GetTitle(),round(rare_uncs_vbf_sr1[2].GetBinContent(j),4), round(rare_uncs_vbf_cr1[2].GetBinContent(j),4))) #pdf shape
        f.write("{1} lnN - - - - - {3}\n".  format(j,rare_uncs_vbf_cr1[2].GetTitle(),round(rare_uncs_vbf_sr1[2].GetBinContent(j),4), round(rare_uncs_vbf_cr1[2].GetBinContent(j),4))) #pdf shape
        f.write("{1} lnN - - {2} - - -\n".  format(j,rare_uncs_vbf_sr1[3].GetTitle(),round(rare_uncs_vbf_sr1[3].GetBinContent(j),4), round(rare_uncs_vbf_cr1[3].GetBinContent(j),4))) #pdf norm
        f.write("{1} lnN - - - - - {3}\n".  format(j,rare_uncs_vbf_cr1[3].GetTitle(),round(rare_uncs_vbf_sr1[3].GetBinContent(j),4), round(rare_uncs_vbf_cr1[3].GetBinContent(j),4))) #pdf norm
        #f.write("{1} lnN {4}/{6} - {2} {5}/{7} - {3}\n".format(j,rare_uncs_vbf_sr1[4].GetTitle(),round(rare_uncs_vbf_sr1[4].GetBinContent(j),4), round(rare_uncs_vbf_cr1[4].GetBinContent(j),4),
        f.write("{1} lnN {4}/{6} - {2} {5}/{7} - {3}\n".format(j,"JEC",round(rare_uncs_vbf_sr1[4].GetBinContent(j),4), round(rare_uncs_vbf_cr1[4].GetBinContent(j),4),
                                                           round(sig_jec_up_sr,4), round(sig_jec_up_cr,4), round(sig_jec_do_sr,4), round(sig_jec_do_cr,4) )) #jec
        #f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,rare_uncs_vbf_sr1[5].GetTitle(),round(rare_uncs_vbf_sr1[5].GetBinContent(j),4), round(rare_uncs_vbf_cr1[5].GetBinContent(j),4),
        f.write("{1} lnN {4} - {2} {5} - {3}\n".format(j,"JER",round(rare_uncs_vbf_sr1[5].GetBinContent(j),4), round(rare_uncs_vbf_cr1[5].GetBinContent(j),4),
                                                                                     round(sig_jer_sr,4), round(sig_jer_cr,4)  )) #jer

       # end of new addition for rare uncs. 
        if hSR_sig.GetBinContent(j) > 0.0:f.write("SigSR_stat_{2}_{0} lnN {1} - - - - -\n".   format(j,round(1+(hSR_sig.GetBinError(j)/hSR_sig.GetBinContent(j)),4),cat))
        elif hSR_sig.GetBinContent(j) == 0.0:f.write("SigSR_stat_{2}_{0} lnN {1} - - - - -\n".format(j,round(1+(hSR_sig.GetBinError(j)),4),cat))

        f.write("BkgSR_stat_{2}_{0} lnN - {1} - - - -\n".   format(j,round(1+(hSRbkg_dom.GetBinError(j)/hSRbkg_dom.GetBinContent(j)),4),cat))

        if hSRbkg_rare.GetBinContent(j) == 0.0:    f.write("RareSR_stat_{2}_{0} gmN 0 - - {1} - - -\n".  format(j,round((hSRbkg_rare.GetBinError(j)),4),cat))
        else:
            if hSRbkg_rare.GetBinError(j) == 1.0:  f.write("RareSR_stat_{2}_{0} lnN - - {1} - - -\n".  format(j,round(1+hSRbkg_rare.GetBinError(j),4),cat))
            else: f.write("RareSR_stat_{2}_{0} lnN - - {1} - - -\n".  format(j,round(1+(hSRbkg_rare.GetBinError(j)/hSRbkg_rare.GetBinContent(j)),4),cat))

        if hSB_sig.GetBinContent(j) > 0.0:f.write("SigSB_stat_{2}_{0} lnN - - - {1} - -\n".   format(j,round(1+(hSB_sig.GetBinError(j)/hSB_sig.GetBinContent(j)),4),cat))
        elif hSB_sig.GetBinContent(j) == 0.0:f.write("SigSB_stat_{2}_{0} lnN - - - {1} - -\n".format(j,round(1+(hSB_sig.GetBinError(j)),4),cat))

        f.write("BkgSB_stat_{2}_{0} lnN - - - - {1} -\n".   format(j,round(1+(hSBbkg_dom.GetBinError(j)/hSBbkg_dom.GetBinContent(j)),4),cat))

        if hSBbkg_rare.GetBinContent(j) == 0.0:    f.write("RareSB_stat_{2}_{0} gmN 0 - - - - - {1}\n".  format(j,round((hSBbkg_rare.GetBinError(j)),4),cat))
        else:
            if hSBbkg_rare.GetBinError(j) == 1.0: f.write("RareSB_stat_{2}_{0} lnN - - - - - {1}\n".  format(j,round(1+hSBbkg_rare.GetBinError(j),4),cat))
            else: f.write("RareSB_stat_{2}_{0} lnN - - - - - {1}\n".  format(j,round(1+(hSBbkg_rare.GetBinError(j)/hSBbkg_rare.GetBinContent(j)),4),cat))

        f.close()    

    os.system("combineCards.py {0} > {1}tempFile.txt".format(fname,carddir)) 
    os.system("mv {0}tempFile.txt {1}".format(carddir,fname)) 


f1.Close()
f2.Close()
f3.Close()
f4.Close()
frare_vbf.Close()
fsig_vbf.Close()


