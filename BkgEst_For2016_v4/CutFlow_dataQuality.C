{
gROOT->Reset();

TFile* f1 = new TFile("ZSRHPVBF_515_v4_2016_Output.root");
TFile* f2 = new TFile("ZSRHPVBF_515_v4_2016_pt30GeV_Output.root");

//TH1F* h2018A = (TH1F*)f1->Get("AK4j1pt_ZNoSelection_MET_2018A");
TH1F* h1B = (TH1F*)f1->Get("ZMT2_ZSRHPVBF_ZJets");
TH1F* h2B = (TH1F*)f1->Get("ZMT2_ZSRHPVBF_WJets");
TH1F* h3B = (TH1F*)f1->Get("ZMT2_ZSRHPVBF_Other");
TH1F* h4B = (TH1F*)f1->Get("ZMT2_ZSRHPVBF_TT");
TH1F* h5B = (TH1F*)f1->Get("ZMT2_ZSRHPVBF_Single top");

TH1F* h1A = (TH1F*)f2->Get("ZMT2_ZSRHPVBF_ZJets");
TH1F* h2A = (TH1F*)f2->Get("ZMT2_ZSRHPVBF_WJets");
TH1F* h3A = (TH1F*)f2->Get("ZMT2_ZSRHPVBF_Other");
TH1F* h4A = (TH1F*)f2->Get("ZMT2_ZSRHPVBF_TT");
TH1F* h5A = (TH1F*)f2->Get("ZMT2_ZSRHPVBF_Single top");

TH1F* hpt50 = (TH1F*)h1B->Clone("hpt50");
TH1F* hpt30 = (TH1F*)h1A->Clone("hpt30");

hpt50->Add(h2B);
hpt50->Add(h3B);
hpt50->Add(h4B);
hpt50->Add(h5B);

hpt30->Add(h2A);
hpt30->Add(h3A);
hpt30->Add(h4A);
hpt30->Add(h5A);


cout<<endl;
cout<<"-------------Total Bkg: with pt cut of 50 GeV-------------------"<<endl; 
//cout<<"---------------------------------------------"<<endl; 
cout<<"     Before reverting the pt cut to 30 GeV"<<endl; 
cout<<"     "<<hpt50->Integral()<<endl;
cout<<"--------------------------------------------------"<<endl; 
cout<<endl;

cout<<"-------------Total Bkg: After reverting the Cut-------------------"<<endl; 
//cout<<"---------------------------------------------"<<endl; 
cout<<"     After reverting the pt cut to 30 GeV"<<endl; 
cout<<"     "<<hpt30->Integral()<<endl;
cout<<"--------------------------------------------------"<<endl; 
cout<<endl;

cout<<"------------- % loss --------------------"<<endl; 
//cout<<"---------------------------------------------"<<endl; 
cout<<"     before to after "<<endl; 
cout<<"     "<<((hpt50->Integral()-hpt30->Integral())/hpt50->Integral())*100<<endl;
cout<<"-----------------------------------------------------------"<<endl; 
cout<<endl;
}

