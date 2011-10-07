
#include "PAS_ICHEP/setTDRStyle_modified.C"
TH2D* hFIT = new TH2D();

void initVertex_XY_BeamFit(){

 setTDRStyle();
 tdrStyle->cd();

 //bool MC = true;
bool MC = false;
//string fileName = "OutNucl_BEAMPIPE.root";
string fileName = "OutNucl_MC.root";

string png = "BeamPipe_BEAMPIPE.png";



float scale = 1.;
float ampStart = 10;


 TFile *f = TFile::Open(fileName.c_str());
  

TCanvas* c1 = new TCanvas("c1", "", 500, 500);

//c1->SetFillColor(10);
//c1->cd();

TText T(1, 6.8, "Pixel Barrel Map");

//hFIT = (TH2D*) f->Get("XY_PIX_BARREL_ZOOM_15z20;1");
hFIT = (TH2D*) f->Get("XY_PIX_BARREL_ZOOM;1");

hFIT->SetTitle("");



//hVertexXY_SYM_ZOOM_rec->SetFillColor(10);
hFIT->SetStats(0);
hFIT->Draw();
 T.Draw();

 double x0, y0, R02;
 fit(x0, y0, R02);

 double R0 = sqrt(R02);

TEllipse L(x0, y0, R0, R0);
L.SetLineColor(kRed);
L.SetLineWidth(2);
L.SetFillStyle(0);
L.Draw();

gPad->SaveAs( png.c_str() );
//gPad->SaveAs( cng.c_str() );
}

// Macro myfunc.C



void myfunction(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

  Float_t x0 = par[0];
  Float_t y0 = par[1];
  Float_t R02 = par[2];

  double dx = 1000;

  f = 0;

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double rho2 = xbin*xbin + ybin*ybin;

      if (rho2 > 3.0*3.0 || rho2 < 2.5*2.5) continue;
      double R2 = (xbin-x0)*(xbin-x0) + (ybin-y0)*(ybin-y0);
      f += fabs(R2-R02)*hFIT->GetBinContent(i, j); 

    }

  }
}



void fit(double &x0, double &y0, double &R02){

  TMinuit* gMinuit = new TMinuit(3);

  gMinuit->SetPrintLevel(1);
  gMinuit->SetFCN(myfunction);

  double arglist[3];
  int ierflg = 0;
  gMinuit->mncler();

   // Set starting values and step sizes for parameters
   // double vstart[2] = {0.1180, 0.0};
   gMinuit->mnparm(0, "x0", 0, 0.01, 0, 0,ierflg);
   gMinuit->mnparm(1, "y0", 0, 0.01, 0, 0,ierflg);
   gMinuit->mnparm(2, "R02", 9, 0.01, 0, 0,ierflg);

   arglist[0] = 500.;
   arglist[1] = 1.;

   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

   double edm,errdef, chi2;
   int nvpar,nparx,icstat;
   gMinuit->mnstat(chi2,edm,errdef,nvpar,nparx,icstat);

   double x0err, y0err, R0err;
   gMinuit->GetParameter(0, x0, x0err);
   gMinuit->GetParameter(1, y0, y0err);
   gMinuit->GetParameter(2, R02, R0err);

//   cout << "MIGRAD" << endl;

   gMinuit->Clear();
}



