void beamhaloplot(){

  TFile *f =TFile::Open("Local.root");

  
  TH1F *beamhaloangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/AnyOccupancyTheta");
  TH1F *expectedbeamhaloangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/ExpectedOccupancyTheta");
  TH1F *beamhaloxyplaneangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/AnyOccupancyAngleToStrip");
  TH1F *expectedbeamhaloxyplaneangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/ExpectedOccupancyAngleToStrip");

  TH2F *ResidualTheta = (TH2F *) f->Get("/DQMData/Muons/MuonSegEff/Beamhalo/ResidualTheta");

  vector<string> Region;
  Region.push_back("Endcap+");
  Region.push_back("Endcap-");
  TH1F *de = new TH1F("de","de",32,0,32);
  TH1F *nu = new TH1F("nu","nu",32,0,32);
  TH1F *deroll = new TH1F("deroll","deroll",36,0,36);
  TH1F *nuroll = new TH1F("nuroll","nuroll",36,0,36);
  TProfile *residulatheta = ResidualTheta->ProfileX("residualtheta",1,200);

  int ybin = ResidualTheta->GetNbinsY();
  int xbin = ResidualTheta->GetNbinsX();
  int sbin = ResidualTheta->GetBinWidth(1);

  TH1D *h_rms = new TH1D("h_rms","h_rms",xbin,0,xbin*sbin);
  
  for(int i=1; i <= xbin ; i++){
    TH1D *temp = ResidualTheta->ProjectionY("temp",i,i);
    double rms = temp->GetRMS();
    double rmserr = temp->GetRMSError();
    cout << "i= " << i << " " << rms << " +- " << rmserr << endl;
    h_rms->SetBinContent(i,rms);
    h_rms->SetBinError(i,rmserr);
    temp->Delete();
  }

  int nderoll[36];
  int nnuroll[36];
  for(int i=0; i< 36 ; i++){
    nnuroll[i]=0;
    nderoll[i]=0;
  }

  for(int region = 0 ; region < 2; region++){
    for(int nch = 1 ; nch <=36 ; nch++){
      for(int ndisk = 1 ; ndisk <= 3 ; ndisk++){
        for(int nring = 2; nring < 4 ; nring++){
          for(int narea = 0 ; narea < 3; narea++){
            string sign = "+";
            string dsign = "";
            if(region == 1) {
              sign="-"; 
              dsign="-";
            }
            string disk = int2string(ndisk);
            string ring = int2string(nring);
            string sector = int2sector(nch);
            string ch = int2ch(nch);
            string area = int2area(narea);

            string sde = Region[region]+"/Disk_"+dsign+disk+"/ring_"+ring+"/sector_"+sector+"/ExpectedOccupancy_RE"+sign+disk+"_R"+ring+"_"+ch+"_"+area;
            string snu = Region[region]+"/Disk_"+dsign+disk+"/ring_"+ring+"/sector_"+sector+"/RPCDataOccupancy_RE"+sign+disk+"_R"+ring+"_"+ch+"_"+area;
            TH1F *detemp = (TH1F *) f->Get(Form("/DQMData/Muons/MuonSegEff/%s",sde));
            TH1F *nutemp = (TH1F *) f->Get(Form("/DQMData/Muons/MuonSegEff/%s",snu));
            de->Add(detemp);
            nu->Add(nutemp);
            nderoll[nch-1] = nderoll[nch-1] + detemp->GetEntries();
            nnuroll[nch-1] = nnuroll[nch-1] + nutemp->GetEntries();
          }
        }
      }
    }
  }
 
  for(int i=0; i < 36 ; i++){
    deroll->SetBinContent(i+1,nderoll[i]);
    nuroll->SetBinContent(i+1,nnuroll[i]);
  }

  TGraphAsymmErrors *beamhaloErr = new TGraphAsymmErrors();
  ploteff(beamhaloangle,expectedbeamhaloangle,beamhaloErr,"Efficiency","global theta (#theta)","beamhalo_angle");

  TGraphAsymmErrors *beamhaloxyErr = new TGraphAsymmErrors();
  ploteff(beamhaloxyplaneangle,expectedbeamhaloxyplaneangle,beamhaloxyErr,"Efficiency","global theta (#theta)","beamhalo_xyangle");

  TGraphAsymmErrors *effErr = new TGraphAsymmErrors();
  ploteff(nu,de,effErr,"Efficiency","strip","eff_strip");

  TGraphAsymmErrors *effrollErr = new TGraphAsymmErrors();
  ploteff(nuroll,deroll,effrollErr,"Efficiency","roll","eff_roll");

  TCanvas *c_occupancy_roll = new TCanvas("c_occupancy_roll","c_occupancy_roll",1);
  nuroll->SetTitle("");
  nuroll->SetStats(0);
  nuroll->Draw();
  deroll->Draw("Same");
  nuroll->GetXaxis()->SetTitle("roll");
  nuroll->GetYaxis()->SetTitle("Occupancy");

  TCanvas *c_residualtheta = new TCanvas("c_residualtheta","c_residualtheta",1);
  residualtheta->Draw();
  residualtheta->GetXaxis()->SetTitle("global theta (#theta)");
  residualtheta->GetYaxis()->SetTitle("Residual (cm)");

  TCanvas *c_rms = new TCanvas("c_rms","c_rms",1);
  h_rms->SetMaximum(11);
  h_rms->SetMarkerStyle(20);
  h_rms->SetMarkerSize(1.2);
  h_rms->Draw("P");
  h_rms->GetXaxis()->SetTitle("global theta (#theta)");
  h_rms->GetYaxis()->SetTitle("sigma");

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
  beamhaloErr->SetMarkerSize(0.1);
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

