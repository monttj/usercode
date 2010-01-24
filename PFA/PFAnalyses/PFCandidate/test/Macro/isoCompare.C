#include <vector>
using namespace std;

void isoCompare(){

  Chain * tree_data = new Chain("Summary/tree", "../../PFAnalysis_RD_Jan22.root");
  Chain * tree_mc = new Chain("Summary/tree", "../../PFAnalysis_MC_Jan22.root");
  //Chain * tree_mc = new Chain("Summary/tree", "../../PFAnalysis_RD_VeryClean_v341.root");

  TCut cutEndcap = "(ChargedHadrons.Eta() > 1.0 || ChargedHadrons.Eta() < -1.0)";
  TCut cutBarrel = "(ChargedHadrons.Eta() < 1.0 && ChargedHadrons.Eta() > -1.0)";
  TCut cutHcal = "ChargedHadrons.hcal() > 0"; 
  TCut cutnhit = "ChargedHadrons.nHits() >= 3";
  TCut cutpT = "ChargedHadrons.Pt() > 1";
  TCut cut = cutnhit;

  vector<string> hName;
  hName.push_back("Charged deposit");
  hName.push_back("Neutral deposit");
  hName.push_back("Gamma deposit");
  hName.push_back("Charged #Delta R");
  hName.push_back("Neutral #Delta R");
  hName.push_back("Gamma #Delta R");
  hName.push_back("Multiplicity");
  hName.push_back("pT");
  hName.push_back("eta");
  hName.push_back("track_Multiplicity");
  hName.push_back("track_pT");
  hName.push_back("track_eta");


  vector<string> var;
  var.push_back("ChargedHadrons.isoDeposit(4).depositWithin(0.3)");
  var.push_back("ChargedHadrons.isoDeposit(5).depositWithin(0.3)");
  var.push_back("ChargedHadrons.isoDeposit(6).depositWithin(0.3)");
  var.push_back("ChargedHadrons.isoDeposit(4).first.deltaR");
  var.push_back("ChargedHadrons.isoDeposit(5).first.deltaR");
  var.push_back("ChargedHadrons.isoDeposit(6).first.deltaR");
  var.push_back("@ChargedHadrons.size()");
  var.push_back("ChargedHadrons.Pt()");
  var.push_back("ChargedHadrons.Eta()");
  var.push_back("@Tracks.size()");
  var.push_back("Tracks.Pt()");
  var.push_back("Tracks.Eta()");
 
 
  vector<string> title;
  title.push_back("Charged Hadron #Sigma E within cone (GeV)");
  title.push_back("Neutral Hadron #Sigma E within cone (GeV)");
  title.push_back("Photon #Sigma E within cone (GeV)");
  title.push_back("Charged Hadron #Delta R");
  title.push_back("Neutral Hadron #Delta R");
  title.push_back("Photon #Delta R");
  title.push_back("Multiplicity");
  title.push_back("Transverse momentum (GeV)");
  title.push_back("Pseudorapidity #eta");
  title.push_back("track_Multiplicity");
  title.push_back("track_Transverse momentum (GeV)");
  title.push_back("track_Pseudorapidity #eta");
 

  vector<TH1*> h_data;
  vector<TH1*> h_mc;
  //Data
  h_data.push_back(new TH1D(Form("h_data_%s",hName[0]),"h_data",80,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[1]),"h_data",80,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[2]),"h_data",80,0,4));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[3]),"h_data",100,0,1));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[4]),"h_data",100,0,1));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[5]),"h_data",100,0,1));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[6]),"h_data",80,0,80));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[7]),"h_data",100,0,10));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[8]),"h_data",30,-3,3));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[9]),"h_data",80,0,80));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[10]),"h_data",100,0,10));
  h_data.push_back(new TH1D(Form("h_data_%s",hName[11]),"h_data",30,-3,3));

  //MC 
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[0]),"h_mc",80,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[1]),"h_mc",80,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[2]),"h_mc",80,0,4));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[3]),"h_mc",100,0,1));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[4]),"h_mc",100,0,1));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[5]),"h_mc",100,0,1));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[6]),"h_mc",80,0,80));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[7]),"h_mc",100,0,10));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[8]),"h_mc",30,-3,3));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[9]),"h_mc",80,0,80));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[10]),"h_mc",100,0,10));
  h_mc.push_back(new TH1D(Form("h_mc_%s",hName[11]),"h_mc",30,-3,3));


  double num_data = tree_data->GetEntries();
  double num_mc = tree_mc->GetEntries();
  double scale = num_data/num_mc;

  for(int i=0; i < hName.size() ; i++){
    plot(tree_data, tree_mc, h_data[i], h_mc[i], var[i], hName[i], title[i], cut, scale);
  }
}

void plot(TChain *tree_data, TChain *tree_mc, TH1* h_data, TH1* h_mc, const TString &var, const TString& hName, const TString& title, TCut cut, const double& scale){

  TCanvas* c = new TCanvas(Form("c_%s",hName.Data()),Form("c_%s",hName.Data()),1); 
  if(hName == "Charged deposit" || hName == "Neutral deposit" || hName == "Gamma deposit" ) gPad->SetLogy();

  tree_data->Draw(Form("%s>>h_data_%s",var.Data(),hName.Data()),cut,"E");
  tree_mc->Draw(Form("%s>>h_mc_%s",var.Data(),hName.Data()),cut,"same");

  h_data->SetMarkerStyle(kFullCircle);
  h_data->SetMarkerSize(0.5);
  h_data->SetStats(0);
  h_data->SetTitle(0);
  h_data->GetXaxis()->SetTitle(title.Data());
  h_data->SetTitle(hName.Data());
  h_mc->SetLineColor(2);
  h_mc->Scale(scale);

  TLegend *l= new TLegend(0.65,0.75,0.89,0.89);
  l->AddEntry(h_data,"Data","p");
  l->AddEntry(h_mc,"MC","l");
  l->SetFillColor(0);
  l->Draw();
 
  //c->Print(Form("c_%s.gif",hName.Data()));
  //c->Print(Form("c_%s.C",hName.Data()));
   
}
