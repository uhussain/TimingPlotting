#include "tdrstyle.C"
#include "PlotStyles.C"

void plotTimingFakes(){
  TString isoCut = "1.5";
  Int_t color1 = TColor::GetColor("#283593"); //dark blue
  Int_t color2 = TColor::GetColor("#0288D1"); //medium blue

  Int_t color3 = TColor::GetColor("#00695C"); //green blue
  Int_t color4 = TColor::GetColor("#F44336"); //red

  setTDRStyle();

  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  TCanvas *c1 = new TCanvas("c","c",800,800);
  setCanvasStyle(c1);
  c1->cd();

  TString plotName = "tauEfficiency-ZTT-PU200";
  TString legLabel = "Jet Fake ZTT 200PU";
  TH1F *basehist = new TH1F("basehist","",100,0,2.5);
  basehist->SetStats(false);
  TString iso200("0.050"), iso140("0.050");


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

  TString numer("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFCharged <"+isoCut);
  TString denom("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && vtxIndex==0");
  TString logand(" && " );

  TString z1("abs(vtxZ) < 2.0"), 
    z2("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp histo
  TH1F temp("temp","temp",71,0,8);

  // gaussian
  TF1 mygaus("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus.SetParameter(0,0);
  mygaus.SetParameter(1,52);

  // pu 200
  TChain pu200_gaus("PFChargedBased/jetNtuple");  
  //pu200_gaus.Add("timing-ZTT-PU200.root");
  pu200_gaus.Add("timing-ZTT-PU200-Jan19.root");


  // first region
  double Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z1,"goff");
  zs_200[0] = 10.*temp.GetMean();
  double Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z1,"goff");
  std::cout<<"Nsel/Ntot = Vals "<<Nsel<<"/"<<Ntot<<"="<<Nsel/Ntot<<std::endl;

  vals_200[0] = Nsel/Ntot;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // second region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z2,"goff");
  zs_200[1] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z2,"goff");
  
  vals_200[1] = Nsel/Ntot;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
 
  // third region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z3,"goff");
  zs_200[2] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z3,"goff");
  
  vals_200[2] = Nsel/Ntot;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // fourth region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z4,"goff");
  zs_200[3] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z4,"goff");

  vals_200[3] = Nsel/Ntot;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);
  //////////////////////////////////////////

  TString numer("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFChargedT3 <"+isoCut);
  TString denom("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && vtxIndex==0");
  TString logand(" && " );

  TString z1("abs(vtxZ) < 2.0"), 
    z2("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp histo
  TH1F temp("temp","temp",71,0,8);

  // gaussian
  TF1 mygaus("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus.SetParameter(0,0);
  mygaus.SetParameter(1,52);

  // first region
  double Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z1,"goff");
  zs_200[0] = 10.*temp.GetMean();
  double Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z1,"goff");
  std::cout<<"Nsel/Ntot = Vals "<<Nsel<<"/"<<Ntot<<"="<<Nsel/Ntot<<std::endl;

  vals_200[0] = Nsel/Ntot;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // second region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z2,"goff");
  zs_200[1] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z2,"goff");
  
  vals_200[1] = Nsel/Ntot;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
 
  // third region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z3,"goff");
  zs_200[2] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z3,"goff");
  
  vals_200[2] = Nsel/Ntot;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // fourth region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z4,"goff");
  zs_200[3] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z4,"goff");

  vals_200[3] = Nsel/Ntot;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff_timingCutT3 = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);


  /////////////////////////////////////////

  //TString numer("jetPt > 10 && vtxIndex==0 && tauPt> 25 ");
  TString numer("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFChargedT2 <"+isoCut);
  //TString numer_time("genMatchedPrompt==1 && vtxIndex==0 && pt > 20 && chIsoZTCut_4sigma/pt < 0.050");
  //TString denom("jetPt > 10 && vtxIndex==0 ");
  TString denom("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && vtxIndex==0");
  TString logand(" && " );

  TString z1("abs(vtxZ) < 2.0"), 
    z2("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp histo
  TH1F temp("temp","temp",71,0,8);

  // gaussian
  TF1 mygaus("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus.SetParameter(0,0);
  mygaus.SetParameter(1,52);


  // first region
  double Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z1,"goff");
  zs_200[0] = 10.*temp.GetMean();
  double Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z1,"goff");
  std::cout<<"Nsel/Ntot = Vals "<<Nsel<<"/"<<Ntot<<"="<<Nsel/Ntot<<std::endl;

  vals_200[0] = Nsel/Ntot;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // second region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z2,"goff");
  zs_200[1] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z2,"goff");
  
  vals_200[1] = Nsel/Ntot;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
 
  // third region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z3,"goff");
  zs_200[2] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z3,"goff");
  
  vals_200[2] = Nsel/Ntot;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // fourth region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z4,"goff");
  zs_200[3] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z4,"goff");

  vals_200[3] = Nsel/Ntot;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff_timingCutT2 = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);


  /////////////////////////////////////////

  //TString numer("jetPt > 10 && vtxIndex==0 && tauPt> 25 ");
  TString numer("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFChargedT4 <"+isoCut);
  //TString numer_time("genMatchedPrompt==1 && vtxIndex==0 && pt > 20 && chIsoZTCut_4sigma/pt < 0.050");
  //TString denom("jetPt > 10 && vtxIndex==0 ");
  TString denom("jetPt > 22 &&  dmf==10  && abs(jetEta) <2.1 && vtxIndex==0");
  TString logand(" && " );

  TString z1("abs(vtxZ) < 2.0"), 
    z2("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp histo
  TH1F temp("temp","temp",71,0,8);

  // gaussian
  TF1 mygaus("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus.SetParameter(0,0);
  mygaus.SetParameter(1,52);


  // first region
  double Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z1,"goff");
  zs_200[0] = 10.*temp.GetMean();
  double Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z1,"goff");
  std::cout<<"Nsel/Ntot = Vals "<<Nsel<<"/"<<Ntot<<"="<<Nsel/Ntot<<std::endl;

  vals_200[0] = Nsel/Ntot;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // second region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z2,"goff");
  zs_200[1] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z2,"goff");
  
  vals_200[1] = Nsel/Ntot;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
 
  // third region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z3,"goff");
  zs_200[2] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z3,"goff");
  
  vals_200[2] = Nsel/Ntot;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // fourth region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denom+logand+z4,"goff");
  zs_200[3] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numer+logand+z4,"goff");

  vals_200[3] = Nsel/Ntot;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff_timingCutT1 = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);


  /////////////////////////////////////////
  //c1->cd();
  basehist->GetXaxis()->SetTitle("density (events / mm)");
  basehist->GetYaxis()->SetTitle("Jet Fake Probability ");  
  basehist->GetYaxis()->SetRangeUser(0.0,0.5);
  basehist->GetXaxis()->SetRangeUser(0.3,2.60);
  basehist->Draw("");
  
//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT1,       color3,            3005,                 23);
  pu200_eff_timingCutT1->Draw("P Same");

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
  leg->AddEntry(pu200_eff_timingCutT1,"T4 Interval Track Req","PL");
  leg->Draw();
  
  c1->SaveAs("~/Dropbox/TimingPlots/"+plotName+"-fake-dm10-no-sig-track-t-req-Jan19.pdf");
  c1->SaveAs("~/Dropbox/TimingPlots/"+plotName+"-fake-dm10-no-sig-track-t-req-Jan19.png");
}
