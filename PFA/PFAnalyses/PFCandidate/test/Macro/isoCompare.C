void isoCompare(){

  Chain * tree_data = new Chain("Summary/tree", "../../PFAnalysis_RD_VeryClean.root");
  Chain * tree_mc = new Chain("Summary/tree", "../../PFAnalysis_MC_Dec6.root");

  TCut cutEndcap = "(ChargedHadrons.Eta() > 1.0 || ChargedHadrons.Eta() < -1.0)";
  TCut cutBarrel = "(ChargedHadrons.Eta() < 1.0 && ChargedHadrons.Eta() > -1.0)";
  TCut cutHcal = "ChargedHadrons.hcal() > 0"; 
  TCut cutnhit = "ChargedHadrons.nHits() >= 3";
  TCut cut= cutnhit;

  vector<string> hName;
  hName.push_back("Charged");
  hName.push_back("Neutral");
  hName.push_back("Gamma");
  hName.push_back("Multiplicity");
  hName.push_back("pT");
  hName.push_back("eta");

  vector<string> var;
  var.push_back("ChargedHadrons.isoDeposit(4).depositWithin(0.5)");
  var.push_back("ChargedHadrons.isoDeposit(5).depositWithin(0.5)");
  var.push_back("ChargedHadrons.isoDeposit(6).depositWithin(0.5)");
  var.push_back("@ChargedHadrons.size()");
  var.push_back("ChargedHadrons.Pt()");
  var.push_back("ChargedHadrons.Eta()");
  
  vector<string> title;
  title.push_back("Energy deposit within cone (GeV)");
  title.push_back("Energy deposit within cone (GeV)");
  title.push_back("Energy deposit within cone (GeV)");
  title.push_back("Multiplicity");
  title.push_back("Transverse momentum (GeV)");
  title.push_back("Pseudorapidity #eta");

  TH1* h_data[6];
  TH1* h_mc[6];

  for(int i=0; i< 3 ; i++){
      h_data[i]= new TH1D(Form("h_data_%s",hName[i]),"h_data",80,0,4);
      h_mc[i] =new TH1D(Form("h_mc_%s",hName[i]),"h_mc",80,0,4);
  }
  h_data[3]= new TH1D(Form("h_data_%s",hName[3]),"h_data",80,0,80);
  h_mc[3] =new TH1D(Form("h_mc_%s",hName[3]),"h_mc",80,0,80);
  h_data[4]= new TH1D(Form("h_data_%s",hName[4]),"h_data",100,0,10);
  h_mc[4] =new TH1D(Form("h_mc_%s",hName[4]),"h_mc",100,0,10);
  h_data[5]= new TH1D(Form("h_data_%s",hName[5]),"h_data",30,-3,3);
  h_mc[5] =new TH1D(Form("h_mc_%s",hName[5]),"h_mc",30,-3,3);

  double num_data = tree_data->GetEntries();
  double num_mc = tree_mc->GetEntries();
  double scale = num_data/num_mc;

  plot(tree_data, tree_mc, h_data[0], h_mc[0], var[0], hName[0], title[0], cut, scale);
  plot(tree_data, tree_mc, h_data[1], h_mc[1], var[1], hName[1], title[1], cut, scale);
  plot(tree_data, tree_mc, h_data[2], h_mc[2], var[2], hName[2], title[2], cut, scale);
  plot(tree_data, tree_mc, h_data[3], h_mc[3], var[3], hName[3], title[3], cut, scale);
  plot(tree_data, tree_mc, h_data[4], h_mc[4], var[4], hName[4], title[4], cut, scale);
  plot(tree_data, tree_mc, h_data[5], h_mc[5], var[5], hName[5], title[5], cut, scale);

}

void plot(TChain *tree_data, TChain *tree_mc, TH1* h_data, TH1* h_mc, const TString &var, const TString& hName, const TString& title, TCut cut, const double& scale){

  TCanvas* c = new TCanvas(Form("c_%s",hName.Data()),Form("c_%s",hName.Data()),1); 
  if(hName == "Charged" || hName == "Neutral" || hName == "Gamma" ) gPad->SetLogy();

  tree_data->Draw(Form("%s>>h_data_%s",var.Data(),hName.Data()),cut,"E");
  tree_mc->Draw(Form("%s>>h_mc_%s",var.Data(),hName.Data()),cut,"same");

  h_data->SetMarkerStyle(kFullCircle);
  h_data->SetMarkerSize(0.5);
  h_data->SetStats(0);
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
