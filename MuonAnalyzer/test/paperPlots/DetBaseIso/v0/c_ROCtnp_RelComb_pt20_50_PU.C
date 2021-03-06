{
//=========Macro generated from canvas: c_RelComb_pt20_50_PU/c_RelComb_pt20_50_PU
//=========  (Mon Mar 14 02:45:21 2011) by ROOT version5.24/00
   TCanvas *c_RelComb_pt20_50_PU = new TCanvas("c_RelComb_pt20_50_PU", "c_RelComb_pt20_50_PU",0,0,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c_RelComb_pt20_50_PU->Range(0,0,1,1);
   c_RelComb_pt20_50_PU->SetFillColor(0);
   c_RelComb_pt20_50_PU->SetBorderMode(0);
   c_RelComb_pt20_50_PU->SetBorderSize(2);
   c_RelComb_pt20_50_PU->SetTickx(1);
   c_RelComb_pt20_50_PU->SetTicky(1);
   c_RelComb_pt20_50_PU->SetLeftMargin(0.15);
   c_RelComb_pt20_50_PU->SetRightMargin(0.05);
   c_RelComb_pt20_50_PU->SetTopMargin(0.05);
   c_RelComb_pt20_50_PU->SetBottomMargin(0.15);
   c_RelComb_pt20_50_PU->SetFrameFillStyle(0);
   c_RelComb_pt20_50_PU->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(21);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(30);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(20);
   grae->SetMarkerSize(1.1);
   grae->SetPoint(0,0.02636996,0.901919);
   grae->SetPointError(0,0.0003203249,0.0003203249,0.00240135,0.0023769);
   grae->SetPoint(1,0.03081359,0.928325);
   grae->SetPointError(1,0.0003462638,0.0003462638,0.00210521,0.00207806);
   grae->SetPoint(2,0.03546345,0.94548);
   grae->SetPointError(2,0.0003714723,0.0003714723,0.00188282,0.00185405);
   grae->SetPoint(3,0.04035456,0.957141);
   grae->SetPointError(3,0.0003962619,0.0003962619,0.00169914,0.00166925);
   grae->SetPoint(4,0.04561532,0.965629);
   grae->SetPointError(4,0.0004212999,0.0004212999,0.0015447,0.00151399);
   grae->SetPoint(5,0.05110176,0.971099);
   grae->SetPointError(5,0.0004459169,0.0004459169,0.00142751,0.00139603);
   grae->SetPoint(6,0.05675553,0.975753);
   grae->SetPointError(6,0.0004699374,0.0004699374,0.00131406,0.00129633);
   grae->SetPoint(7,0.06273225,0.978832);
   grae->SetPointError(7,0.0004940619,0.0004940619,0.0012325,0.00121377);
   grae->SetPoint(8,0.06898135,0.981643);
   grae->SetPointError(8,0.000518086,0.000518086,0.00115881,0.00112612);
   grae->SetPoint(9,0.07582968,0.983814);
   grae->SetPointError(9,0.0005431948,0.0005431948,0.00108525,0.00106498);
   grae->SetPoint(10,0.08293482,0.985477);
   grae->SetPointError(10,0.0005680734,0.0005680734,0.00103133,0.00101033);
   grae->SetPoint(11,0.09004774,0.987115);
   grae->SetPointError(11,0.0005919328,0.0005919328,0.000973877,0.000952276);
   grae->SetPoint(12,0.0971879,0.988754);
   grae->SetPointError(12,0.0006149532,0.0006149532,0.00092122,0.000899087);
   grae->SetPoint(13,0.1046471,0.990028);
   grae->SetPointError(13,0.000638116,0.000638116,0.000874784,0.000852298);
   grae->SetPoint(14,0.1123165,0.991348);
   grae->SetPointError(14,0.0006610856,0.0006610856,0.000832437,0.000809693);
   grae->SetPoint(15,0.120196,0.992291);
   grae->SetPointError(15,0.0006838816,0.0006838816,0.000792045,0.000768953);
   grae->SetPoint(16,0.1282038,0.992938);
   grae->SetPointError(16,0.0007062956,0.0007062956,0.00076249,0.000739049);
   grae->SetPoint(17,0.1365697,0.993716);
   grae->SetPointError(17,0.0007289758,0.0007289758,0.000727638,0.000702733);
   grae->SetPoint(18,0.1453519,0.994106);
   grae->SetPointError(18,0.0007520493,0.0007520493,0.000705616,0.000680673);
   grae->SetPoint(19,0.1542781,0.994225);
   grae->SetPointError(19,0.0007747972,0.0007747972,0.000696161,0.000671061);
   grae->SetPoint(20,0.1630058,0.994649);
   grae->SetPointError(20,0.0007964114,0.0007964114,0.000669462,0.000640238);
   
   TH1 *Graph2 = new TH1F("Graph2","",100,0.01227438,0.1775775);
   Graph2->SetMinimum(0.8899405);
   Graph2->SetMaximum(1.004866);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   Graph2->SetLineStyle(0);
   Graph2->SetMarkerStyle(20);
   Graph2->GetXaxis()->SetTitle("QCD Efficiency");
   Graph2->GetXaxis()->SetLabelFont(42);
   Graph2->GetXaxis()->SetLabelOffset(0.007);
   Graph2->GetXaxis()->SetLabelSize(0.05);
   Graph2->GetXaxis()->SetTitleSize(0.06);
   Graph2->GetXaxis()->SetTitleOffset(0.9);
   Graph2->GetXaxis()->SetTitleFont(42);
   Graph2->GetYaxis()->SetTitle("Signal Efficiency");
   Graph2->GetYaxis()->SetLabelFont(42);
   Graph2->GetYaxis()->SetLabelOffset(0.007);
   Graph2->GetYaxis()->SetLabelSize(0.05);
   Graph2->GetYaxis()->SetTitleSize(0.06);
   Graph2->GetYaxis()->SetTitleOffset(1.3);
   Graph2->GetYaxis()->SetTitleFont(42);
   Graph2->GetZaxis()->SetLabelFont(42);
   Graph2->GetZaxis()->SetLabelOffset(0.007);
   Graph2->GetZaxis()->SetLabelSize(0.05);
   Graph2->GetZaxis()->SetTitleSize(0.06);
   Graph2->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph2);
   
   grae->Draw("acp");
   
   grae = new TGraphAsymmErrors(21);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(5);
   grae->SetFillStyle(3001);
   grae->SetLineColor(2);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(21);
   grae->SetMarkerSize(1.1);
   grae->SetPoint(0,0.02636996,0.90038);
   grae->SetPointError(0,0.0003203249,0.0003203249,0.00216066,0.00213323);
   grae->SetPoint(1,0.03081359,0.924964);
   grae->SetPointError(1,0.0003462638,0.0003462638,0.00190316,0.00187404);
   grae->SetPoint(2,0.03546345,0.940618);
   grae->SetPointError(2,0.0003714723,0.0003714723,0.00170938,0.00167919);
   grae->SetPoint(3,0.04035456,0.953398);
   grae->SetPointError(3,0.0003962619,0.0003962619,0.00152667,0.0014956);
   grae->SetPoint(4,0.04561532,0.961096);
   grae->SetPointError(4,0.0004212999,0.0004212999,0.00140208,0.00137049);
   grae->SetPoint(5,0.05110176,0.967614);
   grae->SetPointError(5,0.0004459169,0.0004459169,0.00128517,0.00125313);
   grae->SetPoint(6,0.05675553,0.972285);
   grae->SetPointError(6,0.0004699374,0.0004699374,0.00119312,0.00116076);
   grae->SetPoint(7,0.06273225,0.975775);
   grae->SetPointError(7,0.0004940619,0.0004940619,0.00111865,0.00108605);
   grae->SetPoint(8,0.06898135,0.978803);
   grae->SetPointError(8,0.000518086,0.000518086,0.00104919,0.00101638);
   grae->SetPoint(9,0.07582968,0.980959);
   grae->SetPointError(9,0.0005431948,0.0005431948,0.000996454,0.000963488);
   grae->SetPoint(10,0.08293482,0.982447);
   grae->SetPointError(10,0.0005680734,0.0005680734,0.000958162,0.000925095);
   grae->SetPoint(11,0.09004774,0.983576);
   grae->SetPointError(11,0.0005919328,0.0005919328,0.000927956,0.000894809);
   grae->SetPoint(12,0.0971879,0.984859);
   grae->SetPointError(12,0.0006149532,0.0006149532,0.000892272,0.000859036);
   grae->SetPoint(13,0.1046471,0.985835);
   grae->SetPointError(13,0.000638116,0.000638116,0.000864079,0.000830775);
   grae->SetPoint(14,0.1123165,0.986656);
   grae->SetPointError(14,0.0006610856,0.0006610856,0.000839541,0.000806179);
   grae->SetPoint(15,0.120196,0.987785);
   grae->SetPointError(15,0.0006838816,0.0006838816,0.00080448,0.000771038);
   grae->SetPoint(16,0.1282038,0.988606);
   grae->SetPointError(16,0.0007062956,0.0007062956,0.00077791,0.000744412);
   grae->SetPoint(17,0.1365697,0.989479);
   grae->SetPointError(17,0.0007289758,0.0007289758,0.000748571,0.000715009);
   grae->SetPoint(18,0.1453519,0.990351);
   grae->SetPointError(18,0.0007520493,0.0007520493,0.000717945,0.000684323);
   grae->SetPoint(19,0.1542781,0.990505);
   grae->SetPointError(19,0.0007747972,0.0007747972,0.000712395,0.000678761);
   grae->SetPoint(20,0.1630058,0.991121);
   grae->SetPointError(20,0.0007964114,0.0007964114,0.000689717,0.000656039);
   grae->Draw("cp");
   
   TLegend *leg = new TLegend(1.700906e-316,1.688874e-316,0,6.373447e-322,NULL,"brNDC");
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
   entry=leg->AddEntry("","MC (PU)","PL");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c_RelComb_pt20_50_PU->Modified();
   c_RelComb_pt20_50_PU->cd();
   c_RelComb_pt20_50_PU->SetSelected(c_RelComb_pt20_50_PU);
}
