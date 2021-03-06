{
//=========Macro generated from canvas: pt_PLOT_mcTrue_true/
//=========  (Mon Mar 14 04:34:13 2011) by ROOT version5.22/00d
   TCanvas *pt_PLOT_mcTrue_true = new TCanvas("pt_PLOT_mcTrue_true", "",37,49,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   pt_PLOT_mcTrue_true->SetHighLightColor(2);
   pt_PLOT_mcTrue_true->Range(-22.1875,0.3875,159.0625,1.1375);
   pt_PLOT_mcTrue_true->SetFillColor(0);
   pt_PLOT_mcTrue_true->SetBorderMode(0);
   pt_PLOT_mcTrue_true->SetBorderSize(2);
   pt_PLOT_mcTrue_true->SetTickx(1);
   pt_PLOT_mcTrue_true->SetTicky(1);
   pt_PLOT_mcTrue_true->SetLeftMargin(0.15);
   pt_PLOT_mcTrue_true->SetRightMargin(0.05);
   pt_PLOT_mcTrue_true->SetTopMargin(0.05);
   pt_PLOT_mcTrue_true->SetBottomMargin(0.15);
   pt_PLOT_mcTrue_true->SetFrameBorderMode(0);
   pt_PLOT_mcTrue_true->SetFrameFillStyle(0);
   pt_PLOT_mcTrue_true->SetFrameBorderMode(0);
   
   TH1 *frame_242501792 = new TH1D("frame_242501792","mcTrue_true",4,5,150);
   frame_242501792->SetMinimum(0.5);
   frame_242501792->SetMaximum(1.1);
   frame_242501792->SetDirectory(0);
   frame_242501792->SetLineStyle(0);
   frame_242501792->SetMarkerStyle(20);
   frame_242501792->GetXaxis()->SetTitle("Probe p_{T} (GeV/c)");
   frame_242501792->GetXaxis()->SetLabelFont(42);
   frame_242501792->GetXaxis()->SetLabelOffset(0.007);
   frame_242501792->GetXaxis()->SetLabelSize(0.05);
   frame_242501792->GetXaxis()->SetTitleSize(0.06);
   frame_242501792->GetXaxis()->SetTitleOffset(0.9);
   frame_242501792->GetXaxis()->SetTitleFont(42);
   frame_242501792->GetYaxis()->SetTitle("Isolation Efficiency");
   frame_242501792->GetYaxis()->SetLabelFont(42);
   frame_242501792->GetYaxis()->SetLabelOffset(0.007);
   frame_242501792->GetYaxis()->SetLabelSize(0.05);
   frame_242501792->GetYaxis()->SetTitleSize(0.06);
   frame_242501792->GetYaxis()->SetTitleOffset(1.3);
   frame_242501792->GetYaxis()->SetTitleFont(42);
   frame_242501792->GetZaxis()->SetLabelFont(42);
   frame_242501792->GetZaxis()->SetLabelOffset(0.007);
   frame_242501792->GetZaxis()->SetLabelSize(0.05);
   frame_242501792->GetZaxis()->SetTitleSize(0.06);
   frame_242501792->GetZaxis()->SetTitleFont(42);
   frame_242501792->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_cnt_eff");
   grae->SetTitle("");
   grae->SetLineStyle(0);
   grae->SetMarkerStyle(20);
   grae->SetMarkerSize(0);
   grae->SetPoint(0,16.59413,0.8725728);
   grae->SetPointError(0,6.594129,3.405871,0.008799005,0.008326824);
   grae->SetPoint(1,37.96726,0.9694724);
   grae->SetPointError(1,17.96726,12.03274,0.0008121556,0.0007920853);
   grae->SetPoint(2,57.14862,0.9959144);
   grae->SetPointError(2,7.148621,92.85138,0.001103189,0.0008875422);
   
   TH1 *hxy_cnt_eff18 = new TH1F("hxy_cnt_eff18","",100,0,164);
   hxy_cnt_eff18->SetMinimum(0.850471);
   hxy_cnt_eff18->SetMaximum(1.010105);
   hxy_cnt_eff18->SetDirectory(0);
   hxy_cnt_eff18->SetStats(0);
   hxy_cnt_eff18->SetLineStyle(0);
   hxy_cnt_eff18->SetMarkerStyle(20);
   hxy_cnt_eff18->GetXaxis()->SetLabelFont(42);
   hxy_cnt_eff18->GetXaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff18->GetXaxis()->SetLabelSize(0.05);
   hxy_cnt_eff18->GetXaxis()->SetTitleSize(0.06);
   hxy_cnt_eff18->GetXaxis()->SetTitleOffset(0.9);
   hxy_cnt_eff18->GetXaxis()->SetTitleFont(42);
   hxy_cnt_eff18->GetYaxis()->SetLabelFont(42);
   hxy_cnt_eff18->GetYaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff18->GetYaxis()->SetLabelSize(0.05);
   hxy_cnt_eff18->GetYaxis()->SetTitleSize(0.06);
   hxy_cnt_eff18->GetYaxis()->SetTitleOffset(1.3);
   hxy_cnt_eff18->GetYaxis()->SetTitleFont(42);
   hxy_cnt_eff18->GetZaxis()->SetLabelFont(42);
   hxy_cnt_eff18->GetZaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff18->GetZaxis()->SetLabelSize(0.05);
   hxy_cnt_eff18->GetZaxis()->SetTitleSize(0.06);
   hxy_cnt_eff18->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_cnt_eff18);
   
   grae->Draw("p");
   
   TH1 *frame_242501792 = new TH1D("frame_242501792","mcTrue_true",4,5,150);
   frame_242501792->SetMinimum(0.5);
   frame_242501792->SetMaximum(1.1);
   frame_242501792->SetDirectory(0);
   frame_242501792->SetLineStyle(0);
   frame_242501792->SetMarkerStyle(20);
   frame_242501792->GetXaxis()->SetTitle("Probe p_{T} (GeV/c)");
   frame_242501792->GetXaxis()->SetLabelFont(42);
   frame_242501792->GetXaxis()->SetLabelOffset(0.007);
   frame_242501792->GetXaxis()->SetLabelSize(0.05);
   frame_242501792->GetXaxis()->SetTitleSize(0.06);
   frame_242501792->GetXaxis()->SetTitleOffset(0.9);
   frame_242501792->GetXaxis()->SetTitleFont(42);
   frame_242501792->GetYaxis()->SetTitle("Isolation Efficiency");
   frame_242501792->GetYaxis()->SetLabelFont(42);
   frame_242501792->GetYaxis()->SetLabelOffset(0.007);
   frame_242501792->GetYaxis()->SetLabelSize(0.05);
   frame_242501792->GetYaxis()->SetTitleSize(0.06);
   frame_242501792->GetYaxis()->SetTitleOffset(1.3);
   frame_242501792->GetYaxis()->SetTitleFont(42);
   frame_242501792->GetZaxis()->SetLabelFont(42);
   frame_242501792->GetZaxis()->SetLabelOffset(0.007);
   frame_242501792->GetZaxis()->SetLabelSize(0.05);
   frame_242501792->GetZaxis()->SetTitleSize(0.06);
   frame_242501792->GetZaxis()->SetTitleFont(42);
   frame_242501792->Draw("AXISSAME");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_fit_eff");
   grae->SetTitle("");
   grae->SetLineColor(2);
   grae->SetLineStyle(2);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(21);
   grae->SetMarkerSize(0.7);
   grae->SetPoint(0,16.19402,0.8550079);
   grae->SetPointError(0,6.194024,3.805976,0.01516155,0.01471739);
   grae->SetPoint(1,37.66984,0.9710988);
   grae->SetPointError(1,17.66984,12.33016,0.001427511,0.001396034);
   grae->SetPoint(2,61.38315,0.9903164);
   grae->SetPointError(2,11.38315,88.61685,0.00235444,0.00211884);
   
   TH1 *hxy_fit_eff29 = new TH1F("hxy_fit_eff29","",100,0,164);
   hxy_fit_eff29->SetMinimum(0.8245874);
   hxy_fit_eff29->SetMaximum(1.007694);
   hxy_fit_eff29->SetDirectory(0);
   hxy_fit_eff29->SetStats(0);
   hxy_fit_eff29->SetLineStyle(0);
   hxy_fit_eff29->SetMarkerStyle(20);
   hxy_fit_eff29->GetXaxis()->SetLabelFont(42);
   hxy_fit_eff29->GetXaxis()->SetLabelOffset(0.007);
   hxy_fit_eff29->GetXaxis()->SetLabelSize(0.05);
   hxy_fit_eff29->GetXaxis()->SetTitleSize(0.06);
   hxy_fit_eff29->GetXaxis()->SetTitleOffset(0.9);
   hxy_fit_eff29->GetXaxis()->SetTitleFont(42);
   hxy_fit_eff29->GetYaxis()->SetLabelFont(42);
   hxy_fit_eff29->GetYaxis()->SetLabelOffset(0.007);
   hxy_fit_eff29->GetYaxis()->SetLabelSize(0.05);
   hxy_fit_eff29->GetYaxis()->SetTitleSize(0);
   hxy_fit_eff29->GetYaxis()->SetTitleOffset(1.3);
   hxy_fit_eff29->GetYaxis()->SetTitleFont(42);
   hxy_fit_eff29->GetZaxis()->SetLabelFont(42);
   hxy_fit_eff29->GetZaxis()->SetLabelOffset(0.007);
   hxy_fit_eff29->GetZaxis()->SetLabelSize(0.05);
   hxy_fit_eff29->GetZaxis()->SetTitleSize(0.06);
   hxy_fit_eff29->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_fit_eff29);
   
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_cnt_eff");
   grae->SetTitle("");
   grae->SetLineColor(2);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(21);
   grae->SetMarkerSize(0.7);
   grae->SetPoint(0,16.59413,0.8725728);
   grae->SetPointError(0,6.594129,3.405871,0.008799005,0.008326824);
   grae->SetPoint(1,37.96726,0.9694724);
   grae->SetPointError(1,17.96726,12.03274,0.0008121556,0.0007920853);
   grae->SetPoint(2,57.14862,0.9959144);
   grae->SetPointError(2,7.148621,92.85138,0.001103189,0.0008875422);
   
   TH1 *hxy_cnt_eff310 = new TH1F("hxy_cnt_eff310","",100,0,164);
   hxy_cnt_eff310->SetMinimum(0.850471);
   hxy_cnt_eff310->SetMaximum(1.010105);
   hxy_cnt_eff310->SetDirectory(0);
   hxy_cnt_eff310->SetStats(0);
   hxy_cnt_eff310->SetLineStyle(0);
   hxy_cnt_eff310->SetMarkerStyle(20);
   hxy_cnt_eff310->GetXaxis()->SetLabelFont(42);
   hxy_cnt_eff310->GetXaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff310->GetXaxis()->SetLabelSize(0.05);
   hxy_cnt_eff310->GetXaxis()->SetTitleSize(0.06);
   hxy_cnt_eff310->GetXaxis()->SetTitleOffset(0.9);
   hxy_cnt_eff310->GetXaxis()->SetTitleFont(42);
   hxy_cnt_eff310->GetYaxis()->SetLabelFont(42);
   hxy_cnt_eff310->GetYaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff310->GetYaxis()->SetLabelSize(0.05);
   hxy_cnt_eff310->GetYaxis()->SetTitleSize(0);
   hxy_cnt_eff310->GetYaxis()->SetTitleOffset(1.3);
   hxy_cnt_eff310->GetYaxis()->SetTitleFont(42);
   hxy_cnt_eff310->GetZaxis()->SetLabelFont(42);
   hxy_cnt_eff310->GetZaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff310->GetZaxis()->SetLabelSize(0.05);
   hxy_cnt_eff310->GetZaxis()->SetTitleSize(0.06);
   hxy_cnt_eff310->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_cnt_eff310);
   
   grae->Draw("p");
   
   TLegend *leg = new TLegend(0.709799,0.2744755,0.9095477,0.4248252,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hxy_fit_eff","Data","LP");
   entry->SetLineColor(2);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry("hxy_cnt_eff","MC","LP");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.7);
   leg->Draw();
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_fit_eff");
   grae->SetTitle("");
   grae->SetLineColor(3);
   grae->SetLineStyle(2);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(3);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(0.7);
   grae->SetPoint(0,16.19402,0.9068654);
   grae->SetPointError(0,6.194024,3.805976,0.01292569,0.01233659);
   grae->SetPoint(1,37.66984,0.9854774);
   grae->SetPointError(1,17.66984,12.33016,0.001031334,0.001010329);
   grae->SetPoint(2,61.38315,0.9961104);
   grae->SetPointError(2,11.38315,88.61685,0.001630782,0.001380242);
   
   TH1 *hxy_fit_eff411 = new TH1F("hxy_fit_eff411","",100,0,164);
   hxy_fit_eff411->SetMinimum(0.8835846);
   hxy_fit_eff411->SetMaximum(1.007846);
   hxy_fit_eff411->SetDirectory(0);
   hxy_fit_eff411->SetStats(0);
   hxy_fit_eff411->SetLineStyle(0);
   hxy_fit_eff411->SetMarkerStyle(20);
   hxy_fit_eff411->GetXaxis()->SetLabelFont(42);
   hxy_fit_eff411->GetXaxis()->SetLabelOffset(0.007);
   hxy_fit_eff411->GetXaxis()->SetLabelSize(0.05);
   hxy_fit_eff411->GetXaxis()->SetTitleSize(0.06);
   hxy_fit_eff411->GetXaxis()->SetTitleOffset(0.9);
   hxy_fit_eff411->GetXaxis()->SetTitleFont(42);
   hxy_fit_eff411->GetYaxis()->SetLabelFont(42);
   hxy_fit_eff411->GetYaxis()->SetLabelOffset(0.007);
   hxy_fit_eff411->GetYaxis()->SetLabelSize(0.05);
   hxy_fit_eff411->GetYaxis()->SetTitleSize(0);
   hxy_fit_eff411->GetYaxis()->SetTitleOffset(1.3);
   hxy_fit_eff411->GetYaxis()->SetTitleFont(42);
   hxy_fit_eff411->GetZaxis()->SetLabelFont(42);
   hxy_fit_eff411->GetZaxis()->SetLabelOffset(0.007);
   hxy_fit_eff411->GetZaxis()->SetLabelSize(0.05);
   hxy_fit_eff411->GetZaxis()->SetTitleSize(0.06);
   hxy_fit_eff411->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_fit_eff411);
   
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_cnt_eff");
   grae->SetTitle("");
   grae->SetLineColor(3);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(3);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(0.7);
   grae->SetPoint(0,16.59413,0.9186893);
   grae->SetPointError(0,6.594129,3.405871,0.00734214,0.006807351);
   grae->SetPoint(1,37.96726,0.9827052);
   grae->SetPointError(1,17.96726,12.03274,0.0006207707,0.0006000483);
   grae->SetPoint(2,57.14862,0.9978599);
   grae->SetPointError(2,7.148621,92.85138,0.0008624286,0.0006378559);
   
   TH1 *hxy_cnt_eff512 = new TH1F("hxy_cnt_eff512","",100,0,164);
   hxy_cnt_eff512->SetMinimum(0.9026321);
   hxy_cnt_eff512->SetMaximum(1.007213);
   hxy_cnt_eff512->SetDirectory(0);
   hxy_cnt_eff512->SetStats(0);
   hxy_cnt_eff512->SetLineStyle(0);
   hxy_cnt_eff512->SetMarkerStyle(20);
   hxy_cnt_eff512->GetXaxis()->SetLabelFont(42);
   hxy_cnt_eff512->GetXaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff512->GetXaxis()->SetLabelSize(0.05);
   hxy_cnt_eff512->GetXaxis()->SetTitleSize(0.06);
   hxy_cnt_eff512->GetXaxis()->SetTitleOffset(0.9);
   hxy_cnt_eff512->GetXaxis()->SetTitleFont(42);
   hxy_cnt_eff512->GetYaxis()->SetLabelFont(42);
   hxy_cnt_eff512->GetYaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff512->GetYaxis()->SetLabelSize(0.05);
   hxy_cnt_eff512->GetYaxis()->SetTitleSize(0);
   hxy_cnt_eff512->GetYaxis()->SetTitleOffset(1.3);
   hxy_cnt_eff512->GetYaxis()->SetTitleFont(42);
   hxy_cnt_eff512->GetZaxis()->SetLabelFont(42);
   hxy_cnt_eff512->GetZaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff512->GetZaxis()->SetLabelSize(0.05);
   hxy_cnt_eff512->GetZaxis()->SetTitleSize(0.06);
   hxy_cnt_eff512->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_cnt_eff512);
   
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_fit_eff");
   grae->SetTitle("");
   grae->SetLineColor(4);
   grae->SetLineStyle(2);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(4);
   grae->SetMarkerStyle(23);
   grae->SetMarkerSize(0.7);
   grae->SetPoint(0,16.19402,0.9303761);
   grae->SetPointError(0,6.194024,3.805976,0.01139732,0.01078307);
   grae->SetPoint(1,37.66984,0.9857958);
   grae->SetPointError(1,17.66984,12.33016,0.0009703961,0.0009314739);
   grae->SetPoint(2,61.38315,0.9966202);
   grae->SetPointError(2,11.38315,88.61685,0.0001584621,0.0001584621);
   
   TH1 *hxy_fit_eff613 = new TH1F("hxy_fit_eff613","",100,0,164);
   hxy_fit_eff613->SetMinimum(0.9111988);
   hxy_fit_eff613->SetMaximum(1.004559);
   hxy_fit_eff613->SetDirectory(0);
   hxy_fit_eff613->SetStats(0);
   hxy_fit_eff613->SetLineStyle(0);
   hxy_fit_eff613->SetMarkerStyle(20);
   hxy_fit_eff613->GetXaxis()->SetLabelFont(42);
   hxy_fit_eff613->GetXaxis()->SetLabelOffset(0.007);
   hxy_fit_eff613->GetXaxis()->SetLabelSize(0.05);
   hxy_fit_eff613->GetXaxis()->SetTitleSize(0.06);
   hxy_fit_eff613->GetXaxis()->SetTitleOffset(0.9);
   hxy_fit_eff613->GetXaxis()->SetTitleFont(42);
   hxy_fit_eff613->GetYaxis()->SetLabelFont(42);
   hxy_fit_eff613->GetYaxis()->SetLabelOffset(0.007);
   hxy_fit_eff613->GetYaxis()->SetLabelSize(0.05);
   hxy_fit_eff613->GetYaxis()->SetTitleSize(0);
   hxy_fit_eff613->GetYaxis()->SetTitleOffset(1.3);
   hxy_fit_eff613->GetYaxis()->SetTitleFont(42);
   hxy_fit_eff613->GetZaxis()->SetLabelFont(42);
   hxy_fit_eff613->GetZaxis()->SetLabelOffset(0.007);
   hxy_fit_eff613->GetZaxis()->SetLabelSize(0.05);
   hxy_fit_eff613->GetZaxis()->SetTitleSize(0.06);
   hxy_fit_eff613->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_fit_eff613);
   
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("hxy_cnt_eff");
   grae->SetTitle("");
   grae->SetLineColor(4);
   grae->SetLineWidth(2);
   grae->SetMarkerColor(4);
   grae->SetMarkerStyle(23);
   grae->SetMarkerSize(0.7);
   grae->SetPoint(0,16.59413,0.9362864);
   grae->SetPointError(0,6.594129,3.405871,0.006635616,0.006075487);
   grae->SetPoint(1,37.96726,0.9880863);
   grae->SetPointError(1,17.96726,12.03274,0.0005203032,0.0004992769);
   grae->SetPoint(2,57.14862,0.9978599);
   grae->SetPointError(2,7.148621,92.85138,0.0008624286,0.0006378559);
   
   TH1 *hxy_cnt_eff714 = new TH1F("hxy_cnt_eff714","",100,0,164);
   hxy_cnt_eff714->SetMinimum(0.9227661);
   hxy_cnt_eff714->SetMaximum(1.005382);
   hxy_cnt_eff714->SetDirectory(0);
   hxy_cnt_eff714->SetStats(0);
   hxy_cnt_eff714->SetLineStyle(0);
   hxy_cnt_eff714->SetMarkerStyle(20);
   hxy_cnt_eff714->GetXaxis()->SetLabelFont(42);
   hxy_cnt_eff714->GetXaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff714->GetXaxis()->SetLabelSize(0.05);
   hxy_cnt_eff714->GetXaxis()->SetTitleSize(0.06);
   hxy_cnt_eff714->GetXaxis()->SetTitleOffset(0.9);
   hxy_cnt_eff714->GetXaxis()->SetTitleFont(42);
   hxy_cnt_eff714->GetYaxis()->SetLabelFont(42);
   hxy_cnt_eff714->GetYaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff714->GetYaxis()->SetLabelSize(0.05);
   hxy_cnt_eff714->GetYaxis()->SetTitleSize(0);
   hxy_cnt_eff714->GetYaxis()->SetTitleOffset(1.3);
   hxy_cnt_eff714->GetYaxis()->SetTitleFont(42);
   hxy_cnt_eff714->GetZaxis()->SetLabelFont(42);
   hxy_cnt_eff714->GetZaxis()->SetLabelOffset(0.007);
   hxy_cnt_eff714->GetZaxis()->SetLabelSize(0.05);
   hxy_cnt_eff714->GetZaxis()->SetTitleSize(0.06);
   hxy_cnt_eff714->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hxy_cnt_eff714);
   
   grae->Draw("p");
   
   leg = new TLegend(0.4631661,0.1942446,0.5634796,0.4446043,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("hxy_fit_eff","RelComb=0.10","LP");
   entry->SetLineColor(2);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry("hxy_fit_eff","RelComb=0.15 ","LP");
   entry->SetLineColor(3);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry("hxy_fit_eff","TrkRel=0.10","LP");
   entry->SetLineColor(4);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(0.7);
   leg->Draw();
   TLatex *   tex = new TLatex(0.6,0.55,"36.1 pb^{-1} at #sqrt{s} = 7 TeV");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.6,0.5,"#DeltaR=0.3");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   pt_PLOT_mcTrue_true->Modified();
   pt_PLOT_mcTrue_true->cd();
   pt_PLOT_mcTrue_true->SetSelected(pt_PLOT_mcTrue_true);
}
