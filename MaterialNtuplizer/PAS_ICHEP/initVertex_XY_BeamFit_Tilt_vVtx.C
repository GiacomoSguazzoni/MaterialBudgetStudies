#include "PAS_ICHEP/setTDRStyle_modified.C"
TH2D* hFIT = new TH2D();
TH1D* hBKG = new TH1D();

TF1* func = new TF1();

TF1* bkg = new TF1();

double R02_ref = 9;
double beam_size = 0.2;

bool secondStep = false;

string sVtx;

TGraphErrors* mX = new TGraphErrors(15);
TGraphErrors* mY = new TGraphErrors(15);
TGraphErrors* mR = new TGraphErrors(15);

TGraphErrors* sX = new TGraphErrors(15);
TGraphErrors* sY = new TGraphErrors(15);
TGraphErrors* sR = new TGraphErrors(15);

//string sOutVtx = "Plots_2T_isNucl/OutVtx_isNucl.root";
//string sOutVtx_png = "Plots_2T_isNucl/OutVtx_isNucl.png";
//string fileName = "2011_2T_isNucl.root";
string sOutVtx = "Plots_4T_isNucl_Before/OutVtx_isNucl.root";
string sOutVtx_png = "Plots_4T_isNucl_Before/OutVtx_isNucl.png";
string fileName = "2011_4T_isNucl_before2T_wVtx.root";

string sXY, sBKG;

TFile *f;

void initVertex_XY_BeamFit_Tilt_vVtx(){
   
  setTDRStyle();
  tdrStyle->cd();

  TFile* out= new TFile(sOutVtx.c_str(),"recreate");
  out->Close();
  f = TFile::Open(fileName.c_str());
  for (int vtx = 2; vtx < 17; vtx++){
    
    initVertex_XY_BeamFit_Tilt(vtx);
    
  }
  f->Close();

  TFile* out= new TFile(sOutVtx.c_str(),"update");
  
  mX->SetTitle("meanX");
  mY->SetTitle("meanY");
  mR->SetTitle("meanR");
  sX->SetTitle("slopeX");
  sY->SetTitle("slopeY");
  sR->SetTitle("slopeR");


  mX->Write();
  mY->Write();
  mR->Write();
  sX->Write();
  sY->Write();
  sR->Write();

  out->Close();

  mX->SetMarkerSize(1);
  mY->SetMarkerSize(1);
  mR->SetMarkerSize(1);

  sX->SetMarkerSize(1);
  sY->SetMarkerSize(1);
  sR->SetMarkerSize(1);



  TCanvas* canVtx = new TCanvas();

  canVtx->Divide(2,3);

  canVtx->cd(1);

  TH1D* PLOTTERX = new TH1D("PLOTTERX", "", 16, 0.5, 16.5);
  PLOTTERX->SetYTitle("x0(z=0)");
  PLOTTERX->SetMaximum(0.2);
  PLOTTERX->SetMinimum(0.0);

  PLOTTERX->DrawCopy();
  mX->Draw("SAME");


  canVtx->cd(3);

  PLOTTERX->SetYTitle("y0(z=0)");
  PLOTTERX->SetMaximum(-0.1);
  PLOTTERX->SetMinimum(-0.3);

  PLOTTERX->DrawCopy();
  mY->Draw("SAME");


  canVtx->cd(5);

  
  PLOTTERX->SetYTitle("R0(z=0)");
  PLOTTERX->SetMaximum(3);
  PLOTTERX->SetMinimum(2.8);

  PLOTTERX->DrawCopy();
  mR->Draw("SAME");


  canVtx->cd(2);

 
  PLOTTERX->SetYTitle("slope x0");
  PLOTTERX->SetMaximum(0.0);
  PLOTTERX->SetMinimum(-0.010);

  PLOTTERX->DrawCopy();
  sX->Draw("SAME");


  canVtx->cd(4);

  PLOTTERX->SetYTitle("slope y0");
  PLOTTERX->SetMaximum(0.010);
  PLOTTERX->SetMinimum(0.0);

  PLOTTERX->DrawCopy();
  sY->Draw("SAME");


  canVtx->cd(6);

  PLOTTERX->SetYTitle("slope R0");
  PLOTTERX->SetMaximum(0.010);
  PLOTTERX->SetMinimum(-0.010);

  PLOTTERX->DrawCopy();
  sR->Draw("SAME");
 
  canVtx->SaveAs(sOutVtx_png.c_str());


}



void initVertex_XY_BeamFit_Tilt(int vtx){

  f->cd();


  func = new TF1("Func", "x*TMath::Power((1+[0]*[0]/(x*x)), 3./2)",1, 10);
  bkg = new TF1("Func", "[0]+x*[1]",2.4, 3.6);
 
  // bool bMC = true;
  bool bMC = false;
  // string fileName = "2011_MC_2T_isNucl.root";

  sVtx = string(Form("vtx_%d", vtx));

  cout << "sVtx = " << sVtx.c_str() << endl; 

  
  sOut = "Plots_4T_isNucl_Before/Out_isNucl_" + sVtx + ".png";
  sBeamPipes = "Plots_4T_isNucl_Before/BeamPipes_bkg1_isNucl_" + sVtx + ".png";
  sParameters = "Plots_4T_isNucl_Before/Parameters_bkg1_isNucl_"+ sVtx + ".png";



  /*

  string fileName = "2011_4T_isNucl_before2T.root";
  string sBeamPipes("Plots_4T_isNucl_Before_before2T/BeamPipes_bkg1.png");
  string sParameters("Plots_4T_isNucl_Before_before2T/Parameters_bkg1.png");
  */

  /*
    string fileName = "2011_4T_isNucl_after2T.root";
    string sBeamPipes("Plots_4T_isNucl_Before_after2T/BeamPipes_bkg1.png");
    string sParameters("Plots_4T_isNucl_Before_after2T/Parameters_bkg1.png");
  */


  float scale = 1.;
  float ampStart = 10;




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

  rX->SetLineColor(kBlue);
  rY->SetLineColor(kBlue);
  rR->SetLineColor(kBlue);

  //c1->SetFillColor(10);
  //c1->cd();

 


  TText* T = new TText(1, 6.8, "Pixel Barrel Map");

  string png = "Plots4T_isNucl/BeamPipe_BEAMPIPE.png";
  int n = -1;
  int l = -1;
  int rn = -1;

  TCanvas* c0 = new TCanvas("c1", "", 1000, 1000);
  c0->Divide(4,4);

  for (int i = 8; i > -8; i--){

    cout << i << endl;
    double z = i*5-2.5;
    func->SetParameter(0, z);

    //hFIT = (TH2D*) f->Get("XY_PIX_BARREL_ZOOM_15z20;1");
    switch (i){
    case 8: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_35z40;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_35z40;1";
      png = "Plots/BeamPipe_BEAMPIPE_35z40.png";
      T = new TText(-2, 0, "35 < z < 40");
      break;
    case 7: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_30z35;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_30z35;1";
      png = "Plots/BeamPipe_BEAMPIPE_30z35.png";
      T = new TText(-2, 0, "30 < z < 35");
      break;
    case 6: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_25z30;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_25z30;1";
      png = "Plots/BeamPipe_BEAMPIPE_25z30.png";
      T = new TText(-2, 0, "25 < z < 30");
      break;
    case 5: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_20z25;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_20z25;1";
      png = "Plots/BeamPipe_BEAMPIPE_20z25.png";
      T = new TText(-2, 0, "20 < z < 25");
      break;
    case 4: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_15z20;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_15z20;1";
      png = "Plots/BeamPipe_BEAMPIPE_15z20.png";
      T = new TText(-2, 0, "15 < z < 20");
      break;
    case 3: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_10z15;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_10z15;1";
      png = "Plots/BeamPipe_BEAMPIPE_10z15.png";
      T = new TText(-2, 0, "10 < z < 15");
      break;
    case 2: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_5z10;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_5z10;1";
      png = "Plots/BeamPipe_BEAMPIPE_5z10.png";
      T = new TText(-2, 0, "5 < z < 10");
      break;
    case 1: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_0z5;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_0z5;1";
      png = "Plots/BeamPipe_BEAMPIPE_0z5.png";
      T = new TText(-2, 0, "0 < z < 5");
      break;
    case 0: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m5z0;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m5z0;1";
      png = "Plots/BeamPipe_BEAMPIPE_m5z0.png";
      T = new TText(-2, 0, "-5 < z < 0");
      break;
    case -1: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m10z5;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m10z5;1";
      png = "Plots/BeamPipe_BEAMPIPE_m10z5.png";
      T = new TText(-2, 0, "-10 < z < -5");
      break;
    case -2: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m15z10;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m15z10;1";
      png = "Plots/BeamPipe_BEAMPIPE_m15z10.png";
      T = new TText(-2, 0, "-15 < z < -10");
      break;
    case -3: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m20z15;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m20z15;1";
      png = "Plots/BeamPipe_BEAMPIPE_m20z15.png";
      T = new TText(-2, 0, "-20 < z < -15");
      break;
    case -4: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m25z20;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m25z20;1";
      png = "Plots/BeamPipe_BEAMPIPE_m25z20.png";
      T = new TText(-2, 0, "-25 < z < -20");
      break;
    case -5: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m30z25;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m30z25;1";
      png = "Plots/BeamPipe_BEAMPIPE_m30z25.png";
      T = new TText(-2, 0, "-30 < z < -25");
      break;
    case -6: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m35z30;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m35z30;1";
      png = "Plots/BeamPipe_BEAMPIPE_m35z30.png";
      T = new TText(-2, 0, "-35 < z < -30");
      break;
    case -7: 
      sXY = sVtx + "XY_PIX_BARREL_ZOOM_m40z35;1";
      sBKG = sVtx + "RHO_BARREL_ZOOM_BEAMPIPE_m40z35;1";
      png = "Plots/BeamPipe_BEAMPIPE_m40z35.png";
      T = new TText(-2, 0, "-40 < z < -35");
      break;

    default: break;

    }

    hFIT = (TH2D*) f->Get(sXY.c_str());
    hBKG = (TH1D*) f->Get(sBKG.c_str());

    c0->cd(16-(i+7));
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

    cout << "RIEMANNING" << endl;

    rn++;

    rX->Expand(rn+1);
    rY->Expand(rn+1);
    rR->Expand(rn+1);

    double rx0, ry0, rR02;

    Riemann(rx0, ry0, rR02);
    rX->SetPoint(rn, i*5-2.5, rx0);
    rY->SetPoint(rn, i*5-2.5, ry0);
    rR->SetPoint(rn, i*5-2.5, sqrt(rR02));

    rX->SetPointError(rn, 2.5, 0.00001);
    rY->SetPointError(rn, 2.5, 0.00001);
    rR->SetPointError(rn, 2.5, 0.00001);

   
    cout << "END RIEMANNING" << endl;
  }

  cout << "PLOTTING" << endl;

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

  // gX->Fit(fX, "", "", -35, 35);

   

  string s = "x = ";
  double r0 = fX->GetParameter(0), err0 = fX->GetParError(0), r1 = fX->GetParameter(1), err1 = fX->GetParError(1);
  s = s + "" + Form("%.3f", r0) + " +- " + Form("%4f", err0) + " + " + Form("%.6f", r1) + "+-" + Form("%.6f", err1) + "*z";
  T = new TText(-10, 0.16, s.data());
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

  //  gY->Fit(fY, "", "", -35, 35);

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


  //   gR->Fit(fR, "", "", -35, 35);

  cout << "FILLING" << endl;
    
  mX->SetPoint(vtx-2, vtx, fX->GetParameter(0));
  mY->SetPoint(vtx-2, vtx, fY->GetParameter(0));
  mR->SetPoint(vtx-2, vtx, fR->GetParameter(0));
  
  mX->SetPointError(vtx-2, 1./2, fX->GetParError(0));
  mY->SetPointError(vtx-2, 1./2, fY->GetParError(0));
  mR->SetPointError(vtx-2, 1./2, fR->GetParError(0));
    
  sX->SetPoint(vtx-2, vtx, fX->GetParameter(1));
  sY->SetPoint(vtx-2, vtx, fY->GetParameter(1));
  sR->SetPoint(vtx-2, vtx, fR->GetParameter(1));
    
  sX->SetPointError(vtx-2, 1./2, fX->GetParError(1));
  sY->SetPointError(vtx-2, 1./2, fY->GetParError(1));
  sR->SetPointError(vtx-2, 1./2, fR->GetParError(1));




  string s = "R0 = ";
  double r0 = fR->GetParameter(0), err0 = fR->GetParError(0), r1 = fR->GetParameter(1), err1 = fR->GetParError(1);
  s = s + "" + Form("%.2f", r0) + " +- " + Form("%2f", err0) + " + " + Form("%.2f", r1) + "+-" + Form("%.2f", err1) + "*z";
  T = new TText(-30, 2.65, s.c_str());
  T->SetTextSize(0.08);
  T->Draw();

  c->Update();

  c0->SaveAs(sBeamPipes.c_str());
  c->SaveAs(sParameters.c_str());

  TFile* out= new TFile(sOutVtx.c_str(),"update");
  gX->SetTitle(Form("gX_%d", vtx));
  gY->SetTitle(Form("gY_%d", vtx));
  gR->SetTitle(Form("gR_%d", vtx));
  gX->Write();
  gY->Write();
  gR->Write();

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

      double CorrectedContent = Content - density*( area/(width*2*TMath::Pi()*rho))*solidAngle*1.0;
	
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


void Riemann(double& rx0, double& ry0, double& rR02){
  
  cout << "Begin riemann" << endl;


  double xg = 0, yg = 0, zg = 0, p2g = 0;

  double N = 0;

  TMatrix M(1,3);

  TMatrix A(3,3);

  double xM=0, yM=0, zM=0;

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
      
      xM += x*Nbin;
      yM += y*Nbin;
      zM += z*Nbin;
      
      N += Nbin;
      
    }

  }

  TMatrix Mg(1,3);
     
  Mg[0][0] = xM;
  Mg[0][1] = yM;
  Mg[0][2] = zM;


  N = N+1e-10;

  Mg *= 1./(N);
  


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



  rx0 = -1.0/2 * n0/(1e-10+c+n2);
  ry0 = -1* n[1][0]/(2*(1e-10+c+n[2][0]));
  rR02 = ( n[0][0]*n[0][0] + n[1][0]*n[1][0] - 4*c*(c+n[2][0]) )/(4*(1e-10+c+n[2][0]) * (c+n[2][0]));
  cout << "x0 = " << rx0 << " y0 = " << ry0 << " r0 = " << sqrt(rR02) << endl;
  
}
