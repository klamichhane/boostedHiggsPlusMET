import sys
from array import array
import ROOT as r

#for 1, 1.5, 1.8, 2.0, 2.5, 3.0, 3.5, 4.5
mass = array('d',[1000, 1500, 1800, 2000, 2500, 3000, 3500])
NLO_0p1=[0.0056657071801246945, 
         0.0005727231501579456,
         0.00018315617607742797,
         0.00009062263600103764,
         0.00001868308774736877,
         4.412202866735033e-6,
         1.1518090410508347e-6,
         #8.933087336020322e-8
    ]

G_ZZ_0p5 = array('d',[])
G_ZZ_1p0 = array('d',[])
br = 0.1*1000 #G->ZZ is 0.1 and 1000 for pb to fb
print("br "+str(br))
k0p5 = (0.5/0.1)*(0.5/0.1)
k1p0 = (1.0/0.1)*(1.0/0.1)
print("k0p5 "+str(k0p5))

for i in range(len(NLO_0p1)):
    G_ZZ_0p5.append(br*k0p5*NLO_0p1[i])
    G_ZZ_1p0.append(br*k1p0*NLO_0p1[i])

for j,k,l in zip(mass,G_ZZ_0p5,G_ZZ_1p0):
    print "for 0p1, 0.5, 1.0; {0}: {1}: {2}".format(j,k,l)

Exp_2016 = array('d',[40.0,7.0,4.0,2.5,1.6,1.4,1.1])
Exp_137 = array('d',[12.0,2.5,1.5,1.0,0.5,0.4,0.38])
print Exp_2016
print Exp_137

n = len(G_ZZ_0p5)
LisaHP = r.TGraph(n,mass,Exp_2016)
FullRun2 = r.TGraph(n,mass,Exp_137)
Th_0p5 = r.TGraph(n,mass,G_ZZ_0p5)
Th_1p0 = r.TGraph(n,mass,G_ZZ_1p0)
LisaHP.SetLineColor(r.kBlack)
FullRun2.SetLineColor(r.kBlue)
LisaHP.SetLineWidth(3)
FullRun2.SetLineWidth(3)
LisaHP.SetLineStyle(7)
FullRun2.SetLineStyle(7)
Th_0p5.SetLineColor(r.kGreen+3) 
Th_1p0.SetLineColor(r.kMagenta+2)
Th_0p5.SetLineWidth(3) 
Th_1p0.SetLineWidth(3)

LisaHP.GetYaxis().SetNdivisions(505);
LisaHP.GetXaxis().SetNdivisions(505);
LisaHP.GetXaxis().SetTitle("M_{G} [GeV]")
LisaHP.GetYaxis().SetTitle("#sigma(G) #times BR(G #rightarrow ZZ) (fb)")
LisaHP.SetMinimum(0.1)
LisaHP.SetMaximum(500)

c = r.TCanvas("c","c",500,500)
c.SetLeftMargin(0.15)
c.SetLogy()
LisaHP.Draw("AL")
FullRun2.Draw("L same")
Th_0p5.Draw("L same") 
Th_1p0.Draw("L same")

leg = r.TLegend(0.46,.6,.85,.88)
leg.SetFillColor(0)
leg.SetLineColor(r.kWhite)
leg.SetTextSize(0.04)

leg.AddEntry(LisaHP,"B2G-17-005 (35.9/fb)","l")
leg.AddEntry(FullRun2,"Full Run2 (137/fb)","l")
leg.AddEntry(Th_0p5,"Bulk G, #tilde{k}=0.5","l")
leg.AddEntry(Th_1p0,"Bulk G, #tilde{k}=1.0","l")

leg.Draw()

txt4 = r.TText(.18,.775,"ggF G incl.")
txt4.SetNDC()
txt4.SetTextSize(0.04)
txt4.SetTextColor(r.kOrange+10)
txt4.Draw("same")

