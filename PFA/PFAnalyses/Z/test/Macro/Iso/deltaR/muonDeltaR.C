#include <vector>
using namespace std;

void muonDeltaR(){
  gROOT->LoadMacro("../../tdrstyle.C");
  setTDRStyle(); 

  //Chain * tree_data = new Chain("Summary/tree", "/tmp/tjkim/PFA/MCv5/PFAnalysis_MuonIso_*.root");
  Chain * tree_data = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv10/PFAnalysis_MuonIso_*.root");
  Chain * tree_mc = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv10/PFAnalysis_MuonIso_*.root");
  TCut cutjet;// = "random_ch_jetpT > 8";
  TCut cutRD4 = "random_ch_th > 0.7";
  TCut cutRD5 = "random_nh_th > 0.7";
  TCut cutRD6 = "random_ph_th > 0.7";// && random_ph_dR >= 0.2";// && TMath::Abs(ran_ph_deta) >= 0.07";// && random_ph_dR >= 0.2";
  TCut cutMC4 = "muon_ch_th  > 0.7 && TMath::Abs(muon_ch_eta) < 2.1 ";
  TCut cutMC5 = "muon_nh_th > 0.7 && TMath::Abs(muon_nh_eta) < 2.1 ";
  TCut cutMC6=  "muon_ph_th > 0.7 && TMath::Abs(muon_ph_eta) < 2.1 ";//&& muon_ph_dR >= 0.2";// && TMath::Abs(mu_ph_deta) >= 0.07";// && muon_ph_dR >= 0.2";//TMath::Abs(mu_ph_deta) >= 0.07";// && muon_ph_dR >= 0.2";

  bool printplot = true;
  plot(tree_data, tree_mc, "random_ch_dR", "muon_ch_dR", "charged_deltaR", "R", "Charged Hadrons dN/dR", 50, 0, 0.5, cutRD4, cutMC4, cutjet, "pre", printplot);
  plot(tree_data, tree_mc, "random_nh_dR", "muon_nh_dR", "neutral_deltaR", "R", "Neutral Hadrons dN/dR", 50, 0, 0.5, cutRD5, cutMC5, cutjet,"pre", printplot);
  plot(tree_data, tree_mc, "random_ph_dR", "muon_ph_dR", "photon_deltaR", "R", " Photons dN/dR", 50, 0, 0.5, cutRD6, cutMC6, cutjet, "pre", printplot);

}

void plot(TChain *tree_data, TChain *tree_mc, const TString &varRD, const TString &varMC, const TString& hName, const TString& xtitle, const TString& ytitle, int nbin, float xlow, float xmax, TCut cutRD, TCut cutMC, TCut cutjet, string name, bool print){

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(),name),Form("c_%s_%s",hName.Data(),name),1); 
  TLegend *l;

  if(hName.Contains("deposit") || hName.Contains("pT")){ 
    gPad->SetLogy();
    l = new TLegend(0.68,0.78,0.90,0.90);
  }else{
    l = new TLegend(0.18,0.67,0.42,0.82);
  }
  //gPad->SetGrid(1,1);
  
  TH1 *h_data = new TH1D(Form("h_data_%s_%s",hName.Data(),name),"h_data",nbin,xlow,xmax);
  TH1 *h_mc = new TH1D(Form("h_mc_%s_%s",hName.Data(),name),"h_mc",nbin,xlow,xmax);
  h_data->Sumw2();

  tree_mc->Draw(Form("%s>>h_mc_%s_%s",varMC.Data(),hName.Data(),name),cutMC,"");
  tree_data->Draw(Form("%s>>h_data_%s_%s",varRD.Data(),hName.Data(),name),cutRD && cutjet,"Esame");

  double num_data = tree_data->GetEntries();
  double num_mc = tree_mc->GetEntries();
  double scale = num_data/num_mc;

  double pivotal_mc = 0;
  double pivotal_data = 0;
  TH1 *h_mc_eta= new TH1F("h_mc_eta","h_mc_eta",60,-3,3);
  TH1 *h_data_eta= new TH1F("h_data_eta","h_data_eta",60,-3,3);
  tree_mc->Project("h_mc_eta","muon_eta","muon_eta < 2.1 && muon_eta > -2.1");
  tree_data->Project("h_data_eta","random_eta",cutjet);
  pivotal_mc = h_mc_eta->GetEntries();
  pivotal_data = h_data_eta->GetEntries();
  h_mc_eta->Delete();
  h_data_eta->Delete();
  cout << "Data= " << num_data << endl;
  cout << "MC= " << num_mc << endl;
  cout << "CH pivotal data= " << pivotal_data << endl;
  cout << "CH pivotal mc= " << pivotal_mc << endl;

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.18,0.87,"CMS Preliminary 2010");

  h_data->SetMarkerStyle(kFullCircle);
  h_data->SetMarkerSize(0.8);//1
  h_data->SetMarkerStyle(8);
  h_data->SetStats(0);
  h_data->GetXaxis()->SetTitle(xtitle.Data());
  h_data->GetYaxis()->SetTitle(ytitle.Data());

  h_mc->SetLineColor(2);
  h_mc->SetLineWidth(2);
  h_mc->SetFillStyle(1001);
  h_mc->SetFillColor(kRed-8);
  h_mc->SetStats(0);
  h_mc->GetXaxis()->SetTitle(xtitle.Data());
  h_mc->GetYaxis()->SetTitle(ytitle.Data());

  h_data->Scale(1/pivotal_data/h_data->GetBinWidth(1));
  h_mc->Scale(1/pivotal_mc/h_mc->GetBinWidth(1));

  h_mc->SetMaximum(4); // 2.5

  //l->AddEntry(h_data,"random cone for MinBias","p");
  l->AddEntry(h_data,"random cone for W #rightarrow #mu#nu","p");
  l->AddEntry(h_mc,"muon for W #rightarrow #mu#nu","F");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  
  if(print){ 
    c->Print(Form("c_%s_%s_Jun1.pdf",hName.Data(),name));
    c->Print(Form("c_%s_%s_Jun1.eps",hName.Data(),name));
    c->Print(Form("c_%s_%s_Jun1.png",hName.Data(),name));
  }
}
