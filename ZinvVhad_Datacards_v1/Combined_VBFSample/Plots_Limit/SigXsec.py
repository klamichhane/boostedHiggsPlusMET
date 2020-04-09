#!/usr/bin/env python
import ROOT as r
from ROOT import *
from array import *
import sys, os

####### ggFWp ###############
# need to return: SigXsec, thXsec, thXsecunc, thmass
mp_ggFWp = [1000,1200,1400,1600,2000,2500,3000,3500,4000,4500] #available sample mass points those are analyzed.
sigXsec_ggFWp = [] # Signal cross sections, set to 1pb (1000,1.0)
for i in mp_ggFWp: sigXsec_ggFWp.append(tuple([i,1.0]))

thmp_ggFWp = []
for i in range(700,4000,100): thmp_ggFWp.append(i+100)

thmass_ggFWp = [] #th mass
for i in thmp_ggFWp: thmass_ggFWp.append(tuple([i,i]))

thXsecunc_ggFWp = [] #theory xsec unc
for i in thmp_ggFWp: thXsecunc_ggFWp.append(tuple([i,0]))

#BRZW: from 800-4000: https://github.com/jngadiub/Cross_Sections_HVT/blob/master/13TeV.txt

BRZW = [0.428731, 0.451309, 0.460359, 0.464974, 0.467605, 0.469214, 0.470248, 0.470938,
        0.471413, 0.471749, 0.471991, 0.472168, 0.472301, 0.472401, 0.472477, 0.472536,
        0.472582, 0.472619, 0.472647, 0.47267,  0.472688, 0.472703, 0.472715, 0.472724,
        0.472732, 0.472738, 0.472743, 0.472748, 0.472751, 0.472754, 0.472756, 0.472758, 0.472759 ]

# CX+ i.e. Wprime plus one in pb:
CXp = [1.0768,      0.901251,   0.687047,    0.512156,    0.381432,    0.285322,     0.214856,     0.162942,
       0.124438,    0.0956578,  0.0739789,   0.0575243,   0.0449418,   0.035265,     0.0277791,    0.021956,
       0.0174056,   0.013834,   0.01102,     0.00879738,  0.00703223,  0.00562985,   0.00451288,   0.00362067,
       0.00290702,  0.0023356,  0.00187714,  0.00150893,  0.00121305,  0.000975141,  0.000783596,  0.000629536,  0.000505512 ]

CXm = [ 0.511085,      0.409766,      0.299486,     0.214767,       0.153962,       0.110992,       0.0806679,    0.0591312,
        0.0437098,     0.0325698,     0.0244536,    0.0184817,      0.0140562,      0.0107528,      0.0082689,    0.00638847,
        0.00495788,    0.00387631,    0.00302043,   0.00236942,     0.00186407,     0.00147046,     0.00116241,   0.000921187,
        0.000731461,   0.000581736,   0.000463361,  0.000369561,    0.000295015,    0.000235716,    0.000188334,  0.000150705,  0.000120638 ]

thXsec_ggFWp = [] #theory Xsec (mass,xsec)
for i in range(len(thmp_ggFWp)):
    xsec = ((CXp[i]+CXm[i])*BRZW[i]*1000)
    thXsec_ggFWp.append(tuple([thmp_ggFWp[i],xsec]))

####### ggF Rad ###############
mp_ggFRad = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000]
sigXsec_ggFRad = [] #sig xsec
for i in mp_ggFRad: sigXsec_ggFRad.append(tuple([i,1.0]))

thmp_ggFRad = [800,900,1000,1500,1800,2000,2500,3000,3500,4500,5000] #theory mass points

thXsecunc_ggFRad = [] #theory xsec unc
for i in thmp_ggFRad: thXsecunc_ggFRad.append(tuple([i,0]))

thmass_ggFRad = []
for i in thmp_ggFRad: thmass_ggFRad.append(tuple([i,i]))

#BR radion to ZZ: from 800-3000:https://github.com/CrossSectionsLHC/WED/blob/master/Radion_Bulk/Decay_long_kl_35_arxiv1110.6452.txt

BRRadtoZZ = [ 0.209229, 0.214519, 0.218696, 0.218696,  0.218696, 0.218696,
         0.218696, 0.218696, 0.218696, 0.218696,  0.218696 ]

RadXsec = [ 0.5434525134607641,     0.3735615328391298,    0.2618915924170746,      0.054417137017588976,
            0.023912714207366757,   0.014293231312611458,  0.004301706042824362,    0.0013843144368847916,
            0.00046996032032601366, 0.0000534104307518241, 0.00001834556207323914]

thXsec_ggFRad = []
for i in range(len(thmp_ggFRad)):
    xsec = (BRRadtoZZ[i]*RadXsec[i]*1000)
    thXsec_ggFRad.append(tuple([thmp_ggFRad[i],xsec]))

####### ggF G ###############
mp_ggFG = [1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500] #available sample mass points those are analyzed.
sigXsec_ggFG = [] # Signal cross sections, set to 1pb (1000,1.0)
for i in mp_ggFG: sigXsec_ggFG.append(tuple([i,1.0]))

thmp_ggFG = [ 1000, 1500, 1800, 2000, 2500, 3000, 3500, 4500, 5000, 6000, 6500  ]

thmass_ggFG = []
for i in thmp_ggFG: thmass_ggFG.append(tuple([i,i]))

thXsecunc_ggFG = []
for i in thmp_ggFG: thXsecunc_ggFG.append(tuple([i,0]))

ggFG_NLO_0p1=[0.0056657071801246945,    0.0005727231501579456,  0.00018315617607742797,
              0.00009062263600103764,   0.00001868308774736877, 4.412202866735033e-6,
              1.1518090410508347e-6,    8.933087336020322e-8,   2.4883397029814656e-8,
              1.834050541862782e-9,     4.6067568192800316e-10  ]

BRGtoZZ = [ 0.12607893374826087, 0.1109356953055133, 0.10747431531156655, 0.10600852517377926,
            0.10379262318163233, 0.102605948149462,  0.1018961877814816,  0.1011246527052455,
            0.10090115453770737, 0.10061067367729358, 0.10051317966856908   ]

k0p5 = (0.5/0.1)*(0.5/0.1) # factor to change Bulk graviton Xsec from k~= 0.1 to 0.5

thXsec_ggFG = []
for i in range(len(thmp_ggFG)):
    xsec0p5 = ggFG_NLO_0p1[i]*k0p5*BRGtoZZ[i]*1000 #1000 to change to fb.
    thXsec_ggFG.append(tuple([thmp_ggFG[i],xsec0p5]))

#print "thXsec_ggFG: {}".format(thXsec_ggFG)

####### VBF G ###############
mp_VBFG = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000]
sigXsec_VBFG = [] #sig xsec
for i in mp_VBFG: sigXsec_VBFG.append(tuple([i,1.0]))

thmp_VBFG = [ 800, 1000, 1500, 1800, 2000, 2500, 3000, 3500, 4500, 5000  ]
thmass_VBFG = []
for i in thmp_VBFG: thmass_VBFG.append(tuple([i,i]))

thXsecunc_VBFG = []
for i in thmp_VBFG: thXsecunc_VBFG.append(tuple([i,0]))

VBFG_NLO_0p1 = [ 0.00044994506943427223, 0.0001478238308263867, 0.00001640641540069989,
                 5.486799520511501e-6,   2.8161410177497724e-6, 5.96167457011135e-7,
                 1.440976398414742e-7,   3.7653825711302106e-8, 2.8801312841217955e-9,
                 8.157049697186479e-10]


BRVBFGtoZZ = [ 0.14301853100044015, 0.12607893374826087, 0.1109356953055133, 0.10747431531156655,
       0.10600852517377926, 0.10379262318163233, 0.102605948149462,  0.1018961877814816,
       0.1011246527052455,  0.10090115453770737   ]

#k0p5 = (0.5/0.1)*(0.5/0.1) # factor to change Bulk graviton Xsec from k~= 0.1 to 0.5
thXsec_VBFG = []
for i in range(len(thmp_VBFG)):
    xsec0p5 = VBFG_NLO_0p1[i]*k0p5*BRVBFGtoZZ[i]*1000 #1000 to change to fb.
    thXsec_VBFG.append(tuple([thmp_VBFG[i],xsec0p5]))
#print "thXsec_VBFG: {}".format(thXsec_VBFG)





# ------------------------------------------
def SetHistoStyle( histo ) :
    histo.SetLineColor(2)
    histo.SetMarkerColor(1)
    histo.GetXaxis().SetTitleFont(42);
    histo.GetXaxis().SetLabelFont(42)
    histo.GetXaxis().SetTitleSize(0.045)
    histo.GetXaxis().SetTitleOffset(1.1)
    histo.GetXaxis().SetLabelOffset(0.011)
    histo.GetXaxis().SetLabelSize(0.04)

    histo.GetYaxis().SetTitleFont(42);
    histo.GetYaxis().SetLabelFont(42)
    histo.GetYaxis().SetTitleSize(0.045)
    histo.GetYaxis().SetTitleOffset(1.3)
    histo.GetYaxis().SetLabelOffset(0.011)
    histo.GetYaxis().SetLabelSize(0.04)

    histo.SetMarkerStyle(9)
    histo.SetMarkerColor(1)
    histo.SetFillColor(2)
    histo.SetFillStyle(1001)
    histo.SetTitle("")
    histo.GetYaxis().SetTitle("")
    histo.GetYaxis().CenterTitle()
    histo.GetXaxis().CenterTitle()
# ------------------------------------------

