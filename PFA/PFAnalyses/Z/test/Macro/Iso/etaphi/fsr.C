void fsr(){
  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("../../tdrstyle.C");
  setTDRStyle();

  Chain * tree2 = new Chain("Summary/tree", "/tmp/tjkim/PFA/Wv10/PFAnalysis_MuonIso_1*.root");

  TH1 *h_pt_fsr = new TH1F("h_pt_fsr","h_pt_sr",10,0,10);
  TH1 *h_pt = new TH1F("h_pt","h_pt",10,0,10);
  tree2->Project("h_pt_fsr","muon_pt","fsr_photon_dR > -1");
  tree2->Project("h_pt","muon_pt");
  cout << "muons= " << h_pt->GetEntries() << endl; 
  cout << "muons which have fsr= " << h_pt_fsr->GetEntries() << endl; 

  TH2 *h2_fsr_phi_eta = new TH2F("h2_fsr_phi_eta","phi_eta",60,-3,3,60,-3,3);
  TH2 *h2_fsr_pt_dR = new TH2F("h2_fsr_pt_dR","pt_dR",50,0,0.5,100,0,10);
  TH2 *h2_reco_pt_dR = new TH2F("h2_reco_pt_dR","pt_dR",50,0,0.5,100,0,10);

  TCanvas *c_fsr_phi_eta = new TCanvas("c_fsr_phi_eta","c_fsr_phi_eta",1);
  tree2->Project("h2_fsr_phi_eta","fsr_photon_phi:fsr_photon_eta","fsr_photon_dR > -1");
  h2_fsr_phi_eta->SetContour(100);
  h2_fsr_phi_eta->Draw("Colz");
  h2_fsr_phi_eta->SetStats(0);
  h2_fsr_phi_eta->GetXaxis()->SetTitle("#Delta#eta");
  h2_fsr_phi_eta->GetYaxis()->SetTitle("#Delta#phi");

  TCanvas *c_fsr_pt_dR = new TCanvas("c_fsr_pt_dR","c_fsr_pt_dR",1);
  //tree2->Project("h2_fsr_pt_dR","fsr_photon_pt:fsr_photon_dR","fsr_photon_dR > -1");
  tree2->Project("h2_fsr_pt_dR","fsr_photon_pt:TMath::Sqrt(fsr_photon_phi*fsr_photon_phi+fsr_photon_eta*fsr_photon_eta)","fsr_photon_dR > -1");
  h2_fsr_pt_dR->SetContour(100);
  h2_fsr_pt_dR->Draw("Colz");
  h2_fsr_pt_dR->SetStats(0);
  h2_fsr_pt_dR->GetXaxis()->SetTitle("R");
  h2_fsr_pt_dR->GetYaxis()->SetTitle("pT (GeV)");
  

  TCanvas *c_reco_pt_dR = new TCanvas("c_reco_pt_dR","c_reco_pt_dR",1);
  tree2->Project("h2_reco_pt_dR","mu_ph_th:mu_ph_dR","mu_ph_dR > -1");
  h2_reco_pt_dR->SetContour(100);
  h2_reco_pt_dR->Draw("Colz");
  h2_reco_pt_dR->SetStats(0);
  h2_reco_pt_dR->GetXaxis()->SetTitle("R");
  h2_reco_pt_dR->GetYaxis()->SetTitle("pT (GeV)");

  c_fsr_phi_eta->Print("c_fsr_phi_eta.eps");
  c_fsr_pt_dR->Print("c_fsr_pt_dR.eps");
  c_reco_pt_dR->Print("c_reco_pt_dR.eps");
}
