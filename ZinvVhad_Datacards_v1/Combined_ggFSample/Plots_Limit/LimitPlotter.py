#!/usr/bin/env python
import ROOT as r
from ROOT import *
from array import *
gROOT.SetBatch(True)
import sys, os
from os.path import isfile, join
import math
#from SigXsec_VBFG import *
from SigXsec import *

sample = sys.argv[1]    #"VBFG" "VBFWp" "VBFRad" "ggFG" "ggFWp" "ggFRad" 
year = "2016"      #"137fb" 
#year = "137fb"      #"137fb" 

if year=="2016":   lumi = "35.8"
elif year=="2017": lumi = "41.5"
elif year=="2018": lumi = "59.5"
else: lumi = "137"

fwd="jj" if "VBF" in sample else ""
if sample=="VBFG" or sample=="ggFG": ytitle = "#sigma(G{}) #times BR(G #rightarrow ZZ) (fb)".format(fwd); xtitle = "M_{Graviton} (GeV)"; title = "Bulk G"
elif sample=="VBFWp" or sample=="ggFWp": ytitle = "#sigma(W'{}) #times BR(W' #rightarrow WZ) (fb)".format(fwd); xtitle = "M_{Wprime} (GeV)"; title = "Wprime"
elif sample=="VBFRad" or sample=="ggFRad": ytitle = "#sigma(Rad{}) #times BR(Rad #rightarrow ZZ) (fb)".format(fwd); xtitle = "M_{Radion} (GeV)"; title = "Radion"

# Extract input arguments
# ------------------------------
path = os.getcwd() # gives current dir
parent = os.path.dirname(path) # gives previous dir i.e. parent of current dir
inputfoldername=parent+"/Combo_"+sample+"_"+year+"/Root_Limit/"
#inputfoldername=parent+"/"+sample+"_"+year+"/Root_Limit/"

# Extract file names in target dir
# ------------------------------
filelist = [f for f in os.listdir(inputfoldername) if isfile(join(inputfoldername, f)) if ".root" in f]

# sig Xsec, thXsec, thXsecunc, theory mass
if sample == "ggFWp": signalmasscrosssection = sigXsec_ggFWp; theorycrosssection = thXsec_ggFWp; theorycrosssectionunc = thXsecunc_ggFWp; theorymass = thmass_ggFWp
elif sample == "ggFRad": signalmasscrosssection = sigXsec_ggFRad; theorycrosssection = thXsec_ggFRad; theorycrosssectionunc = thXsecunc_ggFRad; theorymass = thmass_ggFRad
elif sample == "ggFG": signalmasscrosssection = sigXsec_ggFG; theorycrosssection = thXsec_ggFG; theorycrosssectionunc = thXsecunc_ggFG; theorymass = thmass_ggFG
elif sample == "VBFG": signalmasscrosssection = sigXsec_VBFG; theorycrosssection = thXsec_VBFG; theorycrosssectionunc = thXsecunc_VBFG; theorymass = thmass_VBFG
else: signalmasscrosssection = sigXsec_VBFG; theorycrosssection = thXsec_VBFG; theorycrosssectionunc = thXsecunc_VBFG; theorymass = thmass_VBFG

# Extract r-values from Combine output root files
# ------------------------------
m2sigmaexparray=[]; m1sigmaexparray=[]; meanexparray=[]
p1sigmaexparray=[]; p2sigmaexparray=[]; massarray=[]; masserrorarray=[]
#obsarray=[]
WZbr = 0.13482 if sample=="ggFWp" else 1

for filename in filelist:
    infile=TFile(inputfoldername+"/"+filename,"READ")
    #infile.ls()
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==0 and round(event.quantileExpected,2) == 0.03 : m2sigmaexparray.append((round(event.mh,0),event.limit/WZbr))
        if ie==1 and round(event.quantileExpected,2) == 0.16 : m1sigmaexparray.append((round(event.mh,0),event.limit/WZbr))
        if ie==2 and round(event.quantileExpected,2) == 0.5  : meanexparray.append((round(event.mh,0),event.limit/WZbr))
        if ie==3 and round(event.quantileExpected,2) == 0.84 : p1sigmaexparray.append((round(event.mh,0),event.limit/WZbr))
        if ie==4 and round(event.quantileExpected,2) == 0.98 : p2sigmaexparray.append((round(event.mh,0),event.limit/WZbr))
        #if ie==5 and round(event.quantileExpected,2) == -1.0 : obsarray.append((round(event.mh,0),event.limit))
        if ie==5 and round(event.quantileExpected,2) == -1.0 : masserrorarray.append(0.0)
print "got limits into array"

print "exp limit: {}".format(meanexparray)
# Create r-value limit arrays
# ------------------------------
signalcrosssectionsorted = [ x[1] for x in sorted(signalmasscrosssection, key=lambda tup: tup[0]) ]
theorycrosssectionsorted = [ x[1] for x in sorted(theorycrosssection, key=lambda tup: tup[0]) ]
theorycrosssectionuncsorted = [ x[1] for x in sorted(theorycrosssectionunc, key=lambda tup: tup[0]) ]
theorymasssorted      = [ x[1] for x in sorted(theorymass,      key=lambda tup: tup[0]) ]
#obsarraysorted        = [ x[1] for x in sorted(obsarray,        key=lambda tup: tup[0]) ]
m2sigmaexparraysorted = [ x[1] for x in sorted(m2sigmaexparray, key=lambda tup: tup[0]) ]
m1sigmaexparraysorted = [ x[1] for x in sorted(m1sigmaexparray, key=lambda tup: tup[0]) ]
meanexparraysorted    = [ x[1] for x in sorted(meanexparray,    key=lambda tup: tup[0]) ]
massarraysorted       = [ x[0] for x in sorted(meanexparray,    key=lambda tup: tup[0]) ]
massarraysortedV2     = [ x[0] for x in sorted(signalmasscrosssection,    key=lambda tup: tup[0]) ]
p1sigmaexparraysorted = [ x[1] for x in sorted(p1sigmaexparray, key=lambda tup: tup[0]) ]
p2sigmaexparraysorted = [ x[1] for x in sorted(p2sigmaexparray, key=lambda tup: tup[0]) ]


for imass in massarraysorted:
    if imass not in massarraysortedV2 : 
        print "\nERROR: input limit mass "+str(imass)+" is not included in the signal cross-section array!"
        print "available signal masses: ",massarraysortedV2
        print "..exiting!\n"
        exit(1)


# Create cross-section normalized limit arrays
# ------------------------------
#obsarraysorted        = [a*b for a,b in zip(signalcrosssectionsorted,obsarraysorted)]
m2sigmaexparraysorted = [a*b for a,b in zip(signalcrosssectionsorted,m2sigmaexparraysorted)]
m1sigmaexparraysorted = [a*b for a,b in zip(signalcrosssectionsorted,m1sigmaexparraysorted)]
meanexparraysorted    = [a*b for a,b in zip(signalcrosssectionsorted,meanexparraysorted)]
p1sigmaexparraysorted = [a*b for a,b in zip(signalcrosssectionsorted,p1sigmaexparraysorted)]
p2sigmaexparraysorted = [a*b for a,b in zip(signalcrosssectionsorted,p2sigmaexparraysorted)]

# Create bands for +/- 1 and 2 sigma & theory xsec uncertainty
# ------------------------------
m2bandmeanexpsorted=[]; m1bandmeanexpsorted=[]
p1bandmeanexpsorted=[]; p2bandmeanexpsorted=[]
expLimit = 0; #obsLimit = 0
for im,mass in enumerate(massarraysorted) :
    m2bandmeanexpsorted.append( meanexparraysorted[im]-m2sigmaexparraysorted[im])
    m1bandmeanexpsorted.append( meanexparraysorted[im]-m1sigmaexparraysorted[im])
    p1bandmeanexpsorted.append(-meanexparraysorted[im]+p1sigmaexparraysorted[im])
    p2bandmeanexpsorted.append(-meanexparraysorted[im]+p2sigmaexparraysorted[im])
    
# Calculate limit (obs. & exp.) automatically
# ------------------------------
print "next: create canvas"        

# Create output canvas
# ------------------------------
can=TCanvas("can1","can1",0,0,750,750); can.cd()
gStyle.SetOptStat(0)
can.SetLeftMargin(0.15); can.SetRightMargin(0.10); can.SetTopMargin(0.07); can.SetBottomMargin(0.13)
can.SetTickx(1); can.SetTicky(1); can.SetLogy(1)


# Create limit curves
# ------------------------------
theorycurve             = TGraphErrors ( len(theorycrosssectionsorted), array('d',theorymasssorted), array('d',theorycrosssectionsorted) )
for im,mass in enumerate(theorymasssorted) :
    theorycurve.SetPointError(im,0,theorycrosssectionuncsorted[im])
    
#observedlimit           = TGraph( len(massarraysorted), array('d',massarraysorted), array('d',obsarraysorted) )
m2sigmaexpectedlimit    = TGraph( len(massarraysorted), array('d',massarraysorted), array('d',m2sigmaexparraysorted) )
m1sigmaexpectedlimit    = TGraph( len(massarraysorted), array('d',massarraysorted), array('d',m1sigmaexparraysorted) )
expectedlimit           = TGraph( len(massarraysorted), array('d',massarraysorted), array('d',meanexparraysorted)    )
expected1sigmalimitarea = TGraphAsymmErrors( len(massarraysorted), array('d',massarraysorted), array('d',meanexparraysorted), array('d',masserrorarray), array('d',masserrorarray), array('d',m1bandmeanexpsorted), array('d',p1bandmeanexpsorted)   )
expected2sigmalimitarea = TGraphAsymmErrors( len(massarraysorted), array('d',massarraysorted), array('d',meanexparraysorted), array('d',masserrorarray), array('d',masserrorarray), array('d',m2bandmeanexpsorted), array('d',p2bandmeanexpsorted)   )
p1sigmaexpectedlimit    = TGraph( len(massarraysorted), array('d',massarraysorted), array('d',p1sigmaexparraysorted) )
p2sigmaexpectedlimit    = TGraph( len(massarraysorted), array('d',massarraysorted), array('d',p2sigmaexparraysorted) )

# Create canvas
# ------------------------------
can.cd(); #can.SetLogy(1)
can.SetLeftMargin(0.16)
can.SetRightMargin(0.08)
can.SetTopMargin(0.07)
can.SetBottomMargin(0.13)

# Create legends
# ------------------------------
legend2 = TLegend(0.52,0.6,0.83,0.7)
legend2.SetFillColor(0); legend2.SetLineColor(0); legend2.SetFillColor(0); legend2.SetFillStyle(0)
legend2.SetTextSize(0.027); legend2.SetTextFont(42); legend2.SetTextAlign(12)
if sample   == "ggFG":   legend2.AddEntry(theorycurve,"G_{Bulk} (#tilde{k} = 0.5)","L")
elif sample == "VBFG":   legend2.AddEntry(theorycurve,"G_{Bulk}jj (#tilde{k} = 0.5)","L")
elif sample == "ggFRad": legend2.AddEntry(theorycurve,"Radion (#Lambda_{R} = 3 TeV, kl = 35)","L")
elif sample == "VBFRad": legend2.AddEntry(theorycurve,"Radion jj (#Lambda_{R} = 3 TeV, kl = 35)","L")
elif sample == "ggFWp":  legend2.AddEntry(theorycurve,"W' (HVT model B)","L")
elif sample == "VBFWp":  legend2.AddEntry(theorycurve,"W'jj (HVT model B)","L")
legend = TLegend(0.52,0.7,0.83,0.92)
legend.SetFillColor(0); legend.SetLineColor(0); legend.SetFillColor(0); legend.SetFillStyle(0)
#legend.SetTextSize(0.032); legend.SetTextFont(42); legend.SetTextAlign(12)
legend.SetTextSize(0.027); legend.SetTextFont(42); legend.SetTextAlign(12)
legend.SetHeader("95% CL upper limits")
legend.AddEntry(expectedlimit,"Expected","PL")
legend.AddEntry(expected1sigmalimitarea,"Expected #pm 1 s.d.","F")
legend.AddEntry(expected2sigmalimitarea,"Expected #pm 2 s.d.","F")


# Create labels
# ------------------------------
#cmslabel      = TLatex(); cmslabel.SetTextFont(61);      cmslabel.SetTextAlign(11);      cmslabel.SetNDC();      cmslabel.SetTextSize(0.042)
cmslabel      = TLatex(); cmslabel.SetTextFont(61);      cmslabel.SetTextAlign(11);      cmslabel.SetNDC();      cmslabel.SetTextSize(0.032)
cmsextralabel = TLatex(); cmsextralabel.SetTextFont(52); cmsextralabel.SetTextAlign(11); cmsextralabel.SetNDC(); cmsextralabel.SetTextSize(0.032)
lumilabel     = TLatex(); lumilabel.SetTextFont(42);     lumilabel.SetTextAlign(31);     lumilabel.SetNDC();     lumilabel.SetTextSize(0.032)
vbflabel     = TLatex(); vbflabel.SetTextFont(42);     vbflabel.SetTextAlign(31);     vbflabel.SetNDC();     vbflabel.SetTextSize(0.032)


# Draw & save output 
# ------------------------------
#if sample=="ggFG" or sample == "ggFWp" or sample =="ggFRad": hFrame = TH1D("","",1,1000,4500)
#else: hFrame = TH1D("","",1,800,8000)
hFrame = TH1D("","",1,1000,4500)
hFrame.Draw("HIST")
SetHistoStyle(hFrame)
if year == "137fb": hFrame.GetYaxis().SetRangeUser(0.01,1000.)
else: hFrame.GetYaxis().SetRangeUser(0.1,1000.)
hFrame.GetYaxis().SetTitle(ytitle)
hFrame.GetXaxis().SetTitle(xtitle)
expectedlimit.SetLineStyle(2)
expectedlimit.SetLineWidth(4)
expected1sigmalimitarea.SetFillColor(kGreen+1)
expected1sigmalimitarea.SetLineColor(kGreen+1)
expected1sigmalimitarea.SetFillStyle(1001)
expected2sigmalimitarea.SetFillColor(kOrange)
expected2sigmalimitarea.SetLineColor(kOrange)
expected2sigmalimitarea.SetFillStyle(1001)
theorycurve.SetFillColor(kRed-9)
theorycurve.SetFillStyle(1001)
theorycurve.SetLineColor(kRed+1)
theorycurve.SetLineWidth(3)
expected2sigmalimitarea.Draw("3same")
expected1sigmalimitarea.Draw("3same")
if sample == "ggFG" or sample=="VBFG" or sample=="ggFWp" or sample=="ggFRad": 
    theorycurve.Draw("3same"); theorycurve.Draw("LXsame")
else: print "add theory Xsec for theory line"
expectedlimit.Draw("PLsame")
#expectedlimit.Draw("PCsame")
legend2.Draw()
legend.Draw()
cmslabel.DrawLatex(0.16,0.942,"CMS")
cmsextralabel.DrawLatex(0.26,0.942,"Preliminary")
lumilabel.DrawLatex(0.92,0.942,lumi+" fb^{-1} (13 TeV)")
#vbflabel.DrawLatex(0.4,0.842,sample+" HP")
vbflabel.DrawLatex(0.4,0.842,title+" HP")
gPad.RedrawAxis()
#can.SaveAs("Limit_"+sample+"_HP_"+year+".pdf")
can.SaveAs(year+"/Combined_"+sample+"_Limit_HP_"+year+".pdf")

