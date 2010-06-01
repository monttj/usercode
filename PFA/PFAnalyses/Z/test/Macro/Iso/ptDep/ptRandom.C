void ptRandom(){
  //Chain * tree = new Chain("Summary/tree", "/tmp/tjkim/PFA/W_PHveto2/PFAnalysis_MuonIso_0.root");
  Chain * tree = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");
  Chain * tree_random = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");
  //Chain * tree_random = new Chain("Summary/tree", "/tmp/tjkim/PFA/MCv4/PFAnalysis_MuonIso_*.root");
  
  TH1 *h_pt = new TH1F("h_pt","h_pt",100,0,100);
  tree->Project("h_pt","muon_pt");
  h_pt->Scale(1.0/h_pt->Integral());

  TCanvas *c = new TCanvas("c","c",1);

  TH1 *h_temp = new TH1F("h_temp","h_temp",40,0,4);
  h_temp->Draw(); 
  h_temp->SetStats(0);
  h_temp->SetTitle(0);

  TH1 *h[10];
  TH1 *h_muon = new TH1F("h_muon","h_muon",10,0,1);
  TH1 *h_final = new TH1F("h_final","h_final",10,0,1);
  int nrandom;
  //tree->Project("h_muon","(muon_chIso+muon_nhIso+muon_phIso)/muon_pt","muon_eta < 2.1 && muon_eta > -2.1");  
  tree->Project("h_muon","(muon_chIso+muon_nhIso+muon_ph_iso2)/muon_pt","muon_eta < 2.1 && muon_eta > -2.1");  

  int i = 0;
  while( i < 10){ 
    TString s = int2string(i);
    h[i] = new TH1F(Form("h_%s",s.Data()),Form("h_%s",s.Data()),10,0,1);
    std::ostringstream cut;
    cut.str(std::string());
    int ptwidth = 10;
    float pt = ptwidth/2 + i*ptwidth;
    //tree_random->Project(Form("h_%s",s.Data()),Form("(random_chIso+random_nhIso+random_phIso)/%f",pt),"random_jetpT > 8"); 
    tree_random->Project(Form("h_%s",s.Data()),Form("(random_chIso+random_nhIso+random_phIso)/%f",pt)); 
    nrandom = h[i]->GetEntries();
    cout << cut.str() << ":" << " entries = " << nrandom << endl;
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(3);
    h[i]->Scale(1.0/h[i]->GetEntries());
    double pdf = h_pt->Integral(i*ptwidth+1,i*ptwidth+ptwidth) ;
    double scaledentries = h[i]->GetEntries()*h_pt->Integral(i*ptwidth+1,i*ptwidth+ptwidth) ;
    h[i]->Draw("same");
    h_final->Add(h[i],scaledentries);
    cout << "h_final= " << h_final->GetEntries() << endl;
    i++;
  }

  TCanvas *c2 = new TCanvas("c2","c2",1);
  h_final->Scale(1.0/nrandom);
  h_final->SetLineWidth(4);
  h_final->SetLineColor(9);
  h_final->Draw();
  h_final->SetStats(0);
  h_final->SetTitle(0);
  h_final->GetXaxis()->SetTitle("#Sigma pT/pT");
  h_final->GetYaxis()->SetTitle("Probability");

  cout << "combined / pt= " << h_final->GetEntries() << endl;
  h_muon->Scale(1.0/h_muon->GetEntries());
  h_muon->SetLineWidth(4);
  h_muon->SetLineColor(2);
  h_muon->Draw("same");
  h_muon->SetStats(0);
  h_muon->SetTitle(0);

  TLegend *l_combined = new TLegend(0.5,0.6,0.8,0.8);
  l_combined->SetFillColor(0);
  l_combined->SetLineColor(0);
  l_combined->SetTextSize(0.04);
  //l_combined->AddEntry("h_final","Random Minbias MC","l");
  l_combined->AddEntry("h_final","Random W MC","l");
  l_combined->AddEntry("h_muon","Muon iso. W MC","l");
  l_combined->Draw();

  //c2->Print("c_relative_combined_May26.png");
  c2->Print("c_relative_combined_Jun1.eps");
  //c2->Print("c_relative_combined_May26.pdf");
}

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

