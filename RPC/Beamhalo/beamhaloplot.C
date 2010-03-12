void beamhaloplot(){

  TFile *f =TFile::Open("Rpceff.root");
  
  TH1F *beamhaloangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/beamhaloangle");
  TH1F *expectedbeamhaloangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/expectedbeamhaloangle");
  TH1F *beamhaloxyplaneangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/beamhaloxyplaneangle");
  TH1F *expectedbeamhaloxyplaneangle = (TH1F *) f->Get("/DQMData/Muons/MuonSegEff/expectedbeamhaloxyplaneangle");

  vector<string> Region;
  Region.push_back("Endcap+");
  Region.push_back("Endcap-");
  TH1F *deforRE12 = new TH1F("deforRE12","deforRE12",28,0,28);
  TH1F *nuforRE12 = new TH1F("nuforRE12","nuforRE12",28,0,28);
  TH1F *de = new TH1F("de","de",32,0,32);
  TH1F *nu = new TH1F("nu","nu",32,0,32);
  TH1F *deroll = new TH1F("deroll","deroll",36,0,36);
  TH1F *nuroll = new TH1F("nuroll","nuroll",36,0,36);
  int nderoll[36];
  int nnuroll[36];

  for(int region = 0 ; region < 1; region++){
    for(int nch = 1 ; nch <=36 ; nch++){
      for(int ndisk = 1 ; ndisk <= 3 ; ndisk++){
        for(int nring = 2; nring < 4 ; nring++){
          for(int narea = 0 ; narea < 3; narea++){
            string sign = "+";
            if(region == 1) sign="-"; 
            string disk = int2string(ndisk);
            string ring = int2string(nring);
            string sector = int2sector(nch);
            string ch = int2ch(nch);
            string area = int2area(narea);

            string sde = Region[region]+"/Disk_"+disk+"/ring_"+ring+"/sector_"+sector+"/ExpectedOccupancy_RE"+sign+disk+"_R"+ring+"_"+ch+"_"+area;
            string snu = Region[region]+"/Disk_"+disk+"/ring_"+ring+"/sector_"+sector+"/RPCDataOccupancy_RE"+sign+disk+"_R"+ring+"_"+ch+"_"+area;
            TH1F *detemp = (TH1F *) f->Get(Form("/DQMData/Muons/MuonSegEff/%s",sde));
            TH1F *nutemp = (TH1F *) f->Get(Form("/DQMData/Muons/MuonSegEff/%s",snu));
            if(ndisk == 1 && nring == 2){
              deforRE12->Add(detemp);
              nuforRE12->Add(nutemp);
            }else{
              de->Add(detemp);
              nu->Add(nutemp);
            }
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
  ploteff(beamhaloangle,expectedbeamhaloangle,beamhaloErr,"Efficiency","#theta","beamhalo_angle");

  TGraphAsymmErrors *beamhaloxyErr = new TGraphAsymmErrors();
  ploteff(beamhaloxyplaneangle,expectedbeamhaloxyplaneangle,beamhaloxyErr,"Efficiency","#theta","beamhalo_xyangle");

  TGraphAsymmErrors *effErr = new TGraphAsymmErrors();
  ploteff(nu,de,effErr,"Efficiency","strip","eff_strip");

  TGraphAsymmErrors *effErrforRE12 = new TGraphAsymmErrors();
  ploteff(nuforRE12,deforRE12,effErrforRE12,"Efficiency","strip","eff_strip_forRE12");

  TGraphAsymmErrors *effrollErr = new TGraphAsymmErrors();
  ploteff(nuroll,deroll,effrollErr,"Efficiency","roll","eff_roll");

  TCanvas *c_occupancy_roll = new TCanvas("c_occupancy_roll","c_occupancy_roll",1);
  nuroll->SetTitle("");
  nuroll->SetStats(0);
  nuroll->Draw();
  deroll->Draw("Same");

}

void ploteff(TH1F *nu, TH1F *de, TGraphAsymmErrors *beamhaloErr, TString ytitle, TString xtitle, TString name){
  int nbin = nu->GetNbinsX();
  TH1D *htemp = new TH1D(Form("c_%s",name.Data()),Form("c_%s",name.Data()),nbin,0,nbin);
  htemp->SetMinimum(0);
  htemp->SetMaximum(1.05);
  htemp->SetTitle("");
  htemp->SetStats(0);
  htemp->GetXaxis()->SetTitle(xtitle.Data());
  htemp->GetYaxis()->SetTitle(ytitle.Data());

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  htemp->Draw("");
  beamhaloErr->SetMarkerStyle(20);
  beamhaloErr->SetMarkerSize(0.8);
  beamhaloErr->BayesDivide(nu,de);
  beamhaloErr->Draw("PSame");
  clearXErrorBar(beamhaloErr);
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

