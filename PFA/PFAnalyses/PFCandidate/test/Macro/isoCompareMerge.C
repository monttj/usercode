#include <vector>
using namespace std;

void isoCompareMerge(){
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  Chain * tree_data = new Chain("Summary/tree", "/tmp/tjkim/Jan29/RD/pT/PFAnalysis_RD_*.root");
  Chain * tree_mc = new Chain("Summary/tree", "/tmp/tjkim/Jan29/MC/pT/PFAnalysis_MC_*.root");

  TCut cutEndcap = "(ChargedHadrons.Eta() > 1.0 || ChargedHadrons.Eta() < -1.0)";
  TCut cutBarrel = "(ChargedHadrons.Eta() < 1.0 && ChargedHadrons.Eta() > -1.0)";
  TCut cutHcal = "ChargedHadrons.hcal() > 0"; 
  TCut cutnhit = "ChargedHadrons.nHits() >= 3";
  TCut cutpTforCH = "ChargedHadrons.Pt() > 0.5";
  TCut cutpTforTrack = "Tracks.Pt() > 0.5";
  TCut cutThresholdForCH = "ChargedHadrons.isoDeposit(4).second  > 0.4";
  TCut cutThresholdForNeutral = "ChargedHadrons.isoDeposit(5).second > 0.4";
  TCut cutThresholdForPhoton = "ChargedHadrons.isoDeposit(6).second > 0.4";
  TCut cut; // = cutBarrel;

  vector<string> hName;
  hName.push_back("Charged_deposit_3");
  hName.push_back("Neutral_deposit_3");
  hName.push_back("Gamma_deposit_3");
  hName.push_back("Charged_deposit_5");
  hName.push_back("Neutral_deposit_5");
  hName.push_back("Gamma_deposit_5");
  hName.push_back("Charged_DeltaR");
  hName.push_back("Neutral_DeltaR");
  hName.push_back("Gamma_DeltaR");

  vector<string> var;
  var.push_back("ChargedHadrons.isoDeposit(4).depositWithin(0.3)");
  var.push_back("ChargedHadrons.isoDeposit(5).depositWithin(0.3)");
  var.push_back("ChargedHadrons.isoDeposit(6).depositWithin(0.3)");
  var.push_back("ChargedHadrons.isoDeposit(4).depositWithin(0.5)");
  var.push_back("ChargedHadrons.isoDeposit(5).depositWithin(0.5)");
  var.push_back("ChargedHadrons.isoDeposit(6).depositWithin(0.5)");
  var.push_back("ChargedHadrons.isoDeposit(4).first.deltaR");
  var.push_back("ChargedHadrons.isoDeposit(5).first.deltaR");
  var.push_back("ChargedHadrons.isoDeposit(6).first.deltaR");
 
 
  vector<string> title;
  title.push_back("Charged hadron #Sigma p_{T} [GeV/c]");
  title.push_back("Neutral hadron #Sigma p_{T} [GeV/c]");
  title.push_back("Photon #Sigma p_{T} [GeV]");
  title.push_back("Charged hadron #Sigma p_{T} [GeV/c]");
  title.push_back("Neutral hadron #Sigma p_{T} [GeV/c]");
  title.push_back("Photon #Sigma p_{T} [GeV]");
  title.push_back("Charged Hadron #Delta R");
  title.push_back("Neutral Hadron #Delta R");
  title.push_back("Photon #Delta R");
 

  vector<TH1*> h_data;
  vector<TH1*> h_mc;
  //Data
  h_data.push_back(new TH1D(Form("h_data_%s",hName[0]),"h_data",40,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[1]),"h_data",40,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[2]),"h_data",40,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[3]),"h_data",40,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[4]),"h_data",40,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[5]),"h_data",40,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[6]),"h_data",100,0,1));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[7]),"h_data",100,0,1));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[8]),"h_data",100,0,1));
  //MC 
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[0]),"h_mc",40,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[1]),"h_mc",40,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[2]),"h_mc",40,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[3]),"h_mc",40,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[4]),"h_mc",40,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[5]),"h_mc",40,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[6]),"h_mc",100,0,1));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[7]),"h_mc",100,0,1));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[8]),"h_mc",100,0,1));

  for(size_t t=0; t < h_data.size() ; t++){
    h_data[t]->Sumw2();
  }


  double num_data = tree_data->GetEntries();
  double num_mc = tree_mc->GetEntries();
  double scale = num_data/num_mc;

  plotMerge(tree_data, tree_mc, h_data[0], h_data[3],  h_mc[0], h_mc[3], var[0], var[3], hName[0], hName[3], title[0], cut, scale);
  plotMerge(tree_data, tree_mc, h_data[1], h_data[4],  h_mc[1], h_mc[4], var[1], var[4], hName[1], hName[4], title[1], cut, scale);
  plotMerge(tree_data, tree_mc, h_data[2], h_data[5],  h_mc[2], h_mc[5], var[2], var[5], hName[2], hName[5], title[2], cut, scale);
}

void plotMerge(TChain *tree_data, TChain *tree_mc, TH1* h_data1, TH1* h_data2, TH1* h_mc1, TH1* h_mc2, const TString &var1, const TString &var2, const TString& hName1, const TString& hName2,  const TString& title, TCut cut, const double& scale){

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName1.Data(), hName2.Data()),Form("c_%s_%s",hName1.Data(), hName2.Data()),1); 
  gPad->SetLogy();
  //gPad->SetGrid(1,1);

  tree_data->Draw(Form("%s>>h_data_%s",var1.Data(),hName1.Data()),cut,"E");
  tree_mc->Draw(Form("%s>>h_mc_%s",var1.Data(),hName1.Data()),cut,"same");
  tree_data->Draw(Form("%s>>h_data_%s",var2.Data(),hName2.Data()),cut,"sameE");
  tree_mc->Draw(Form("%s>>h_mc_%s",var2.Data(),hName2.Data()),cut,"same");
  double nentries_data1 = h_data1->Integral();
  double nentries_mc1 = h_mc1->Integral();
  double tempscale1 = nentries_data1/nentries_mc1;
 
  double nentries_data2 = h_data2->Integral();
  double nentries_mc2 = h_mc2->Integral();
  double tempscale2 = nentries_data2/nentries_mc2;

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.18,0.87,"CMS Preliminary");
  label->DrawLatex(0.18,0.82,"900 GeV minimum bias");
 
  h_data1->SetMarkerSize(1);
  h_data1->SetMarkerStyle(8);
  h_data1->SetStats(0);
  h_data1->SetTitle(0);
  h_data1->GetXaxis()->SetTitle(title.Data());
  h_data1->GetYaxis()->SetTitle("Entries");
  h_data1->Scale(1/h_data1->GetBinWidth(1)/nentries_data1);
  h_mc1->SetLineColor(4);
  h_mc1->SetLineWidth(2);
  h_mc1->Scale(tempscale1*1/h_data1->GetBinWidth(1)/nentries_data1);

  h_data2->SetMarkerSize(1);
  h_data2->SetMarkerStyle(24);
  h_data2->Scale(1/h_data2->GetBinWidth(1)/nentries_data2);
  h_mc2->SetLineColor(2);
  h_mc2->SetLineWidth(2);
  h_mc2->Scale(tempscale2*1/h_data2->GetBinWidth(1)/nentries_data2);

  TLegend *l= new TLegend(0.60,0.54,0.92,0.77);
  l->AddEntry(h_data2,"Data #DeltaR=0.3","p");
  l->AddEntry(h_mc2,"MC #DeltaR=0.5","l");
  l->AddEntry(h_data1,"Data #DeltaR=0.5","p");
  l->AddEntry(h_mc1,"MC #DeltaR=0.3","l");
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
 
  c->Print(Form("Merge/c_%s_%s.pdf",hName1.Data(),hName2.Data()));
  c->Print(Form("Merge/c_%s_%s.eps",hName1.Data(),hName2.Data()));
   
}
