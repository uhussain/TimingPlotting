
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include <math.h>
#include <TEfficiency.h>
#include <TMath.h>
#include <TFormula.h>
#include <iostream>
#include <string>
#include <iostream>
#include <cmath>
#include "TLegend.h"
#include "TPad.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TF1.h"
#include "THStack.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TTree.h"
#include "TPaveText.h"
#include "tdrstyle.C"
#include "TStyle.h"
#include "TAxis.h"
#include "TGaxis.h"

void applyPadStyle(TPad* pad1){
  pad1->SetFillColor(0);
  pad1->Draw();  pad1->cd();  pad1->SetLeftMargin(0.15);  pad1->SetBottomMargin(0.13); pad1->SetRightMargin(0.05);
  //pad1->SetGrid();
  pad1->SetGrid(10,10);
}

void plotFakes(){
  TString fileName = "timing-ZTT-PU200.root"; 
  TString treePath = "PFChargedBased/jetNtuple";
  int bins = 20;
  int low  = 0;
  int high = 200;

  TString isoCut = "2";
  //Plotting Variables
  TString variable = "jetPt";
  TString GenCut= "jetPt>18&&abs(jetEta)<2.1&&vtxIndex==0";
  TString RecoCut= "PFCharged<"+isoCut+"&&" + GenCut;
  TString RecoCut1= "PFChargedT2<"+isoCut+"&&" + GenCut;
  TString RecoCut2= "PFChargedT3<"+isoCut+"&&" + GenCut;


  //Style
  TString xaxis = "Jet p_{T} [GeV]";
  int markerstyle = 20;
  Color_t color = TColor::GetColor("#283593");//dark blue color1
  Color_t color1 = TColor::GetColor("#F44336");//red color4
  Color_t color2 = TColor::GetColor("#0288D1"); //green blue color2
  TString outFileName = "plotFakes-ZTT";

  setTDRStyle();
  //tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");

  TFile *tauFile    = new TFile(fileName);

  if(!tauFile->IsOpen()||tauFile==0){
    std::cout<<"ERROR FILE "<< fileName<<" NOT FOUND; EXITING"<<std::endl;
    exit(0);
  }

  TCanvas *Tcan= new TCanvas("Tcan","",100,20,600,600); Tcan->cd();  Tcan->SetFillColor(0);
  TPad* pad1 = new TPad("pad1","The pad",0,0,0.98,0.98);

  applyPadStyle(pad1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);

  TTree* tauTree = (TTree*)tauFile->Get(treePath);
  if(tauTree == 0){
    std::cout<<"ERROR Tau Tree is "<< tauTree<<" NOT FOUND; EXITING"<<std::endl;
    exit(0);
  }

  /// first
  TH1F* Denom;
  Denom = new TH1F("Denom","Denom",bins,low,high);
  Denom->Sumw2();
  tauTree->Draw(variable+">>+Denom",GenCut);

  TH1F* Num;
  Num = new TH1F("Num","Num",bins,low,high);
  tauTree->Draw(variable+">>+Num",RecoCut);

  Num->Divide(Denom);

  /// second
  TH1F* Denom1;
  Denom1 = new TH1F("Denom1","Denom1",bins,low,high);
  Denom1->Sumw2();
  tauTree->Draw(variable+">>+Denom1",GenCut);

  TH1F* Num1;
  Num1 = new TH1F("Num1","Num1",bins,low,high);
  tauTree->Draw(variable+">>+Num1",RecoCut1);

  Num1->Divide(Denom1);
  Num1->SetMarkerStyle(markerstyle);
  Num1->SetMarkerColor(color1);
  ////
  /// third
  TH1F* Denom2;
  Denom2 = new TH1F("Denom2","Denom2",bins,low,high);
  Denom2->Sumw2();
  tauTree->Draw(variable+">>+Denom2",GenCut);

  TH1F* Num2;
  Num2 = new TH1F("Num2","Num2",bins,low,high);
  tauTree->Draw(variable+">>+Num2",RecoCut2);

  Num2->Divide(Denom2);

  Num2->SetMarkerStyle(markerstyle);
  Num2->SetMarkerColor(color2);
  ////

  gStyle->SetErrorX(0.5);

  Num->GetXaxis()->SetTitle(xaxis);
  Num->GetYaxis()->SetTitle("Fake Proability ");
  Num->GetYaxis()->SetTitleOffset(1.1);
  Num->SetMarkerStyle(markerstyle);
  Num->SetMarkerColor(color);
  Num->Draw("P");
  Num1->Draw("P same");
  Num2->Draw("P same");

  Num->SetFillStyle(1001);
  Num->SetLineWidth((short)1.5);
  Num->SetMaximum(0.3);
  Num->SetMinimum(0);

  TLegend *leg = new TLegend(.5, .6, .77, .8,"","nbNDC");  
  leg->SetBorderSize(0);
  leg->SetShadowColor(kWhite);
  leg->SetFillColor(kWhite);
  leg->SetTextSize(0.03);
  //leg->AddEntry(pu200_eff,"PF Charged Iso All","PL"); 
  leg->AddEntry(Num,"Nominal PF Charged Isolation","PL");
  leg->AddEntry(Num1,"T2 Interval Track Req","PL");
  leg->AddEntry(Num2,"T3 Interval Track Req","PL");
  leg->Draw();


  Tcan->cd();
  Tcan->SaveAs(outFileName+".pdf");
}
