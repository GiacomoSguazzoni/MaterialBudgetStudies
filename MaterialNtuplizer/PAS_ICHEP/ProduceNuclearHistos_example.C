int nbins, nbins1, nbins2; 
double min, max;
double min1, max1;
double min2, max2;
string histo_title;
string xaxis_title;
string plotName, plotNameFake;
string variable, variable1, variable2;
TCut cut;
 TCut cut0;
// TCut generalCut = "(isNucl || isNuclLoose) ";
///TCut nuclCut = "isNucl && (tkDxy[0] > 0.15 || tkDxy[0] < -0.15) && (tkDxy[1] > 0.15 || tkDxy[1] < -0.15) && (tkDxy[2] > 0.15 || tkDxy[2] < -0.15)";// && nOut - nOutTkStep67Poor - nOutTkStep67Good > 0 && mOut > 0.6 && (pt > 0.8 || pt < 0.1) && ptOut > 0.5 && angle < 15";
///TCut nuclLooseCut = "isNuclLoose && (tkDxy[0] > 0.15 || tkDxy[0] < -0.15) && (tkDxy[1] > 0.15 || tkDxy[1] < -0.15) && (tkDxy[2] > 0.15 || tkDxy[2] < -0.15)"; // && nOut - nOutTkStep67Poor - nOutTkStep67Good == 2 && mOut > 0.6 && ptOut > 0.5 && angle < 15";
//TCut generalCut =  (nuclCut || nuclLooseCut) && "mOut/ptOut > 0.8";
TCut runs = "run == 153191";
TCut nuclCut = "isNucl && (tkDxy[0] > 0.3 || tkDxy[0] < -0.3) && (tkDxy[1] > 0.3 || tkDxy[1] < -0.3) && mOut > 0.7 && evt_NofflineVtx < 6.1";//  && angle < 6";// && (nOutTkStep67Poor + nOutTkStep67Good == 0)";
TCut nuclLooseCut = "isNuclLoose && (tkDxy[0] > 0.3 || tkDxy[0] < -0.3) && (tkDxy[1] > 0.3 || tkDxy[1] < -0.3) && mOut > 0.7 && evt_NofflineVtx <  6.1";
TCut generalCut =  (nuclCut);// || nuclLooseCut); // && "mOut/ptOut*sin(thetaOut) > 0.25")
TCut cutFAKE = "isAssoc==0";
// TCut generalCut = "";
TCut BarrelCut = "TMath::Abs(z) < 1000";
TCut TIBCut = "TMath::Abs(z) < 20 && rho > 17";
TCut FPIXCut = "rho < 19";

TCut RailCut = "!( (phiOut > -2*TMath::Pi()/3 && phiOut < -1*TMath::Pi()/3) || (phiOut > TMath::Pi()/3 && phiOut < 2*TMath::Pi()/3) )";



 TH1F* numRecVertex1 = new TH1F();
 TH2F* numRecVertex2 = new TH2F();
 TH3F* numRecVertex3 = new TH3F();

 TFile *f1, *f2, *write;

bool bDATA = false;

 TCanvas* Canvas  = new TCanvas("Canvas", "",  500, 500);

TTree* R2S;

void ProduceNuclearHistos_example(){

 


  string s_file = "example_NI.root";
  
//  string s1 = "/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/4T/20110531_ntuple_nuclint.root"; bDATA = false;

  string s1 = "ntuple_NI.root";

  f1  = TFile::Open(s1.data());


  R2S = ntupleR2S->CopyTree(generalCut);

 R2S->SetAlias("rho", "sqrt(x*x+y*y)");

 R2S->SetAlias("PIX_x", "-0.147");
 R2S->SetAlias("PIX_y", "-0.378");
 R2S->SetAlias("PIX_z", "-0.485");
 R2S->SetAlias("PIX_z06", "-0.6");
 R2S->SetAlias("rhoShift", "sqrt( (x-PIX_x)*(x-PIX_x)+(y-PIX_y)*(y-PIX_y) )");
 R2S->SetAlias("p", "sqrt( (x-PIX_x)*(x-PIX_x)+(y-PIX_y)*(y-PIX_y) )");

 R2S->SetAlias("cosShift", "(x-PIX_x)/rhoShift");

 R2S->SetAlias("zShift", "z-PIX_z");

 R2S->SetAlias("P", "ptOut");

 if (bDATA) generalCut =  generalCut;
 else generalCut =  generalCut;

 RailCut = "cosShift < -1/2.  || cosShift > 1/2.";


 /*
FCN=10340.4 FROM MIGRAD    STATUS=CONVERGED     280 CALLS         281 TOTAL
                     EDM=0.000144842    STRATEGY= 1      ERROR MATRIX ACCURATE
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  x0           7.51145e-02   2.08214e-04   6.84889e-06  -4.70489e+01
   2  y0          -1.73901e-01   1.52677e-04   5.91533e-06   1.07475e+02
   3  R0           8.51282e+00   7.63835e-04   2.21906e-05   9.53501e+00
 EXTERNAL ERROR MATRIX.    NDIM=  25    NPAR=  3    ERR DEF=1
  4.335e-08  1.558e-08  1.174e-07
  1.558e-08  2.331e-08  6.554e-08
  1.174e-07  6.554e-08  5.834e-07
 PARAMETER  CORRELATION COEFFICIENTS
       NO.  GLOBAL      1      2      3
        1  0.74377   1.000  0.490  0.738
        2  0.57294   0.490  1.000  0.562
        3  0.77309   0.738  0.562  1.000
 */


 /*

MC beam pipe corrected:

   2  Mean         2.93989e+00   2.10168e-04   1.43973e-06   2.37972e-02
   3  Sigma        3.04202e-02   1.55038e-04   9.49746e-06  -2.13246e-03



DATA BEAM PIPE CORRECTED

   2  Mean         2.93656e+00   1.24991e-04   1.85890e-06  -1.25195e-03
   3  Sigma        3.28939e-02   9.03305e-05   1.13489e-05  -6.52762e-04

 */

 R2S->SetAlias("x_minus", "-0.03");
 R2S->SetAlias("x_plus", "+0.03");
 R2S->SetAlias("y_minus",  "-0.03");
 R2S->SetAlias("y_plus", "+0.03");


 R2S->SetAlias("BEAM_x_shift_minus", "0.086-0.03-0.0007*z");
 R2S->SetAlias("BEAM_x_shift_plus", "0.086+0.03-0.0007*z");
 R2S->SetAlias("BEAM_y_shift_minus", "-0.197-0.03+0.0007*z");
 R2S->SetAlias("BEAM_y_shift_plus", "-0.197+0.03+0.0005*z");


 R2S->SetAlias("BEAM_x_shift_minus_700", "0.086-0.07-0.0007*z");
 R2S->SetAlias("BEAM_x_shift_plus_700", "0.086+0.07-0.0007*z");
 R2S->SetAlias("BEAM_y_shift_minus_700", "-0.197-0.07+0.0007*z");
 R2S->SetAlias("BEAM_y_shift_plus_700", "-0.197+0.07+0.0007*z");

 R2S->SetAlias("BEAM_x", "0.086-0.0007*z");
 R2S->SetAlias("BEAM_y", "-0.197+0.0007*z");
 R2S->SetAlias("rhoShiftBeam", "sqrt( (x-BEAM_x)*(x-BEAM_x)+(y-BEAM_y)*(y-BEAM_y) )");
 R2S->SetAlias("rhoShiftBeam_xminus", "sqrt( (x-BEAM_x_shift_minus)*(x-BEAM_x_shift_minus)+(y-BEAM_y)*(y-BEAM_y) )");
 R2S->SetAlias("rhoShiftBeam_xplus", "sqrt( (x-BEAM_x_shift_plus)*(x-BEAM_x_shift_plus)+(y-BEAM_y)*(y-BEAM_y) )");
 R2S->SetAlias("rhoShiftBeam_yminus", "sqrt( (x-BEAM_x)*(x-BEAM_x)+(y-BEAM_y_shift_minus)*(y-BEAM_y_shift_minus) )");
 R2S->SetAlias("rhoShiftBeam_yplus", "sqrt( (x-BEAM_x)*(x-BEAM_x)+(y-BEAM_y_shift_plus)*(y-BEAM_y_shift_plus) )");


 R2S->SetAlias("rhoBeam_xminus", "sqrt( (x-x_minus)*(x-x_minus)+y*y )");
 R2S->SetAlias("rhoBeam_xplus", "sqrt( (x-x_plus)*(x-x_plus)+y*y )");
 R2S->SetAlias("rhoBeam_yminus", "sqrt( x*x+(y-y_minus)*(y-y_minus) )");
 R2S->SetAlias("rhoBeam_yplus", "sqrt( x*x+(y-y_plus)*(y-y_plus) )");


  write  = new TFile(s_file.data(), "RECREATE");

 //PSFile = new TPostScript(psFileName, 112);

// ================ BEGINING OF REC STUDY ================ //





//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 280;
 min = -70, max = min + nbins*0.5;
 nbins1 = 280;
 min1 = -70, max1 = min1 + nbins1*0.5;
 nbins2 = 600;
 min2 = -150, max2 = min2 + nbins2*0.5;

 plotName  = "TRACKER";
 histo_title = "TRACKER";
 xaxis_title = "x Nucl (cm)";
 yaxis_title = "y Nucl (cm)";
 zaxis_title = "z Nucl (cm)";
 variable = "x";
 variable1 = "y";
 variable2 = "z";

 cut0 = "";
 cut = cut0&&generalCut;

 PlottiPlotta3D();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 400; 
 min = -20, max = min + nbins*0.1;
 nbins1 = 400; 
 min1 = -20, max1 = min1 + nbins1*0.1;
 nbins2 = 1200;
 min2 = -60, max2 = min2 + nbins2*0.1;

 plotName  = "PIXEL";
 histo_title = "PIXEL";
 xaxis_title = "x Nucl (cm)";
 yaxis_title = "y Nucl (cm)";
 zaxis_title = "z Nucl (cm)";
 variable = "x";
 variable1 = "y";
 variable2 = "z";

 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta3D();




}





void setParams(TH1F* f, char* title, int Color, int Style, int Width){


  f->SetStats(0);
  f->Sumw2();

  f->SetXTitle(title);

  f->SetTitleSize(0.06, "X");
  f->SetTitleOffset(0.6, "X");

  f->SetLineColor(Color);
  f->SetLineStyle(Style);
  f->SetLineWidth(Width);



}


void setParams(TH2F* f, char* title, int Color, int Style, int Width){


  f->SetStats(0);
  f->Sumw2();

  f->SetXTitle(title);

  f->SetTitleSize(0.06, "X");
  f->SetTitleOffset(0.6, "X");

  f->SetLineColor(Color);
  f->SetLineStyle(Style);
  f->SetLineWidth(Width);



}




void PlottiPlotta(){

 Canvas->Clear();
 Canvas->cd();


 f1->cd();
 numRecVertex1 = new TH1F("numRecVertex1", histo_title.data(), nbins, min, max);
 setParams(numRecVertex1, xaxis_title.data(), 1, 1, 2); 
 string plot = variable + ">> numRecVertex1";
 //     R2S->Draw(plot.data(), cut, opt.data(), 100000000, 10000);
 R2S->Draw(plot.data(), cut, "", 10000000, 0);

 Canvas->Update(); 

 write->cd();
 numRecVertex1->Write(plotName.data());

 if (!bDATA){
   numRecVertex1 = new TH1F("numRecVertex1", histo_title.data(), nbins, min, max);
   plotNameFake = plotName+"_FAKE";

   R2S->Draw(plot.data(), cut&&cutFAKE, "", 100000000, 0);

   write->cd();
   numRecVertex1->Write(plotNameFake.data());
 }

}



void PlottiPlotta2D(){

 Canvas->Clear();
 Canvas->cd();


 f1->cd();
 numRecVertex2 = new TH2F("numRecVertex2", histo_title.data(), nbins, min, max, nbins1, min1, max1);
 setParams(numRecVertex2, xaxis_title.data(), 1, 1, 2); 
 string plot = "" + variable + ":" + variable1 + ">> numRecVertex2";
 cout << plot.data() << endl;
 //     R2S->Draw(plot.data(), cut, opt.data(), 100000000, 10000);
 R2S->Draw(plot.data(), cut, "", 100000000, 0);

 write->cd();
 numRecVertex2->Write(plotName.data());

 if(!bDATA){
   numRecVertex2 = new TH2F("numRecVertex2", histo_title.data(), nbins, min, max, nbins1, min1, max1);
   plotNameFake = plotName+"_FAKE";

   R2S->Draw(plot.data(), cut&&cutFAKE, "", 100000000, 0);

   write->cd();
   numRecVertex2->Write(plotNameFake.data());
 }
}

void PlottiPlotta3D(){

 Canvas->Clear();
 Canvas->cd();


 f1->cd();
 numRecVertex3 = new TH3F("numRecVertex3", histo_title.data(), nbins, min, max, nbins1, min1, max1, nbins2, min2, max2);
// setParams(numRecVertex3, xaxis_title.data(), 1, 1, 2); 
 string plot = "" + variable2 + ":" + variable1 + ":" + variable + ">> numRecVertex3";
 cout << plot.data() << endl;
 //     R2S->Draw(plot.data(), cut, opt.data(), 100000000, 10000);
 R2S->Draw(plot.data(), cut, "", 100000000, 0);

 write->cd();
 numRecVertex3->Write(plotName.data());
 /*
 if(!bDATA){
   numRecVertex2 = new TH3F("numRecVertex3", histo_title.data(), nbins, min, max, nbins1, min1, max1);
   plotNameFake = plotName+"_FAKE";

   R2S->Draw(plot.data(), cut&&cutFAKE, "", 100000000, 0);

   write->cd();
   numRecVertex2->Write(plotNameFake.data());
 }
 */
}


