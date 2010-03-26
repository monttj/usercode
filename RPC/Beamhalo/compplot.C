void compplot(){

  TFile *f_1 = TFile::Open("/tmp/tjkim/cosmic2010/Run130445v8/Local.root");
  TFile *f_2 = TFile::Open("/tmp/tjkim/cosmic2010/Run130445v9/Local.root");
  
  vector<string> Region;
  Region.push_back("Endcap+");
  Region.push_back("Endcap-");

  TH1F *deroll_1 = new TH1F("deroll_1","deroll",36,0,36);
  TH1F *nuroll_1 = new TH1F("nuroll_1","nuroll",36,0,36);
  TH1F *deroll_2 = new TH1F("deroll_2","deroll",36,0,36);
  TH1F *nuroll_2 = new TH1F("nuroll_2","nuroll",36,0,36);

  int nderoll_1[36];
  int nnuroll_1[36];
  int nderoll_2[36];
  int nnuroll_2[36];

  for(int i=0; i< 36 ; i++){
    nnuroll_1[i]=0;
    nderoll_1[i]=0;
    nnuroll_2[i]=0;
    nderoll_2[i]=0;
  }

  for(int region = 0 ; region < 1; region++){
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
            TH1F *detemp_1 = (TH1F *) f_1->Get(Form("/DQMData/Muons/MuonSegEff/%s",sde));
            TH1F *nutemp_1 = (TH1F *) f_1->Get(Form("/DQMData/Muons/MuonSegEff/%s",snu));
            nderoll_1[nch-1] = nderoll_1[nch-1] + detemp_1->GetEntries();
            nnuroll_1[nch-1] = nnuroll_1[nch-1] + nutemp_1->GetEntries();
            TH1F *detemp_2 = (TH1F *) f_2->Get(Form("/DQMData/Muons/MuonSegEff/%s",sde));
            TH1F *nutemp_2 = (TH1F *) f_2->Get(Form("/DQMData/Muons/MuonSegEff/%s",snu));
            nderoll_2[nch-1] = nderoll_2[nch-1] + detemp_2->GetEntries();
            nnuroll_2[nch-1] = nnuroll_2[nch-1] + nutemp_2->GetEntries();
          }
        }
      }
    }
  }
 
  for(int i=0; i < 36 ; i++){
    cout << "bx49: nu= " << nnuroll_1[i] << "de= " << nderoll_1[i] << endl;
    cout << "bx53: nu= " << nnuroll_2[i] << "de= " << nderoll_2[i] << endl;
 
    deroll_1->SetBinContent(i+1,nderoll_1[i]);
    nuroll_1->SetBinContent(i+1,nnuroll_1[i]);
    deroll_2->SetBinContent(i+1,nderoll_2[i]);
    nuroll_2->SetBinContent(i+1,nnuroll_2[i]);
  }

  TGraphAsymmErrors *effrollErr1 = new TGraphAsymmErrors();
  TGraphAsymmErrors *effrollErr2 = new TGraphAsymmErrors();
  ploteff(nuroll_1,deroll_1,effrollErr1, nuroll_2,deroll_2,effrollErr2, "Efficiency","chamber","eff_ch");

}

void ploteff(TH1F *nu1, TH1F *de1, TGraphAsymmErrors *Err1, TH1F *nu2, TH1F *de2, TGraphAsymmErrors *Err2,  TString ytitle, TString xtitle, TString name){
  int nbin = nu1->GetNbinsX();
  int binsize = nu1->GetBinWidth(1);
  TH1D *htemp = new TH1D(Form("c_%s",name.Data()),Form("c_%s",name.Data()),nbin,0,nbin*binsize);
  htemp->SetMinimum(0);
  htemp->SetMaximum(1.05);
  htemp->SetTitle("");
  htemp->SetStats(0);
  htemp->GetXaxis()->SetTitle(xtitle.Data());
  htemp->GetYaxis()->SetTitle(ytitle.Data());

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  htemp->Draw("");
  Err1->SetMarkerColor(2);
  Err1->SetMarkerStyle(20);
  Err1->SetMarkerSize(0.9);
  Err1->BayesDivide(nu1,de1);
  Err1->Draw("PSame");
  clearXErrorBar(Err1);
  Err2->SetMarkerColor(4);
  Err2->SetMarkerStyle(20);
  Err2->SetMarkerSize(0.9);
  Err2->BayesDivide(nu2,de2);
  Err2->Draw("PSame");
  clearXErrorBar(Err2);

  TLegend *l= new TLegend(0.50,0.35,0.79,0.45);
  l->AddEntry(Err1,"bx 49","p");
  l->AddEntry(Err2,"bx 53","p");
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->SetTextSize(0.04);
  l->Draw();

 
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

