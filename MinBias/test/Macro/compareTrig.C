bool debug = false;

void compareTrig(){
  
  TFile *f1 = TFile::Open("hltmenu_1TeV_1.0e10_startup_run122314_PD_MinBias_ohlt_all_2009_12_3.root");
  TFile *f2 = TFile::Open("hltmenu_1TeV_1.0e10_startup_pythiaD6T_ohlt_30k_2009_12_3.root");

  TH2F *overlap_data = (TH2F *) f1->Get("overlap");
  TH2F *overlap_mc = (TH2F *) f2->Get("overlap");  
  TH2F *num_data = (TH2F *) f1->Get("trigCorrNum");
  TH2F *num_mc = (TH2F *) f2->Get("trigCorrNum");

  int nbin = num_data->GetNbinsY();
 
  for(int i=1 ; i <= nbin ;i++){ 
    string t = int2string(i);
    string name = "c"+t;
    TCanvas *c = new TCanvas(name.c_str(),"c",1);
    char *na = num_data->GetYaxis()->GetBinLabel(i);
    TH1D *x = overlap_data->ProjectionY("xh",i,i);
    TH1D *y = overlap_mc->ProjectionY("yh",i,i);

    //get denominators 
    double de_data = num_data->GetBinContent(i,i);
    double de_mc = num_mc->GetBinContent(i,i);

    if(debug) { 
      cout << na << endl;
      cout << "data= " << de_data << " mc= " << de_mc << endl;
    }
    //Set error from overlap plot
    for(int j=1; j <= nbin; j++){
      //get numerators
      double nu_data = num_data->GetBinContent(i,j);
      double nu_mc = num_mc->GetBinContent(i,j);

      double xerr = sigma(nu_data, de_data,3);
      double yerr = sigma(nu_mc, de_mc,3);
 
      if(debug){
        cout << "data= " << nu_data << " err= " << xerr << endl;
        cout << "mc= " << nu_mc << " err= " << yerr << endl;  
      }
      x->SetBinError(j,xerr);
      y->SetBinError(j,yerr);

    }

    //Set histograms 
    x->SetStats(0);
    x->Draw("P");
    y->Draw("PSame");
    x->SetMarkerStyle(20);
    y->SetMarkerStyle(22);
    x->SetMarkerSize(1.2);
    y->SetMarkerSize(1.2);
    x->SetMarkerColor(2);
    y->SetMarkerColor(4);
    x->SetLineColor(2);
    y->SetLineColor(4);
  
    TLegend *l= new TLegend(0.6,0.91,1.0,1.0);
    l->SetHeader(na);
    l->AddEntry(x,"Data","pl");
    l->AddEntry(y,"MC","pl");
    l->SetFillColor(0);
    l->SetLineColor(0);
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
  if( de != 0 ) de_err = sqrt(de)/de;
  err = de*sqrt(nu_err*nu_err+de_err*de_err);
  return err;
}

