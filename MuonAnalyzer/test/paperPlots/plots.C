#include "muStyle.h"
#include "ParticleBasedIso/c_ROCtnp_QCD_MC_pt20_50_PU.h"
#include "ParticleBasedIso/c_eff_QCD_MC_pt20_50_PU.h"
#include "ParticleBasedIso/c_eff_pt_isIso.h"
#include "DetBaseIso/c_ROCtnp_RelComb_pt20_50_PU.h"
#include "DetBaseIso/c_ROCtnp_TrkRelISO_pt20_50_PU.h"
#include "DetBaseIso/c_eff_RelComb_pt20_50_PU.h"
#include "DetBaseIso/c_eff_TrkRelISO_pt20_50_PU.h"
#include "DetBaseIso/c_eff_pt_DetectorIso.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsIsoCut.h"
#include "LKT_PLOTS/muonsFromZ_trkRel_EfficVsIsoCut.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsPt.h"
#include "LKT_PLOTS/muonsFromZ_trkRel_EfficVsPt.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsEta.h"
#include "LKT_PLOTS/c_ROC_LKT_RelComb_DATAblack_MCWITHPUred.h"
#include "LKT_PLOTS/muonsFromZ_combinedRelative_EfficVsNCaloTowers.h"

void draw(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2){
   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphAsymmErrors *grae1 = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae2 = new TGraphAsymmErrors();

   if( type.Contains("cEffPFBaseIso") ){
     EffParticleIsoData(grae1);
     EffParticleIsoMC(grae2);
   }else if ( type.Contains("cEffDETBaseIsorel")){
     EffDetectorRelIsoData(grae1);
     EffDetectorRelIsoMC(grae2);
   }else if ( type.Contains("cEffDETBaseIsotrk")){
     EffDetectorTrkIsoData(grae1);
     EffDetectorTrkIsoMC(grae2);
   }

   SetStyleGraphErrors(grae1, 1, 20, 0, 1.1, ytitle, xtitle, 0.8, 1.02);
   SetStyleGraphErrors(grae2, 2, 21, 0, 1.1, ytitle, xtitle, 0.8, 1.02);

   grae1->Draw("APC");
   grae2->Draw("PCSame");

   SetLegend(grae1, grae2, head, leg1, leg2);
   c->Print(Form("%s.pdf",type.Data()));
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
   c->Print(Form("%s.pdf",type.Data()));
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
   c->Print(Form("%s.pdf",type.Data()));
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
   c->Print(Form("%s.pdf",type.Data()));
}

void draw(TString& type, TString& ytitle, TString& xtitle, TString& head, TString &leg1, TString& leg2, TString& leg3){
   TCanvas *c = new TCanvas(Form("%s",type.Data()), Form("%s",type.Data()) ,5,49,400,400);
   SetStyleCanvas(c);

   TGraphAsymmErrors *grae1data = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae2data = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae3data = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae1mc = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae2mc = new TGraphAsymmErrors();
   TGraphAsymmErrors *grae3mc = new TGraphAsymmErrors();

   if( type.Contains("cEffPFBasePT") ){
     SetEffPFPt(grae1data, grae1mc);
     SetEffPFPt2(grae2data, grae2mc);
     SetEffPFPt3(grae3data, grae3mc);
   }else if( type.Contains("cEffDETBasePT") ){
     SetEffDetPt(grae1data, grae1mc);
     SetEffDetPt2(grae2data, grae2mc);
     SetEffDetPt3(grae3data, grae3mc);
   }

   SetStyleGraphErrors(grae1data, 2, 20, 2, 1.1, ytitle, xtitle, 0.5, 1.02);
   SetStyleGraphErrors(grae2data, 3, 22, 2, 1.1, ytitle, xtitle, 0.5, 1.02);
   SetStyleGraphErrors(grae3data, 4, 23, 2, 1.1, ytitle, xtitle, 0.5, 1.02);

   SetStyleGraphErrors(grae1mc, 2, 20, 1, 1.1, ytitle, xtitle, 0.5, 1.02);
   SetStyleGraphErrors(grae2mc, 3, 22, 1, 1.1, ytitle, xtitle, 0.5, 1.02);
   SetStyleGraphErrors(grae3mc, 4, 23, 1, 1.1, ytitle, xtitle, 0.5, 1.02);

   grae1data->Draw("AP");
   grae2data->Draw("PSame");
   grae3data->Draw("PSame");
   grae1mc->Draw("PSame");
   grae2mc->Draw("PSame");
   grae3mc->Draw("PSame");

   SetLegend(grae1data, grae2data, grae3data, head, leg1, leg2, leg3);
   c->Print(Form("%s.pdf",type.Data()));
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

  SetStyleGraphErrors(grae1ROCdetrel, 2, 23, 0, 1.1,  ytitle, xtitle, 0.8, 1.02);
  SetStyleGraphErrors(grae1ROCdettrk, 3, 22, 0, 1.1, ytitle, xtitle, 0.8, 1.02);
  SetStyleGraphErrors(grae1ROCpf, 4, 20, 0, 1.1, ytitle, xtitle, 0.8, 1.02);
  SetStyleGraphErrors(grae1ROCLKT, 6, 24, 0, 1.1, ytitle, xtitle, 0.8, 1.02);

  grae1ROCdetrel->Draw("APC");
  grae1ROCdettrk->Draw("PCSame");
  grae1ROCpf->Draw("PCSame");
  grae1ROCLKT->Draw("PSame");

  SetLegend(grae1ROCpf, grae1ROCdetrel, grae1ROCdettrk, grae1ROCLKT, "Data", "PF Iso", "Det Iso", "Det Iso (track)", "LKT");

  c->Print(Form("%s.pdf",type.Data()));
}

void plots(){
   //Efficiency for pf
   draw("cEffPFBaseIso", "Isolation Efficiency", "RelIso", "PF Iso", "Data", "MC");
   //Efficiency for detrel
   draw("cEffDETBaseIsorel", "Isolation Efficiency", "RelIso", "Det Iso", "Data", "MC"); 
   //Efficiency for dettrk
   draw("cEffDETBaseIsotrk", "Isolation Efficiency", "RelIso", "Det Iso (track)", "Data", "MC");
   //Efficiency for LKT : caution! it is different style
   drawLKT("cEffLKTrel", "Isolation Efficiency", "RelIso", "LKT", "Data", "MC");
   drawLKT("cEffLKTtrk", "Isolation Efficiency", "RelIso", "LKT (track)", "Data", "MC");
   drawLKT("cEffLKTPTrel", "Isolation Efficiency", "p_{T}", "LKT", "Data", "MC");
   drawLKT("cEffLKTPTtrk", "Isolation Efficiency", "p_{T}", "LKT (track)", "Data", "MC");
   drawLKT("cEffLKTETA", "Isolation Efficiency", "#eta", "LKT", "MC (PU=0)", "Data (PU=0)", "MC (PU=10)");
   drawLKT("cEffLKTNCal", "Isolation Efficiency (PV=1)", "Number of Active CaloTowers", "LKT", "Z #rightarrow #mu#mu", "Data", "t#bar{t} #rightarrow ll", "SUSY LM0");

   //Efficiency as a function of pT for PF
   draw("cEffPFBasePT", "Isolation Efficiency", "p_{T}", "PF Iso", "iso 0.12", "iso 0.16", "iso 0.20");

   //Efficiency as a function of pT for Det
   draw("cEffDETBasePT", "Isolation Efficiency", "p_{T}", "Det Iso", "iso 0.10", "iso 0.15", "iso 0.10 (track)");

   //ROC for data all
   drawROC("cROCallData","Signal Efficiency","Enhanced QCD Efficiency", "Data", "PF Iso", "Det Iso", "Det Iso (track)", "LKT");

}
