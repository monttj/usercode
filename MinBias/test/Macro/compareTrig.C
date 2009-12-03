void compareTrig(){
  TFile *f1 = TFile::Open("hltmenu_1TeV_1.0e10_startup_run122314_PD_MinBias_ohlt_all.root");
  TFile *f2 = TFile::Open("hltmenu_1TeV_1.0e10_startup_pythiaD6T_ohlt_30k.root");
  TH2F *overlap_data = (TH2F *) f1->Get("overlap");
  TH2F *overlap_mc = (TH2F *) f2->Get("overlap");

  int nbin = overlap_data->GetNbinsY();
 
  for(int i=1 ; i <= nbin ;i++){ 
    string t = int2string(i);
    string name = "c"+t;
    TCanvas *c = new TCanvas(name.c_str(),"c",1);
    char *na = overlap_data->GetYaxis()->GetBinLabel(i);

    TH1D *x = overlap_data->ProjectionY("xh",i,i);
    TH1D *y = overlap_mc->ProjectionY("yh",i,i);

    x->SetStats(0);
    x->Draw();
    y->Draw("Same");
    x->SetLineColor(2);
    y->SetLineColor(4);

    TLegend *l= new TLegend(0.6,0.7,0.89,0.89);
    l->SetHeader(na);
    l->AddEntry(x,"Data","l");
    l->AddEntry(y,"MC","l");
    l->SetFillColor(0);
    l->Draw();

    x->Clear();
    y->Clear();
  }

}

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

