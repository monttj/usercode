#include <vector>
using namespace std;
reco::IsoDeposit::Vetos dVetos;

void muonIso(){
  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("../../tdrstyle.C");
  setTDRStyle();

  //Chain * tree1 = new Chain("Summary/tree", "/tmp/tjkim/PFA/MCv4/PFAnalysis_MuonIso_*.root");
  Chain * tree1 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");
  Chain * tree2 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");

  cout << "tree1 = " << tree1->GetEntries() << endl;
  cout << "tree2 = " << tree2->GetEntries() << endl;

  TCut cut1 = "random_eta > -2.1 && random_eta < 2.1";
  TCut cut2 = "muon_eta > -2.1 && muon_eta < 2.1";

  vector<string> hName;
  hName.push_back("Charged_deposit_4");
  hName.push_back("Neutral_deposit_4");
  hName.push_back("Gamma_deposit_4");

  vector<string> title;
  title.push_back("Charged hadron #Sigma p_{T} [GeV/c]");
  title.push_back("Neutral hadron #Sigma p_{T} [GeV/c]");
  title.push_back("Photon #Sigma p_{T} [GeV]");
 
  plot( tree1, tree2, "random_chIso", "muon_chIso", hName[0], title[0], 40, 0, 4, cut1, cut2, "CH", true);
  plot( tree1, tree2, "random_nhIso", "muon_nhIso", hName[1], title[1], 40, 0, 4, cut1, cut2, "NH", true);
  plot( tree1, tree2, "random_ph_iso2", "muon_ph_iso2", hName[2], title[2], 40, 0, 4, cut1, cut2, "PH", true);
}

void plot(TChain *tree1, TChain *tree2, const TString &var1, const TString &var2, const TString& hName,  const TString& title, int nbin, double xlow, double xmax,  TCut cut1, TCut cut2, const TString& name, bool print){

  TString leg1 = "random cone W MC";
  TString leg2 = "muon iso. W MC";

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1); 
  gPad->SetLogy();
  //gPad->SetGrid(1,1);

  tree2->Draw(Form("%s>>h_2_%s_%s",var2.Data(),hName.Data(),name.Data()),cut2,"");
  tree1->Draw(Form("%s>>h_1_%s_%s",var1.Data(),hName.Data(),name.Data()),cut1,"same");

  cout << "1 n. of object = " << h_1->GetEntries() << endl;   
  cout << "2 n. of object = " << h_2->GetEntries() << endl;   

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.18,0.87,"  #sqrt{s} =7 TeV");
  label->DrawLatex(0.18,0.82,"  #DeltaR = 0.4");
 
  h_2->SetStats(0);
  h_2->SetTitle(0);
  h_2->GetXaxis()->SetTitle(title.Data());
  h_2->GetYaxis()->SetTitle("Probability");
  h_2->SetMaximum(1.2);
  h_2->SetMinimum(0.0001);

  h_1->SetLineWidth(2);
  h_1->SetLineColor(4);
  h_1->Scale(1/h_1->GetEntries());

  h_2->SetLineWidth(2);
  h_2->SetLineColor(2);
  h_2->Scale(1/h_2->GetEntries());

  TLegend *l= new TLegend(0.40,0.57,0.92,0.80);
  l->AddEntry(h_1,Form("%s",leg1.Data()),"l");
  l->AddEntry(h_2,Form("%s",leg2.Data()),"l");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  if(print){ 
    c->Print(Form("c_%s_%s_Jun1.pdf",hName.Data(),name.Data()));
    c->Print(Form("c_%s_%s_Jun1.png",hName.Data(),name.Data()));
    c->Print(Form("c_%s_%s_Jun1.eps",hName.Data(),name.Data()));
  }
 
  TCanvas* c_eff = new TCanvas(Form("c_eff_%s_%s",hName.Data(), name.Data()),Form("c_eff_%s_%s",hName.Data(), name.Data()),1);

  TGraphAsymmErrors *eff_mc1 = new TGraphAsymmErrors();
  TGraphAsymmErrors *eff_mc2 = new TGraphAsymmErrors();

  for(int i=1 ; i <= nbin ;i++ ){
    eff_mc1->SetPoint(i-1, h_1->GetBinCenter(i), h_1->Integral(1,i));
    eff_mc2->SetPoint(i-1, h_2->GetBinCenter(i), h_2->Integral(1,i));
  }

  TH1D *h = new TH1D(Form("h_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  h->SetMinimum(0);  
  h->SetMaximum(1.05);
  h->SetTitle("");
  h->SetStats(0);
  h->GetXaxis()->SetTitle(title.Data());
  h->GetYaxis()->SetTitle("Efficiency");
  h->Draw();

  eff_mc1->SetMarkerStyle(20);
  eff_mc1->SetMarkerSize(1.2);
  eff_mc1->SetMarkerColor(4);
  eff_mc1->Draw("PSame");

  eff_mc2->SetMarkerStyle(20);
  eff_mc2->SetMarkerSize(1.2);
  eff_mc2->SetMarkerColor(2);
  eff_mc2->Draw("PSame");

  TLegend *l= new TLegend(0.40,0.37,0.92,0.60);
  l->AddEntry(eff_mc1,Form("%s",leg1.Data()),"p");
  l->AddEntry(eff_mc2,Form("%s",leg2.Data()),"p");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  if(print){
    c_eff->Print(Form("c_eff_%s_%s_Jun1.pdf",hName.Data(),name.Data()));
    c_eff->Print(Form("c_eff_%s_%s_Jun1.png",hName.Data(),name.Data()));
    c_eff->Print(Form("c_eff_%s_%s_Jun1.eps",hName.Data(),name.Data()));
  }

}

