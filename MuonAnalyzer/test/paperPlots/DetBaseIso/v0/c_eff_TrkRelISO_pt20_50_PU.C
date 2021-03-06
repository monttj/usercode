{
//=========Macro generated from canvas: c_eff_TrkRelISO_pt20_50_PU/c_eff_TrkRelISO_pt20_50_PU
//=========  (Mon Mar 14 02:51:39 2011) by ROOT version5.24/00
   TCanvas *c_eff_TrkRelISO_pt20_50_PU = new TCanvas("c_eff_TrkRelISO_pt20_50_PU", "c_eff_TrkRelISO_pt20_50_PU",4,49,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c_eff_TrkRelISO_pt20_50_PU->Range(0,0,1,1);
   c_eff_TrkRelISO_pt20_50_PU->SetFillColor(0);
   c_eff_TrkRelISO_pt20_50_PU->SetBorderMode(0);
   c_eff_TrkRelISO_pt20_50_PU->SetBorderSize(2);
   c_eff_TrkRelISO_pt20_50_PU->SetTickx(1);
   c_eff_TrkRelISO_pt20_50_PU->SetTicky(1);
   c_eff_TrkRelISO_pt20_50_PU->SetLeftMargin(0.15);
   c_eff_TrkRelISO_pt20_50_PU->SetRightMargin(0.05);
   c_eff_TrkRelISO_pt20_50_PU->SetTopMargin(0.05);
   c_eff_TrkRelISO_pt20_50_PU->SetBottomMargin(0.15);
   c_eff_TrkRelISO_pt20_50_PU->SetFrameFillStyle(0);
   c_eff_TrkRelISO_pt20_50_PU->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(25);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(30);
   grae->SetFillStyle(3001);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(20);
   grae->SetMarkerSize(1.1);
   grae->SetPoint(0,0.01,0.778421);
   grae->SetPointError(0,0,0,0.00325366,0.00324058);
   grae->SetPoint(1,0.02,0.862726);
   grae->SetPointError(1,0,0,0.00271051,0.00267289);
   grae->SetPoint(2,0.03,0.910877);
   grae->SetPointError(2,0,0,0.00225379,0.00222201);
   grae->SetPoint(3,0.04,0.937044);
   grae->SetPointError(3,0,0,0.00192253,0.00189734);
   grae->SetPoint(4,0.05,0.953343);
   grae->SetPointError(4,0,0,0.00167178,0.00165129);
   grae->SetPoint(5,0.06,0.965333);
   grae->SetPointError(5,0,0,0.00145702,0.00143433);
   grae->SetPoint(6,0.07,0.973976);
   grae->SetPointError(6,0,0,0.00128373,0.00124381);
   grae->SetPoint(7,0.08,0.979249);
   grae->SetPointError(7,0,0,0.00114645,0.00112817);
   grae->SetPoint(8,0.09,0.983199);
   grae->SetPointError(8,0,0,0.00104406,0.00101104);
   grae->SetPoint(9,0.1,0.985796);
   grae->SetPointError(9,0,0,0.000970396,0.000931474);
   grae->SetPoint(10,0.11,0.987588);
   grae->SetPointError(10,0,0,0.000903146,0.000868723);
   grae->SetPoint(11,0.12,0.989542);
   grae->SetPointError(11,0,0,0.000835416,0.000800017);
   grae->SetPoint(12,0.13,0.991314);
   grae->SetPointError(12,0,0,0.000768184,0.000734178);
   grae->SetPoint(13,0.14,0.992544);
   grae->SetPointError(13,0,0,0.000715294,0.000681914);
   grae->SetPoint(14,0.15,0.993242);
   grae->SetPointError(14,0,0,0.000683709,0.000650955);
   grae->SetPoint(15,0.16,0.994338);
   grae->SetPointError(15,0,0,0.000635448,0.000601511);
   grae->SetPoint(16,0.17,0.994976);
   grae->SetPointError(16,0,0,0.000600532,0.000566788);
   grae->SetPoint(17,0.18,0.995374);
   grae->SetPointError(17,0,0,0.000577079,0.000543739);
   grae->SetPoint(18,0.19,0.995885);
   grae->SetPointError(18,0,0,0.000548604,0.00051478);
   grae->SetPoint(19,0.2,0.996201);
   grae->SetPointError(19,0,0,0.000529398,0.000494949);
   grae->SetPoint(20,0.21,0.996556);
   grae->SetPointError(20,0,0,0.000505851,0.000471443);
   grae->SetPoint(21,0.22,0.996599);
   grae->SetPointError(21,0,0,0.000499483,0.000464857);
   grae->SetPoint(22,0.23,0.996884);
   grae->SetPointError(22,0,0,0.000484966,0.000447823);
   grae->SetPoint(23,0.24,0.997219);
   grae->SetPointError(23,0,0,0.000460972,0.000425143);
   grae->SetPoint(24,0.25,0.997368);
   grae->SetPointError(24,0,0,0.000447419,0.00041168);
   
   TH1 *Graph1 = new TH1F("Graph1","",100,0,0.274);
   Graph1->SetMinimum(0.7529061);
   Graph1->SetMaximum(1.020041);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->SetLineStyle(0);
   Graph1->SetMarkerStyle(20);
   Graph1->GetXaxis()->SetTitle("TrkRelIso");
   Graph1->GetXaxis()->SetLabelFont(42);
   Graph1->GetXaxis()->SetLabelOffset(0.007);
   Graph1->GetXaxis()->SetLabelSize(0.05);
   Graph1->GetXaxis()->SetTitleSize(0.06);
   Graph1->GetXaxis()->SetTitleOffset(0.9);
   Graph1->GetXaxis()->SetTitleFont(42);
   Graph1->GetYaxis()->SetTitle("Isolation Efficiency");
   Graph1->GetYaxis()->SetLabelFont(42);
   Graph1->GetYaxis()->SetLabelOffset(0.007);
   Graph1->GetYaxis()->SetLabelSize(0.05);
   Graph1->GetYaxis()->SetTitleSize(0.06);
   Graph1->GetYaxis()->SetTitleOffset(1.3);
   Graph1->GetYaxis()->SetTitleFont(42);
   Graph1->GetZaxis()->SetLabelFont(42);
   Graph1->GetZaxis()->SetLabelOffset(0.007);
   Graph1->GetZaxis()->SetLabelSize(0.05);
   Graph1->GetZaxis()->SetTitleSize(0.06);
   Graph1->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph1);
   
   grae->Draw("acp");
   
   grae = new TGraphAsymmErrors(25);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(5);
   grae->SetFillStyle(3001);
   grae->SetLineColor(2);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(21);
   grae->SetMarkerSize(1.1);
   grae->SetPoint(0,0.01,0.784021);
   grae->SetPointError(0,0,0,0.00271844,0.00270202);
   grae->SetPoint(1,0.02,0.869416);
   grae->SetPointError(1,0,0,0.0022299,0.00220854);
   grae->SetPoint(2,0.03,0.917291);
   grae->SetPointError(2,0,0,0.00182625,0.00180212);
   grae->SetPoint(3,0.04,0.944543);
   grae->SetPointError(3,0,0,0.00152034,0.00149463);
   grae->SetPoint(4,0.05,0.959837);
   grae->SetPointError(4,0,0,0.00130657,0.00127997);
   grae->SetPoint(5,0.06,0.970885);
   grae->SetPointError(5,0,0,0.00112111,0.00109387);
   grae->SetPoint(6,0.07,0.978294);
   grae->SetPointError(6,0,0,0.000973786,0.000946115);
   grae->SetPoint(7,0.08,0.982713);
   grae->SetPointError(7,0,0,0.000872622,0.000844692);
   grae->SetPoint(8,0.09,0.986136);
   grae->SetPointError(8,0,0,0.000784424,0.000756294);
   grae->SetPoint(9,0.1,0.988692);
   grae->SetPointError(9,0,0,0.000710823,0.000682542);
   grae->SetPoint(10,0.11,0.990512);
   grae->SetPointError(10,0,0,0.000653004,0.000624615);
   grae->SetPoint(11,0.12,0.991941);
   grae->SetPointError(11,0,0,0.000603431,0.000574956);
   grae->SetPoint(12,0.13,0.992938);
   grae->SetPointError(12,0,0,0.000566155,0.000537618);
   grae->SetPoint(13,0.14,0.993718);
   grae->SetPointError(13,0,0,0.000535064,0.000506479);
   grae->SetPoint(14,0.15,0.994064);
   grae->SetPointError(14,0,0,0.000520616,0.00049201);
   grae->SetPoint(15,0.16,0.994454);
   grae->SetPointError(15,0,0,0.00050384,0.000475207);
   grae->SetPoint(16,0.17,0.995018);
   grae->SetPointError(16,0,0,0.000478511,0.000449842);
   grae->SetPoint(17,0.18,0.995451);
   grae->SetPointError(17,0,0,0.000458022,0.000429325);
   grae->SetPoint(18,0.19,0.995754);
   grae->SetPointError(18,0,0,0.000443086,0.000414368);
   grae->SetPoint(19,0.2,0.995971);
   grae->SetPointError(19,0,0,0.000432084,0.000403351);
   grae->SetPoint(20,0.21,0.996101);
   grae->SetPointError(20,0,0,0.000425339,0.000396597);
   grae->SetPoint(21,0.22,0.996274);
   grae->SetPointError(21,0,0,0.000416167,0.000387413);
   grae->SetPoint(22,0.23,0.996534);
   grae->SetPointError(22,0,0,0.000401996,0.000373221);
   grae->SetPoint(23,0.24,0.996707);
   grae->SetPointError(23,0,0,0.000392248,0.000363462);
   grae->SetPoint(24,0.25,0.997011);
   grae->SetPointError(24,0,0,0.000374547,0.000345736);
   grae->Draw("cp");
   
   TLegend *leg = new TLegend(0,0,7.90505e-322,5.533535e-322,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","p_{T}=20-50 GeV","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","Data","PL");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("","MC(PU)","PL");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c_eff_TrkRelISO_pt20_50_PU->Modified();
   c_eff_TrkRelISO_pt20_50_PU->cd();
   c_eff_TrkRelISO_pt20_50_PU->SetSelected(c_eff_TrkRelISO_pt20_50_PU);
}
