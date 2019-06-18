{

tree->Draw("Jets_neutralEmEnergyFraction*(abs(Jets.Eta())>2.6)*(abs(Jets.Eta())<3.0):Jets.Pt()*(abs(Jets.Eta())>2.6)*(abs(Jets.Eta())<3.0)>>test1(50,50,1050,50,0.01,1)", "MET>200 && JetsAK8[0].Pt()>200 && NMuons==0 && NElectrons ==0 && BTags==0 && PFCaloMETRatio<5. && globalSuperTightHalo2016Filter==1 && HBHENoiseFilter==1 && HBHEIsoNoiseFilter==1 && eeBadScFilter==1 && EcalDeadCellTriggerPrimitiveFilter==1 && BadChargedCandidateFilter==1 && BadPFMuonFilter ==1 && JetID ==1 && (TriggerPass[110] == 1 || TriggerPass[112] == 1 || TriggerPass[116] == 1 || TriggerPass[118] == 1 || TriggerPass[120] == 1 || TriggerPass[124] == 1 || TriggerPass[126] == 1 || TriggerPass[128] == 1 || TriggerPass[131] == 1 || TriggerPass[133] == 1 || TriggerPass[135] == 1 || TriggerPass[136] == 1)", "colz")

gStyle->SetOptStat(0)
c1->SetLogz(1)

test1->SetTitle("2016 F: 2.6<|#eta|<3.0")
test1->GetYaxis()->SetTitle("Neutral EMF")
test1->GetXaxis()->SetTitle("Jet p_{T}")
test1->GetYaxis()->SetLabelFont(43);
test1->GetYaxis()->SetLabelSize(24);
test1->GetYaxis()->SetTitleFont(43);
test1->GetYaxis()->SetTitleSize(24);
test1->GetYaxis()->SetTitleOffset(1.7);

test1->GetXaxis()->SetLabelFont(43);
test1->GetXaxis()->SetLabelSize(24);
test1->GetXaxis()->SetTitleFont(43);
test1->GetXaxis()->SetTitleSize(24);
test1->GetXaxis()->SetTitleOffset(1.7);

test1->Draw("colz")

gPad->SetLeftMargin(1.5)
gPad->SetBottomMargin(1.5)

TLine *l = new TLine(50,1.0,1050,0.1);
l->SetLineColor(kRed);
l->SetLineWidth(3);
l->Draw("same");


}
