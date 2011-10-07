
#include "PAS_ICHEP/setTDRStyle_modified.C"

TH1F* hDATA = new TH1F();
TH1F* hMC = new TH1F();
TH1F* hMC_FAKE = new TH1F();

TH2F* hDATA2D = new TH2F();
TH2F* hMC2D = new TH2F();
TH2F* hMC_FAKE2D = new TH2F();

TString psFileName = "OutNucl_BEAMPIPE_0T.ps";

//string filein_data("OutNucl_BEAMPIPE_DATA.root");
//string filein_data("2011_MC_2T_isNucl.root");
//string filein_mc("2011_MC_2T_isNucl.root");

string filein_data("2011_2T_isNucl.root");
string filein_mc("2011_2T_isNucl.root");
string png_rep("Plots_2T_isNucl/");

/*
string filein_data("2011_4T_isNucl_before2T.root");
string filein_mc("2011_4T_isNucl_before2T.root");
string png_rep("Plots_4T_isNucl_before2T/");
*/
/*
string filein_data("2011_4T_isNucl_after2T.root");
string filein_mc("2011_4T_isNucl_after2T.root");
string png_rep("Plots_4T_isNucl_after2T/");
*/

string filein_data_norm("MC_2T_.root");
string filein_mc_norm("MC_2T_.root");

//string filein_data("OutNucl_DATA_pt15.root");
//string filein_mc("OutNucl_MC_pt15.root");

//string filein_data("OutNucl_DATA_20CMBARREL.root");
//string filein_mc("OutNucl_MC_20CMBARREL.root");
//string filein_data("OutNucl_NuclLoose_DATA.root");
//string filein_mc("OutNucl_NuclLoose_MC.root");


TF1* func = new TF1();

TF1* bkg = new TF1();

double bScaleSolidAngle = false;

string kind;

char* DATA;
char* MC;

bool bLbl = true;

TLegend* Legend = new TLegend();

	
TCanvas *Canvas = new TCanvas("APSPlots","APSPlots");
char *Title, *xTitle, *yTitle;

Bool_t bLogX = false, bLogY = false, bLegend = false;
Bool_t bUseDiffMC = false, bUseFake;

Bool_t bDrawData = true;
Bool_t bScale = false;
TText* T = new TText(1, 6.8, "Pixel Barrel Map");

bool bText = 0;

void Plot_NUCLEARS_BEAMPIPE(){

  func = new TF1("Func", "x*TMath::Power((1+[0]*[0]/(x*x)), 3./2)",1, 10);
  bkg = new TF1("Func", "[0]+x*[1]",2.4, 3.6);


  setTDRStyle();
  tdrStyle->cd();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.12);

  hMC->Sumw2(); 	hDATA->Sumw2(); 

  //	L_default->Copy(*Legend);
  Legend->SetFillColor(10);
  Legend->SetBorderSize(0);
  Legend->SetX1NDC(0.55); 	Legend->SetX2NDC(0.80);
  Legend->SetY1NDC(0.70); 	Legend->SetY2NDC(0.88);
  Legend->SetTextSize(0.04);
  
  TDatime* DateAndTime = new TDatime(); DateAndTime->Set();
  Int_t Date = DateAndTime->GetDate();
  char DateOut[50]; Int_t Year = Date/10000, Month = (Date-Year*10000)/100, 
		      Day = Date - Year*10000 - Month*100; 
  sprintf(DateOut,"%d/%.2d/%d", Day, Month, Year);
  
  TPaveText* Q2Date = new TPaveText(0.75, 0.0, 0.90, 0.03, "bNDC");
  Q2Date->SetBorderSize(0);
  Q2Date->SetLineColor(kBlack);
  Q2Date->AddText(DateOut);
  
  Canvas->SetFillColor(10);      // white background
  
  
  
  bDrawData = false;

  TPostScript *PSFile = new TPostScript(psFileName, 112);
 
  bText  = true;
 for (int i = 8; i > -8; i--){
   bScaleSolidAngle = true;
   cout << i << endl;

   double z = i*5-2.5;
   func->SetParameter(0, z);


   //hFIT = (TH2D*) f->Get("XY_PIX_BARREL_ZOOM_15z20;1");
   switch (i){
   case 8: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_35z40";
     T = new TText(-2, 0, "35 < z < 40");
     break;
   case 7: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_30z35";
     T = new TText(-2, 0, "30 < z < 35");
     break;
   case 6: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_25z30";
     T = new TText(-2, 0, "25 < z < 30");
     break;
   case 5: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_20z25";
     T = new TText(-2, 0, "20 < z < 25");
     break;
   case 4: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_15z20";
     T = new TText(-2, 0, "15 < z < 20");
     break;
   case 3:      
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_10z15";
     T = new TText(-2, 0, "10 < z < 15");
     break;
   case 2: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_5z10";
     T = new TText(-2, 0, "5 < z < 10");
     break;
   case 1: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_0z5";
     T = new TText(-2, 0, "0 < z < 5");
     break;
   case 0: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m5z0";
     T = new TText(-2, 0, "-5 < z < 0");
     break;
   case -1: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m10z5";
     T = new TText(-2, 0, "-10 < z < -5");
     break;
   case -2: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m15z10";
     T = new TText(-2, 0, "-15 < z < -10");
     break;
   case -3: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m20z15";
     T = new TText(-2, 0, "-20 < z < -15");
     break;
   case -4: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m25z20";
     T = new TText(-2, 0, "-25 < z < -20");
     break;
   case -5: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m30z25";
     T = new TText(-2, 0, "-30 < z < -25");
     break;
   case -6: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m35z30";
     T = new TText(-2, 0, "-35 < z < -30");
     break;
   case -7: 
     MC = "RHO_BARREL_ZOOM_BEAMPIPE_m40z35";
     T = new TText(-2, 0, "-40 < z < -35");
     break;

   default: break;

   }

   DATA = MC;

    Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm)"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
    Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;
  }


  PSFile->NewPage();


  bScaleSolidAngle = false;


  bText  = false;






  DATA = "RHO_BARREL_ZOOM_BEAMPIPE";  MC = "RHO_BARREL_ZOOM_BEAMPIPE"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm)"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x + 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_XMINUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_XMINUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x - 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();
  

  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_YPLUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y + 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();



  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_YMINUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_YMINUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y - 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();

  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x + 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_XMINUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_XMINUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x - 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();
  

  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_YPLUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y + 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();



  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_YMINUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_YMINUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y - 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();




















  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm)"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x + 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x - 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();
  

  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YPLUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y + 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();



  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y - 300 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();

  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x + 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) x - 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();
  

  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YPLUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y + 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();



  DATA = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS_700";  MC = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS_700"; Title = "Normalised to beam-pipe NI"; xTitle = "R shift beam (cm) y - 700 #mum"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();




  DATA = "dxy";  MC = "dxy"; Title = "dxy"; xTitle = "dxy"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();

  DATA = "M_Out";  MC = "M_Out"; Title = "M_Out"; xTitle = "M_Out"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();



  DATA = "M_Out_over_Pout";  MC = "M_Out_over_Pout"; Title = "M_Out/P_Out"; xTitle = "M_Out/P_Out"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();

  
  DATA = "M_Out_over_Pout";  MC = "M_Out_over_Pout"; Title = "M_Out/P_Out"; xTitle = "M_Out/P_Out"; yTitle = ""; bLogY=true; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();



  DATA = "M_Out_over_Pout_BeamPipe";  MC = "M_Out_over_Pout_BeamPipe"; Title = "M_Out_over_Pout_BeamPipe"; xTitle = "M_Out_over_Pout_BeamPipe"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "M_Out_over_Pout_BeamPipe";  MC = "M_Out_over_Pout_BeamPipe"; Title = "M_Out_over_Pout_BeamPipe"; xTitle = "M_Out_over_Pout_BeamPipe"; yTitle = ""; bLogY=true; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();


  DATA = "M_Out_BeamPipe";  MC = "M_Out_BeamPipe"; Title = "M_Out in beam pipe"; xTitle = "M_Out"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();

  DATA = "SinTheta_Out";  MC = "SinTheta_Out"; Title = "Sin Theta Out"; xTitle = "sin(\theta_{Out})"; yTitle = ""; bLogY=false; bLegend = true;  bUseDiffMC = true;
  
  Plots(); bLogY=false;bLegend = false;  bUseDiffMC = false;

  PSFile->NewPage();
 

  /*
  PSFile->NewPage();
  
  DATA = "RHOZ"; MC = ""; Title = "#rho"; xTitle = "z"; yTitle = "#rho"; bLogY=false; bLegend = false; 
  
  Plots2D(); bLogY=false; bLegend = false;
  */

  PSFile->Close();
  delete PSFile; 
}	

void Plots() {   

	TString* sDATA = new TString(""); sDATA->Append(DATA); sDATA->Append(";1");
	TString* sMC = new TString(""); 
	if (bUseDiffMC)  sMC->Append(MC); 
	else  sMC->Append(DATA);
	sMC->Append(";1");

	TString* sMC_FAKE = new TString(""); 
	if (bUseDiffMC)  sMC_FAKE->Append(MC); 
	else  sMC_FAKE->Append(DATA);
	sMC_FAKE->Append("_FAKE;1");


	cout << sDATA->Data() << endl;
	cout << sMC->Data() << endl;
	cout << sMC_FAKE->Data() << endl;
	TFile* FileData = new TFile(filein_data.data());

	hDATA = new TH1F(*((TH1F*)FileData->Get(sDATA->Data()))); 
	
	TFile* FileMC = new TFile(filein_mc.data());

	hMC = new TH1F(*((TH1F*)FileMC->Get(sMC->Data()))); 




	  if(FileMC->Get(sMC_FAKE->Data())){
	    bUseFake = true;
	    hMC_FAKE = new TH1F(*((TH1F*)FileMC->Get(sMC_FAKE->Data()))); 
	    /*
	    TH1F* hMCNuclLoose = new TH1F(*((TH1F*)FileMC->Get("isNUCLLOOSE;1"))); 
	    TH1F* hMCNuclLooseFake = new TH1F(*((TH1F*)FileMC->Get("isNUCLLOOSE_FAKE;1"))); 
	    cout << "All Nucl Loose = " <<  hMCNuclLoose->GetBinContent(2) 
		 << " fake Nucl Loose = " <<  hMCNuclLooseFake->GetBinContent(2) 
		 << " fake rate = " <<  hMCNuclLooseFake->GetBinContent(2)/hMCNuclLoose->GetBinContent(2)*100 << endl; 

	    TH1F* hMCNuclLoose = new TH1F(*((TH1F*)FileMC->Get("isNUCL;1"))); 
	    TH1F* hMCNuclLooseFake = new TH1F(*((TH1F*)FileMC->Get("isNUCL_FAKE;1"))); 
	    cout << "All Nucl = " <<  hMCNuclLoose->GetBinContent(2) 
		 << " fake Nucl = " <<  hMCNuclLooseFake->GetBinContent(2) 
		 << " fake rate = " <<  hMCNuclLooseFake->GetBinContent(2)/hMCNuclLoose->GetBinContent(2)*100 << endl; 
	    */
	  } else {
	    bUseFake = false;
	  }

	  bUseFake = false;

	  //	  TH1F* hMCNorm = new TH1F(*((TH1F*)FileMC->Get("ETA;1"))); 
	  // TH1F* hDATANorm = new TH1F(*((TH1F*)FileData->Get("ETA;1"))); 
	  //	  TFile* FileData_norm = new TFile(filein_data_norm.data());
	  //	  TFile* FileMC_norm = new TFile(filein_mc_norm.data());
	  TH1F* hMCNorm = new TH1F(*((TH1F*)FileMC->Get("isBEAMPIPE;1"))); 
	  TH1F* hDATANorm = new TH1F(*((TH1F*)FileData->Get("isBEAMPIPE_SHIFTBEAM;1"))); 



	Double_t IntDATA = hDATANorm->Integral();
	Double_t IntMC = hMCNorm->Integral();
	
	cout << "hMCNorm" << IntMC << " hDATANorm = " << IntDATA << endl;

	if (bScale){
	  hMC->Scale(IntDATA/IntMC);
	  if (bUseFake) hMC_FAKE->Scale(IntDATA/IntMC);
	}

	cout << "Before Set" << endl;

	SET();
	cout << "End" << endl;

}






void Plots2D() {   

	TString* sDATA = new TString(""); sDATA->Append(DATA); sDATA->Append(";1");
	TString* sMC = new TString(""); 
	if (bUseDiffMC)  sMC->Append(MC); 
	else  sMC->Append(DATA);
	sMC->Append(";1");

	TString* sMC_FAKE = new TString(""); 
	if (bUseDiffMC)  sMC_FAKE->Append(MC); 
	else  sMC_FAKE->Append(DATA);
	sMC_FAKE->Append("_FAKE;1");


	cout << sDATA->Data() << endl;
	cout << sMC->Data() << endl;
	cout << sMC_FAKE->Data() << endl;
	TFile* FileData = new TFile(filein_data.data());

	hDATA2D = new TH2F(*((TH2F*)FileData->Get(sDATA->Data()))); 
	
	TFile* FileMC = new TFile(filein_mc.data());

	hMC2D = new TH2F(*((TH2F*)FileMC->Get(sMC->Data()))); 


	  if(FileMC->Get(sMC_FAKE->Data())){
	    bUseFake = true;
	    hMC_FAKE2D = new TH2F(*((TH2F*)FileMC->Get(sMC_FAKE->Data()))); 
	  } else {
	    bUseFake = false;
	  }

	  
	  TH1F* hMCNorm = new TH1F(*((TH1F*)FileMC->Get("ETA;1"))); 
	  TH1F* hDATANorm = new TH1F(*((TH1F*)FileData->Get("ETA;1"))); 



	  Double_t IntDATA = hDATANorm->Integral();
	  Double_t IntMC = hMCNorm->Integral();
	
	  cout << "hMCNorm" << IntMC << " hDATANorm = " << IntDATA << endl;

	  if (bScale){
	    hMC2D->Scale(IntDATA/IntMC);
	    if (bUseFake) hMC_FAKE2D->Scale(IntDATA/IntMC);
	  }	  

	cout << "Before Set" << endl;

	SET2D();
	cout << "End" << endl;

}











void SET(){


  gPad->SetLogx(bLogX);
  gPad->SetLogy(bLogY);

  hMC->SetTitle("");
  hMC->SetTitleOffset(0.85, "X");
  hMC->SetXTitle(xTitle);
  hMC->SetYTitle(yTitle);

  hMC->SetStats(0); 
  hMC->SetLineColor(kBlack);
  hMC->SetFillColor(kGreen);

  
  if (bUseFake){
    hMC_FAKE->SetLineColor(kYellow);
    hMC_FAKE->SetFillColor(kYellow);
  }

  hDATA->SetMarkerColor(kBlack);
  hDATA->SetMarkerStyle(20);
  hDATA->SetMarkerSize(0.8);

  if (bScaleSolidAngle) Scale(hMC);

  Double_t max = hMC->GetMaximum();
  if (hDATA->GetMaximum() > max) max = hDATA->GetMaximum();

  if (bLogY)
    hMC->SetMaximum(2*hMC->GetMaximum());
  else 
    hMC->SetMaximum(1.1*max);

  hMC->SetMinimum(0.1);
  hMC->SetMaximum(1.25*hMC->GetMaximum());
  /*
  hMC->SetLabelSize(0.054, "Y");
  hMC->SetTitleSize(0.06, "Y");

  hMC->SetTitleOffset(0.95, "X");
  hMC->SetLabelSize(0.060, "X");
  hMC->SetTitleSize(0.070, "X");
  */

 

  hMC->DrawCopy("H");	
  if (bDrawData) hDATA->DrawCopy("SAMEPE");
  if (bUseFake) hMC_FAKE->DrawCopy("SAMEH");

  Legend->Clear();
  Legend->SetHeader(Title);

  TLegendEntry* lFitData = Legend->AddEntry(hDATA, " Data","p");
  TLegendEntry* lFitDjango = Legend->AddEntry(hMC, " MC","f");
  if (bUseFake) TLegendEntry* lFitDjango = Legend->AddEntry(hMC_FAKE, " Fakes","f");
  if (bLegend) Legend->Draw();

  Canvas->Update();

  if (bText) T->Draw();

  string png(png_rep.c_str());
  png.append(DATA);
  if (bLogY) png.append("_log");
  png.append(".png");

  gPad->SaveAs( png.c_str() );

}


void SET2D(){


  gPad->SetLogx(bLogX);
  gPad->SetLogy(bLogY);

  hMC2D->SetTitle("MC");
  hMC2D->SetXTitle(xTitle);
  hMC2D->SetYTitle(yTitle);

  hDATA2D->SetTitle("DATA");
  hDATA2D->SetXTitle(xTitle);
  hDATA2D->SetYTitle(yTitle);

  hMC_FAKE2D->SetTitle("MC_FAKE");
  hMC_FAKE2D->SetXTitle(xTitle);
  hMC_FAKE2D->SetYTitle(yTitle);

  hMC2D->SetStats(0); 

  Canvas->Clear();
  Canvas->Divide(2,2);

  gStyle->SetPalette(1);

  int max = 1.3*hDATA2D->GetMaximum();
  int min = 1.9;

  string opt = "COLZ";

  hDATA2D->SetMinimum(min);
  hMC2D->SetMinimum(min);
  hMC_FAKE2D->SetMinimum(min);

  hDATA2D->SetMaximum(max);
  hMC2D->SetMaximum(max);
  hMC_FAKE2D->SetMaximum(max);

  


  Canvas->cd(1);
  if (bDrawData) hDATA2D->DrawCopy(opt.data());


  string png("Plots/");
  png.append(DATA);
  png.append("_DATA.png");

  //  gPad->SaveAs( png.c_str() );

  Canvas->cd(2);
  hMC2D->DrawCopy(opt.data());
  
  string png("Plots/");
  png.append(DATA);
  png.append("_MC.png");

  //  gPad->SaveAs( png.c_str() );


  if (bUseFake) {

    Canvas->cd(3);
    hMC_FAKE2D->DrawCopy(opt.data());

  string png("Plots/");
  png.append(DATA);
  png.append("_FAKE.png");

  //  gPad->SaveAs( png.c_str() );

  }

  Canvas->Update();

}


void Scale(TH1F* dist){

  

  for (int i = 1; i <= dist->GetNbinsX(); i++){

    double x = dist->GetBinCenter(i);
    double d = dist->GetBinContent(i) * func->Eval(x);

    dist->SetBinContent(i, d);

    if (x > 2.5 && x < 3.3) dist->SetBinError(i, 1e10);

  }
     
  dist->Fit(bkg, "", "", 2.3, 3.6);
 

}
