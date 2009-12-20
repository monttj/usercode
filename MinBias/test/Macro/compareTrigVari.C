void compareTrigVari(){

  TChain chain("Events");
  chain.Add("/afs/cern.ch/user/t/tjkim/scratch0/minbias/ntuple/MinimumBias-rereco/123596_v5/bambu_000_*.root");

  int nbin = 100;
  double xlow = 0.0;
  double xup = 100.0;

  TH1F *h_de = new TH1F("h_de","h_de",nbin,xlow,xup);
  TH1F *h_nu = new TH1F("h_nu","h_nu",nbin,xlow,xup);
  TH1F *h_ef = new TH1F("h_ef","h_ef",nbin,xlow,xup);
 
  TCut c_34 = "L1TechBitsBeforeMask.At(34) == 1";
  TCut c_40 = "L1TechBitsBeforeMask.At(40) == 1";
  TCut c_41 = "L1TechBitsBeforeMask.At(41) == 1";

  chain.Project("h_de","Pixel3Tracks.fNumEntries", c_34);
  chain.Project("h_nu","Pixel3Tracks.fNumEntries", c_40);

  h_ef->Divide(h_nu, h_de);

  //Set Error
  for(int i=1; i <= nbin; i++){
    double nnu = h_nu->GetBinContent(i);
    double nde = h_de->GetBinContent(i);
    double err = sigma(nnu,nde);
    h_ef->SetBinError(i,err);
  }

  h_ef->GetXaxis()->SetTitle("Multiplicity");
  h_ef->GetYaxis()->SetTitle("Bit 40/Bit 34");
  h_ef->Draw();
}

//Counting experiment from binomial distribution sigma = sqrt(p(1-p)/n)  
double sigma(double nu, double de){
  double err = 0;
  if( de != 0 ) {
    float p = nu/de;
    err = sqrt( p*(1-p)/de );
  }
  return err;
}

