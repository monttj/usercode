void compbxplot(){

  TFile *f_1 = TFile::Open("/tmp/tjkim/cosmic2010/Run130445v6/Local.root");
  TFile *f_2 = TFile::Open("/tmp/tjkim/cosmic2010/Run130445v10/Local.root");
 
 
  vector<string> Region;
  Region.push_back("Endcap+");
  Region.push_back("Endcap-");

  TH1F *bx_1 = new TH1F("bx_1","RPC BX",36,0,36);
  TH1F *bx_2 = new TH1F("bx_2","RPC BX",36,0,36);

  TH1F *bx_chamber_1[36];
  TH1F *bx_chamber_2[36];
  for(int i=0; i < 36; i++){
    string si = int2string(i);
    bx_chamber_1[i] = new TH1F(Form("bx1_chamber_%s",si),"bx",11,-5.5,5.5); 
    bx_chamber_2[i] = new TH1F(Form("bx2_chamber_%s",si),"bx",11,-5.5,5.5); 
  }
  for(int region = 1 ; region <= 1; region++){
    for(int nch = 1 ; nch <=36 ; nch++){
      for(int ndisk = 3 ; ndisk <= 3 ; ndisk++){
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

            string sbx = Region[region]+"/Disk_"+dsign+disk+"/ring_"+ring+"/sector_"+sector+"/BXDistribution_RE"+sign+disk+"_R"+ring+"_"+ch+"_"+area;
            TH1F *temp_1 = (TH1F *) f_1->Get(Form("/DQMData/Muons/MuonSegEff/%s",sbx));
            bx_chamber_1[nch-1]->Add(temp_1);
            TH1F *temp_2 = (TH1F *) f_2->Get(Form("/DQMData/Muons/MuonSegEff/%s",sbx));
            bx_chamber_2[nch-1]->Add(temp_2);
          }
        }
      }
    }
  }
 
  for(int i=0; i < 36 ; i++){
    double mean1 = bx_chamber_1[i]->GetMean(1);
    double err1 = bx_chamber_1[i]->GetRMS();
    double mean2 = bx_chamber_2[i]->GetMean(1);
    double err2 = bx_chamber_2[i]->GetRMS();
    bx_1->SetBinContent(i+1,mean1);
    bx_2->SetBinContent(i+1,mean2);
  //  bx_1->SetBinError(i+1,err1);
  //  bx_2->SetBinError(i+1,err2);

  }

  plotbx(bx_1,bx_2,"RPC BX","Chamber","bx");
}

void plotbx(TH1F *h1, TH1F *h2, TString ytitle, TString xtitle, TString name){

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  h1->SetMinimum(-5.5);
  h1->SetMaximum(5.5);
  h1->SetStats(0);
  h1->SetTitle("");
  h1->SetMarkerColor(2);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.9);
  h1->GetYaxis()->SetTitle(ytitle);
  h1->GetXaxis()->SetTitle(xtitle);
  h1->Draw("P");
  h2->SetMarkerColor(4);
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(0.9);
  h2->Draw("PSame");

  TLegend *l= new TLegend(0.70,0.75,0.89,0.89);
  l->AddEntry(h1,"bx 49","p");
  l->AddEntry(h2,"bx 53","p");
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

