#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TString.h"
#include <iostream>

using namespace std;

TH1F* getTruthCrossSection(TH1F * h, double x){

  TH1F* out = (TH1F*)h->Clone("out");
  for(int i=1; i <= h->GetNbinsX(); i++){
    double dsigma = x * h->GetBinContent(i) / ( h->GetBinWidth(i) * h->Integral() );
    double normalized = dsigma / x;
    out->SetBinContent(i,normalized);
  }
  return out;

}

void mttPlot(){

  //TFile * file_TJ = new TFile("crab/results_TTJets_2/vallot_topdecay.root");
  TFile * file_TJ = new TFile("crab/new/files/newTTJetsApr15/vallot_topdecay.root");
  TFile * file = new TFile("$WORK/data/export/common/Top/ntuple/Gen/hist/Fall11/v0/hist_madgraph.root");

  TH1F * hmTT_Full = (TH1F*) file->Get("all/hmTT_Full");
  TH1F * hmTT_Pton = (TH1F*) file->Get("all/hmTT_Pton");
  TH1F * hmTT_Ptcl = (TH1F*) file->Get("all/hmTT_Ptcl");
  TH1F * hmLLBBMet_Ptcl = (TH1F*) file->Get("all/hmLLBBMet_Ptcl");
  TH1F * hmLLJJMet_Ptcl = (TH1F*) file->Get("all/hmLLJJMet_Ptcl");

  TH1F * hMtt_Full = (TH1F*) file_TJ->Get("topDecayGenHisto/hMtt_Full");
  TH1F * hMtt_DIL_Pton = (TH1F*) file_TJ->Get("topDecayGenHisto/hMtt_DIL_Pton");
  TH1F * hMtt_DIL_Ptcl = (TH1F*) file_TJ->Get("topDecayGenHisto/hMtt_DIL_Ptcl");
  TH1F * hMtt_LPJ_Pton = (TH1F*) file_TJ->Get("topDecayGenHisto/hMtt_LPJ_Pton");

  hmTT_Full->Rebin(10);
  hmTT_Pton->Rebin(10);
  hmTT_Ptcl->Rebin(10);
  hmLLBBMet_Ptcl->Rebin(10);
  hmLLJJMet_Ptcl->Rebin(10); 

  hMtt_Full->Rebin(10);
  hMtt_DIL_Pton->Rebin(10); 
  hMtt_DIL_Ptcl->Rebin(10); 
  hMtt_LPJ_Pton->Rebin(10); 

  hmTT_Full =  getTruthCrossSection( hmTT_Full, 165);
  hmTT_Pton =  getTruthCrossSection( hmTT_Pton, 165);
  hmTT_Ptcl =  getTruthCrossSection( hmTT_Ptcl, 165);
  hmLLBBMet_Ptcl =  getTruthCrossSection( hmLLBBMet_Ptcl, 165);
  hmLLJJMet_Ptcl =  getTruthCrossSection( hmLLJJMet_Ptcl, 165);

  //hMtt_Full =  getTruthCrossSection( hMtt_Full, 165);
  //hMtt_DIL_Pton =  getTruthCrossSection( hMtt_DIL_Pton, 165); 
  //hMtt_DIL_Ptcl =  getTruthCrossSection( hMtt_DIL_Ptcl, 165); 
  //hMtt_LPJ_Pton =  getTruthCrossSection( hMtt_LPJ_Pton, 165); 

  TCanvas * c= new TCanvas("c","c",1);
  c->SetLogy();

  hMtt_DIL_Pton->SetTitle("");
  hMtt_DIL_Pton->SetStats(0);
  //hMtt_DIL_Pton->SetMinimum(0.00001);
  hMtt_DIL_Pton->SetAxisRange(200,2000,"X");
  //hMtt_DIL_Pton->SetAxisRange(200,1400,"X");
  hMtt_DIL_Pton->GetXaxis()->SetTitle("M_{t#bar{t}} (GeV)");
  //hMtt_DIL_Pton->GetYaxis()->SetTitle("1/#sigma d#sigma/dM");
  hMtt_DIL_Pton->GetYaxis()->SetTitle("Entries");

  //hmTT_Full->Draw();
  //hmTT_Pton->Draw("same");
  //hmTT_Ptcl->Draw("same");
  //hmLLBBMet_Ptcl->Draw("same");
  //hmLLJJMet_Ptcl->Draw("same");

  //hmTT_Full->Rebin(2);
  //hmTT_Pton->Rebin(2);
  //hmTT_Ptcl->Rebin(2);
  //hmLLBBMet_Ptcl->Rebin(2);
  //hmLLJJMet_Ptcl->Rebin(2);

  //hmTT_Full->SetLineColor(2);
  hmTT_Pton->SetLineColor(3);
  hmTT_Ptcl->SetLineColor(4);
  hmLLBBMet_Ptcl->SetLineColor(7);
  hmLLJJMet_Ptcl->SetLineColor(6);

  hMtt_Full->SetLineColor(2);
  hMtt_Full->SetLineWidth(2);
  hMtt_DIL_Pton->SetLineColor(3);
  hMtt_DIL_Pton->SetLineWidth(2);

  hMtt_DIL_Ptcl->SetLineColor(4);
  hMtt_DIL_Ptcl->SetLineWidth(2);

  //hMtt_LPJ_Pton->SetLineColor(4);
  //hMtt_LPJ_Pton->SetLineWidth(2);

  //hMtt_Full->Draw();
  hMtt_DIL_Pton->Draw();
  hMtt_DIL_Ptcl->Draw("same");
  //hMtt_LPJ_Pton->Draw("same");

  TLegend *l = new TLegend(0.55,0.68,0.92,0.88);
  //l->AddEntry(hmTT_Full,"Full phase space","L");
  //l->AddEntry(hmTT_Pton,"M_{t#bar{t}} w. parton cut","L");
  //l->AddEntry(hmTT_Ptcl,"M_{t#bar{t}} w. particle cut","L");
  //l->AddEntry(hmLLBBMet_Ptcl,"2l+2b+met with particle cut","L");
  //l->AddEntry(hmLLJJMet_Ptcl,"2l+2j+met","L");
  //l->AddEntry(hMtt_Full,"M_{t#bar{t}} Full","L");
  l->AddEntry(hMtt_DIL_Pton,"M_{t#bar{t}} DIL parton","L");
  l->AddEntry(hMtt_DIL_Ptcl,"M_{t#bar{t}} DIL particle","L");
  //l->AddEntry(hMtt_LPJ_Pton,"M_{t#bar{t}} LPJ visible","L");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print("mttbar.pdf"); 
}


