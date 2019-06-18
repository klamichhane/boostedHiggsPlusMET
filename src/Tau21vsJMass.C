#include <cassert>
#include <cmath>

#include "TH1.h"
#include "TH2.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TRandom.h"

TCanvas* Tau21vsJMass()
{
   TFile* f_1 = new TFile("plotObs_ZNoSelection_baseline_VBFG_1000.root");
   //TH2F *h1   = (TH2F*)f_1->Get("Tau21vsJMass_ZNoSelection_VBFG_1000");
   TH2F *h1   = (TH2F*)f_1->Get("Tau21vsJMass_ZNoSelection_VBFG_1000");
   TCanvas* c = new TCanvas;
   c->SetRightMargin(0.2);
   c->SetLeftMargin(0.2);
   c->SetBottomMargin(0.2);

   //h1->Add(h2);
   //h1->Add(h3);
   //h1->Add(h4);
   // h1 properties for first canvas:
   h1->GetXaxis()->SetTitle("AK8 L1J Mass [GeV]");
   h1->GetYaxis()->SetTitle("#tau_{21}");
   h1->GetYaxis()->SetTitleOffset(0.8);
   h1->SetTitle("Tau21 vs J Mass");
   h1->Draw("colz");
   gPad->Update();
   //c->Print("J_NemfvsEta_MET2017F_before.pdf");
   return c;
}
