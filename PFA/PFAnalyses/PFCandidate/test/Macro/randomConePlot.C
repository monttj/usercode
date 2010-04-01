#include <vector>
using namespace std;

void randomConePlot(){
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle(); 

  Chain * tree_data = new Chain("Summary/tree", "/tmp/tjkim/PFA/Apr1/RD/PFAnalysis_RD_4.root");
  Chain * tree_mc = new Chain("Summary/tree", "/tmp/tjkim/PFA/Apr1/MC/PFAnalysis_MC_6.root");

  TCut Endcap = "(RandomCones.Eta() > 1.479 || RandomCones.Eta() < -1.479)";
  TCut Barrel = "(RandomCones.Eta() < 1.479 && RandomCones.Eta() > -1.479)";
  TCut ThresholdForCH = "RandomCones.isoDeposit(4).second  > 0.4";
  TCut ThresholdForNeutral = "RandomCones.isoDeposit(5).second > 0.4";
  TCut ThresholdForPhoton = "RandomCones.isoDeposit(6).second > 0.4";
  TCut cut;

  plot(tree_data, tree_mc, "RandomCones.isoDeposit(4).first.deltaR", "charged_deltaR", "Charged Hadron R", "dN/dR", 50, 0, 0.5, cut, "pre", false);
  plot(tree_data, tree_mc, "RandomCones.isoDeposit(5).first.deltaR", "neutral_deltaR", "Neutral Hadron R", "dN/dR", 50, 0, 0.5, cut, "pre", false);
  plot(tree_data, tree_mc, "RandomCones.isoDeposit(6).first.deltaR", "photon_deltaR", "Photon R", "dN/dR", 50, 0, 0.5, cut, "pre", false);

}

void plot(TChain *tree_data, TChain *tree_mc, const TString &var, const TString& hName, const TString& xtitle, const TString& ytitle, int nbin, float xlow, float xmax, TCut cut, string name, bool print){

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

  tree_mc->Draw(Form("%s>>h_mc_%s_%s",var.Data(),hName.Data(),name),cut,"");
  tree_data->Draw(Form("%s>>h_data_%s_%s",var.Data(),hName.Data(),name),cut,"Esame");

  double num_data = tree_data->GetEntries();
  double num_mc = tree_mc->GetEntries();
  double scale = num_data/num_mc;

  double pivotal_mc = 0;
  double pivotal_data = 0;
  TH1 *h_mc_pt= new TH1F("h_mc_pt","h_mc_pt",40,0,4);
  TH1 *h_data_pt= new TH1F("h_data_pt","h_data_pt",40,0,4);
  tree_mc->Project("h_mc_pt","RandomCones.Pt()",cut);
  tree_data->Project("h_data_pt","RandomCones.Pt()",cut);
  pivotal_mc = h_mc_pt->GetEntries();
  pivotal_data = h_data_pt->GetEntries();
  h_mc_pt->Delete();
  h_data_pt->Delete();
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

  h_mc->SetMaximum(2.5); // 1.55

  l->AddEntry(h_data,"7 TeV Data","p");
  l->AddEntry(h_mc,"Simulation","F");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  
  if(print){ 
    c->Print(Form("c_%s_%s.pdf",hName.Data(),name));
    c->Print(Form("c_%s_%s.eps",hName.Data(),name));
    c->Print(Form("c_%s_%s.png",hName.Data(),name));
  }
}
