void SetStyleCanvas(TCanvas *c){
   gStyle->SetOptFit(1);
   c->Range(-0.004321055,0.806335,0.1101512,1.01563);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.15);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.15);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
}

void SetStyleGraphErrors(TGraphErrors *grae, int color, int mstyle, int lstyle, double size, TString & ytitle, TString & xtitle, double min , double max){

   grae->SetName("");
   grae->SetTitle("");
   grae->SetMarkerColor(color);
   grae->SetLineColor(color);
   grae->SetLineWidth(2);
   grae->SetLineStyle(lstyle);
   grae->SetMarkerStyle(mstyle);
   grae->SetMarkerSize(size);

   grae->SetMinimum(min);
   grae->SetMaximum(max);
   grae->SetLineStyle(0);
   grae->GetXaxis()->SetTitle(Form("%s",xtitle.Data()));
   grae->GetXaxis()->SetLabelFont(42);
   grae->GetXaxis()->SetLabelOffset(0.007);
   grae->GetXaxis()->SetLabelSize(0.05);
   grae->GetXaxis()->SetTitleSize(0.06);
   grae->GetXaxis()->SetTitleOffset(0.9);
   grae->GetXaxis()->SetTitleFont(42);
   grae->GetYaxis()->SetTitle(Form("%s",ytitle.Data()));
   grae->GetYaxis()->SetLabelFont(42);
   grae->GetYaxis()->SetLabelOffset(0.007);
   grae->GetYaxis()->SetLabelSize(0.05);
   grae->GetYaxis()->SetTitleSize(0.06);
   grae->GetYaxis()->SetTitleOffset(1.25);
   grae->GetYaxis()->SetTitleFont(42);
 
}

void SetStyleGraphErrors(TGraphAsymmErrors *grae, int color, int mstyle, int lstyle, double size, TString & ytitle, TString & xtitle, double min , double max){

   grae->SetName("");
   grae->SetTitle("");
   grae->SetMarkerColor(color);
   grae->SetLineColor(color);
   grae->SetLineWidth(2);
   grae->SetLineStyle(lstyle);
   grae->SetMarkerStyle(mstyle);
   grae->SetMarkerSize(size);

   grae->SetMinimum(min);
   grae->SetMaximum(max);
   grae->GetXaxis()->SetTitle(Form("%s",xtitle.Data()));
   grae->GetXaxis()->SetLabelFont(42);
   grae->GetXaxis()->SetLabelOffset(0.007);
   grae->GetXaxis()->SetLabelSize(0.05);
   grae->GetXaxis()->SetTitleSize(0.06);
   grae->GetXaxis()->SetTitleOffset(0.9);
   grae->GetXaxis()->SetTitleFont(42);
   grae->GetYaxis()->SetTitle(Form("%s",ytitle.Data()));
   grae->GetYaxis()->SetLabelFont(42);
   grae->GetYaxis()->SetLabelOffset(0.007);
   grae->GetYaxis()->SetLabelSize(0.05);
   grae->GetYaxis()->SetTitleSize(0.06);
   grae->GetYaxis()->SetTitleOffset(1.25);
   grae->GetYaxis()->SetTitleFont(42);

}

void SetLegend(TGraph *grae1, TString & head, TString & leg1, TString st1) {
   TLegend *leg = new TLegend(0.6,0.25,0.9,0.45,NULL,"brNDC");
   SetLegendBase(leg);
   TLegendEntry *entry=leg->AddEntry("NULL",Form("%s",head.Data()),"h");
   leg->AddEntry(grae1,Form("%s",leg1.Data()),Form("%s",st1.Data()));
   leg->Draw();
}

void SetLegend(TGraph *grae1, TGraph *grae2, TString & head, TString & leg1, TString & leg2, TString st1, TString st2) {
   TLegend *leg = new TLegend(0.6,0.25,0.9,0.45,NULL,"brNDC");
   SetLegendBase(leg);
   TLegendEntry *entry=leg->AddEntry("NULL",Form("%s",head.Data()),"h");
   leg->AddEntry(grae1,Form("%s",leg1.Data()),Form("%s",st1.Data()));
   leg->AddEntry(grae2,Form("%s",leg2.Data()),Form("%s",st2.Data()));
   leg->Draw();
}

void SetLegend(TGraph *grae1, TGraph *grae2, TGraph *grae3, TString & head, TString & leg1, TString & leg2, TString & leg3, TString st1, TString st2, TString st3) {
   TLegend *leg = new TLegend(0.6,0.25,0.9,0.45,NULL,"brNDC");
   SetLegendBase(leg);
   TLegendEntry *entry=leg->AddEntry("NULL",Form("%s",head.Data()),"h");
   leg->AddEntry(grae1,Form("%s",leg1.Data()),Form("%s",st1.Data()));
   leg->AddEntry(grae2,Form("%s",leg2.Data()),Form("%s",st2.Data()));
   leg->AddEntry(grae3,Form("%s",leg3.Data()),Form("%s",st3.Data()));
   leg->Draw();
}

void SetLegend(TGraph *grae1, TGraph *grae2, TGraph *grae3, TGraph *grae4, TString & head, TString & leg1, TString & leg2, TString & leg3, TString & leg4,TString st1, TString st2, TString st3, TString st4) {
   TLegend *leg = new TLegend(0.6,0.25,0.9,0.45,NULL,"brNDC");
   SetLegendBase(leg);
   TLegendEntry *entry=leg->AddEntry("NULL",Form("%s",head.Data()),"h");
   leg->AddEntry(grae1,Form("%s",leg1.Data()),Form("%s",st1.Data()));
   leg->AddEntry(grae2,Form("%s",leg2.Data()),Form("%s",st2.Data()));
   leg->AddEntry(grae3,Form("%s",leg3.Data()),Form("%s",st3.Data()));
   leg->AddEntry(grae4,Form("%s",leg4.Data()),Form("%s",st4.Data()));
   leg->Draw();
}

void SetLegendBase(TLegend* leg) {
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
}

TGraphErrors * getROC(TGraphErrors * sig, TGraphErrors *bkg){
  TGraphErrors * gr =  new TGraphErrors();
  int npoint = sig->GetN();

  for(int i = 0; i < npoint ; i++){
    double sigx;
    double sigy;
    double bkgx;
    double bkgy;
    sig->GetPoint(i,sigx, sigy);
    bkg->GetPoint(i,bkgx, bkgy);
    gr->SetPoint(i,bkgy,sigy);  
  }

  return gr;
}

TGraphErrors * getSF(TGraphErrors * sig, TGraphErrors *bkg){
  TGraphErrors * gr =  new TGraphErrors();
  int npoint = sig->GetN();
   
  for(int i = 0; i < npoint ; i++){
    double sigx;
    double sigy;
    double bkgx;
    double bkgy;
    double sf = 0 ;
    if( bkgy != 0 ) sf = sigy/bkgy;
    sig->GetPoint(i,sigx, sigy);
    bkg->GetPoint(i,bkgx, bkgy);
    gr->SetPoint(i,sigx,sf);
  }
   
  return gr;
}

TGraphAsymmErrors * getSF(TGraphAsymmErrors * sig, TGraphAsymmErrors *bkg){
  TGraphAsymmErrors * gr =  new TGraphAsymmErrors();
  int npoint = sig->GetN();

  for(int i = 0; i < npoint ; i++){
    double bkgx;
    double bkgy;
    double sigx;
    double sigy;
    double sigxhigh = sig->GetErrorXhigh(i);
    double sigxlow = sig->GetErrorXlow(i);
    double sigyhigh = sig->GetErrorYhigh(i);
    double sigylow = sig->GetErrorYlow(i);
    sig->GetPoint(i,sigx,sigy);
    bkg->GetPoint(i,bkgx, bkgy);

    double sf = 0;
    double sferrhigh = 0;
    double sferrlow = 0;
    if( bkgy !=0 ) {
      sf = sigy/bkgy;
      sferrhigh = sigyhigh/bkgy; 
      sferrlow =  sigylow/bkgy;
    }
    gr->SetPoint(i,sigx,sf);
    gr->SetPointEXhigh(i, sigxhigh);
    gr->SetPointEXlow(i,  sigxlow);
    gr->SetPointEYhigh(i, sigyhigh);
    gr->SetPointEYlow(i,  sigylow);

  }

  return gr;
}

TGraphAsymmErrors * getTemp(int min, int max){
  TGraphAsymmErrors * gr =  new TGraphAsymmErrors();
  for(int i = min; i < max ; i++){
    gr->SetPoint(i,i*0.01,0);
  }

  return gr;
}

void clearXErrorBar(TGraphErrors * gr)
{
   for (Int_t i=0; i< gr->GetN(); ++i) {
      gr->SetPointError(i,0,0);
   }
}

