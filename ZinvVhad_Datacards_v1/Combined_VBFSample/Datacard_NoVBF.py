import ROOT as r
import sys
import os
import math

mass=sys.argv[1]
sample=sys.argv[2] # VBFG, VBFWp, VBFRad
year=sys.argv[3] # 137fb, 2016, 2017, 2018

purity = "HP"

#currently using sample from 2017 so scaling it to respective years (lumi)
if year=="137fb":   scale = 3.3012
elif year=="2016":  scale = 0.863
elif year=="2017":  scale = 1.0
elif year=="2018":  scale = 1.434

#using vbf sample for all case: sam="VBFG"
if sample=="VBFG" or sample=="ggFG": sam="VBFG"
if sample=="VBFRad" or sample=="ggFRad": sam="VBFRad"
if sample=="VBFWp" or sample=="ggFWp": sam="VBFWp"

if "VBF" in sample: cat = "VBF"; cat1 = "VBF"; binning = "VBF137"        
elif "ggF" in sample: cat = "VBFfail"; cat1 = "ggF";binning = "VBFfail137"        

print ""
print "using "+sam+" sample for both VBF and ggF(VBFfail) category !!!"
print ""
print "his: {0}; his1: {1}".format(cat,cat1)

f1 = r.TFile.Open("../ForLimit/EstBkg_"+purity+cat+"_"+year+"_varbin.root")
f2 = r.TFile.Open("../ForLimit/Signal_"+sam+"_"+"ZSR"+purity+cat+"_"+binning+"_AN_v1_varbin_2017.root")
f3 = r.TFile.Open("../ForLimit/Signal_"+sam+"_"+"ZSB"+purity+cat+"_"+binning+"_AN_v1_varbin_2017.root")
f4 = r.TFile.Open("../ForLimit/SystUnc_AN_v1_NonRes.root")

print "f1 EstBkg: {}".format(f1)
print "f2 Sig SR: {}".format(f2)
print "f3 Sig SB: {}".format(f3)
print "f4 Unc   : {}".format(f4)

hSRbkg_est = f1.Get('EstBkg')   # Est bkg in SR
hSRbkg_dom = f1.Get('Dom_SR')        # SR Dom bkg  
hSRbkg_rare = f1.Get('Rare_SR') # SR SubDom bkg

hSBbkg_data = f1.Get('Data_SB')   # SB Data
hSBbkg_dom = f1.Get('Dom_SB')        # SB Dom bkg 
hSBbkg_rare = f1.Get('Rare_SB') # SB SubDom bkg

hSR_sig =    f2.Get('ZMT_{0}_ZSR{1}{2}_{3}_{4}_inc_ovrflw'.format(binning,purity,cat,sam,mass))  # Sig in SR
hSB_sig =    f3.Get('ZMT_{0}_ZSB{1}{2}_{3}_{4}_inc_ovrflw'.format(binning,purity,cat,sam,mass))  # Sig in SR

hPDF_HP = f4.Get('PDFunc_{0}_HP'.format(cat))
hScale_HP = f4.Get('Scaleunc_{0}_HP'.format(cat))

histo = [hSR_sig, hSRbkg_dom, hSRbkg_rare, hSB_sig, hSBbkg_dom, hSBbkg_rare,  hSRbkg_est, hSBbkg_data, hPDF_HP, hScale_HP]

for l in range(len(histo)):
    print "histo[i]: {}".format(histo[l].GetName())


nbins=0
#for i in range(8):
for i in range(len(histo)):
    nbins = histo[i].GetNbinsX()
    #for j in xrange(1,nbins+2):
    for j in xrange(1,nbins+1):
        bincontent = histo[i].GetBinContent(j)
        if bincontent < 0.00001:
            histo[i].SetBinContent(j,0.000001)

inputfoldername = os.getcwd()

for j in xrange(1,nbins+1):
    fname=inputfoldername+"/"+sample+"_"+year+"/"+sample+"_Card_MG{0}_bin{1}_{2}.txt".format(mass,int(histo[0].GetBinLowEdge(j)),year)
    sRcat = "sR_{1}_{0}".format(j,cat1)
    cRcat = "cR_{1}_{0}".format(j,cat1)
    with open(fname,'w') as f :
        f.write("imax 2  number of channels\n")
        f.write("jmax 2  number of backgrounds\n")
        f.write("kmax *  number of nuisance parameters (sources of systematic uncertainties)\n")
        f.write("bin         {0:<25s}{1:<25s}\n".format(sRcat,cRcat))
        f.write("observation {0:<25.15f}{1:<25.15f}\n".format(histo[6].GetBinContent(j), histo[7].GetBinContent(j)))
        f.write("bin         {0:<25s}{0:<25s}{0:<25s}{1:<25s}{1:<25s}{1:<25s}\n".format(sRcat,cRcat))
        f.write("process     {0:<25s}{1:<25s}{2:<25s}{0:<25s}{1:<25s}{2:<25s}\n".format('sig','bkg','rare'))
        f.write("process     {0:<25s}{1:<25s}{2:<25s}{0:<25s}{1:<25s}{2:<25s}\n".format('0','1','2'))
        f.write("rate        {0:<25.15f}{1:<25.15f}{2:<25.15f}{3:<25.15f}{4:<25.15f}{5:<25.15f}\n".format(
        (histo[0].GetBinContent(j)*0.001*scale), #scaling to 137/fb and 0.0001 scaling Xsec to 1fb  
        (histo[1].GetBinContent(j)),  
        (histo[2].GetBinContent(j)),  
        (histo[3].GetBinContent(j)*0.001*scale), 
        (histo[4].GetBinContent(j)),  
        (histo[5].GetBinContent(j)) )) 
        f.write("#--------------------------\n")
        f.write("flat_{0} lnU - 100 - - 100 -\n".           format(j))
        f.write("bkgPdfUnc lnN - {1} - - {1} -\n".          format(j,histo[8].GetBinContent(j),cat))
        f.write("bkgScaleUnc lnN - {1} - - {1} -\n".        format(j,histo[9].GetBinContent(j),cat))
        f.write("rareUnc_{0} lnN - - 1.2 - - 1.2\n".        format(j))
        f.write("sigUnc_{0} lnN 1.2 - - 1.2 - -\n".         format(j))
        f.write("SigSR_stat_{2}_{0} lnN {1} - - - - -\n".   format(j,1+(histo[0].GetBinError(j)/histo[0].GetBinContent(j)),cat))
        f.write("BkgSR_stat_{2}_{0} lnN - {1} - - - -\n".   format(j,1+(histo[1].GetBinError(j)/histo[1].GetBinContent(j)),cat))
        f.write("RareSR_stat_{2}_{0} lnN - - {1} - - -\n".  format(j,1+(histo[2].GetBinError(j)/histo[2].GetBinContent(j)),cat))
        f.write("SigSB_stat_{2}_{0} lnN - - - {1} - -\n".   format(j,1+(histo[3].GetBinError(j)/histo[3].GetBinContent(j)),cat))
        f.write("BkgSB_stat_{2}_{0} lnN - - - - {1} -\n".   format(j,1+(histo[4].GetBinError(j)/histo[4].GetBinContent(j)),cat))
        f.write("RareSB_stat_{2}_{0} lnN - - - - - {1}\n".  format(j,1+(histo[5].GetBinError(j)/histo[5].GetBinContent(j)),cat))
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
f2.Close()
f3.Close()
f4.Close()


