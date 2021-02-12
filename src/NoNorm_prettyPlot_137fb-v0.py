from sys import argv

import ROOT as r
r.gROOT.SetBatch(True)

r.gROOT.ProcessLine(".L tdrstyle.C")
r.gROOT.ProcessLine("setTDRStyle()")

year = argv[1]
cat = argv[2]

location = "AN_ORv1_files"
plotloc  = "AN_ORv1_plots"

plot_dir        = plotloc+"/{0}/{1}/".format(cat,year)
input_file_name = location+"/{0}_ORv1/{1}_AN_v1_{0}.root".format(year,cat)
output_file_name= location+"/{0}_ORv1/Output_NoNorm/{1}_AN_v1_{0}_Output_NoNorm.root".format(year,cat)
#input_file_name = location+"/Systematics_LP/{0}/{1}_AN_v1_{0}.root".format(year,cat)
#output_file_name= location+"/Systematics_LP/{0}/Output_NoNorm/{1}_AN_v1_{0}_Output_NoNorm.root".format(year,cat)

if year == "2016": lumi="35.8/fb"
elif year == "2017": lumi="41.5/fb"
elif year == "2018": lumi="59.5/fb"
elif year == "137fb": lumi="137/fb"


input_file = r.TFile(input_file_name,"READ")    

def plot(plot_var = "photonIsoChrgLowSieie_EB_photonLoose" ):

    samples=[#["QCD_200to300",
             ["ST_s-channel",
              "ST_t-channel_antitop",
              "ST_t-channel_top",
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
              "Other_WWZ",
              "Other_WZTo1L1Nu2Q",
              "Other_WZTo1L3Nu",
              #"Other_WZ",
              "Other_WZZ",
              "Other_ZZTo2L2Q",
              "Other_ZZTo2Q2Nu",
              "Other_ZZZ",
              "Other_TTTT",
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

    if year == "137fb": signal_samples=["VBFG_1000_MC2016", "VBFG_1000_MC2017","VBFG_1000_MC2018"]
    else:
        signal_samples=["VBFG_1000"];
    signal_labels = ["VBFG 1000 (1 pb)"]
    signal_labels1 = ["VBFG_1000_MC{0}".format(year)]

    if year=="2016": data_samples=["MET_2016B","MET_2016C","MET_2016D","MET_2016E","MET_2016F","MET_2016G","MET_2016H"]
    if year=="2017": data_samples=["MET_2017B","MET_2017C","MET_2017D","MET_2017E","MET_2017F"]
    if year=="2018": data_samples=["MET_2018A","MET_2018B","MET_2018C","MET_2018D"]
    if year=="137fb":data_samples=["MET_2016H","MET_2016G","MET_2016F","MET_2016E","MET_2016D","MET_2016C","MET_2016B",
                                   "MET_2017F","MET_2017E","MET_2017D","MET_2017C","MET_2017B",
                                   "MET_2018D","MET_2018C","MET_2018B","MET_2018A"]

    samples_labels = ["SnglT","TT","Other","WJets","ZJets"]
    samples_fill_color = [r.kOrange,r.kCyan,r.kOrange+3,r.kBlue,r.kGreen+1]
    samples_line_color = [1,1,1,1,1]
    signal_line_color = [2]
    
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
    for i,sig_names in enumerate(signal_samples) :
        #for j,sig_name in enumerate(sig_names):
        if len(signal_histo) <= i :
            signal_histo.append(input_file.Get(plot_var+"_"+sig_names))
            if signal_histo[-1]==None :
                print "looking for:",plot_var+"_"+sig_names
                print input_file.ls(plot_var+"_"+sig_names)
                assert(signal_histo[-1]!=None)
            elif signal_histo[-1].Integral() < 0.0001 :
                print "oops.",plot_var+"_"+sig_names,"is empty"
            signal_histo[-1].SetLineColor(signal_line_color[0])
            signal_histo[-1].SetLineWidth(2)
            signal_histo[-1].SetName(plot_var+"_"+signal_labels1[0])
        else :
            signal_histo[-1].Add(input_file.Get(plot_var+"_"+sig_names))

    if year == "137fb":
        total_sig = None
        for i,h in enumerate(signal_histo) :
            if h==None: continue
            if total_sig==None: total_sig = r.TH1F(h)
                #total_sig.SetName(plot_var+"_sum")
            else : total_sig.Add(h)


#    signal_histo=[]
#    for i,signal_sample_names in enumerate(signal_samples) :
#        #if i<len(signal_samples):
#        if i==0:
#            signal_histo.append(input_file.Get(plot_var+"_"+signal_sample_names))
#            signal_histo[-1].SetLineColor(r.kRed)
#            signal_histo[-1].SetLineWidth(2)
#            if signal_histo[-1]==None :
#                print "looking for:",plot_var+"_"+sample_name
#                assert(signal_histo[-1]!=None)
#        else :
#            signal_histo[-1].Add(input_file.Get(plot_var+"_"+signal_sample_names))

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
        else : total.Add(h)

    for i,h in enumerate(samples_histo) : stack.Add(h)

    # For legend
    leg = r.TLegend(0.45,.77,.9,.92) 
    leg.SetNColumns(4)
    leg.SetFillColor(0)
    leg.SetLineColor(r.kWhite)

    if data_histo: leg.AddEntry(data_histo[-1],"data","p") 
    for i in range(len(samples_histo)):
        leg.AddEntry(samples_histo[i],samples_labels[i],"f")
    leg.AddEntry(signal_histo[-1],signal_labels[0],"f")
    #for i in range(len(signal_histo)): leg.AddEntry(signal_histo[i],sig,"f")


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
    if year == "137fb": total_sig.Draw("histo SAME")
    #else: 
    #for i in range(len(signal_histo)): signal_histo[0].Draw("histo SAME")
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

    #Catext = r.TText(.17,.8,cat)
    #Catext.SetNDC()
    #Catext.SetTextFont(51)
    #Catext.SetTextSize(0.08)
    #Catext.Draw()

    CMStext = r.TText(.17,.95,"CMS")
    CMStext.SetNDC()
    CMStext.SetTextFont(61)
    CMStext.SetTextSize(0.08)
    CMStext.Draw()
    
    #SIMtext = r.TText(.28,.95,"preliminary")
    SIMtext = r.TText(.28,.95,"Work in Progress")
    SIMtext.SetNDC()
    SIMtext.SetTextFont(52)
    #SIMtext.SetTextSize(0.08)
    SIMtext.SetTextSize(0.06)
    SIMtext.Draw()
    
    LUMItext = r.TText(.60,.95,"13 TeV ({0})".format(lumi))
    #LUMItext = r.TText(.60,.95,"13 TeV (59.5/fb)")
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
    ratio.GetXaxis().SetNdivisions(505);
    # Draw a horizontal line at 1 in ratio plot
    nbins = ratio.GetNbinsX()
    l = r.TLine(ratio.GetBinLowEdge(1),1.0,ratio.GetBinLowEdge(nbins+1),1.0);
    l.SetLineColor(r.kRed);
    l.SetLineWidth(2);
    ratio.Draw() 
    l.Draw("same"); 
    

    can.SaveAs(plot_dir+"/"+plot_var+".pdf")

    # for space between legend and plot 
    topPad.SetLogy()
    if total!=None:
        stack.SetMaximum(200.0*max(total.GetMaximum(),data_histo[0].GetMaximum()))
    else :
        stack.SetMaximum(200.0*data_histo[0].GetMaximum())
    stack.SetMinimum(0.1)
    can.SaveAs(plot_dir+"/"+plot_var+"_LogY.pdf")

    output_file.cd()
    for h in samples_histo :
        r.TH1F(h).Write()
    data_histo[0].Write()
    total.Write()
    #if year == "137fb": total_sig.Write()
    #else: 
    for i in signal_histo : r.TH1F(i).Write()


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

print ""
print "Input file : {0}".format(input_file_name)
print "Output file: {0}".format(output_file_name)
print "plot dir   : {0}".format(plot_dir)
print ""

    
output_file.Close()
input_file.Close()