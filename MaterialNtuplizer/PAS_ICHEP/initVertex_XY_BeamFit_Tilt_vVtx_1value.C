#include "PAS_ICHEP/setTDRStyle_modified.C"
TH2D* hFIT = new TH2D();
TH1D* hBKG = new TH1D();

TF1* func = new TF1();

TF1* bkg = new TF1();

double R02_ref = 9;
double beam_size = 0.2;

bool secondStep = false;

void initVertex_XY_BeamFitMerged_Tilt_vVtx_1value(){

  setTDRStyle();
  tdrStyle->cd();

  func = new TF1("Func", "x*TMath::Power((1+[0]*[0]/(x*x)), 3./2)",1, 10);
  bkg = new TF1("Func", "[0]+x*[1]",2.4, 3.6);
 
  // bool bMC = true;
  bool bMC = false;
  // string fileName = "2011_MC_2T_isNucl.root";
  //    string fileName = "2011_4T_isNucl_before2T_wVtx.root"; 
  string fileName = "2011_2T_isNucl.root";
  string sBeamPipes("Plots_2T_3vtx_BeamCorr/BeamPipes_bkg1_isNucl_3Vtx.png");
  string sParameters("Plots_2T_3vtx_BeamCorr/Parameters_bkg1_isNucl_3Vtx.png");
  string sN("Plots_2T_3vtx_BeamCorr/Nnucl_vtx_bkg1_isNucl_3Vtx.png");
  string cBeamPipes("Plots_2T_3vtx_BeamCorr/BeamPipes_bkg1_isNucl_3Vtx.C");
  string cParameters("Plots_2T_3vtx_BeamCorr/Parameters_bkg1_isNucl_3Vtx.C");
  string rBeamPipes("Plots_2T_3vtx_BeamCorr/BeamPipes_bkg1_isNucl_3Vtx.root");
  string rParameters("Plots_2T_3vtx_BeamCorr/Parameters_bkg1_isNucl_3Vtx.root");
  /*
    string fileName = "2011_2T_isNucl_before2T.root";
    string sBeamPipes("Plots_2T_isNucl_before2T/BeamPipes_bkg1.png");
    string sParameters("Plots_2T_isNucl_before2T/Parameters_bkg1.png");
  */

  /*
    string fileName = "2011_2T_isNucl_after2T.root";
    string sBeamPipes("Plots_2T_isNucl_after2T/BeamPipes_bkg1.png");
    string sParameters("Plots_2T_isNucl_after2T/Parameters_bkg1.png");
  */


  float scale = 1.;
  float ampStart = 10;


  TFile *f = TFile::Open(fileName.c_str());

  TEllipse* L = new TEllipse(0, 0, 3, 3);  
  TEllipse* Ll = new TEllipse(0, 0, 3, 3);
  TEllipse* LL = new TEllipse(0, 0, 3, 3);

  TCanvas* c1 = new TCanvas("c1", "", 500, 500);

  TGraphErrors* gX = new TGraphErrors(1);
  TGraphErrors* gY = new TGraphErrors(1);
  TGraphErrors* gR = new TGraphErrors(1);


  TGraphErrors* rX = new TGraphErrors(1);
  TGraphErrors* rY = new TGraphErrors(1);
  TGraphErrors* rR = new TGraphErrors(1);
  TGraphErrors* rN = new TGraphErrors(1);

  rX->SetLineColor(kBlue);
  rY->SetLineColor(kBlue);
  rR->SetLineColor(kBlue);

  //c1->SetFillColor(10);
  //c1->cd();

 


  TText* T = new TText(1, 6.8, "Pixel Barrel Map");

  string png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE.png";
  int n = -1;
  int l = -1;
  int rn = -1;

  TCanvas* c2 = new TCanvas("c2", "", 500, 500);

  TCanvas* c0 = new TCanvas("c1", "", 1000, 1000);
  c0->Divide(4,4);

  for (int i = 8; i > -8; i--){

    cout << i << endl;
    double z = i*5-2.5;
    func->SetParameter(0, z);

    //hFIT = (TH2D*) f->Get("XY_PIX_BARREL_ZOOM_15z20;1");
    switch (i){
    case 8: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_35z40;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_35z40;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_35z40.png";
      T = new TText(-2, 0, "35 < z < 40");
      break;
    case 7: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_30z35;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_30z35;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_30z35.png";
      T = new TText(-2, 0, "30 < z < 35");
      break;
    case 6: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_25z30;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_25z30;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_25z30.png";
      T = new TText(-2, 0, "25 < z < 30");
      break;
    case 5: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_20z25;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_20z25;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_20z25.png";
      T = new TText(-2, 0, "20 < z < 25");
      break;
    case 4: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_15z20;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_15z20;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_15z20.png";
      T = new TText(-2, 0, "15 < z < 20");
      break;
    case 3: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_10z15;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_10z15;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_10z15.png";
      T = new TText(-2, 0, "10 < z < 15");
      break;
    case 2: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_5z10;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_5z10;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_5z10.png";
      T = new TText(-2, 0, "5 < z < 10");
      break;
    case 1: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_0z5;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_0z5;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_0z5.png";
      T = new TText(-2, 0, "0 < z < 5");
      break;
    case 0: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m5z0;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m5z0;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m5z0.png";
      T = new TText(-2, 0, "-5 < z < 0");
      break;
    case -1: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m10z5;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m10z5;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m10z5.png";
      T = new TText(-2, 0, "-10 < z < -5");
      break;
    case -2: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m15z10;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m15z10;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m15z10.png";
      T = new TText(-2, 0, "-15 < z < -10");
      break;
    case -3: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m20z15;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m20z15;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m20z15.png";
      T = new TText(-2, 0, "-20 < z < -15");
      break;
    case -4: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m25z20;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m25z20;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m25z20.png";
      T = new TText(-2, 0, "-25 < z < -20");
      break;
    case -5: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m30z25;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m30z25;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m30z25.png";
      T = new TText(-2, 0, "-30 < z < -25");
      break;
    case -6: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m35z30;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m35z30;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m35z30.png";
      T = new TText(-2, 0, "-35 < z < -30");
      break;
    case -7: 
      hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m40z35;1");
      hBKG = (TH1D*) f->Get("vtx_3RHO_BARREL_ZOOM_BEAMPIPE_m40z35;1");
      png = "Plots_2T_3vtx_BeamCorr/BeamPipe_BEAMPIPE_m40z35.png";
      T = new TText(-2, 0, "-40 < z < -35");
      break;

    default: break;

    }
    gStyle->SetPalette(1);

    c2->cd();
    hFIT->Draw("COLZ");
    c2->SaveAs(png.c_str());

    string png_beamcorr = png + "_beamcorr.png"; 
    
    c2->cd();

    TH2D* hFIT_BeamCorr = new TH2D();
    hFIT->Copy(*hFIT_BeamCorr);

    for (int k = 1; k <= hFIT->GetNbinsX(); k++){
      for (int l = 1; l <= hFIT->GetNbinsY(); l++){

	double x =   hFIT->GetXaxis()->GetBinCenter(k);
	double y =   hFIT->GetXaxis()->GetBinCenter(l);
      
      double x_beam = 0.08, y_beam = 0.04;
      
      double rho_bms = sqrt((x-x_beam)*(x-x_beam) + (y-y_beam)*(y-y_beam));

      double dz = 5.;

	  double width = hBKG->GetBinWidth(1);
  	double area =   hFIT->GetXaxis()->GetBinWidth(1) * hFIT->GetXaxis()->GetBinWidth(1);

	double rho = sqrt(x*x+y*y);

//      double solidAngle_bms = 3./(rho_bms) * 3./bkg->Eval(rho_bms);
//      double solidAngle_bms = 3./(rho) * 3./bkg->Eval(rho);
//	double solidAngle_bms = 9./(rho_bms*rho_bms);
	double solidAngle_bms = 9./(rho*rho);


      hFIT_BeamCorr->SetBinContent(k, l, hFIT->GetBinContent(k,l));///solidAngle_bms);
      }
    }

    hFIT_BeamCorr->Draw("COLZ");
    c2->SaveAs(png_beamcorr.c_str());

    c0->cd(3-(i+7));
    // c0->cd();
    hFIT->SetTitle("");
    
      
    


    substractBkg();
   
    //hVertexXY_SYM_ZOOM_rec->SetFillColor(10);
    hFIT->SetStats(0);
    hFIT->Draw();
    T->Draw();
    //     bkg->Draw();   
    c0->Update();


    secondStep = false;
   
    double z = i*5-2.5;

    double x0 = 0.09-0.0007*z, ex, y0 = -0.18+0.0007*z, ey, R02 = 2.93*2.93, eR02;
    if(bMC) x0 = 0., y0 = 0, R02 = 2.93*2.93;

    if (i < 100){

      bool converged = fit(x0, ex, y0, ey, R02, eR02);
      double x0_1 = x0, y0_1 = y0, R02_1 = R02;

      //   cout << "x0 = " << x0 << " y0 = " << y0 << " R = " << R << endl;

      if (converged){

	n++;
	double R0 = sqrt(R02);
	double eR0 = eR02/(2*R02);

	gX->Expand(n+1);
	gY->Expand(n+1);
	gR->Expand(n+1);

	gX->SetPoint(n, i*5-2.5, x0);
	gY->SetPoint(n, i*5-2.5, y0);
	gR->SetPoint(n, i*5-2.5, R0);

	gX->SetPointError(n, 2.5, ex);
	gY->SetPointError(n, 2.5, ey);
	gR->SetPointError(n, 2.5, eR0);

	secondStep = true;
	R02_ref = R02;
	//     beam_size = 0.25;
 
     
	converged = fit(x0, ex, y0, ey, R02, eR02);
	if (converged){
	  x0_1 = x0, y0_1 = y0, R02_1 = R02;
	  converged = fit(x0, ex, y0, ey, R02, eR02);
	}


	if (!converged){

	  x0 = x0_1, y0 = y0_1, R02 = R02_1;
	}
    
     
	double R0 = sqrt(R02);
	double eR0 = eR02/(2*R0);

	gX->SetPoint(n, i*5-2.5, x0);
	gY->SetPoint(n, i*5-2.5, y0);
	gR->SetPoint(n, i*5-2.5, R0);

	gX->SetPointError(n, 2.5, ex);
	gY->SetPointError(n, 2.5, ey);
	gR->SetPointError(n, 2.5, eR0);

	L = new TEllipse(x0, y0, R0, R0);
	L->SetLineColor(kMagenta);
	L->SetLineWidth(2);
	L->SetFillStyle(0);
	L->Draw();
     
       
	Ll = new TEllipse(x0, y0, R0-beam_size, R0-beam_size);
	Ll->SetLineColor(kMagenta);
	Ll->SetLineWidth(1);
	Ll->SetLineStyle(2);
	Ll->SetFillStyle(0);
	//     Ll->Draw();
     
	LL = new TEllipse(x0, y0, R0+beam_size, R0+beam_size);
	LL->SetLineColor(kMagenta);
	LL->SetLineWidth(1);
	Ll->SetLineStyle(2);
	LL->SetFillStyle(0);
	//     LL->Draw();
     

      }
    }

    rn++;

    rX->Expand(rn+1);
    rY->Expand(rn+1);
    rR->Expand(rn+1);
    rN->Expand(rn+1);

    double rx0=0, ry0=0, rR02=0, N=0;

    Riemann(rx0, ry0, rR02, N);
    rX->SetPoint(rn, i*5-2.5, rx0);
    rY->SetPoint(rn, i*5-2.5, ry0);
    rR->SetPoint(rn, i*5-2.5, sqrt(rR02));

    rX->SetPointError(rn, 2.5, 1e-10);
    rY->SetPointError(rn, 2.5, 1e-10);
    rR->SetPointError(rn, 2.5, 1e-10);

   
    rN->SetPoint(rn, i*5-2.5, N);
    rN->SetPointError(rn, 2.5, 1e-10);

  }

  TH1D* PLOTTERX = new TH1D("PLOTTERX", "", 1, -40, 40);
  PLOTTERX->SetMaximum(0.2);
  PLOTTERX->SetMinimum(0.0);

  if(bMC){
    PLOTTERX->SetMaximum(0.2);
    PLOTTERX->SetMinimum(-0.2);
  }

  TH1D* PLOTTERY = new TH1D("PLOTTERY", "", 1, -40, 40);
  PLOTTERY->SetMaximum(-0.1);
  PLOTTERY->SetMinimum(-0.3);
  if(bMC){
    PLOTTERY->SetMaximum(0.3);
    PLOTTERY->SetMinimum(-0.3);
  }

  TH1D* PLOTTER_R = new TH1D("PLOTTER_R", "", 1, -40, 40);
 PLOTTER_R->SetMaximum(3);
  PLOTTER_R->SetMinimum(2.5);
   
  TCanvas* c = new TCanvas();

  c->Divide(1,3);

  c->cd(1);
  PLOTTERX->SetYTitle("x0");
  PLOTTERX->Draw();
  gX->Draw("SAME");
  rX->Draw("SAME");

   
  TF1* fX = new TF1("fX", "[0]+[1]*x", -35, 35);
  double z0, x0, z1, x1;
  gX->GetPoint(1, z0, x0);
  gX->GetPoint(14, z1, x1);
   
  cout << "(x0+x1)/2 = " << (x1+x0)/2 << " slope = " << (x1-x0)/(z1-z0) << endl;
  double p0 = (x1+x0)/2, p1 = (x1-x0)/(z1-z0);
  fX->SetParameters(p0, p1);
  fX->SetParameter(0, p0);
  fX->SetParameter(1, p1);
   
  for (int i = 0; i < gX->GetN(); i++){
    double ey = gX->GetErrorY(i);
    gX->SetPointError(i, 2.5, ey*10);
  }

  gX->Fit(fX, "", "", -35, 35);
   
  for (int i = 0; i < gX->GetN(); i++){
    double ey = gX->GetErrorY(i);
    gX->SetPointError(i, 2.5, ey/10);
  }

   gX->Fit(fX, "", "", -35, 35);

   

  string s = "x = ";
  double r0 = fX->GetParameter(0), err0 = fX->GetParError(0), r1 = fX->GetParameter(1), err1 = fX->GetParError(1);
  s = s + "" + Form("%.3f", r0) + " +- " + Form("%4f", err0) + " + " + Form("%.6f", r1) + "+-" + Form("%.6f", err1) + "*z";
  T = new TText(-10, 0.3, s.data());
  T->SetTextSize(0.08);
  T->Draw();

  c->Update();

  c->cd(2);
  PLOTTERY->SetYTitle("y0");
  PLOTTERY->Draw();
  gY->Draw("SAME");
  rY->Draw("SAME");

  TF1* fY = new TF1("fY", "[0]+[1]*x", -35, 35);
  double z0, y0, z1, y1;
  gY->GetPoint(1, z0, y0);
  gY->GetPoint(14, z1, y1);
   
  cout << "(y0+y1)/2 = " << (y1+y0)/2 << " slope = " << (y1-y0)/(z1-z0) << endl;
  double p0 = (y1+y0)/2, p1 = (y1-y0)/(z1-z0);
  fY->SetParameters(p0, p1);
  fY->SetParameter(0, p0);
  fY->SetParameter(1, p1);
   
  for (int i = 0; i < gY->GetN(); i++){
    double ey = gY->GetErrorY(i);
    gY->SetPointError(i, 2.5, ey*10);
  }

  gY->Fit(fY, "", "", -35, 35);
   
  for (int i = 0; i < gY->GetN(); i++){
    double ey = gY->GetErrorY(i);
    gY->SetPointError(i, 2.5, ey/10);
  }

  gY->Fit(fY, "", "", -35, 35);

  string s = "y = "; 

  double r0 = fY->GetParameter(0), err0 = fY->GetParError(0), r1 = fY->GetParameter(1), err1 = fY->GetParError(1);
  s = s + "" + Form("%.3f", r0) + " +- " + Form("%4f", err0) + " + " + Form("%.6f", r1) + "+-" + Form("%.6f", err1) + "*z";
  T = new TText(-30, -0.28, s.data());
  T->SetTextSize(0.08);
  T->Draw();

  c->Update();

  c->cd(3);
  PLOTTER_R->SetYTitle("R0");
  PLOTTER_R->Draw();
  gR->Draw("SAME");
  rR->Draw("SAME");

  TF1* fR = new TF1("fR", "[0]+[1]*x", -35, 35);
  double z0, R0, z1, R1;
   
  gR->GetPoint(1, z0, R0);
  gR->GetPoint(14, z1, R1);
   
  cout << "(R0+R1)/2 = " << (R1+R0)/2 << " slope = " << (R1-R0)/(z1-z0) << endl;
   
  double p0 = (R1+R0)/2, p1 = 0;
  fR->SetParameter(0, p0);
  fR->SetParameter(1, p1);

  for (int i = 0; i < gR->GetN(); i++){
    double ey = gR->GetErrorY(i);
    gR->SetPointError(i, 2.5, ey*10);
  }


  gR->Fit(fR, "", "", -35, 35);

  for (int i = 0; i < gR->GetN(); i++){
    double ey = gR->GetErrorY(i);
    gR->SetPointError(i, 2.5, ey/10);
  }


     gR->Fit(fR, "", "", -35, 35);


  string s = "R0 = ";
  double r0 = fR->GetParameter(0), err0 = fR->GetParError(0), r1 = fR->GetParameter(1), err1 = fR->GetParError(1);
  s = s + "" + Form("%.2f", r0) + " +- " + Form("%2f", err0) + " + " + Form("%.2f", r1) + "+-" + Form("%.2f", err1) + "*z";
  T = new TText(-30, 2.65, s.c_str());
  T->SetTextSize(0.08);
  T->Draw();

  c->Update();

  c0->SaveAs(sBeamPipes.c_str());
  c->SaveAs(sParameters.c_str());
  c0->SaveAs(cBeamPipes.c_str());
  c->SaveAs(cParameters.c_str());
  c0->SaveAs(rBeamPipes.c_str());
  c->SaveAs(rParameters.c_str());

  c->cd();
  c->Clear();
  rN->Draw("ACL");
  c->SaveAs(sN.c_str());


  TFile* out= new TFile("Plots_2T_3vtx_BeamCorr/out_Parameters_bkg1_3vtx.root","recreate");
  gX->Write("gX");
  gY->Write("gY");
  gR->Write("gR");
  rX->Write("rX");
  rY->Write("rY");
  rR->Write("rR");
  rN->Write("rN");
  out->Close();
}

// Macro myfunc.C



void myfunction(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

  Float_t x0 = par[0];
  Float_t y0 = par[1];
  Float_t R02 = par[2];

  double dx = 1000;

  f = 0;

  double bwidth = 0.05/2;
  double sigma2 = bwidth*bwidth;///3;
  double rezo2 = 0.01*0.01;
  double R0 = sqrt(R02);

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double rho2 = xbin*xbin + ybin*ybin;
      if (rho2 < 2.6*2.6 || rho2 > 3.2*3.2 ) continue;
      double R = sqrt((xbin-x0)*(xbin-x0) + (ybin-y0)*(ybin-y0));
      if (secondStep) {
	//	if (R > sqrt(R02_ref)+beam_size) continue;
	//	if(fabs(R-R0) < bwidth) continue;
	//	else {
	//	double d = fabs(R-R0);//-bwidth;
	double d = fabs(R-R0);
	f += d*d/(sigma2+rezo2)*hFIT->GetBinContent(i, j);
	//	f += d*d*hFIT->GetBinContent(i, j);
	//	} 
      } else {
	double d = fabs(R-R0);
	f += d*d*hFIT->GetBinContent(i, j)*hFIT->GetBinContent(i, j);
      }
    }

  }
}



bool fit(double &x0, double& ex, double &y0, double &ey, double &R02, double &eR02){

  TMinuit* gMinuit = new TMinuit(3);

  gMinuit->SetPrintLevel(1);
  gMinuit->SetFCN(myfunction);

  double arglist[3];
  int ierflg = 0;
  gMinuit->mncler();

  // Set starting values and step sizes for parameters
  // double vstart[2] = {0.1180, 0.0};
  gMinuit->mnparm(0, "x0", x0, 0.01, 0, 0,ierflg);
  gMinuit->mnparm(1, "y0", y0, 0.01, 0, 0,ierflg);
  gMinuit->mnparm(2, "R02", R02, 0.01, 0, 0,ierflg);

  //gMinuit->FixParameter(2);

  arglist[0] = 500.;
  arglist[1] = 1.;

  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

  double edm,errdef, chi2;
  int nvpar,nparx,icstat;
  gMinuit->mnstat(chi2,edm,errdef,nvpar,nparx,icstat);

  gMinuit->GetParameter(0, x0, ex);
  gMinuit->GetParameter(1, y0, ey);
  gMinuit->GetParameter(2, R02, eR02);

  //   cout << "MIGRAD" << endl;

  gMinuit->Clear();

  return (chi2 > 1e-20);
}


substractBkg(){

  for (int i = 1; i <= hBKG->GetNbinsX(); i++){


    double x = hBKG->GetBinCenter(i);
    double solidAngle = 1./func->Eval(x);
    double d = hBKG->GetBinContent(i) * 1./solidAngle;

    hBKG->SetBinContent(i, d);

    if (x > 2.5 && x < 3.3) hBKG->SetBinError(i, 1e10);

  }
     
  hBKG->Fit(bkg, "", "", 2.3, 3.6);

  double width = hBKG->GetBinWidth(1);
  double area =   hFIT->GetXaxis()->GetBinWidth(1) * hFIT->GetXaxis()->GetBinWidth(1);

  for (int k = 1; k <= hFIT->GetNbinsX(); k++){
    for (int l = 1; l <= hFIT->GetNbinsY(); l++){

      double x =   hFIT->GetXaxis()->GetBinCenter(k);
      double y =   hFIT->GetXaxis()->GetBinCenter(l);



      double rho = sqrt(x*x + y*y);
      if (rho > 3.6) continue; 

      double bkgBin = hBKG->FindBin(rho);

      double solidAngle = 1./func->Eval(rho);

      
      double Content = hFIT->GetBinContent(k, l);


      double density = bkg->Eval(rho);

      double x_beam = 0.08, y_beam = 0.035;

      double rho_bms = sqrt((x-x_beam)*(x-x_beam) + (y-y_beam)*(y-y_beam));

      double dz = 5.;

//      double solidAngle_bms =  3./(rho_bms) * 3./bkg->Eval(rho_bms);

//      double solidAngle_bms =  3./(rho) * 3./bkg->Eval(rho);

//      double solidAngle_bms =  9./(rho_bms*rho_bms);// * 3./bkg->Eval(rho);
      double solidAngle_bms =  9./(rho*rho);// * 3./bkg->Eval(rho);



      double CorrectedContent = (Content - density*( area/(width*2*TMath::Pi()*rho))*solidAngle*1.0);//solidAngle_bms;
	
      if (CorrectedContent < 0) CorrectedContent = 0;

      CorrectedContent = abs(CorrectedContent);

     
      if ((rho < 2.4) && 1 == 0){
	std::cout << "Content = " << Content  << " rho = " << rho << " solidAngle = " << solidAngle << " area = " << area << " bkg area = " << area/(width*2*TMath::Pi()*rho) << endl;
	cout << "Content = " << Content << " density*solidAngle = " << density*solidAngle << " bkg = " << density*( area/(width*2*TMath::Pi()*rho))*solidAngle*0.8 << " corrected content = " <<  CorrectedContent << endl;
      }

      hFIT->SetBinContent(k, l, CorrectedContent);
    }
  }

}


void Riemann(double& rx0, double& ry0, double& rR02, double &N){
  
  double xg = 0, yg = 0, zg = 0, p2g = 0;


  TMatrix M(1,3);
  TMatrix Mg(1,3);
  TMatrix A(3,3);

  

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
      double Nbin = hFIT->GetBinContent(i, j);

      if (Nbin < 1e-5) continue;

      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double R2 = ybin*ybin + xbin*xbin;
      double R = sqrt(R2);
      double p = (1+R2);

      if (R < 2.6 || R > 3.2 ) continue;

      double cosPhi = xbin/R;
      double sinPhi = ybin/R;
      double x = R*cosPhi/p;
      double y = R*sinPhi/p;
      double z = R2/p;

      Mg[0][0] += x*Nbin;
      Mg[0][1] += y*Nbin;
      Mg[0][2] += z*Nbin;
      N += Nbin;

    }

  }

  Mg *= 1./N;

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){

      double Nbin = hFIT->GetBinContent(i, j);

      if (Nbin < 1e-5) continue;

      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double R2 = ybin*ybin + xbin*xbin;
      double R = sqrt(R2);
      double p = (1+R2);

      if (R < 2.6 || R > 3.2 ) continue;

      double cosPhi = xbin/R;
      double sinPhi = ybin/R;
      double x = R*cosPhi/p;
      double y = R*sinPhi/p;
      double z = R2/p;


      TMatrix Diff(1,3);

      Diff[0][0] = (x-Mg[0][0]);
      Diff[0][1] = (y-Mg[0][1]);
      Diff[0][2] = (z-Mg[0][2]);
      
      TMatrix ntDiff = Diff;
      TMatrix tDiff = Diff.Transpose(Diff);

      TMatrix mDiff = tDiff*ntDiff;

      A += Nbin*mDiff;

    }

  }

  cout << "N = " << N << endl;
  
  A *= (1.0/N);
  
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++)
      cout << " " << A[i][j];
    cout << ""<<endl;
  }

  TVectorF eigVal;

  TMatrix Egenv = A.EigenVectors(eigVal);

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++)
      cout << " " << Egenv[i][j];
    cout << " is Eigenv"<<endl;
  }




  for(int i = 0; i < 3; i++){
      cout << " " << eigVal[i];
  }

  cout << "" << endl;

  TMatrix n(3,1);
  n[0][0] = Egenv[0][2];
  n[1][0] = Egenv[1][2]; 
  n[2][0] = Egenv[2][2];
  


   TMatrix zero = A*n - eigVal[2]*n;

  
  for(int i = 0; i < 3; i++){
      cout << " " << n[i][0];
    cout << " is n "<<endl;
  }

  for(int i = 0; i < 3; i++){
      cout << " " << zero[i][0];
    cout << " is An - lbda*n "<<endl;
  }

  /*
  cout << "Norm = " << n[0][0]*n[0][0] + n[1][0]*n[1][0] + n[2][0]*n[2][0] << endl;

  for(int i = 0; i < 3; i++){
      cout << " " << Mg[0][i];
  }
  cout << " is Mg" << endl; 
  */

  double xg = Mg[0][0], yg = Mg[0][1], zg = Mg[0][2];
  double n0 = n[0][0], n1 = n[1][0], n2 = n[2][0];

  double c = -1*( xg*n0 + yg*n1 + zg*n2);

  //  cout << "c = " << c << endl;



  rx0 = -1.0/2 * n0/(c+n2);
  ry0 = -1* n[1][0]/(2*(c+n[2][0]));
  rR02 = ( n[0][0]*n[0][0] + n[1][0]*n[1][0] - 4*c*(c+n[2][0]) )/(4*(c+n[2][0]) * (c+n[2][0]));
  cout << "x0 = " << rx0 << " y0 = " << ry0 << " r0 = " << sqrt(rR02) << endl;
  
}
