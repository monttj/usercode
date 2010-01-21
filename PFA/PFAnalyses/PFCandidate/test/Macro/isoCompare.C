void isoCompare(){

  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libPFAnalysesPFCandidate.so");
  gSystem->Load("libPFAnalysesRootTools.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libCintex.so");
  ROOT::Cintex::Cintex::Enable();
  
  Chain * tree_data = new Chain("Summary/tree", "../../PFAnalysis_RD_VeryClean.root");
  Chain * tree_mc = new Chain("Summary/tree", "../../PFAnalysis_MC_Dec6.root");

  TCut isocutCharged = "ChargedHadrons.isoDeposit(4).depositWithin(0.3) == 0";
  TCut isocutNeutral = "ChargedHadrons.isoDeposit(5).depositWithin(0.3) == 0";
  TCut isocutGamma = "ChargedHadrons.isoDeposit(6).depositWithin(0.3) == 0";

  vector<string> particle;
  particle.push_back("Charged");
  particle.push_back("Neutral");
  particle.push_back("Gamma");
 
  TH1* h_data[3];
  TH1* h_mc[3];

  for(int i=0; i< 3 ; i++){
    h_data[i]= new TH1D(Form("h_data_%s",particle[i]),"h_data",80,0,4);;
    h_mc[i] =new TH1D(Form("h_mc_%s",particle[i]),"h_mc",80,0,4);;
  }

  double num_data = tree_data->GetEntries();
  double num_mc = tree_mc->GetEntries();
  cout << "data= " << num_data << " num_mc= " << num_mc << endl;
  double scale=  num_data/num_mc;
  cout << "scale= " << scale << endl;

  string varCharged = "ChargedHadrons.isoDeposit(4).depositWithin(0.5)";
  string varNeutral = "ChargedHadrons.isoDeposit(5).depositWithin(0.5)";
  string varGamma = "ChargedHadrons.isoDeposit(6).depositWithin(0.5)";

  vector<string> var;
  var.push_back(varCharged);
  var.push_back(varNeutral);
  var.push_back(varGamma);

  plot(tree_data, tree_mc, h_data[0], h_mc[0], var[0], particle[0], scale);
  plot(tree_data, tree_mc, h_data[1], h_mc[1], var[1], particle[1], scale);
  plot(tree_data, tree_mc, h_data[2], h_mc[2], var[2], particle[2], scale);

}
void plot(TChain *tree_data, TChain *tree_mc, TH1* h_data, TH1* h_mc, TString var, TString particle, const double& scale){

  TCanvas* c = new TCanvas(Form("c_%s",particle.Data()),Form("c_%s",particle.Data()),1); 
  gPad->SetLogy();

  tree_data->Draw(Form("%s>>h_data_%s",var.Data(),particle.Data()),"","E");
  tree_mc->Draw(Form("%s>>h_mc_%s",var.Data(),particle.Data()),"","same");

  h_data->SetMarkerStyle(kFullCircle);
  h_data->SetMarkerSize(0.5);
  h_mc->SetLineColor(2);
  h_data->SetStats(0);
  h_data->GetXaxis()->SetTitle("Energy deposit within cone (GeV)");
  h_data->SetTitle(particle.Data());
  h_mc->Scale(scale);

  TLegend *l= new TLegend(0.65,0.75,0.89,0.89);
  l->AddEntry(h_data,"data","p");
  l->AddEntry(h_mc,"mc","l");
  l->SetFillColor(0);
  l->Draw();
 
  c->Print(Form("c_%s.gif",particle.Data()));
  c->Print(Form("c_%s.C",particle.Data()));
   
}
