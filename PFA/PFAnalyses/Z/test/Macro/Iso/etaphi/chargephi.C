void chargephi(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("../../tdrstyle.C");
  setTDRStyle();

  //Chain * tree1 = new Chain("Summary/tree", "/tmp/tjkim/PFA/MCv4/PFAnalysis_MuonIso_2.root");
  Chain * tree1 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");
  Chain * tree2 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");

  TCut jetcut;
  //TCut jetcut = "random_jetpT > 7";
  TCut cut1 = "mu_ph_mcharge > 0 && mu_ph_deta < 0.01 && mu_ph_dR < 0.2";
  TCut cut2 = "mu_ph_mcharge < 0 && mu_ph_deta < 0.01 && mu_ph_dR < 0.2";

  TH1 *h_temp_phi = new TH1F("h_temp_phi","h_temp_phi", 80, -0.4, 0.4);

  TH1 *h_muon_pos_phi = new TH1F("h_muon_pos_phi","h_muon_pos_phi", 80, -0.4, 0.4);
  TH1 *h_muon_neg_phi = new TH1F("h_muon_neg_phi","h_muon_neg_phi", 80, -0.4, 0.4);

  h_muon_pos_phi->SetLineColor(4);
  h_muon_neg_phi->SetLineColor(2);

  TH1 *h_muon_pt = new TH1F("h_muon_pt", "h_muon_pt", 500, 0, 500);
  tree2->Project("h_muon_pt","muon_pt");

  cout << "muon = " << h_muon_pt->GetEntries() << endl;

  TCanvas *c_phi = new TCanvas ("c_phi","c_phi",1);
  h_temp_phi->SetStats(0);
  h_temp_phi->GetXaxis()->SetTitle("#Delta#phi");
  h_temp_phi->SetTitle(0);
  h_temp_phi->SetMaximum(0.004);
  //h_temp_phi->SetMaximum(0.1);
  h_temp_phi->Draw();

  tree1->Draw("mu_ph_dphi>>h_muon_pos_phi",cut1,"same");  
  tree2->Draw("mu_ph_dphi>>h_muon_neg_phi",cut2,"same");
  h_muon_pos_phi->Scale(1.0/h_muon_pt->GetEntries());
  h_muon_neg_phi->Scale(1.0/h_muon_pt->GetEntries());

  TLegend * l_phi = new TLegend(0.5,0.7,0.8,0.9);
  l_phi->SetLineColor(0);
  l_phi->SetFillColor(0);
  l_phi->SetTextSize(0.04);
  l_phi->AddEntry("h_muon_pos_phi","#gamma around pos. muon","l");
  l_phi->AddEntry("h_muon_neg_phi","#gamma around neg. muon","l");
  l_phi->Draw();
  
  c_phi->Print("c_chargephi_May28.png");
  c_phi->Print("c_chargephi_May28.pdf");
  c_phi->Print("c_chargephi_May28.eps");
}
