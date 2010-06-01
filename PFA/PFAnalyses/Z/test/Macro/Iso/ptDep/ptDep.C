void ptDep(){
  Chain * tree = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv5/PFAnalysis_MuonIso_1.root");

  TCanvas *c = new TCanvas("c","c",1);

  TH1 *h_temp = new TH1F("h_temp","h_temp",40,0,4);
  h_temp->Draw(); 
  h_temp->SetStats(0);
  h_temp->SetTitle(0);

  TH1 *h[4];

  int i = 0;
  while( i < 4){ 
    TString s = int2string(i);
    h[i] = new TH1F(Form("h_%s",s.Data()),Form("h_%s",s.Data()),40,0,4);
    std::ostringstream cut;
    cut.str(std::string());
    double ptmin = i*20;
    double ptmax = i*20 + 20; 
    cut << "muon_pt  > " <<  ptmin << " && " << "muon_pt < " << ptmax ;
    tree->Draw(Form("muon_chIso>>h_%s",s.Data()), cut.str().c_str(),"same"); 
    cout << cut.str() << ":" << " entries = " << h[i]->GetEntries() << endl;
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(3);
    h[i]->Scale(1.0/h[i]->GetEntries());
    i++;
  }
}

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

