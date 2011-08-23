#include "muStyle.h"
#include "ParticleBasedIso/c_ROCtnp_pt20_50_PU.h"
#include "ParticleBasedIso/c_eff_QCD_MC_pt20_50_PU.h"
#include "ParticleBasedIso/c_eff_pt_PFIso.h"
#include "DetBaseIso/ROCtnp_TrkCalo.h"
#include "DetBaseIso/ROCtnp_TrkOnly.h"
#include "DetBaseIso/Eff_RelComb_pt20_50.h"
#include "DetBaseIso/Eff_TrkRelISO_pt20_50.h"
#include "DetBaseIso/c_eff_pt_DetIso_Effs_PtBinned_NEW.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsIsoCut.h"
#include "LKT_PLOTS/muonsFromZ_trkRel_EfficVsIsoCut.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsPt.h"
#include "LKT_PLOTS/muonsFromZ_trkRel_EfficVsPt.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsEta.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsNCaloTowers_noSUSY.h"
#include "LKT_PLOTS/efficiencies_data.h"
#include "LKT_PLOTS/efficiencies_MC.h"

void draw(TString& type, TString& ytitle, TString& xtitle, TString& head,  double min, double max, TString &leg1, TString& leg2, TString &leg3 = ""){
   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphAsymmErrors *grae1data = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae1mc = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae2data = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae2mc = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae1sf = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae2sf = new TGraphAsymmErrors();

   TGraphErrors *grae1LKTdata = new TGraphErrors();
   TGraphErrors *grae1LKTmc = new TGraphErrors();
   TGraphErrors *grae1LKTsf = new TGraphErrors();

   int datacolor1 = 1;
   int datacolor2 = 1;

   //ISO
   if( type.Contains("cEffPFBaseISO") ){
     EffParticleIsoData(grae1data);
     EffParticleIsoMC(grae1mc);
     grae1sf = getSF(grae1data, grae1mc);
   }else if ( type.Contains("cEffDETBaseISOrel")){
     EffDetectorRelIsoData(grae1data);
     EffDetectorRelIsoMC(grae1mc);
     EffLKTIsoData(grae1LKTdata);
     EffLKTIsoMC(grae1LKTmc);
     grae1sf = getSF(grae1data, grae1mc);
     grae1LKTsf = getSF(grae1LKTdata, grae1LKTmc);
   }else if ( type.Contains("cEffDETBaseISOtrk")){
     EffDetectorTrkIsoData(grae1data);
     EffDetectorTrkIsoMC(grae1mc);
     EffLKTTrkIsoData(grae1LKTdata);
     EffLKTTrkIsoMC(grae1LKTmc);
     grae1sf = getSF(grae1data, grae1mc);
     grae1LKTsf = getSF(grae1LKTdata, grae1LKTmc);
   }

  //PT
   if( type.Contains("cEffPFBasePT") ){
     datacolor1 = 2;
     datacolor2 = 4;
     SetEffPFPt(grae1data, grae1mc);
     SetEffPFPt3(grae2data, grae2mc);
     grae1sf = getSF(grae1data, grae1mc);
     grae2sf = getSF(grae2data, grae2mc);
   }else if( type.Contains("cEffDETBasePTrel") ){
     datacolor1 = 2;
     datacolor2 = 4;
     SetEffDetPtRel10(grae1data, grae1mc);
     SetEffDetPtRel15(grae2data, grae2mc);
     SetEffLKTPt(grae1LKTmc, grae1LKTdata);
     grae1sf = getSF(grae1data, grae1mc);
     grae2sf = getSF(grae2data, grae2mc);
     grae1LKTsf = getSF(grae1LKTdata, grae1LKTmc);
   }else if( type.Contains("cEffDETBasePTtrk") ){
     datacolor1 = 2;
     datacolor2 = 4;
     SetEffDetPtTrk05(grae1data, grae1mc);
     SetEffDetPtTrk10(grae2data, grae2mc);
     SetEffLKTTrkPt(grae1LKTmc, grae1LKTdata);
     grae1sf = getSF(grae1data, grae1mc);
     grae2sf = getSF(grae2data, grae2mc);
     grae1LKTsf = getSF(grae1LKTdata, grae1LKTmc);
   }

   //ROC
   if( type.Contains("cROCPFBaseIso")){
     ROCParticleIsoData(grae1data);
     ROCParticleIsoMC(grae1mc);
   }else if ( type.Contains("cROCDETBaseIsorel")){
     ROCDetectorRelIsoData(grae1data);
     ROCDetectorRelIsoMC(grae1mc);
     //data LKT
     //ROCLKTIsoData(grae1LKTdata);
     TGraphErrors *graeTbkgData = new TGraphErrors();
     TGraphErrors *graeTsigData = new TGraphErrors();
     EffLKTIsoData(graeTsigData);
     SetDataQCDEffLKT(graeTbkgData);
     grae1LKTdata = getROC(graeTsigData, graeTbkgData);
     //mc LKT
     TGraphErrors *graeTbkg = new TGraphErrors();
     TGraphErrors *graeTsig = new TGraphErrors();
     EffLKTIsoMC(graeTsig);
     SetMCQCDEffLKT(graeTbkg);
     grae1LKTmc = getROC(graeTsig, graeTbkg);
   }else if ( type.Contains("cROCDETBaseIsotrk")){
     ROCDetectorTrkIsoData(grae1data);
     ROCDetectorTrkIsoMC(grae1mc);
   }

   SetStyleGraphErrors(grae1data, datacolor1, 20, 0, 0.9, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae2data, datacolor2, 20, 0, 0.9, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae1mc, 2, 21, 0, 0.9, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae1LKTdata, 4, 24, 0, 0.9, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae1LKTmc, 6, 20, 0, 0.9, ytitle, xtitle, min, max);

   TGraphAsymmErrors *temp = new TGraphAsymmErrors();
   temp = getTemp(1,27);

   //ISO draw
   if( type.Contains("cEffPFBaseISO") || type.Contains("cEffDETBaseISO") ){
     SetStyleGraphErrors(temp, 2, 23, 0, 0.0,  ytitle, xtitle, min, max);
     temp->Draw("APC");
     if( type.Contains("cEffPFBaseISO") ){
       grae1data->Draw("PCSame");
       grae1mc->Draw("PCSame");
       SetLegend(grae1data, grae1mc, head, leg1, leg2, "PL", "PL");
     }else if ( type.Contains("cEffDETBaseISO") ) {
       grae1data->Draw("PCSame");
       grae1mc->Draw("PCSame");
       grae1LKTdata->Draw("PSame");
       grae1LKTmc->Draw("PSame");
       clearXErrorBar(grae1LKTdata);
       clearXErrorBar(grae1LKTmc);
       SetLegend(grae1data, grae1mc, grae1LKTdata, grae1LKTmc, head, leg1, leg2, "LKT Data", "LKT MC", "PL","PL","P","P",0.6, 0.20, 0.9,0.50);
     }
   }

   //PT draw
   if( type.Contains("cEffPFBasePT") ){
     grae1data->Draw("AP");
     grae2data->Draw("PSame");
     SetLegend(grae1data, grae2data, head, leg1, leg2, "PL", "PL");
   }else if( type.Contains("cEffDETBasePT") ){
     grae1data->Draw("APSame");
     grae2data->Draw("PSame");
     grae1LKTdata->Draw("PSame");
     SetLegend(grae1data, grae2data, grae1LKTdata, head, leg1, leg2, leg3, "PL", "PL", "P");
   }

   //ROC draw
   if( type.Contains("ROC") ){
     SetStyleGraphErrors(temp, 2, 23, 0, 0.0,  ytitle, xtitle, min, max);
     if( type.Contains("cROCPFBaseIso") || type.Contains("cROCDETBaseIsotrk") ){
       grae1data->Draw("APC");
       grae1mc->Draw("PCSame");
       SetLegend(grae1data, grae1mc, head, leg1, leg2, "PL", "PL");
     }else if ( type.Contains("cROCDETBaseIsorel") ) {
       grae1data->Draw("APC");
       grae1mc->Draw("PCSame");
       grae1LKTdata->Draw("PSame");
       grae1LKTmc->Draw("PSame");
       clearXErrorBar(grae1LKTdata);
       clearXErrorBar(grae1LKTmc);
       SetLegend(grae1data, grae1mc, grae1LKTdata, grae1LKTmc, head, leg1, leg2, "LKT Data", "LKT MC", "PL","PL","P","P",0.6, 0.20, 0.9,0.50);
     }
   }
   SetLabel(0.6,0.6,36);
   c->Print(Form("%s.eps",type.Data()));

   //SF for pt
   if (type.Contains("cEffPFBasePT") || type.Contains("cEffDETBasePT") ){ 
     TCanvas *c_sf = new TCanvas(Form("%sSF",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
     SetStyleCanvas(c_sf);

     min = 0.75;
     max = 1.2;
     SetStyleGraphErrors(grae1sf, 2, 20, 0, 0.9, "Data/MC", xtitle, min, max);
     SetStyleGraphErrors(grae2sf, 4, 20, 0, 0.9, "Data/MC", xtitle, min, max);
     SetStyleGraphErrors(grae1LKTsf, 4, 24, 0, 0.9, "Data/MC", xtitle, min, max);

     if( type.Contains("cEffPFBasePT") ){
       grae1sf->Draw("AP");
       grae2sf->Draw("PSame");
       SetLegend(grae1sf, grae2sf, head, leg1, leg2, "PL", "PL");
     }else if( type.Contains("cEffDETBasePT") ){
       grae1sf->Draw("APSame");
       grae2sf->Draw("PSame");
       grae1LKTsf->Draw("PSame");
       SetLegend(grae1sf, grae2sf, grae1LKTsf, head, leg1, leg2, leg3, "PL", "PL", "P");
     }
     SetLabel(0.6,0.88,36);
     c_sf->Print(Form("%sSF.eps",type.Data()));
   }

   //SF for efficiency
   if ( type.Contains("cEffPFBaseISO") || type.Contains("cEffDETBaseISO") ){
     TCanvas *c_sf = new TCanvas(Form("%sSF",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
     SetStyleCanvas(c_sf);
     min = 0.93;
     max = 1.07;
     SetStyleGraphErrors(grae1sf, 2, 20, 0, 0.9, "Data/MC", xtitle, min, max);
     SetStyleGraphErrors(grae1LKTsf, 4, 24, 0, 0.9, "Data/MC", xtitle, min, max);

     SetStyleGraphErrors(temp, 2, 23, 0, 0.0,  "Data/MC", xtitle, min, max);
     temp->Draw("AP");

     if( type.Contains("cEffPFBaseISO") ){
       grae1sf->Draw("PSame");
       SetLegend(grae1sf, head, "T&P",  "PL");
     }else if( type.Contains("cEffDETBaseISO") ){
       grae1sf->Draw("PSame");
       grae1LKTsf->Draw("PSame");
       SetLegend(grae1sf, grae1LKTsf, head, "T&P", "LKT", "PL", "P");
     }
     SetLabel(0.6,0.88,36);
     c_sf->Print(Form("%sSF.eps",type.Data()));
   }
}

void drawLKT(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2){
   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphErrors *grae1 = new TGraphErrors();
   TGraphErrors *grae2 = new TGraphErrors();

   if( type.Contains("cEffLKTrel") ){
     EffLKTIsoData(grae1);
     EffLKTIsoMC(grae2);
   }else if( type.Contains("cEffLKTtrk")){
     EffLKTTrkIsoData(grae1);
     EffLKTTrkIsoMC(grae2);
   }else if( type.Contains("cEffLKTPTrel")){
     SetEffLKTPt(grae2, grae1);
   }else if( type.Contains("cEffLKTPTtrk")){
     SetEffLKTTrkPt(grae2, grae1);
   }

   SetStyleGraphErrors(grae1, 1, 20, 0, 0.81, ytitle, xtitle, 0.8, 1.02);
   SetStyleGraphErrors(grae2, 2, 21, 0, 0.81, ytitle, xtitle, 0.8, 1.02);
   
   grae2->Draw("AP");
   grae1->Draw("PSame");
   
   SetLegend(grae1, grae2, head, leg1, leg2);
   SetLabel(0.6,0.6,36);
   c->Print(Form("%s.eps",type.Data()));
}  

void drawLKT(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2, TString& leg3, double miny = 0.85, double maxy = 1.02){

   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphErrors *grae1 = new TGraphErrors();
   TGraphErrors *grae2 = new TGraphErrors();
   TGraphErrors *grae3 = new TGraphErrors();

   if( type.Contains("cEffLKTETA")){
     SetEffLKTETA(grae1, grae2, grae3);
   }else if (type.Contains("cEffLKTNCal")){
     SetEffLKTNCal(grae1, grae2, grae3);
   }

   SetStyleGraphErrors(grae1, 2, 20, 0, 0.81, ytitle, xtitle, miny, maxy);
   SetStyleGraphErrors(grae2, 1, 21, 0, 0.81, ytitle, xtitle, miny, maxy);
   SetStyleGraphErrors(grae3, 4, 22, 0, 0.81, ytitle, xtitle, miny, maxy);

   grae1->Draw("AP");
   grae2->Draw("PSame");
   grae3->Draw("PSame");

   if( type.Contains("cEffLKTETA")){
     SetLegend(grae1, grae2, grae3, head, leg1, leg2, leg3,"PL","PL","PL", 0.6,0.20,0.9,0.40);
     SetLabel(0.6,0.48,36);
   }else if( type.Contains("cEffLKTNCal")){
     SetLegend(grae1, grae2, grae3, head, leg1, leg2, leg3,"PL","PL","PL", 0.6,0.58,0.9,0.81);
     SetLabel(0.6,0.88,36);
   }

   c->Print(Form("%s.eps",type.Data()));
}

void drawLKT(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2, TString& leg3, TString & leg4){

   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphErrors *grae1 = new TGraphErrors();
   TGraphErrors *grae2 = new TGraphErrors();
   TGraphErrors *grae3 = new TGraphErrors();
   TGraphErrors *grae4 = new TGraphErrors();

   if( type.Contains("cEffLKTNCal")){
     SetEffLKTNCal(grae1, grae2, grae3, grae4);
   }

   SetStyleGraphErrors(grae1, 2, 20, 0, 0.81, ytitle, xtitle, 0.8, 1.02);
   SetStyleGraphErrors(grae2, 1, 21, 0, 0.81, ytitle, xtitle, 0.8, 1.02);
   SetStyleGraphErrors(grae3, 3, 22, 0, 0.81, ytitle, xtitle, 0.8, 1.02);
   SetStyleGraphErrors(grae4, 4, 23, 0, 0.81, ytitle, xtitle, 0.8, 1.02);

   grae1->Draw("AP");
   grae2->Draw("PSame");
   grae3->Draw("PSame");
   grae4->Draw("PSame");

   SetLegend(grae1, grae2, grae3, grae4, head, leg1, leg2, leg3, leg4,"PL","PL","PL","PL", 0.6, 0.58, 0.9, 0.81);
   SetLabel(0.6,0.88,36);
   c->Print(Form("%s.eps",type.Data()));
}

void drawROC(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2, TString& leg3, TString & leg4){
  TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
  SetStyleCanvas(c);

  TGraphAsymmErrors *grae1ROCdetrel = new TGraphAsymmErrors();
  TGraphAsymmErrors *grae1ROCdettrk = new TGraphAsymmErrors();
  TGraphAsymmErrors *grae1ROCpf = new TGraphAsymmErrors();
  TGraphErrors *grae1ROCLKT = new TGraphErrors();
  
  ROCDetectorRelIsoData(grae1ROCdetrel);
  ROCDetectorTrkIsoData(grae1ROCdettrk);
  ROCParticleIsoData(grae1ROCpf);

  TGraphErrors *graeTbkgData = new TGraphErrors();
  TGraphErrors *graeTsigData = new TGraphErrors();
  EffLKTIsoData(graeTsigData);
  SetDataQCDEffLKT(graeTbkgData);
  grae1ROCLKT = getROC(graeTsigData, graeTbkgData);

  //ROCLKTIsoData(grae1ROCLKT);
 
  //limit trk ROC to 10 points 
  grae1ROCdettrk = getModifiedROC(grae1ROCdettrk, 10);
 
  TGraphAsymmErrors *temp = new TGraphAsymmErrors();
  temp=getTemp(1, 14);
  SetStyleGraphErrors(temp, 2, 23, 0, 0.0,  ytitle, xtitle, 0.77, 1.02);

  SetStyleGraphErrors(grae1ROCdetrel, 2, 23, 0, 0.8,  ytitle, xtitle, 0.8, 1.1);
  SetStyleGraphErrors(grae1ROCdettrk, 3, 22, 0, 0.8, ytitle, xtitle, 0.8, 1.1);
  SetStyleGraphErrors(grae1ROCpf, 4, 20, 0, 0.8, ytitle, xtitle, 0.8, 1.1);
  SetStyleGraphErrors(grae1ROCLKT, 6, 20, 0, 0.8, ytitle, xtitle, 0.8, 1.1);

  //draw error band *****
  grae1ROCdetrel->SetFillColor(2);
  grae1ROCdetrel->SetFillStyle(3001);

  grae1ROCdettrk->SetFillColor(3);
  grae1ROCdettrk->SetFillStyle(3001);

  grae1ROCpf->SetFillColor(4);
  grae1ROCpf->SetFillStyle(3001);
  //end draw error band *****

  temp->Draw("APC");
  grae1ROCdetrel->Draw("3CPSame");
  grae1ROCdettrk->Draw("3CPSame");
  grae1ROCpf->Draw("3CPSame");
  grae1ROCLKT->Draw("PSame");

  SetLegend(grae1ROCpf, grae1ROCdetrel, grae1ROCdettrk, grae1ROCLKT, "Data", leg1, leg2, leg3, leg4, "PL","PL","PL","P",0.6, 0.20, 0.9,0.50);
  SetLabel(0.19,0.88,36);

  c->Print(Form("%s.eps",type.Data()));
}

void plots(){
   //Efficiency for pf
   draw("cEffPFBaseISO", "Isolation Efficiency", "Isolation Threshold", "\I_{PF}",  0.85, 1.01, "T&P Data", "T&P MC");
   draw("cEffDETBaseISOrelLKT", "Isolation Efficiency", "Isolation Threshold", "\I_{comb}^{rel}", 0.85, 1.01, "T&P Data", "T&P MC"); 
   draw("cEffDETBaseISOtrkLKT", "Isolation Efficiency", "Isolation Threshold", "\I_{trk}^{rel}", 0.85, 1.01, "T&P Data", "T&P MC");

   //Efficiency for LKT : caution! it is different style
   //drawLKT("cEffLKTrel", "Isolation Efficiency", "RelIso", "LKT", "Data", "MC");
   //drawLKT("cEffLKTtrk", "Isolation Efficiency", "RelIso", "LKT (track)", "Data", "MC");
   //drawLKT("cEffLKTPTrel", "Isolation Efficiency", "p_{T}", "LKT", "Data", "MC");
   //drawLKT("cEffLKTPTtrk", "Isolation Efficiency", "p_{T}", "LKT (track)", "Data", "MC");
   drawLKT("cEffLKTETA", "Isolation Efficiency", "#eta", "LKT, Z #rightarrow #mu#mu", "MC", "Data", "MC (PU=10)");
   drawLKT("cEffLKTNCal", "Isolation Efficiency", "Number of Active CaloTowers", "LKT", "Z #rightarrow #mu#mu (MC)", "Z #rightarrow #mu#mu (Data)", "t#bar{t} #rightarrow ll (MC)", 0.8, 1.02);

   //Efficiency as a function of pT for PF
   draw("cEffPFBasePT", "Isolation Efficiency", "p_{T} (GeV/c)", "\I_{PF}",  0.5, 1.1, "T&P (Th. 0.12)", "T&P (Th. 0.20)");
   draw("cEffDETBasePTtrk", "Isolation Efficiency", "p_{T} (GeV/c)", "\I_{trk}^{rel}", 0.5, 1.1, "T&P (Th. 0.05)", "T&P (Th. 0.10)", "LKT (Th. 0.10)");
   draw("cEffDETBasePTrel", "Isolation Efficiency", "p_{T} (GeV/c)", "\I_{comb}^{rel}", 0.5, 1.1, "T&P (Th. 0.10)", "T&P (Th. 0.15)", "LKT (Th. 0.15)");

   //ROC for data all
   drawROC("cROCallData","Signal Efficiency","Background Efficiency", "Data", "\I_{PF} (T&P)", "\I_{comb}^{rel} (T&P)", "\I_{trk}^{rel} (T&P)", "\I_{comb}^{rel} (LKT)");
   draw("cROCPFBaseIso", "Signal Efficiency", "Background Efficiency", "\I_{PF}",  0.85, 1.01, "T&P Data", "T&P MC");
   draw("cROCDETBaseIsotrk", "Signal Efficiency", "Background Efficiency", "\I_{trk}^{rel}", 0.85, 1.01, "T&P Data", "T&P MC");
   draw("cROCDETBaseIsorel", "Signal Efficiency", "Background Efficiency", "\I_{comb}^{rel}", 0.85, 1.01, "T&P Data", "T&P MC");

}
