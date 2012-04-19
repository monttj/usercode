#include "TH2.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"

void dRIso(){

 TFile * file = new TFile("$WORK/data/export/common/Top/ntuple/ElEl/MC/Fall11_v1/vallot_TTbarTuneZ2.root"); 
 TTree * tree = (TTree*) file->Get("ElEl/tree");
 
 TH2F * h2DRIso1 = new TH2F("h2DRIso1","h2DRIso", 100, 0.0, 1.0, 100, 0.0, 1.0);
 TH2F * h2DRIso2 = new TH2F("h2DRIso2","h2DRIso", 100, 0.0, 1.0, 100, 0.0, 1.0);
 TH2F * h2DRIso3 = new TH2F("h2DRIso3","h2DRIso", 100, 0.0, 1.0, 100, 0.0, 1.0);

 TCut pre = "@jetspt30.size() >=2";

 tree->Project("h2DRIso1", "sqrt( (jetspt30[0].eta() - eta1)^2 + (jetspt30[0].phi() - phi1)^2 ):relIso1",pre);
 tree->Project("h2DRIso2", "sqrt( (jetspt30[1].eta() - eta1)^2 + (jetspt30[1].phi() - phi1)^2 ):relIso1",pre);
 tree->Project("h2DRIso3", "sqrt( (jetspt30[2].eta() - eta1)^2 + (jetspt30[2].phi() - phi1)^2 ):relIso1",pre);
 
 TCanvas * c1= new TCanvas("c1","c1",1); 
 h2DRIso1->GetXaxis()->SetTitle("Leading lepton Isolation");
 h2DRIso1->GetYaxis()->SetTitle("dR(lepton, leading jet) ");
 h2DRIso1->Draw("col");   

 TCanvas * c2= new TCanvas("c2","c2",1);
 h2DRIso2->GetXaxis()->SetTitle("Leading lepton Isolation");
 h2DRIso2->GetYaxis()->SetTitle("dR(lepton, second leading jet) ");
 h2DRIso2->Draw("col");

 TCanvas * c3= new TCanvas("c3","c3",1);
 h2DRIso3->GetXaxis()->SetTitle("Leading lepton Isolation");
 h2DRIso3->GetYaxis()->SetTitle("dR(lepton, third leading jet) ");
 h2DRIso3->Draw("col");

 c1->Print("h2DIso1ee.eps");
 c2->Print("h2DIso2ee.eps");
 c3->Print("h2DIso3ee.eps");


 // 1D plots
 TH1F* hDR1 = new TH1F("hDR1","hDR",100,0.0,1.0);
 TH1F* hDRIso1 = new TH1F("hDRIso1","hDR",100,0.0,1.0);
 TH1F* hDRLooseIso1 = new TH1F("hDRLooseIso1","hDR",100,0.0,1.0);
 TH1F* hDR2 = new TH1F("hDR2","hDR",100,0.0,1.0);
 TH1F* hDRIso2 = new TH1F("hDRIso2","hDR",100,0.0,1.0);
 TH1F* hDRLooseIso2 = new TH1F("hDRLooseIso2","hDR",100,0.0,1.0);

 tree->Project("hDR1","sqrt( (jetspt30[0].eta() - eta1)^2 + (jetspt30[0].phi() - phi1)^2 )",pre);
 tree->Project("hDRIso1","sqrt( (jetspt30[0].eta() - eta1)^2 + (jetspt30[0].phi() - phi1)^2 )","relIso1 < 0.2",pre);
 tree->Project("hDRLooseIso1","sqrt( (jetspt30[0].eta() - eta1)^2 + (jetspt30[0].phi() - phi1)^2 )","relIso1 < 0.3",pre);
 
 tree->Project("hDR2","sqrt( (jetspt30[1].eta() - eta1)^2 + (jetspt30[1].phi() - phi1)^2 )",pre);
 tree->Project("hDRIso2","sqrt( (jetspt30[1].eta() - eta1)^2 + (jetspt30[1].phi() - phi1)^2 )","relIso1 < 0.2",pre);
 tree->Project("hDRLooseIso2","sqrt( (jetspt30[1].eta() - eta1)^2 + (jetspt30[1].phi() - phi1)^2 )","relIso1 < 0.3",pre);

 //leading jet
 TCanvas * c1DR= new TCanvas("c1DR","c1DR",1);
 hDR1->Draw();

 TCanvas * c1DRIso= new TCanvas("c1DRIso","c1DRIso",1);
 hDRIso1->Draw();

 cout << "total = " << hDRIso1->GetEntries() << endl;
 cout << "fraction = " << hDRIso1->Integral(0,50) << endl;

 TCanvas * c1DRLooseIso= new TCanvas("c1DRLooseIso","c1DRIso",1);
 hDRLooseIso1->Draw();

 //second leading jet
 TCanvas * c2DR= new TCanvas("c2DR","c2DR",1);
 hDR2->Draw();

 TCanvas * c2DRIso= new TCanvas("c2DRIso","c2DRIso",1);
 hDRIso2->Draw();

 cout << "total = " << hDRIso2->GetEntries() << endl;
 cout << "fraction = " << hDRIso2->Integral(0,50) << endl;

 TCanvas * c2DRLooseIso= new TCanvas("c2DRLooseIso","c2DRIso",1);
 hDRLooseIso2->Draw();


 c1DR->Print("hDR1ee.eps");
 c1DRIso->Print("hDIso1ee.eps");
 c1DRLooseIso->Print("hDRLooseIso1ee.eps");

 c2DR->Print("hDR2ee.eps");
 c2DRIso->Print("hDIso2ee.eps");
 c2DRLooseIso->Print("hDRLooseIso2ee.eps");


}
