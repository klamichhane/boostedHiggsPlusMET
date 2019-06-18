from sys import argv

import ROOT as r
r.gROOT.SetBatch(True)

r.gROOT.ProcessLine(".L tdrstyle.C")
r.gROOT.ProcessLine("setTDRStyle()")

#plot_dir="ZSB_All_May15/2018/ZSBHPVBF"
plot_dir="ZSB_All_May30/2018/ZSBHPVBF"
#plot_dir="ZSB_All_May15/2018/ZSBNoVBF_AfterHEM"
#plot_dir="ZSB_All_May15/2018/ZSBNoVBF_AfterHTBeforeHEM"
#plot_dir="Alpha_Closure/2018"
#plot_dir="ZSB_All_May15/2018/baseline_NoVBF"
#plot_dir="ZNoVBF/AK4nAK8L1JCut_v1/2018"
#plot_dir="ZNoVBF/HTRatio_Opt_v6/2018"
#plot_dir="ZSB_2018_All/baseline_HP_VBF"
#plot_dir="Z_baseline_2018_All/V1" # Filter vs Calculated HEMDPhi
#plot_dir="Z_baseline_2018_All/BeforeHEMVeto"
#plot_dir="ZNoVBF_2018_AfterHEMCut_plots/For_2018D_HEMDphi"
#input_file_name = "ZNoSel_2018_All.root"
#input_file_name = "ZSBHPVBF_515_v3_2018.root"
input_file_name = "ZSBHPVBF_515_v4_2018.root"
#input_file_name = "ZSBNoVBF_515_AfterHEMVeto_2018.root"
#input_file_name = "ZSBNoVBF_515_AfterHTBeforeHEM_2018.root"
#input_file_name = "Alpha_SBHP_VBF_515_v4_2018.root"
#input_file_name = "ZNoSel_new_Ecal_v2_2018.root"
#input_file_name = "ZNoSel_new_v0_2018_EcalNemf.root"
#input_file_name = "test_ZSBNoVBF.root"
#input_file_name = "ZSBHPVBF_2018_All.root"
#input_file_name = "File_2018_All/BeforeHEMFilter_2018ADbkg.root"
#output_file_name = "ZNoSel_2018_All_Output.root"
#output_file_name = "ZNoSel_new_Ecal_v2_2018_Output.root"
#output_file_name = "Alpha_SBHP_NoVBF_515_v4_2018.root"
#output_file_name = "Alpha_Closure_Files/2018/Closure_2018_v3/Alpha_SBHP_VBF_515_v4_2018_Output.root"
output_file_name = "ZSBHPVBF_515_v4_2018_Output.root"
#output_file_name = "ZSBNoVBF_515_AfterHEMVeto_2018_Output.root"
#output_file_name = "ZSBNoVBF_515_AfterHTBeforeHEMVeto_2018_Output.root"
#output_file_name = "ZSBNoVBF_2018_All_Output.root"

input_file = r.TFile(input_file_name,"READ")    

def plot(plot_var = "photonIsoChrgLowSieie_EB_photonLoose" ):

    samples=[#["QCD_200to300",
             ["ST_s-channel",
              "ST_tW_antitop",
              "ST_tW_top"],
             ["TT_600to800",
              "TT_800to1200",
              "TT_1200to2500",
              "TT_2500toInf",
              "TT_1LFromT",
              "TT_1LFromTbar",
              "TT_2L"],
             ["Other_WWTo1L1Nu2Q",
              "Other_WZTo1L3Nu",
              "Other_ZZTo2L2Q",
              "Other_TTWJetsToLNu",
              "Other_TTWJetsToQQ",
              "Other_TTGJets",
              "Other_TTZToLLNuNu",
              "Other_TTZToQQ"],
             ["WJets_100to200",
              "WJets_200to400",
              "WJets_400to600",
              "WJets_600to800",
              "WJets_800to1200",
              "WJets_1200to2500",
              "WJets_2500toInf"],
             ["ZJets_100to200",
              "ZJets_200to400",
              "ZJets_400to600",
              "ZJets_600to800",
              "ZJets_800to1200",
              "ZJets_1200to2500",
              "ZJets_2500toInf"]
             ]

    signal_samples=["VBFG_1200"]

    data_samples=["MET_2018D",#]
                "MET_2018C",
                "MET_2018B",
                "MET_2018A"]

    samples_labels = ["Single top","TT","Other","WJets","ZJets"]
    samples_fill_color = [r.kOrange,r.kCyan,r.kOrange+3,r.kBlue,r.kGreen+1]
    samples_line_color = [1,1,1,1,1]
    
    samples_histo=[]
    
    total = None
    stack = r.THStack("stack","stack")
   
    for i,sample_names in enumerate(samples) :   
        for j,sample_name in enumerate(sample_names): 
            if len(samples_histo) <= i : 
                samples_histo.append(input_file.Get(plot_var+"_"+sample_name))
                if samples_histo[-1]==None :
                    print "looking for:",plot_var+"_"+sample_name
                    print input_file.ls(plot_var+"_"+sample_name)
                    #input_file.ls()
                    assert(samples_histo[-1]!=None)
                elif samples_histo[-1].Integral() < 0.0001 :
                    print "oops.",plot_var+"_"+sample_name,"is empty"
                samples_histo[-1].SetLineColor(samples_line_color[i])
                samples_histo[-1].SetFillColor(samples_fill_color[i])
                samples_histo[-1].SetName(plot_var+"_"+samples_labels[i])
            else : 
                samples_histo[-1].Add(input_file.Get(plot_var+"_"+sample_name))
 ## for signal sample
    signal_histo=[]
    for i,signal_sample_names in enumerate(signal_samples) :
        if i==0:
            signal_histo.append(input_file.Get(plot_var+"_"+signal_sample_names))
            signal_histo[-1].SetLineColor(r.kRed)
            signal_histo[-1].SetLineWidth(2)
            #signal_histo[-1].SetName(plot_var+"_"+signal_samples_labels[i])
            if signal_histo[-1]==None :
                print "looking for:",plot_var+"_"+sample_name
                assert(signal_histo[-1]!=None)
        else :
            signal_histo[-1].Add(input_file.Get(plot_var+"_"+signal_sample_name))
 ## end of signal sample

    data_histo=[]
    for i,s in enumerate(data_samples):
        if i == 0 : 
            data_histo.append(input_file.Get(plot_var+"_"+s))
            data_histo[-1].SetMarkerStyle(8)
            data_histo[-1].SetName(plot_var+"_Data")
            if data_histo[-1]==None :
                print "looking for:",plot_var+"_"+sample_name
                assert(data_histo[-1]!=None)
        else : 
            data_histo[-1].Add(input_file.Get(plot_var+"_"+s))

    #print "data integral",data_histo[-1].Integral()
    for i,h in enumerate(samples_histo) : 
        if h==None: continue
        if total==None:
            total = r.TH1F(h)
            total.SetName(plot_var+"_sum")
        else : 
            total.Add(h)

    for i,h in enumerate(samples_histo) : 
        #print h.GetTitle(),"before",h.Integral()
        if h.Integral()>0 and total!=None:
            h.Scale(data_histo[0].Integral()/total.Integral())
        #print h.GetTitle(),"after",h.Integral()
        stack.Add(h)
    if total!=None and total.Integral()>0: 
    #if total!=None: 
        total.Scale(data_histo[0].Integral()/total.Integral())

    # For legend
    leg = r.TLegend(0.45,.77,.9,.92) 
    leg.SetNColumns(4)
    leg.SetFillColor(0)
    leg.SetLineColor(r.kWhite)

    if data_histo:
       #leg.AddEntry(data_histo[-1],"data","p") 
       leg.AddEntry(data_histo[-1],"MET 2018","p") 
    for i in range(len(samples_histo)):
        leg.AddEntry(samples_histo[i],samples_labels[i],"f")
    for i in range(len(signal_histo)):
        leg.AddEntry(signal_histo[i],"VBFG 1200","f")
        #leg.AddEntry(signal_histo[i],signal_samples_labels[i],"f")


    can = r.TCanvas("can","can",500,500)
    topPad = r.TPad("topPad","topPad",0.,0.4,.99,.99);
    botPad = r.TPad("botPad","botPad",0.,0.01,.99,.39);
    botPad.SetBottomMargin(0.35);
    botPad.SetTopMargin(0.02);
    topPad.SetTopMargin(0.06);
    topPad.SetBottomMargin(0.01);
    topPad.Draw();
    botPad.Draw(); 
    topPad.cd();
    
    stack.Draw("histo")    
    #for j in signal_histo :
    signal_histo[0].Draw("histo SAME")
    data_histo[0].Draw("SAME,e1p") 
    leg.Draw()

    if total!=None:
        stack.SetMaximum(1.5*max(total.GetMaximum(),samples_histo[0].GetMaximum()))
    else :
        stack.SetMaximum(1.5*samples_histo[0].GetMaximum())
    stack.SetMinimum(0.1)

    stack.GetYaxis().SetTitle("Events")
    stack.GetYaxis().SetLabelFont(43);
    stack.GetYaxis().SetLabelSize(24);
    stack.GetYaxis().SetTitleFont(43);
    stack.GetYaxis().SetTitleSize(24);
    stack.GetYaxis().SetTitleOffset(1.7);

    stack.GetXaxis().SetLabelFont(43);
    stack.GetXaxis().SetLabelSize(24);
    stack.GetXaxis().SetTitleFont(43);
    stack.GetXaxis().SetTitleSize(24);
    stack.GetXaxis().SetTitleOffset(1.7);

    CMStext = r.TText(.17,.95,"CMS")
    CMStext.SetNDC()
    CMStext.SetTextFont(61)
    CMStext.SetTextSize(0.08)
    CMStext.Draw()
    
    SIMtext = r.TText(.28,.95,"preliminary")
    SIMtext.SetNDC()
    SIMtext.SetTextFont(52)
    SIMtext.SetTextSize(0.08)
    SIMtext.Draw()
    
    #LUMItext = r.TText(.45,.95,"13 TeV (38.6/fb : Post-HEM)")
    #LUMItext = r.TText(.60,.95,"(14/fb : Pre-HEM)") # RunA
    #LUMItext = r.TText(.60,.95,"(38.6/fb : Post-HEM)") # Run D
    #LUMItext = r.TText(.65,.95,"13 TeV (20.9/fb : Pre-HEM)")
    LUMItext = r.TText(.60,.95,"13 TeV (59.5/fb)")
    LUMItext.SetNDC()
    LUMItext.SetTextFont(51)
    LUMItext.SetTextSize(0.08)
    LUMItext.Draw()

    botPad.cd()
    ratio = r.TH1F(data_histo[0])
    ratio.SetMarkerStyle(8)
    ratio.SetName(plot_var+"_ratio")
    if total!=None:
        ratio.Divide(total)
    ratio.GetYaxis().SetRangeUser(0,2)
    ratio.GetYaxis().SetTitle("Data/MC")
    ratio.GetXaxis().SetTitle(data_histo[0].GetXaxis().GetTitle())
    ratio.GetYaxis().SetLabelFont(43);
    ratio.GetYaxis().SetLabelSize(24);
    ratio.GetYaxis().SetTitleFont(43);
    ratio.GetYaxis().SetTitleSize(24);
    ratio.GetYaxis().SetNdivisions(505);
    ratio.GetYaxis().SetTitleOffset(1.7);

    ratio.GetXaxis().SetLabelFont(43);
    ratio.GetXaxis().SetLabelSize(24);
    ratio.GetXaxis().SetTitleFont(43);
    ratio.GetXaxis().SetTitleSize(24);
    ratio.GetXaxis().SetTitleOffset(2.8);
    # Draw a horizontal line at 1 in ratio plot
    nbins = ratio.GetNbinsX()
    l = r.TLine(ratio.GetBinLowEdge(1),1.0,ratio.GetBinLowEdge(nbins+1),1.0);
    l.SetLineColor(r.kRed);
    l.SetLineWidth(2);
    ratio.Draw() 
    l.Draw("same"); 
    

    can.SaveAs("../plots/"+plot_dir+"/"+plot_var+".png")
    # for space between legend and plot 
    topPad.SetLogy()
    if total!=None:
        stack.SetMaximum(20.0*max(total.GetMaximum(),data_histo[0].GetMaximum()))
    else :
        stack.SetMaximum(20.0*data_histo[0].GetMaximum())
    stack.SetMinimum(0.1)
    can.SaveAs("../plots/"+plot_dir+"/"+plot_var+"_LogY.png")

    output_file.cd()
    for h in samples_histo :
        r.TH1F(h).Write()
    data_histo[0].Write()
    for i in signal_histo :
        r.TH1F(i).Write()


output_file = r.TFile(output_file_name,"RECREATE")
    
vars = []
list = input_file.GetListOfKeys()
next = r.TIter(list);
key = next()
while(key != None ) :
    obj = key.ReadObj();
    if obj.InheritsFrom("TH1") and not obj.InheritsFrom("TH2"):
        name = r.TString(obj.GetName())
        if name.Contains("_ZJets_100to200") : 
            #print name
            #print "integral:",obj.Integral()
            vars.append(name.ReplaceAll("_ZJets_100to200","").Data())
    else :
        print obj.Print()
    key = next()

print vars
for var in vars : 
    plot(var)

    
output_file.Close()
input_file.Close()
