void beamhaloplot(){

  TFile *f =TFile::Open("Rpceff_1.root");
  
  TH1F *beamhaloangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/beamhaloangle");
  TH1F *expectedbeamhaloangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/expectedbeamhaloangle");
  TH1F *beamhaloxyplaneangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/beamhaloxyplaneangle");
  TH1F *expectedbeamhaloxyplaneangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/expectedbeamhaloxyplaneangle");
  
  int nbin = beamhaloangle->GetNbinsX();
  TH1D *htemp = new TH1D("htemp","htemp",nbin,0,nbin);
  htemp->SetMinimum(0);
  htemp->SetMaximum(1.05);

  htemp->SetTitle("");
  htemp->SetStats(0);
  htemp->GetXaxis()->SetTitle("#theta");
  htemp->GetYaxis()->SetTitle("Efficiency");


  TCanvas *c_beamhalo_angle = new TCanvas("c_beamhalo_angle","c_beamhalo_angle",1);
  htemp->Draw("");
  TGraphAsymmErrors *beamhaloErr = new TGraphAsymmErrors();
  beamhaloErr->SetMarkerStyle(20);
  beamhaloErr->SetMarkerSize(0.8);
  beamhaloErr->BayesDivide(beamhaloangle,expectedbeamhaloangle);
  beamhaloErr->Draw("PSame");
  clearXErrorBar(beamhaloErr);

  TCanvas *c_beamhalo_xyangle = new TCanvas("c_beamhalo_xyangle","c_beamhalo_xyangle",1);
  htemp->Draw("");
  TGraphAsymmErrors *beamhaloxyErr = new TGraphAsymmErrors();
  beamhaloxyErr->SetMarkerStyle(20);
  beamhaloxyErr->SetMarkerSize(0.8);
  beamhaloxyErr->BayesDivide(beamhaloxyplaneangle,expectedbeamhaloxyplaneangle);
  beamhaloxyErr->Draw("PSame");
  clearXErrorBar(beamhaloxyErr);

}

void clearXErrorBar(TGraphAsymmErrors * gr)
{
   for (Int_t i=0; i< gr->GetN(); ++i) {
      gr->SetPointEXhigh(i,0);
      gr->SetPointEXlow(i,0);
   }
}


