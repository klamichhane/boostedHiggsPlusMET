#!/usr/bin/env python
from ROOT import *
from array import *
gROOT.SetBatch(True)
import sys, os
from os.path import isfile, join
import math

# ------------------------------
def SetHistoStyle( histo ) :
    histo.SetLineColor(2)
    histo.SetMarkerColor(1)
    histo.GetXaxis().SetTitleFont(42);
    histo.GetYaxis().SetTitleFont(42);
    histo.GetXaxis().SetTitleSize(0.05);
    histo.GetYaxis().SetTitleSize(0.05);
    histo.GetXaxis().SetTitleFont(42)
    histo.GetYaxis().SetTitleFont(42)
    histo.GetXaxis().SetLabelFont(42)
    histo.GetYaxis().SetLabelFont(42)
    histo.GetXaxis().SetTitleSize(0.055)
    histo.GetYaxis().SetTitleSize(0.055)
    histo.GetXaxis().SetTitleOffset(1.1)
    histo.GetYaxis().SetTitleOffset(1.3)
    histo.GetXaxis().SetLabelOffset(0.011)
    histo.GetYaxis().SetLabelOffset(0.011)
    histo.GetXaxis().SetLabelSize(0.045)
    histo.GetYaxis().SetLabelSize(0.045)
    histo.SetMarkerStyle(9)
    histo.SetMarkerColor(1)
    histo.SetFillColor(2)
    histo.SetFillStyle(1001)
    histo.SetTitle("")
    histo.GetYaxis().SetTitle("Count")
    histo.GetYaxis().CenterTitle()
    histo.GetXaxis().CenterTitle()
# ------------------------------

print 'Make sure there is no other root files besides the limit in the inputfoldername !!!'
print "run the program: with argument for the category: VBF or No VBF"


# Extract input arguments
# ------------------------------
inputfoldername="/home/kamal/VBF_ZZ_March2019/boostedHiggsPlusMET/src/BkgEst_Alpha/May_FullRun2_v4/LimitPlot/"
limitname="VBF" # will be used only to save file and label the category on plot.
#limitname=sys.argv[1] # will be used only to save file and label the category on plot.


# Extract file names in target dir
# ------------------------------
filelist = [f for f in os.listdir(inputfoldername) if isfile(join(inputfoldername, f)) if ".root" in f]
#print filelist


# Signal cross sections
# ------------------------------
signalmasscrosssection = [ 
    (1000 ,1.0  ), # set to 1 pb 
    (1200 ,1.0  ),
    (1400 ,1.0  ),
    (1600 ,1.0  ),
    (1800 ,1.0  ),
    (2000 ,1.0  ),
    (2500 ,1.0  ),
    (3000 ,1.0  ),
    (3500 ,1.0  ),
    (4000 ,1.0  ),
    (4500 ,1.0  )
    ]

# Theory cross sections
# ------------------------------
theorycrosssection = [ 
    (1000 , 0.0684798),
    (1200 , 0.055003),
    (1400 , 0.044479),
    (1600 , 0.0362064),
    (1800 , 0.0296363),
    (2000 , 0.0243714),
    (2500 , 0.0201627),
    (3000 , 0.0167339),
    (3500 , 0.013949),
    (4000 , 0.0116662),
    (4500 , 0.00980217)
    ]

# Theory cross sections Unc
# ------------------------------
theorycrosssectionunc = [ 
    (1000 , 0),
    (1200 , 0),
    (1400 , 0),
    (1600 , 0),
    (1800 , 0),
    (2000 , 0),
    (2500 , 0),
    (3000 , 0),
    (3500 , 0),
    (4000 , 0),
    (4500 , 0)
    ]

# Theory mass
# ------------------------------
theorymass = [ 
    (1000 , 1000),
    (1200 , 1200),
    (1400 , 1400),
    (1600 , 1600),
    (1800 , 1800),
    (2000 , 2000),
    (2500 , 2500),
    (3000 , 3000),
    (3500 , 3500),
    (4000 , 4000),
    (4500 , 4500)
    ]

# Extract r-values from Combine output root files
# ------------------------------
m2sigmaexparray=[]
m1sigmaexparray=[]
meanexparray=[]
p1sigmaexparray=[]
p2sigmaexparray=[]
#obsarray=[]
massarray=[]
masserrorarray=[]
#print
for filename in filelist:
#    print  filename
    infile=TFile(inputfoldername+"/"+filename,"READ")
    #infile.ls()
    tr=infile.Get("limit")
    for ie,event in enumerate(tr):
        if ie==0 and round(event.quantileExpected,2) == 0.03 : m2sigmaexparray.append((round(event.mh,0),event.limit))
        if ie==1 and round(event.quantileExpected,2) == 0.16 : m1sigmaexparray.append((round(event.mh,0),event.limit))
        if ie==2 and round(event.quantileExpected,2) == 0.5  : meanexparray.append((round(event.mh,0),event.limit))
        if ie==3 and round(event.quantileExpected,2) == 0.84 : p1sigmaexparray.append((round(event.mh,0),event.limit))
        if ie==4 and round(event.quantileExpected,2) == 0.98 : p2sigmaexparray.append((round(event.mh,0),event.limit))
        #if ie==5 and round(event.quantileExpected,2) == -1.0 : obsarray.append((round(event.mh,0),event.limit))
        if ie==5 and round(event.quantileExpected,2) == -1.0 : masserrorarray.append(0.0)
print "got limits into array"

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
m2bandmeanexpsorted=[]
m1bandmeanexpsorted=[]
p1bandmeanexpsorted=[]
p2bandmeanexpsorted=[]
expLimit = 0
#obsLimit = 0
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
can.SetTickx(1); can.SetTicky(1); can.SetLogy(0)


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
can.cd(); can.SetLogy(1)
can.SetLeftMargin(0.16)
can.SetRightMargin(0.08)
can.SetTopMargin(0.07)
can.SetBottomMargin(0.13)

# Create legends
# ------------------------------
legend2 = TLegend(0.52,0.6,0.83,0.7)
legend2.SetFillColor(0); legend2.SetLineColor(0); legend2.SetFillColor(0); legend2.SetFillStyle(0)
legend2.SetTextSize(0.032); legend2.SetTextFont(42); legend2.SetTextAlign(12)
legend2.AddEntry(theorycurve,"#sigma_{Th} (G_{Bulk}#rightarrow ZZ), #tilde{k}=0.1","FL")
legend = TLegend(0.52,0.7,0.83,0.92)
legend.SetFillColor(0); legend.SetLineColor(0); legend.SetFillColor(0); legend.SetFillStyle(0)
legend.SetTextSize(0.032); legend.SetTextFont(42); legend.SetTextAlign(12)
legend.SetHeader("95% CL upper limits")
legend.AddEntry(expectedlimit,"Expected","PL")
legend.AddEntry(expected1sigmalimitarea,"Expected #pm 1 s.d.","F")
legend.AddEntry(expected2sigmalimitarea,"Expected #pm 2 s.d.","F")


# Create labels
# ------------------------------
cmslabel      = TLatex(); cmslabel.SetTextFont(61);      cmslabel.SetTextAlign(11);      cmslabel.SetNDC();      cmslabel.SetTextSize(0.042)
cmsextralabel = TLatex(); cmsextralabel.SetTextFont(52); cmsextralabel.SetTextAlign(11); cmsextralabel.SetNDC(); cmsextralabel.SetTextSize(0.042)
lumilabel     = TLatex(); lumilabel.SetTextFont(42);     lumilabel.SetTextAlign(31);     lumilabel.SetNDC();     lumilabel.SetTextSize(0.042)
vbflabel     = TLatex(); vbflabel.SetTextFont(42);     vbflabel.SetTextAlign(31);     vbflabel.SetNDC();     vbflabel.SetTextSize(0.042)


# Draw & save output 
# ------------------------------
hFrame = TH1D("","",1,1000,4500)
hFrame.Draw("HIST")
SetHistoStyle(hFrame)
hFrame.GetYaxis().SetRangeUser(0.001,500.)
hFrame.GetYaxis().SetTitle("#sigma (fb)")
hFrame.GetXaxis().SetTitle("M_{G} (GeV)")
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
theorycurve.SetLineWidth(2)
expected2sigmalimitarea.Draw("3same")
expected1sigmalimitarea.Draw("3same")
theorycurve.Draw("3same")
theorycurve.Draw("LXsame")
expectedlimit.Draw("PLsame")
legend2.Draw()
legend.Draw()
cmslabel.DrawLatex(0.16,0.942,"CMS")
cmsextralabel.DrawLatex(0.26,0.942,"Preliminary")
lumilabel.DrawLatex(0.92,0.942,"137 fb^{-1} (13 TeV)")
vbflabel.DrawLatex(0.35,0.842,"VBF")
gPad.RedrawAxis()
can.SaveAs("limitPlotter_"+limitname+".pdf")

#print 
if expLimit <= massarraysorted[0] or expLimit >= massarraysorted[len(massarraysorted)-1] : print "No expected limit calculation possible!"
elif expLimit != 0 : 
    print "Expected Limit: %.0f GeV" % expLimit
