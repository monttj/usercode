#include "muStyle.h"
#include "ParticleBasedIso/c_ROCtnp_QCD_MC_pt20_50_PU.h"
#include "ParticleBasedIso/c_eff_QCD_MC_pt20_50_PU.h"
#include "ParticleBasedIso/c_eff_pt_PFIso.h"
#include "DetBaseIso/ROCtnp_RelComb_pt20_50.h"
#include "DetBaseIso/ROCtnp_TrkRelISO_pt20_50.h"
#include "DetBaseIso/Eff_RelComb_pt20_50.h"
#include "DetBaseIso/Eff_TrkRelISO_pt20_50.h"
#include "DetBaseIso/c_eff_pt_DetIso_Effs_PtBinned_NEW.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsIsoCut.h"
#include "LKT_PLOTS/muonsFromZ_trkRel_EfficVsIsoCut.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsPt.h"
#include "LKT_PLOTS/muonsFromZ_trkRel_EfficVsPt.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsEta.h"
#include "LKT_PLOTS/c_ROC_LKT_RelComb_DATAblack_MCWITHPUred.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsNCaloTowers.h"
#include "LKT_PLOTS/efficienciesData.h"

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
     ROCLKTIsoData(grae1LKTdata);
     TGraphErrors *graeTbkg = new TGraphErrors();
     TGraphErrors *graeTsig = new TGraphErrors();
     EffLKTIsoMC(graeTsig);
     SetDataQCDEffLKT(graeTbkg);
     grae1LKTmc = getROC(graeTsig, graeTbkg);
   }else if ( type.Contains("cROCDETBaseIsotrk")){
     ROCDetectorTrkIsoData(grae1data);
     ROCDetectorTrkIsoMC(grae1mc);
   }

   SetStyleGraphErrors(grae1data, datacolor1, 20, 0, 0.0, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae2data, datacolor2, 20, 0, 0.0, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae1mc, 2, 21, 0, 0.0, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae1LKTdata, 4, 24, 0, 1.2, ytitle, xtitle, min, max);
   SetStyleGraphErrors(grae1LKTmc, 6, 20, 0, 1.2, ytitle, xtitle, min, max);

   //ISO draw
   if( type.Contains("cEffPFBaseISO") ){
     grae1data->Draw("APC");
     grae1mc->Draw("PCSame");
     SetLegend(grae1data, grae1mc, head, leg1, leg2, "PL", "PL");
   }else if ( type.Contains("cEffDETBaseISO") ) {
     grae1data->Draw("APC");
     grae1mc->Draw("PCSame");
     grae1LKTdata->Draw("PSame");
     grae1LKTmc->Draw("PSame");
     clearXErrorBar(grae1LKTdata);
     clearXErrorBar(grae1LKTmc);
     SetLegend(grae1data, grae1mc, grae1LKTdata, grae1LKTmc, head, leg1, leg2, "LKT Data", "LKT MC", "PL","PL","P","P");
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
     SetLegend(grae1data, grae1mc, grae1LKTdata, grae1LKTmc, head, leg1, leg2, "LKT Data", "LKT MC", "PL","PL","P","P");
   }

   c->Print(Form("%s.eps",type.Data()));

   //SF draw
   if (type.Contains("cEffPFBasePT") || type.Contains("cEffDETBasePT") ){ 
     TCanvas *c_sf = new TCanvas(Form("%sSF",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
     SetStyleCanvas(c_sf);

     min = 0.75;
     max = 1.2;
     SetStyleGraphErrors(grae1sf, 2, 20, 0, 0.0, "Data/MC", xtitle, min, max);
     SetStyleGraphErrors(grae2sf, 4, 20, 0, 0.0, "Data/MC", xtitle, min, max);
     SetStyleGraphErrors(grae1LKTsf, 4, 24, 0, 1.2, "Data/MC", xtitle, min, max);

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
     c_sf->Print(Form("%sSF.eps",type.Data()));
   }

   if ( type.Contains("cEffPFBaseISO") || type.Contains("cEffDETBaseISO") ){
     TCanvas *c_sf = new TCanvas(Form("%sSF",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
     SetStyleCanvas(c_sf);
     min = 0.93;
     max = 1.07;
     SetStyleGraphErrors(grae1sf, 2, 20, 0, 0.0, "Data/MC", xtitle, min, max);
     SetStyleGraphErrors(grae1LKTsf, 4, 24, 0, 1.2, "Data/MC", xtitle, min, max);

     if( type.Contains("cEffPFBaseISO") ){
       grae1sf->Draw("AP");
       SetLegend(grae1sf, head, "T&P",  "PL");
     }else if( type.Contains("cEffDETBaseISO") ){
       grae1sf->Draw("APSame");
       grae1LKTsf->Draw("PSame");
       SetLegend(grae1sf, grae1LKTsf, head, "T&P", "LKT", "PL", "P");
     }

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
   c->Print(Form("%s.eps",type.Data()));
}  

void drawLKT(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2, TString& leg3){

   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphErrors *grae1 = new TGraphErrors();
   TGraphErrors *grae2 = new TGraphErrors();
   TGraphErrors *grae3 = new TGraphErrors();

   if( type.Contains("cEffLKTETA")){
     SetEffLKTETA(grae1, grae2, grae3);
   }

   SetStyleGraphErrors(grae1, 2, 20, 0, 0.81, ytitle, xtitle, 0.85, 1.02);
   SetStyleGraphErrors(grae2, 1, 21, 0, 0.81, ytitle, xtitle, 0.85, 1.02);
   SetStyleGraphErrors(grae3, 3, 22, 0, 0.81, ytitle, xtitle, 0.85, 1.02);

   grae1->Draw("AP");
   grae2->Draw("PSame");
   grae3->Draw("PSame");

   SetLegend(grae1, grae2, grae3, head, leg1, leg2, leg3);
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

   SetLegend(grae1, grae2, grae3, grae4, head, leg1, leg2, leg3, leg4);
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
  ROCLKTIsoData(grae1ROCLKT);

  TGraphAsymmErrors *temp = new TGraphAsymmErrors();
  temp=getTemp(1, 17);
  SetStyleGraphErrors(temp, 2, 23, 0, 0.0,  ytitle, xtitle, 0.8, 1.02);

  SetStyleGraphErrors(grae1ROCdetrel, 2, 23, 0, 0.0,  ytitle, xtitle, 0.8, 1.02);
  SetStyleGraphErrors(grae1ROCdettrk, 3, 22, 0, 0.0, ytitle, xtitle, 0.8, 1.02);
  SetStyleGraphErrors(grae1ROCpf, 4, 20, 0, 0.0, ytitle, xtitle, 0.8, 1.02);
  SetStyleGraphErrors(grae1ROCLKT, 6, 20, 0, 1.1, ytitle, xtitle, 0.8, 1.02);

  temp->Draw("APC");
  grae1ROCdetrel->Draw("PCSame");
  grae1ROCdettrk->Draw("PCSame");
  grae1ROCpf->Draw("PCSame");
  grae1ROCLKT->Draw("PSame");

  SetLegend(grae1ROCpf, grae1ROCdetrel, grae1ROCdettrk, grae1ROCLKT, "Data", leg1, leg2, leg3, leg4, "PL","PL","PL","P");

  c->Print(Form("%s.eps",type.Data()));
}

void plots(){
   //Efficiency for pf
   draw("cEffPFBaseISO", "Isolation Efficiency", "Isolation Threshold", "PF iso",  0.85, 1.01, "T&P Data", "T&P MC");
   draw("cEffDETBaseISOrelLKT", "Isolation Efficiency", "Isolation Threshold", "Det iso (trk+calo)", 0.85, 1.01, "T&P Data", "T&P MC"); 
   draw("cEffDETBaseISOtrkLKT", "Isolation Efficiency", "Isolation Threshold", "Det iso (trk-only)", 0.85, 1.01, "T&P Data", "T&P MC");

   //Efficiency for LKT : caution! it is different style
   //drawLKT("cEffLKTrel", "Isolation Efficiency", "RelIso", "LKT", "Data", "MC");
   //drawLKT("cEffLKTtrk", "Isolation Efficiency", "RelIso", "LKT (track)", "Data", "MC");
   //drawLKT("cEffLKTPTrel", "Isolation Efficiency", "p_{T}", "LKT", "Data", "MC");
   //drawLKT("cEffLKTPTtrk", "Isolation Efficiency", "p_{T}", "LKT (track)", "Data", "MC");
   //drawLKT("cEffLKTETA", "Isolation Efficiency", "#eta", "LKT", "MC (PU=0)", "Data (PU=0)", "MC (PU=10)");
   //drawLKT("cEffLKTNCal", "Isolation Efficiency (PV=1)", "Number of Active CaloTowers", "LKT", "Z #rightarrow #mu#mu", "Data", "t#bar{t} #rightarrow ll", "SUSY LM0");

   //Efficiency as a function of pT for PF
   draw("cEffPFBasePT", "Isolation Efficiency", "p_{T} (GeV/c)", "PF iso",  0.5, 1.05, "T&P (Th. 0.12)", "T&P (Th. 0.20)");
   draw("cEffDETBasePTtrk", "Isolation Efficiency", "p_{T} (GeV/c)", "Det iso (trk-only)", 0.5, 1.05, "T&P (Th. 0.05)", "T&P (Th. 0.10)", "LKT (Th. 0.10)");
   draw("cEffDETBasePTrel", "Isolation Efficiency", "p_{T} (GeV/c)", "Det iso (trk+calo)", 0.5, 1.05, "T&P (Th. 0.10)", "T&P (Th. 0.15)", "LKT (Th. 0.15)");

   //ROC for data all
   drawROC("cROCallData","Signal Efficiency","Enhanced QCD Efficiency", "Data", "pflow (T&P)", "trk+calo (T&P)", "trk-only (T&P)", "trk+calo (LKT)");
   draw("cROCPFBaseIso", "Signal Efficiency", "Enhanced QCD Efficiency", "PF iso",  0.85, 1.01, "T&P Data", "T&P MC");
   draw("cROCDETBaseIsotrk", "Signal Efficiency", "Enhanced QCD Efficiency", "Det iso (trk-only)", 0.85, 1.01, "T&P Data", "T&P MC");
   draw("cROCDETBaseIsorel", "Signal Efficiency", "Enhanced QCD Efficiency", "Det iso (trk+calo)", 0.85, 1.01, "T&P Data", "T&P MC");

}
