#include "tdrstyle.C"

TGraphAsymmErrors * plotTimeReturnTGraphAsymmErrors(TChain &pu200_gaus, TString numerator, TString denominator){
  //TString numeratorNominal = numer + "&& PFCharged <" + isoCut;

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

  TString z1("abs(vtxZ) < 3.0"), 
    z2("abs(vtxZ) < 6.5 && abs(vtxZ) > 3.0"), 
    z3("abs(vtxZ) < 8.3 && abs(vtxZ) > 6.5"), 
    z4("abs(vtxZ) < 9.0 && abs(vtxZ) > 7.75"); //fix me should be 6.0 to 8.0
  
  // temp histo
  TH1F temp("temp","temp",71,0,8);

  // gaussian
  TF1 mygaus("gaussian","exp( -(([0]-x)**2)/(2*[1]*[1]))/sqrt(2*TMath::Pi()*[1]*[1])",0,200);
  mygaus.SetParameter(0,0);
  mygaus.SetParameter(1,52);

  // first region
  double Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denominator+"&&"+z1,"goff");
  zs_200[0] = 10.*temp.GetMean();
  double Nsel = pu200_gaus.Draw("abs(vtxZ)",numerator+"&&"+z1,"goff");
  std::cout<<"Nsel/Ntot = Vals "<<Nsel<<"/"<<Ntot<<"="<<Nsel/Ntot<<std::endl;

  vals_200[0] = Nsel/Ntot;
  erhi_200[0] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[0];
  erlo_200[0] = vals_200[0] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // second region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denominator+"&&"+z2,"goff");
  zs_200[1] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numerator+"&&"+z2,"goff");
  
  vals_200[1] = Nsel/Ntot;
  erhi_200[1] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[1];
  erlo_200[1] = vals_200[1] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
 
  // third region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denominator+"&&"+z3,"goff");
  zs_200[2] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numerator+"&&"+z3,"goff");
  
  vals_200[2] = Nsel/Ntot;
  erhi_200[2] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[2];
  erlo_200[2] = vals_200[2] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);

  // fourth region
  Ntot = pu200_gaus.Draw("abs(vtxZ) >> temp",denominator+"&&"+z4,"goff");
  zs_200[3] = 10.*temp.GetMean();
  Nsel = pu200_gaus.Draw("abs(vtxZ)",numerator+"&&"+z4,"goff");

  vals_200[3] = Nsel/Ntot;
  erhi_200[3] = TEfficiency::ClopperPearson(Ntot,Nsel,0.683,true) - vals_200[3];
  erlo_200[3] = vals_200[3] - TEfficiency::ClopperPearson(Ntot,Nsel,0.683,false);
  
  for( unsigned i = 0; i < 3; ++i ) {
    dens_200[i] = 200*mygaus.Eval(zs_200[i]);
    std::cout<< i<<" density region: "<<dens_200[i]<<"(events/mm) values: "<<vals_200[i]<<std::endl;
    std::cout << "200PU region " << i+1 << ' ' << zs_200[i] << ' ' << 200*mygaus.Eval(zs_200[i]) << ' ' <<   vals_200[i] << " +/- " << (erhi_200[i])  << "/" << ( erlo_200[i]) << std::endl;
    std::cout<<std::endl;
  }

  TGraphAsymmErrors *pu200_eff = new TGraphAsymmErrors (4,dens_200,vals_200,exl,exh,erlo_200,erhi_200);

  return pu200_eff;


}
