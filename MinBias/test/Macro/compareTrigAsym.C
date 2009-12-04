bool debug = false;

void clearXErrorBar(TGraphAsymmErrors * gr)
{
   for (Int_t i=0; i< gr->GetN(); ++i) {
      gr->SetPointEXhigh(i,0);
      gr->SetPointEXlow(i,0);
   }
}


void compareTrigAsym(){
  
  TFile *f1 = TFile::Open("hltmenu_1TeV_1.0e10_startup_run122314_PD_MinBias_ohlt_all_2009_12_3.root");
  TFile *f2 = TFile::Open("hltmenu_1TeV_1.0e10_startup_pythiaD6T_ohlt_30k_2009_12_3.root");

  TH2F *overlap_data = (TH2F *) f1->Get("overlap");
  TH2F *overlap_mc = (TH2F *) f2->Get("overlap");  
  TH2F *num_data = (TH2F *) f1->Get("trigCorrNum");
  TH2F *num_mc = (TH2F *) f2->Get("trigCorrNum");
  

  int nbin = num_data->GetNbinsY();
  TH1D *htemp = overlap_data->ProjectionY("htemp",0,0);
  htemp->SetMinimum(0);
  htemp->SetMaximum(1.05);

  for(int i=1 ; i <= nbin ;i++){ 
    TH1D *nux = new TH1D("nux","nux",nbin,1,nbin+1);
    TH1D *nuy = new TH1D("nuy","nuy",nbin,1,nbin+1);
    TH1D *dex = new TH1D("dex","dex",nbin,1,nbin+1);
    TH1D *dey = new TH1D("dey","dey",nbin,1,nbin+1);

    string t = int2string(i);
    string name = "c"+t;
    TCanvas *c = new TCanvas(name.c_str(),"c",1);
    char *na = num_data->GetYaxis()->GetBinLabel(i);
    TH1D *x = overlap_data->ProjectionY("xh",0,0);
    TH1D *y = overlap_mc->ProjectionY("yh",0,0);

    //get denominators 
    double de_data = num_data->GetBinContent(i,i);
    double de_mc = num_mc->GetBinContent(i,i);
    if(de_data == 0 ) de_data = 100000;
    if(de_mc == 0 ) de_mc = 100000;

    if(debug) { 
      cout << na << endl;
      cout << "data= " << de_data << " mc= " << de_mc << endl;
    }
    //Set error from overlap plot
    for(int j=1; j <= nbin; j++){
      //get numerators
      double nu_data = num_data->GetBinContent(i,j);
      double nu_mc = num_mc->GetBinContent(i,j);

      if(debug){
        cout << "data= " << nu_data << endl; //" err= " << xerr << endl;
        cout << "mc= " << nu_mc << endl; //" err= " << yerr << endl;  
      }

      nux->SetBinContent(j,nu_data);
      nuy->SetBinContent(j,nu_mc);
      dex->SetBinContent(j,de_data);
      dey->SetBinContent(j,de_mc);
    }

    //Set histograms 
    htemp->SetTitle("");
    htemp->SetStats(0);
    htemp->Draw("");
    htemp->GetXaxis()->LabelsOption("v");
    htemp->GetXaxis()->LabelsOption("v");

    //TGaxis *axis4 = new TGaxis(nbin+1,-0.05,nbin+1,1.05,-0.05,1.05,510,"+L"); 
    //axis4->SetName("axis4"); 
    //axis4->SetLabelOffset(0.01); 
    //axis4->Draw(); 

    TGraphAsymmErrors *dataErr = new TGraphAsymmErrors();
    dataErr->SetMarkerStyle(20);
    dataErr->SetMarkerSize(1.2);
    dataErr->SetMarkerColor(2);
    dataErr->BayesDivide(nux,dex);
    dataErr->Draw("PSame");
    clearXErrorBar(dataErr);

    TGraphAsymmErrors *mcErr = new TGraphAsymmErrors();
    mcErr->SetMarkerStyle(22);
    mcErr->SetMarkerSize(1.2);
    mcErr->SetMarkerColor(4);
    mcErr->BayesDivide(nuy,dey);
    mcErr->Draw("PSame");
    clearXErrorBar(mcErr);
 
    c->SetBottomMargin(0.35);

    TLegend *l= new TLegend(0.6,0.91,1.0,1.0);
    l->SetHeader(na);
    l->AddEntry(dataErr,"Data","LP");
    l->AddEntry(mcErr,"MC","LP");
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->Draw();

    x->Clear();
    y->Clear();
    nux->Clear();
    dex->Clear();
    nuy->Clear();
    dey->Clear();
    dataErr->Clear();
    mcErr->Clear(); 
  }

}

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

//Counting experiment from binomial distribution sigma = sqrt(p(1-p)/n)  
double sigma(double nu, double de, int a){
  double err = 0;
  if( de != 0 ) {
    float p = nu/de;
    err = a*sqrt( p*(1-p)/de );
  } 
  return err;
}

//combined error = sqrt(dx/x*dx/x + dy/y*dy/y) 
double combinederror(double nu, double de){
  double err = 0;
  double nu_err=0;
  double de_err=0;
  if( nu != 0 ) nu_err = sqrt(nu)/nu;
  if( de != 0 ) {
    de_err = sqrt(de)/de;
    err = (nu/de)*sqrt(nu_err*nu_err+de_err*de_err);
  }
  return err;
}


