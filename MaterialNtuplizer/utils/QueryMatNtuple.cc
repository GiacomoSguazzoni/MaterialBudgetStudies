// ###################################################################
// # Program to query the conversion and nuclear interaction ntuples #
// ###################################################################
// # Author: Mauro Dinardo                                           #
// ###################################################################
#ifndef __CINT__
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TLegend.h>
#include <TTree.h>
#endif

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#define VARtoPLOT "Z" // R or Z
#define NIorCONV  "NI" // NI or conv
#define MCorDATA  "MC" // MC or Data


void QueryMatNtuple (string varToPlot, string NIorConv, string MCorData)
{
  stringstream myString;
  string generalCut;
  TFile*_file0  = NULL;
  TTree* myTree = NULL;
  TCanvas* c0   = NULL;
  TH1D* h0      = NULL;

  if (NIorConv == "conv")
    {
      // ####################
      // # Conversion files #
      // ####################
      if (MCorData == "MC")
	_file0 = TFile::Open("ntuple_conversion_byHit_QCD_Pt-15to30_TuneZ2_7TeV_pythia6_GEN-SIM-RECODEBUG_PU_S6_START44_V5-v1_008F7171-D525-E111-8F0E-001EC9D7FA20.root");
	// _file0 = TFile::Open("ntuple_conversion_byPos_QCD_Pt-15to30_TuneZ2_7TeV_pythia6_GEN-SIM-RECODEBUG_PU_S6_START44_V5-v1_008F7171-D525-E111-8F0E-001EC9D7FA20.root");
	// _file0 = TFile::Open("ntuple_conversion_byPos_QCD_Pt-0to5_TuneZ2_7TeV_pythia6_GEN-SIM-RECO_PU_S6_START44_V9B-v1_008A3C79-C247-E111-B999-90E6BA19A20A.root");
      else if (MCorData == "Data")
	_file0 = TFile::Open("MaterialRun2011A_ntuple_conversion.root");
	// _file0 = TFile::Open("MaterialRun2011B_ntuple_conversion.root");


      myTree = (TTree*)_file0->Get("ntupleR2S");
      c0 = new TCanvas("c0","c0",10,10,700,500);
      c0->cd();
      if (varToPlot == "R")
	{
	  h0 = new TH1D("h0","h0",30.*6.,0,60);
	  h0->SetXTitle("R [cm]");
	}
      else if (varToPlot == "Z")
	{
	  h0 = new TH1D("h0","h0",30.*12.,-60,60);
	  h0->SetXTitle("Z [cm]");
	}
      h0->SetYTitle("Entries [#]");
      h0->SetFillColor(kGreen);
      

      // #######################
      // # Cut for conversions #
      // #######################
      if (MCorData == "MC") generalCut = "(isAssoc && pt1 > 0.1 && pt2 > 0.1 && nHits1 > 4 && nHits2 > 4 && q_hp == 1)";
      else if (MCorData == "Data") generalCut = "(pt1 > 0.1 && pt2 > 0.1 && nHits1 > 4 && nHits2 > 4 && q_hp == 1)";
      myString.str("");
      if (varToPlot == "R")
	{
	  myString << generalCut << " && abs(z) < 26";
	  myTree->Draw("sqrt(x*x+y*y)>>h0",myString.str().c_str());
	}
      else if (varToPlot == "Z")
	{
	  myString << generalCut << " && sqrt(x*x+y*y) > 3.5 && sqrt(x*x+y*y) < 19";
	  myTree->Draw("z>>h0",myString.str().c_str());
	}
    }
  else if (NIorConv == "NI")
    {
      // ############
      // # NI files #
      // ############
    if (MCorData == "MC")
      // _file0 = TFile::Open("ntuple_nuclint_byHit_QCD_Pt-15to30_TuneZ2_7TeV_pythia6_GEN-SIM-RECODEBUG_PU_S6_START44_V5-v1_008F7171-D525-E111-8F0E-001EC9D7FA20.root");
      _file0 = TFile::Open("ntuple_nuclint_byPos_QCD_Pt-15to30_TuneZ2_7TeV_pythia6_GEN-SIM-RECODEBUG_PU_S6_START44_V5-v1_008F7171-D525-E111-8F0E-001EC9D7FA20.root");
    else if (MCorData == "Data")
      _file0 = TFile::Open("MaterialRun2011A_ntuple_nuclint.root");
    // _file0 = TFile::Open("MaterialRun2011B_ntuple_nuclint.root");


    myTree = (TTree*)_file0->Get("ntupleR2S");
    c0 = new TCanvas("c0","c0",10,10,700,500);
    c0->cd();
    if (varToPlot == "R")
      {
	h0 = new TH1D("h0","h0",30.*6.,0,60);
	h0->SetXTitle("R [cm]");
      }
    else if (varToPlot == "Z")
      {
	h0 = new TH1D("h0","h0",30.*12.,-60,60);
	h0->SetXTitle("Z [cm]");
      }
    h0->SetYTitle("Entries [#]");
    h0->SetFillColor(kGreen);
 

    // ##############
    // # Cut for NI #
    // ##############
    if (MCorData == "MC") generalCut = "(isAssoc && ((isNucl && (nOut - nOutTkStep67Poor - nOutTkStep67Good > 0) && (mOut > 0.6) && (pt > 0.8 || pt < 0.1) && (ptOut > 0.5) && (angle < 15)) || (isNuclLoose && (nOut - nOutTkStep67Poor - nOutTkStep67Good == 2) && (mOut > 0.6) && (ptOut > 0.5) && (angle<15))))";
    else if (MCorData == "Data") generalCut = "((isNucl && (nOut - nOutTkStep67Poor - nOutTkStep67Good > 0) && (mOut > 0.6) && (pt > 0.8 || pt < 0.1) && (ptOut > 0.5) && (angle < 15)) || (isNuclLoose && (nOut - nOutTkStep67Poor - nOutTkStep67Good == 2) && (mOut > 0.6) && (ptOut > 0.5) && (angle<15)))";
    myString.str("");
    if (varToPlot == "R")
      {
	myString << generalCut << " && (angle < 15)";
	myTree->Draw("sqrt(x*x+y*y)>>h0",myString.str().c_str());
      }
    else if (varToPlot == "Z")
      {
	myString << generalCut << " && sqrt(x*x+y*y) > 3.5 && sqrt(x*x+y*y) < 19";
	myTree->Draw("z>>h0",myString.str().c_str());
      }
    }


  cout << "Query: " << myString.str().c_str() << endl;
  h0->Draw();
  c0->Update();
}


int main (int argc, char** argv)
{
  TApplication theApp ("Applications", &argc, argv);


  // ##########################
  // # Set histo layout style #
  // ##########################
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);
  gStyle->SetOptFit(1112);
  gStyle->SetOptStat(1110);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleOffset(1.3,"y"); 
  TGaxis::SetMaxDigits(3);

  QueryMatNtuple(VARtoPLOT,NIorCONV,MCorDATA);


  theApp.Run (); // Eventloop on air
}
