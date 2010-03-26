void rmsplot(){

  TFile *f =TFile::Open("Local.root");
  
  TH2F *ResidualTheta = (TH2F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/ResidualTheta");
  TH2F *ClusterSizeTheta = (TH2F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/ClusterSizeTheta");

  TH1D *h_residual = new TH1D("h_residual","h_residual",9,0,90);
  TH1D *h_cluster = new TH1D("h_cluster","h_cluster",9,0,90);

  getRMS(ResidualTheta, h_residual, "Residual");
  getRMS(ClusterSizeTheta, h_cluster, "Cluster");

}

void getRMS(TH2F *h2, TH1D *h1, TString name){
  
  int ybin = h2->GetNbinsY();

  for(int i=1; i <= 9 ; i++){
    TH1D *temp = h2->ProjectionY("temp",i*2-1,i*2);
    TH1D *temp_opp = h2->ProjectionY("temp_opp",37-i*2,37-(i*2-1));
    temp->Add(temp_opp);
    double sigma = temp->GetRMS();
    double sigmaerr = temp->GetRMSError();
    double xm = 0.0;
    double xm2 = 0.0;
    double xn = 0.0;
    for(int j=1; j <= ybin ; j++){
      xn += temp->GetBinContent(j);
      xm2 += temp->GetBinContent(j)*temp->GetBinCenter(j)*temp->GetBinCenter(j);
    }
    double rms = 0.0;
    double rmserr = 0.0;
    if( xn !=0){
      rms = sqrt(TMath::Sqrt(xm2/xn));
      rmserr = rms/TMath::Sqrt(xn);
    }
    h1->SetBinContent(i,rms);
    h1->SetBinError(i,rmserr);
    //h1->SetBinContent(i,sigma);
    //h1->SetBinError(i,sigmaerr);
    temp->Delete();
    temp_opp->Delete();

    cout << "i= " << i << " " << rms << " +- " << rmserr << endl;
  }

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  h1->SetTitle("");
  h1->SetMaximum(3);
  h1->SetMinimum(0.5);
  h1->SetMarkerColor(2);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.8);
  h1->SetStats(0);
  h1->Draw("P");
  h1->GetXaxis()->SetTitle(Form("global theta (#theta)"));
  h1->GetYaxis()->SetTitle(Form("%s RMS (cm)",name.Data()));
  c->Print(Form("c_%s.eps",name.Data()));
}

void ploteff(TH1F *nu, TH1F *de, TGraphAsymmErrors *beamhaloErr, TString ytitle, TString xtitle, TString name){
  int nbin = nu->GetNbinsX();
  int binsize = nu->GetBinWidth(1);
  TH1D *htemp = new TH1D(Form("c_%s",name.Data()),Form("c_%s",name.Data()),nbin,0,nbin*binsize);
  htemp->SetMinimum(0);
  htemp->SetMaximum(1.05);
  htemp->SetTitle("");
  htemp->SetStats(0);
  htemp->GetXaxis()->SetTitle(xtitle.Data());
  htemp->GetYaxis()->SetTitle(ytitle.Data());

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  htemp->Draw("");
  beamhaloErr->SetMarkerStyle(20);
  beamhaloErr->SetMarkerSize(1);
  beamhaloErr->BayesDivide(nu,de);
  beamhaloErr->Draw("PSame");
  clearXErrorBar(beamhaloErr);
 
  c->Print(Form("c_%s.eps",name.Data()));
}

void clearXErrorBar(TGraphAsymmErrors * gr)
{
   for (Int_t i=0; i< gr->GetN(); ++i) {
      gr->SetPointEXhigh(i,0);
      gr->SetPointEXlow(i,0);
   }
}

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

string int2sector(int i){
  string s = "";
  if(i <= 6) s = "1";
  if( 6 < i && i <= 12) s = "2";
  if( 12 < i && i <= 18) s = "3";
  if( 18 < i && i <= 24) s = "4";
  if( 24 < i && i <= 30) s = "5";
  if( 30 < i && i <= 36) s = "6";
  return s;
}

string int2ch(int i){
  string pre="";
  if( i < 10) {
    pre = "CH0";
  }else{
    pre = "CH";
  }

  stringstream ss;
  ss << i;
  string s= ss.str();
  string out = pre+s;
  return out;
}

string int2area(int i){
  string s="";
  if( i == 0) s = "A";
  if( i == 1) s = "B";
  if( i == 2) s = "C";
  return s;
}

