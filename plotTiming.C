#include "tdrstyle.C"
#include "PlotStyles.C"
#include "plotTimeReturnTGraphAsymmErrors.C"
#include "plotTimeReturnTGraphAsymmErrors1Line.C"

void plotTiming(){
  TString isoCut = "2";
  Int_t color1 = TColor::GetColor("#283593"); //dark blue
  Int_t color2 = TColor::GetColor("#0288D1"); //medium blue

  Int_t color3 = TColor::GetColor("#00695C"); //green blue
  Int_t color4 = TColor::GetColor("#F44336"); //red

  Int_t color5 = TColor::GetColor("#FF9900"); //Mustard Yellow

  setTDRStyle();

  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  TCanvas *c1 = new TCanvas("c","c",800,800);
  setCanvasStyle(c1);
  c1->cd();
  TString plotName = "tauEfficiency-TTBar-200PU";
  TString legLabel = "Tau Efficiency TTBar 200PU";
  TH1F *basehist = new TH1F("basehist","",100,0,2.5);

  TChain pu200_gaus("PFChargedBased/Ntuple");  
  pu200_gaus.Add("timing-Jan26-2/ZTT-RelVal-200.root");

  TChain pu0_gaus("PFChargedBased/Ntuple");  
  pu0_gaus.Add("timing-Jan26-2/ZTT-RelVal-0.root");

  basehist->SetStats(false);
  TString iso200("0.050"), iso140("0.050");
  TString date = "2_2_17";


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
  
  //TString numer("genTauPt > 10 && vtxIndex==0 && tauPt> 25 ");
  TString numer("genTauPt > 22 && abs(genTauEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFCharged <"+isoCut);
  //TString numer_time("genMatchedPrompt==1 && vtxIndex==0 && pt > 20 && chIsoZTCut_4sigma/pt < 0.050");
  //TString denom("genTauPt > 10 && vtxIndex==0 ");
  TString denom("genTauPt > 22 && abs(genTauEta) <2.1 && vtxIndex==0");
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
  TChain pu200_gaus("PFChargedBased/Ntuple");  
  //TChain pu200_gaus("VLooseMVA/Ntuple");  
  pu200_gaus.Add("/data/uhussain/TauTimingPhase2/CMSSW_8_1_0_pre16/src/RecoTauTag/phase2Taus/test/timing-TTBar-PU200r2-v1.root");
  //pu200_gaus.Add("ZTT-timing0PU.root");

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
  TString numerator = "genTauPt > 30 && abs(genTauEta) < 2.1 && (dmf!=5&&dmf!=6 && dmf > -1) && (dmf == 0 || dmf == 1 || (dmf == 10 && good3ProngT4>0))  &&  tauPt> 30 && vtxIndex==0";
  TString denominator = "genTauPt > 30 && abs(genTauEta) <2.1 && vtxIndex==0 && (dmf!=5&&dmf!=6 && dmf > -1) && (dmf == 0 || dmf == 1 || (dmf == 10&& good3ProngT4>0))";

  //TString numerator = "genTauPt > 22 && abs(genTauEta) < 2.1 && (dmf!=5&&dmf!=6 && dmf > -1) && (dmf == 0 || dmf == 1 || (dmf == 10 && good3ProngT4>0))  &&  tauPt> 25 && vtxIndex==0";
  //TString denominator = "genTauPt > 22 && abs(genTauEta) <2.1 && vtxIndex==0 && (dmf!=5&&dmf!=6 && dmf > -1) && (dmf == 0 || dmf == 1 || (dmf == 10&& good3ProngT4>0))";
  TString logand = " && ";

  TString numeratorNominal = numerator + "&& PFCharged <"+isoCut;
  TGraphAsymmErrors *pu200_eff = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorNominal, denominator);
  //TGraphAsymmErrors *pu0_eff   = plotTimeReturnTGraphAsymmErrors(pu0_gaus, numeratorNominal,denominator);
  TGraphAsymmErrors *pu0_eff   = plotTimeReturnTGraphAsymmErrors1Line(pu0_gaus, numeratorNominal,denominator);
  //////////////////////////////////////////

  //TString numer("genTauPt > 10 && vtxIndex==0 && tauPt> 25 ");
  TString numer_1("genTauPt > 22 && abs(genTauEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFChargedT3 <"+isoCut);
  //TString numer_time("genMatchedPrompt==1 && vtxIndex==0 && pt > 20 && chIsoZTCut_4sigma/pt < 0.050");
  //TString denom("genTauPt > 10 && vtxIndex==0 ");
  TString denom_1("genTauPt > 22 && abs(genTauEta) <2.1 && vtxIndex==0");
  TString logand_1(" && " );

  TString z1_1("abs(vtxZ) < 2.0"), 
    z2_1("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3_1("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4_1("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp histo
  TH1F temp_1("temp_1","temp_1",71,0,8);

  // gaussian
  TF1 mygaus_1("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus_1.SetParameter(0,0);
  mygaus_1.SetParameter(1,52);


  // first region
  double Ntot_1 = pu200_gaus.Draw("abs(vtxZ) >> temp_1",denom_1+logand_1+z1_1,"goff");
  zs_200[0] = 10.*temp_1.GetMean();
  double Nsel_1 = pu200_gaus.Draw("abs(vtxZ)",numer_1+logand_1+z1_1,"goff");
  std::cout<<"Nsel_1/Ntot_1 = Vals "<<Nsel_1<<"/"<<Ntot_1<<"="<<Nsel_1/Ntot_1<<std::endl;

  vals_200[0] = Nsel_1/Ntot_1;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,false);

  // second region
  Ntot_1 = pu200_gaus.Draw("abs(vtxZ) >> temp_1",denom_1+logand_1+z2_1,"goff");
  zs_200[1] = 10.*temp_1.GetMean();
  Nsel_1 = pu200_gaus.Draw("abs(vtxZ)",numer_1+logand_1+z2_1,"goff");
  
  vals_200[1] = Nsel_1/Ntot_1;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,false);
 
  // third region
  Ntot_1 = pu200_gaus.Draw("abs(vtxZ) >> temp_1",denom_1+logand_1+z3_1,"goff");
  zs_200[2] = 10.*temp_1.GetMean();
  Nsel_1 = pu200_gaus.Draw("abs(vtxZ)",numer_1+logand_1+z3_1,"goff");
  
  vals_200[2] = Nsel_1/Ntot_1;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,false);

  // fourth region
  Ntot_1 = pu200_gaus.Draw("abs(vtxZ) >> temp_1",denom_1+logand_1+z4_1,"goff");
  zs_200[3] = 10.*temp_1.GetMean();
  Nsel_1 = pu200_gaus.Draw("abs(vtxZ)",numer_1+logand_1+z4_1,"goff");

  vals_200[3] = Nsel_1/Ntot_1;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot_1,Nsel_1,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus_1.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus_1.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff_timingCutT3 = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);


  /////////////////////////////////////////

  //TString numer("genTauPt > 10 && vtxIndex==0 && tauPt> 25 ");
  TString numer_2("genTauPt > 22 && abs(genTauEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFChargedT2 <"+isoCut);
  //TString numer_time("genMatchedPrompt==1 && vtxIndex==0 && pt > 20 && chIsoZTCut_4sigma/pt < 0.050");
  //TString denom("genTauPt > 10 && vtxIndex==0 ");
  TString denom_2("genTauPt > 22 && abs(genTauEta) <2.1 && vtxIndex==0");
  TString logand_2(" && " );

  TString z1_2("abs(vtxZ) < 2.0"), 
    z2_2("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3_2("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4_2("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp_2 histo
  TH1F temp_2("temp_2","temp_2",71,0,8);

  // gaussian
  TF1 mygaus_2("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus_2.SetParameter(0,0);
  mygaus_2.SetParameter(1,52);

  // first region
  double Ntot_2 = pu200_gaus.Draw("abs(vtxZ) >> temp_2",denom_2+logand_2+z1_2,"goff");
  zs_200[0] = 10.*temp_2.GetMean();
  double Nsel_2 = pu200_gaus.Draw("abs(vtxZ)",numer_2+logand_2+z1_2,"goff");
  std::cout<<"Nsel_2/Ntot_2 = Vals "<<Nsel_2<<"/"<<Ntot_2<<"="<<Nsel_2/Ntot_2<<std::endl;

  vals_200[0] = Nsel_2/Ntot_2;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,false);

  // second region
  Ntot_2 = pu200_gaus.Draw("abs(vtxZ) >> temp_2",denom_2+logand_2+z2_2,"goff");
  zs_200[1] = 10.*temp_2.GetMean();
  Nsel_2 = pu200_gaus.Draw("abs(vtxZ)",numer_2+logand_2+z2_2,"goff");
  
  vals_200[1] = Nsel_2/Ntot_2;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,false);
 
  // third region
  Ntot_2 = pu200_gaus.Draw("abs(vtxZ) >> temp_2",denom_2+logand_2+z3_2,"goff");
  zs_200[2] = 10.*temp_2.GetMean();
  Nsel_2 = pu200_gaus.Draw("abs(vtxZ)",numer_2+logand_2+z3_2,"goff");
  
  vals_200[2] = Nsel_2/Ntot_2;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,false);

  // fourth region
  Ntot_2 = pu200_gaus.Draw("abs(vtxZ) >> temp_2",denom_2+logand_2+z4_2,"goff");
  zs_200[3] = 10.*temp_2.GetMean();
  Nsel_2 = pu200_gaus.Draw("abs(vtxZ)",numer_2+logand_2+z4_2,"goff");

  vals_200[3] = Nsel_2/Ntot_2;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot_2,Nsel_2,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus_2.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus_2.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff_timingCutT2 = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);

  //TString numer("genTauPt > 22 && abs(genTauEta) <2.1 && dmf==10  &&  tauPt> 25 && vtxIndex==0 && PFChargedT3 <"+isoCut);
  TString numeratorT3 = numerator + "&& PFChargedT3 <"+isoCut;
  TGraphAsymmErrors *pu200_eff_timingCutT3 = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorT3, denominator);  

  /////////////////////////////////////////

  TString numeratorT2 = numerator + "&& PFChargedT2<"+isoCut;
  TGraphAsymmErrors *pu200_eff_timingCutT2 = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorT2, denominator);  

  /////////////////////////////////////////
  TString numeratorT1 = numerator + "&& PFChargedT4 <"+isoCut;
  //TString numeratorT1v0 = numerator + "&& PFChargedT4 <5";

  //TString numer("genTauPt > 10 && vtxIndex==0 && tauPt> 25 ");
  TString numer_3("genTauPt > 22 && abs(genTauEta) <2.1 && tauPt> 25 && vtxIndex==0 && PFChargedT1 <"+isoCut);
  //TString numer_time("genMatchedPrompt==1 && vtxIndex==0 && pt > 20 && chIsoZTCut_4sigma/pt < 0.050");
  //TString denom("genTauPt > 10 && vtxIndex==0 ");
  TString denom_3("genTauPt > 22 && abs(genTauEta) <2.1 && vtxIndex==0");
  TString logand_3(" && " );

  TString z1_3("abs(vtxZ) < 2.0"), 
    z2_3("abs(vtxZ) < 4.0 && abs(vtxZ) > 2.0"), 
    z3_3("abs(vtxZ) < 7.0 && abs(vtxZ) > 4.0"), 
    z4_3("abs(vtxZ) < 8.0 && abs(vtxZ) > 7.0"); //fix me should be 6.0 to 8.0

  // temp_3 histo
  TH1F temp_3("temp_3","temp_3",71,0,8);

  // gaussian
  TF1 mygaus_3("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus_3.SetParameter(0,0);
  mygaus_3.SetParameter(1,52);

  // first region
  double Ntot_3 = pu200_gaus.Draw("abs(vtxZ) >> temp_3",denom_3+logand_3+z1_3,"goff");
  zs_200[0] = 10.*temp_3.GetMean();
  double Nsel_3 = pu200_gaus.Draw("abs(vtxZ)",numer_3+logand_3+z1_3,"goff");
  std::cout<<"Nsel_3/Ntot_3 = Vals "<<Nsel_3<<"/"<<Ntot_3<<"="<<Nsel_3/Ntot_3<<std::endl;

  vals_200[0] = Nsel_3/Ntot_3;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,false);

  // second region
  Ntot_3 = pu200_gaus.Draw("abs(vtxZ) >> temp_3",denom_3+logand_3+z2_3,"goff");
  zs_200[1] = 10.*temp_3.GetMean();
  Nsel_3 = pu200_gaus.Draw("abs(vtxZ)",numer_3+logand_3+z2_3,"goff");
  
  vals_200[1] = Nsel_3/Ntot_3;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,false);
 
  // third region
  Ntot_3 = pu200_gaus.Draw("abs(vtxZ) >> temp_3",denom_3+logand_3+z3_3,"goff");
  zs_200[2] = 10.*temp_3.GetMean();
  Nsel_3 = pu200_gaus.Draw("abs(vtxZ)",numer_3+logand_3+z3_3,"goff");
  
  vals_200[2] = Nsel_3/Ntot_3;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,false);

  // fourth region
  Ntot_3 = pu200_gaus.Draw("abs(vtxZ) >> temp_3",denom_3+logand_3+z4_3,"goff");
  zs_200[3] = 10.*temp_3.GetMean();
  Nsel_3 = pu200_gaus.Draw("abs(vtxZ)",numer_3+logand_3+z4_3,"goff");

  vals_200[3] = Nsel_3/Ntot_3;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot_3,Nsel_3,0.683,false);
  
  for( unsigned i = 0; i < 4; ++i ) {
    dens_200[i] = 200*mygaus_3.Eval(zs_200[i]);
    std::cout<< i<<" density: "<<dens_200[i]<<" values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus_3.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
  }

  TGraphAsymmErrors *pu200_eff_timingCutT1 = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);

  TGraphAsymmErrors *pu200_eff_timingCutT1 = plotTimeReturnTGraphAsymmErrors(pu200_gaus, numeratorT1, denominator);  
  TGraphAsymmErrors *pu0_eff_timingCutT1   = plotTimeReturnTGraphAsymmErrors(pu0_gaus, numeratorT1, denominator);

  /////////////////////////////////////////
  basehist->GetXaxis()->SetTitle("density (events / mm)");
  basehist->GetYaxis()->SetTitle("Tau ID Efficiency ");  
  basehist->GetYaxis()->SetRangeUser(0.0,1.0);
  basehist->GetXaxis()->SetRangeUser(0.3,2.60);
  basehist->Draw("");

  //setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT1,       color3,            3005,                 23);
  pu200_eff_timingCutT1->Draw("P Same");

  pu200_eff_timingCutT1->SetLineColor(color3);
  pu200_eff_timingCutT1->SetMarkerColor(color3);
  pu200_eff_timingCutT1->SetFillColor(color3);
  pu200_eff_timingCutT1->SetFillStyle(3005);
  pu200_eff_timingCutT1->SetMarkerStyle(23);
  pu200_eff_timingCutT1->Draw("P Same");

  pu200_eff_timingCutT2->SetLineColor(color2);
  pu200_eff_timingCutT2->SetMarkerColor(color2);
  pu200_eff_timingCutT2->SetFillColor(color2);
  pu200_eff_timingCutT2->SetFillStyle(3005);
  pu200_eff_timingCutT2->SetMarkerStyle(23);
=======
  setPlotStyleAsymm(  pu200_eff_timingCutT2,       color2,            3005,                 23);
  pu200_eff_timingCutT2->Draw("P Same");

  //setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(  pu200_eff_timingCutT3,       color4,            3005,                 23);
  pu200_eff_timingCutT3->Draw("P Same");

//setPlotStyleAsymm(                  plot , Int_t  color, Int_t fillStyle,  Int_t MarkerStyle){
  setPlotStyleAsymm(             pu200_eff,       color1,            3005,                 23);
  pu200_eff->Draw("P Same");

  TLegend *leg = new TLegend(.55, .706, .75, .92,legLabel,"nbNDC");  
  leg->SetBorderSize(0);
  leg->SetShadowColor(kWhite);
  leg->SetFillColor(kWhite);
  leg->SetTextSize(0.03);
  leg->AddEntry(pu200_eff,"PF Charged Iso All","PL"); 
  leg->AddEntry(pu200_eff_timingCutT1,"T1 Interval Track Req","PL");
  leg->AddEntry(pu200_eff_timingCutT2,"T2 Interval Track Req","PL");
  leg->AddEntry(pu200_eff_timingCutT3,"T3 Interval Track Req","PL");
  leg->Draw();
  
  c1->SaveAs("TimingPlots/"+plotName+".pdf");
  c1->SaveAs("TimingPlots/"+plotName+".png");
  pu0_eff->SetFillColor(kBlue+4);
  pu0_eff->SetFillStyle(3005);
  pu0_eff->Draw("4, Same");
  //pu0_eff->SetFillColor(kBlue+4);
  //pu0_eff->SetFillStyle(3005);
  //pu0_eff->Draw("4, Same");

  TLegend *leg = new TLegend(.55, .706, .75, .92,legLabel,"nbNDC");  
  setLegendStyles(leg,legLabel, 2);

  leg->AddEntry(            pu200_eff,   "PF Charged Isolation Nominal","PL"); 
  leg->AddEntry(pu200_eff_timingCutT2,"2#sigma Interval Tracks","PL");
  leg->AddEntry(pu200_eff_timingCutT3,"3#sigma Interval Tracks","PL");
  leg->AddEntry(pu200_eff_timingCutT1,"4#sigma Interval Tracks","PL");
  leg->Draw();
  
  c1->SaveAs("~/Dropbox/"+date+"/TimingPlots/"+plotName+".pdf");
  c1->SaveAs("~/Dropbox/"+date+"/TimingPlots/"+plotName+".png");
}
