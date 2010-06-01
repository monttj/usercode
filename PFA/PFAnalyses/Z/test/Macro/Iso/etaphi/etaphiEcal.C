void etaphiEcal(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("../../tdrstyle.C");
  setTDRStyle();

  //Chain * tree1 = new Chain("Summary/tree", "/tmp/tjkim/PFA/MCv4/PFAnalysis_MuonIso_2.root");
  Chain * tree1 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");
  Chain * tree2 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv9/PFAnalysis_MuonIso_*.root");

  TCut jetcut;
  //TCut jetcut = "random_jetpT > 7";
  TCut cut1 = "ran_ph_dR < 0.2 && ran_ph_deta < 0.01";
  TCut cut2 = "mu_ph_dR < 0.2 && TMath::Abs(mu_ph_deta) < 0.01";

  TH1 *h_temp_eta = new TH1F("h_temp_eta","h_temp_eta", 80, -0.4, 0.4);
  TH1 *h_temp_phi = new TH1F("h_temp_phi","h_temp_phi", 80, -0.4, 0.4);

  TH1 *h_muon_eta = new TH1F("h_muon_eta","h_muon_eta", 80, -0.4, 0.4);
  TH1 *h_muon_phi = new TH1F("h_muon_phi","h_muon_phi", 80, -0.4, 0.4);
  TH1 *h_random_eta = new TH1F("h_random_eta", "h_random_eta",80, -0.4, 0.4);
  TH1 *h_random_phi = new TH1F("h_random_phi", "h_random_phi",80, -0.4, 0.4);

  h_muon_eta->SetLineColor(2);
  h_muon_phi->SetLineColor(2);
  h_random_eta->SetLineColor(4);
  h_random_phi->SetLineColor(4);

  TH1 *h_muon_pt = new TH1F("h_muon_pt", "h_muon_pt", 500, 0, 500);
  TH1 *h_random_pt = new TH1F("h_random_pt","h_random_pt", 500, 0, 500);
  tree1->Project("h_random_pt","random_pt",jetcut);
  tree2->Project("h_muon_pt","muon_pt");

  cout << "muon = " << h_muon_pt->GetEntries() << endl;
  cout << "random = " << h_random_pt->GetEntries() << endl;

  TCanvas *c_eta = new TCanvas ("c_eta","c_eta",1);
  h_temp_eta->SetStats(0);
  h_temp_eta->GetXaxis()->SetTitle("#Delta#eta");
  h_temp_eta->SetTitle(0);
  h_temp_eta->SetMaximum(0.007);
  h_temp_eta->Draw();

  //tree1->Draw("ran_ph_decaleta>>h_random_eta",jetcut && cut1,"same");
  tree2->Draw("mu_ph_decaleta>>h_muon_eta",cut2,"same");
  h_muon_eta->Scale(1.0/h_muon_pt->GetEntries());
  //h_random_eta->Scale(1.0/h_random_pt->GetEntries());

  TLegend * l_eta = new TLegend(0.6,0.7,0.8,0.9);
  l_eta->SetLineColor(0);
  l_eta->SetFillColor(0);
  l_eta->SetTextSize(0.04);
  l_eta->AddEntry("h_muon_phi","#gamma around muon","l");
  //l_eta->AddEntry("h_random_phi","#gamma around random","l");
  l_eta->Draw();

  //c_eta->Print("c_deta_May26.png");
  //c_eta->Print("c_deta_May26.pdf");
  c_eta->Print("c_deta_Jun1.eps");


  TCanvas *c_phi = new TCanvas ("c_phi","c_phi",1);
  h_temp_phi->SetStats(0);
  h_temp_phi->GetXaxis()->SetTitle("#Delta#phi");
  h_temp_phi->SetTitle(0);
  h_temp_phi->SetMaximum(0.004);
  h_temp_phi->Draw();

  //tree1->Draw("ran_ph_decalphi>>h_random_phi",jetcut && cut1,"same");  
  tree2->Draw("mu_ph_decalphi>>h_muon_phi",cut2,"same");
  h_muon_phi->Scale(1.0/h_muon_pt->GetEntries());
  //h_random_phi->Scale(1.0/h_random_pt->GetEntries());

  TLegend * l_phi = new TLegend(0.6,0.7,0.8,0.9);
  l_phi->SetLineColor(0);
  l_phi->SetFillColor(0);
  l_phi->SetTextSize(0.04);
  l_phi->AddEntry("h_muon_phi","#gamma around muon","l");
  //l_phi->AddEntry("h_random_phi","#gamma around random","l");
  l_phi->Draw();
  
  //c_phi->Print("c_dphi_May26.png");
  //c_phi->Print("c_dphi_May26.pdf");
  c_phi->Print("c_dphi_Jun1.eps");
}
