{
gROOT->Reset();

TFile* f1 = new TFile("plotObs_ZNoSelection_baseline_MET_2018A.root");
TFile* f2 = new TFile("plotObs_ZNoSelection_baseline_MET_2018B.root");
TFile* f3 = new TFile("plotObs_ZNoSelection_baseline_MET_2018C.root");
TFile* f4 = new TFile("plotObs_ZNoSelection_baseline_MET_2018D.root");
TFile* f5 = new TFile("plotObs_ZNoSelection_baseline_VBFG_1200.root");

TH1F* h2018A = (TH1F*)f1->Get("NVtx_ZNoSelection_MET_2018A");
TH1F* h2018B = (TH1F*)f2->Get("NVtx_ZNoSelection_MET_2018B");
TH1F* h2018C = (TH1F*)f3->Get("NVtx_ZNoSelection_MET_2018C");
TH1F* h2018D = (TH1F*)f4->Get("NVtx_ZNoSelection_MET_2018D");
TH1F* hVBFG = (TH1F*)f5->Get("NVtx_ZNoSelection_VBFG_1200");

cout<<"-------------Before HTRatio Cut--------------"<<endl; 
//cout<<"---------------------------------------------"<<endl; 
cout<<"-----2018A-----2018B-----2018C-----2018D-----VBF G"<<endl; 
cout<<"     "<<h2018A->Integral()<<"     "<<h2018B->Integral()<<"     "<<h2018C->Integral()<<"     "<<h2018D->Integral()<<"   "<<hVBFG->Integral()<<endl;
cout<<"------------------------------------------------"<<endl; 


}

