#include "tdrstyle.C"
#include "PlotStyles.C"
#include "plotTimeReturnTGraphAsymmErrors.C"
#include "plotTimeReturnTGraphAsymmErrorsRange2.C"
#include "plotTimeReturnTGraphAsymmErrors1Line.C"
#include "plotDistributions.C"

void plotTimingFakesAllSamples(){

  TString isoCut = "2";

  setTDRStyle();

  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  TGaxis::SetMaxDigits(4);

  TCanvas *c1 = new TCanvas("c","c",800,800);
  setCanvasStyle(c1);
  c1->cd();

  // pu 200
  TChain pu200_gaus("PFChargedBased/jetNtuple");  
  pu200_gaus.Add("timing-Feb1/ZTT-RelVal-200.root");

  //pu 140
  TChain pu140_gaus("PFChargedBased/jetNtuple");  
  pu140_gaus.Add("timing-Feb1/ZTT-RelVal-140.root");

  TChain pu0_gaus("PFChargedBased/jetNtuple");  
  pu0_gaus.Add("timing-Feb1/ZTT-RelVal-0.root");

  TString plotName = "compilation-jetFakeProbability-ZTT-200-iso-2GeV-denom-genJetMatch-reco-V2";
  TString legLabel = "Jets PF Charged Isolation < 2 GeV";

  TH1F *basehist = new TH1F("basehist","",100,0,5);
  basehist->SetStats(false);
  TString iso200("0.050"), iso140("0.050");
  TString date = "2_2_17";

  //TString numerator = "jetPt > 22 && jetPt < 400 && genJetMatch > 0 &&  dmf==10 && good3ProngT3 > 0  && abs(jetEta) <2.1 && abs(tauEta)<2.1 && tauPt> 30 && vtxIndex==0";
  //TString denominator = "jetPt > 22 && jetPt < 400 && genJetMatch > 0 && abs(jetEta) <2.1 && vtxIndex==0";
  TString numerator = "jetPt > 30 && jetPt < 400 && genJetMatch>0 && (dmf!=5&&dmf!=6 && dmf > 0) && abs(jetEta) <2.1 && abs(tauEta)<2.1 && tauPt> 35 && vtxIndex==0";
  TString denominator = "jetPt > 30 && jetPt < 400 && genJetMatch>0 && abs(jetEta) <2.1 && vtxIndex==0 && (dmf!=5&&dmf!=6 && dmf > 0)";

  TString logand = " && ";

  double zs_200[4]   = {0.,0.,0.,0.};
  double vals_200[4] = {0.,0.,0.,0.};
  double erhi_200[4] = {0.,0.,0.,0.};
  double erlo_200[4] = {0.,0.,0.,0.};
  double zs_140[4]   = {0.,0.,0.,0.};
  double vals_140[4] = {0.,0.,0.,0.};
  double erhi_140[4] = {0.,0.,0.,0.};
  double erlo_140[4] = {0.,0.,0.,0.};
  double dens_200[4] = {0.,0.,0.,0.};

  double zs_time_200[4]   = {0.,0.,0.,0.};
  double vals_time_200[4] = {0.,0.,0.,0.};
  double erhi_time_200[4] = {0.,0.,0.,0.};
  double erlo_time_200[4] = {0.,0.,0.,0.};
  double zs_time_140[4]   = {0.,0.,0.,0.};
  double vals_time_140[4] = {0.,0.,0.,0.};
  double erhi_time_140[4] = {0.,0.,0.,0.};
  double erlo_time_140[4] = {0.,0.,0.,0.};

  double exl[4] = {0.,0.,0.,0.};
  double exh[4] = {0.,0.,0.,0.};

  //plotDistributions(pu0_gaus,denominator,"jetPt-denominator-0PU");

  TString numeratorNominal = numerator + "&& PFCharged <" + isoCut;
  //plotDistributions(pu200_gaus,numeratorNominal,"jetPt-nominal");
  TGraphAsymmErrors *pu200_eff = plotTimeReturnTGraphAsymmErrorsRange2(pu200_gaus, numeratorNominal,denominator);
  TGraphAsymmErrors *pu140_eff = plotTimeReturnTGraphAsymmErrors(pu140_gaus, numeratorNominal,denominator);
  TGraphAsymmErrors *pu0_eff   = plotTimeReturnTGraphAsymmErrors1Line(pu0_gaus, numeratorNominal,denominator);

  /////////////////////////////////////////

  TString numeratorT4 = numerator + "&& PFChargedT4 <"+isoCut;
  //plotDistributions(pu200_gaus,numeratorT4,"jetPt-T4");
  TGraphAsymmErrors *pu200_eff_timingCutT4 = plotTimeReturnTGraphAsymmErrorsRange2(pu200_gaus, numeratorT4,denominator);
  TGraphAsymmErrors *pu140_eff_timingCutT4 = plotTimeReturnTGraphAsymmErrors(pu140_gaus, numeratorT4,denominator);

  //TGraphAsymmErrors *pu0_eff_timingCutT4   = plotTimeReturnTGraphAsymmErrors(pu0_gaus,   numeratorT4,denominator);

  /////////////////////////////////////////
  basehist->GetXaxis()->SetTitle("density (events / mm)");
  basehist->GetYaxis()->SetTitle("Jet Fake Probability ");  
  basehist->GetYaxis()->SetRangeUser(0.0,0.05);
  basehist->GetXaxis()->SetRangeUser(0.5,2);
  basehist->GetYaxis()->SetLabelSize(0.035);

  basehist->Draw("");
  
//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT4,       color4,            3005,                 33);
  pu200_eff_timingCutT4->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu140_eff_timingCutT4,       color1,            3005,                 33);
  pu140_eff_timingCutT4->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(             pu140_eff,       color3,            3005,                 23);
  pu140_eff->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(             pu200_eff,       color5,            3005,                 23);
  pu200_eff->Draw("P Same");

  ////////////////// PU 0
//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  //TGraphErrors *errorBand = new TGraphErrors(n,x,y,ex,ey);
  //pu0_eff_timingCutT4->SetFillColor(kBlue+4);
  //pu0_eff_timingCutT4->SetFillStyle(3005);   
  //setPlotStyleAsymm(  pu0_eff_timingCutT4,       color3,            3005,                 23);
  pu0_eff->SetFillColor(kBlue+4);
  pu0_eff->SetFillStyle(3005);   
  pu0_eff->Draw("4, Same");


  //setLegendStyles options
  //Legend option 0 == manual set
  //              1 == upper left
  //              2 == lower left
  //              3 == lower right
  //              4 == upper right
  //              5 == center upper
  //              6 == center lower
  //
  TLegend *leg = new TLegend(.15, .606, .35, .92,legLabel,"nbNDC");
  setLegendStyles(leg,legLabel, 5);



  leg->AddEntry(pu140_eff,"140PU HL-LHC","PL");
  leg->AddEntry(pu140_eff_timingCutT4,"140PU HL-LHC + MIP Timing","PL");

  leg->AddEntry(pu200_eff,"200PU HL-LHC","PL");
  leg->AddEntry(pu200_eff_timingCutT4,"200PU HL-LHC + MIP Timing","PL");

  leg->AddEntry(            pu0_eff,   "Zero Pileup","F"); 

  leg->Draw();

  TLine *line = new TLine(0,0.15,3,0.15);
  line->Draw();  
  c1->SaveAs("~/Dropbox/"+date+"/TimingPlots/"+plotName+".pdf");
  c1->SaveAs("~/Dropbox/"+date+"/TimingPlots/"+plotName+".png");
}
