#include "tdrstyle.C"

void plotDistributions(TChain &pu200_gaus, TString denominator, TString name){

  TString z1("abs(vtxZ) < 2.0"), 
    z2("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  TCanvas *c2 = new TCanvas("c2","c2",800,800);
  TH1F *basehist_dist = new TH1F("basehist_dist","",20,0,400);
  setCanvasStyle(c2);
  c2->cd();
  
  TH1F *jetPtZ1 = new TH1F("jetPtZ1","jetPtZ1",20,0,400);
  pu200_gaus.Draw("jetPt>>jetPtZ1",denominator+"&&"+z1);
  //setPlotStyle(  jetPtZ1,       color3,            3005,                 23);
  jetPtZ1->SetLineColor(color3);
  jetPtZ1->SetMarkerColor(color3);
  jetPtZ1->SetLineWidth(2);

  TH1F *jetPtZ2 = new TH1F("jetPtZ2","jetPtZ2",20,0,400);
  pu200_gaus.Draw("jetPt>>jetPtZ2",denominator+"&&"+z2);
  //setPlotStyle(  jetPtZ2,       color2,            3005,                 23);
  jetPtZ2->SetLineColor(color2);
  jetPtZ2->SetMarkerColor(color2);
  jetPtZ2->SetLineWidth(2);


  TH1F *jetPtZ3 = new TH1F("jetPtZ3","jetPtZ3",20,0,400);
  pu200_gaus.Draw("jetPt>>jetPtZ3",denominator+"&&"+z3);
  //setPlotStyle(  jetPtZ3,       color4,            3005,                 23);
  jetPtZ3->SetLineColor(color4);
  jetPtZ3->SetMarkerColor(color4);
  jetPtZ3->SetLineWidth(2);


  TH1F *jetPtZ4 = new TH1F("jetPtZ4","jetPtZ4",20,0,400);
  pu200_gaus.Draw("jetPt>>jetPtZ4",denominator+"&&"+z4);
  //setPlotStyle(  jetPtZ4,       color1,            3005,                 23);
  jetPtZ4->SetLineColor(color1);
  jetPtZ4->SetMarkerColor(color1);
  jetPtZ4->SetLineWidth(2);


  jetPtZ1->Scale(1/jetPtZ1->Integral());
  jetPtZ2->Scale(1/jetPtZ2->Integral());
  jetPtZ3->Scale(1/jetPtZ3->Integral());
  jetPtZ4->Scale(1/jetPtZ4->Integral());
  
  jetPtZ1->Draw("HIST");
  jetPtZ2->Draw("HIST,same");
  jetPtZ3->Draw("HIST,same");
  jetPtZ4->Draw("HIST,same");

  jetPtZ1->GetYaxis()->SetRangeUser(0.0,0.5);
  // jetPtZ1->GetXaxis()->SetRangeUser(0.3,2.60);

  TLegend *leg = new TLegend(.15, .606, .35, .92, name,"nbNDC");
  setLegendStyles(leg,name, 4);

  leg->AddEntry(  jetPtZ1,"Z1","PL"); 
  leg->AddEntry(  jetPtZ2,"Z2","PL");
  leg->AddEntry(  jetPtZ3,"Z3","PL");
  leg->AddEntry(  jetPtZ4,"Z4","PL");
  leg->Draw();

  c2->SaveAs("distributions/"+name+".png");
}
