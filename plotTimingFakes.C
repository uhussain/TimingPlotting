#include "tdrstyle.C"
#include "PlotStyles.C"
#include "plotTimeReturnTGraphAsymmErrors.C"

void plotTimingFakes(){

  TString isoCut = "5";

  Int_t color1 = TColor::GetColor("#283593"); //dark blue
  Int_t color2 = TColor::GetColor("#0288D1"); //medium blue

  Int_t color3 = TColor::GetColor("#00695C"); //green blue
  Int_t color4 = TColor::GetColor("#F44336"); //red

  setTDRStyle();

  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  TGaxis::SetMaxDigits(4);

  TCanvas *c1 = new TCanvas("c","c",800,800);
  setCanvasStyle(c1);
  c1->cd();

  // pu 200
  TChain pu200_gaus("PFChargedBased/jetNtuple");  
  pu200_gaus.Add("timing-Jan25/ZTT200PU-addThreeProngCheck.root");
  TString plotName = "tauEfficiency-ZTT-PU200-3prongTReq-5GeVCut-test";
  TString legLabel = "Jet Fake ZTT 200PU";

  TH1F *basehist = new TH1F("basehist","",100,0,2.5);
  basehist->SetStats(false);
  TString iso200("0.050"), iso140("0.050");
  TString date = "1_25_17";

  TString numer = "jetPt > 22 &&  dmf==10  && good3ProngT3 > 0 && abs(jetEta) <2.1 && tauPt> 25 && vtxIndex==0";
  TString denom = "jetPt > 22 && abs(jetEta) <2.1 && vtxIndex==0";
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

  TString numeratorNominal = numer + "&& PFCharged <" + isoCut;
  TGraphAsymmErrors *pu200_eff = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorNominal,denom);

  //////////////////////////////////////////
  
  TString numeratorT3 = numer + "&& PFChargedT3 <"+isoCut;
  TGraphAsymmErrors *pu200_eff_timingCutT3 = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorT3,denom);
  /////////////////////////////////////////

  TString numeratorT2 = numer + "&& PFChargedT2 <"+isoCut;
  TGraphAsymmErrors *pu200_eff_timingCutT2 = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorT2,denom);

  /////////////////////////////////////////

  TString numeratorT4 = numer + "&& PFChargedT4 <"+isoCut;
  TGraphAsymmErrors *pu200_eff_timingCutT4 = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorT4,denom);

  /////////////////////////////////////////
  basehist->GetXaxis()->SetTitle("density (events / mm)");
  basehist->GetYaxis()->SetTitle("Jet Fake Probability ");  
  basehist->GetYaxis()->SetRangeUser(0.0,0.018);
  basehist->GetXaxis()->SetRangeUser(0.3,2.60);
  basehist->Draw("");
  
//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT4,       color3,            3005,                 23);
  pu200_eff_timingCutT4->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT2,       color2,            3005,                 23);
  pu200_eff_timingCutT2->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT3,       color4,            3005,                 23);
  pu200_eff_timingCutT3->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(             pu200_eff,       color1,            3005,                 23);
  pu200_eff->Draw("P Same");

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
  setLegendStyles(leg,legLabel, 4);

  leg->AddEntry(            pu200_eff,   "PF Charged Iso All","PL"); 
  leg->AddEntry(pu200_eff_timingCutT2,"T2 Interval Track Req","PL");
  leg->AddEntry(pu200_eff_timingCutT3,"T3 Interval Track Req","PL");
  leg->AddEntry(pu200_eff_timingCutT4,"T4 Interval Track Req","PL");
  leg->Draw();
  
  c1->SaveAs("~/Dropbox/"+date+"/TimingPlots/"+plotName+".pdf");
  c1->SaveAs("~/Dropbox/"+date+"/TimingPlots/"+plotName+".png");
}
