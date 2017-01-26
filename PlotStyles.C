#include "tdrstyle.C"

void setCanvasStyle(TCanvas *c1){
  c1->SetBottomMargin(0.15);
}

void setPlotStyleAsymm( TGraphAsymmErrors *plot, Int_t color, Int_t fillStyle, Int_t markerStyle){

  plot->SetLineColor(color);
  plot->SetMarkerColor(color);
  plot->SetFillStyle(fillStyle);
  plot->SetMarkerStyle(markerStyle);

}


  //Legend option 0 == manual set
  //              1 == upper left
  //              2 == lower left
  //              3 == lower right
  //              4 == upper right
  //              5 == center upper
  //              6 == center lower
  //
void setLegendStyles( TLegend *leg , TString legLabel = "", Int_t option = 0){
  //upper left
  if(option == 1){
    leg->SetX1(0.15);
    leg->SetY1(0.606);
    leg->SetX2(0.35);
    leg->SetY2(0.92);
    //leg = new TLegend(.15, .606, .35, .92,legLabel,"nbNDC");  
  }
  //lower left
  if(option == 2){
    leg->SetX1(0.15);
    leg->SetY1(0.206);
    leg->SetX2(0.35);
    leg->SetY2(0.52);
    //leg = new TLegend(.15, .206, .35, .52,legLabel,"nbNDC");  
  }
  //lower right
  if(option == 3){
    leg->SetX1(0.55);
    leg->SetY1(0.206);
    leg->SetX2(0.75);
    leg->SetY2(0.52);
    //leg = new TLegend(.55, .206, .75, .52,legLabel,"nbNDC");  
  }
  //upper right
  if(option == 4){
    leg->SetX1(0.55);
    leg->SetY1(0.606);
    leg->SetX2(0.75);
    leg->SetY2(0.92);
    //leg = new TLegend(.55, .606, .75, .92,legLabel,"nbNDC");  
  }
  //center upper
  if(option == 5){
    leg->SetX1(0.45);
    leg->SetY1(0.606);
    leg->SetX2(0.65);
    leg->SetY2(0.92);
    //leg = new TLegend(.45, .606, .65, .92,legLabel,"nbNDC");  
  }
  //center lower
  if(option == 6){
    leg->SetX1(0.45);
    leg->SetY1(0.206);
    leg->SetX2(0.65);
    leg->SetY2(0.52);
    //leg = new TLegend(.45, .206, .65, .52,legLabel,"nbNDC");  
  }
  leg->SetBorderSize(0);
  leg->SetShadowColor(kWhite);
  leg->SetFillColor(kWhite);
  leg->SetTextSize(0.03);
}
