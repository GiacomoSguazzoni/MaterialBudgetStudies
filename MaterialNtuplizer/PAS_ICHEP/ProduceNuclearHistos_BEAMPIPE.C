int nbins, nbins1; 
double min, max;
double min1, max1;
string histo_title;
string xaxis_title;
string plotName, plotNameFake;
string variable, variable1;
TCut cut;
 TCut cut0;
// TCut generalCut = "(isNucl || isNuclLoose) ";
///TCut nuclCut = "isNucl && (tkDxy[0] > 0.15 || tkDxy[0] < -0.15) && (tkDxy[1] > 0.15 || tkDxy[1] < -0.15) && (tkDxy[2] > 0.15 || tkDxy[2] < -0.15)";// && nOut - nOutTkStep67Poor - nOutTkStep67Good > 0 && mOut > 0.6 && (pt > 0.8 || pt < 0.1) && ptOut > 0.5 && angle < 15";
///TCut nuclLooseCut = "isNuclLoose && (tkDxy[0] > 0.15 || tkDxy[0] < -0.15) && (tkDxy[1] > 0.15 || tkDxy[1] < -0.15) && (tkDxy[2] > 0.15 || tkDxy[2] < -0.15)"; // && nOut - nOutTkStep67Poor - nOutTkStep67Good == 2 && mOut > 0.6 && ptOut > 0.5 && angle < 15";
//TCut generalCut =  (nuclCut || nuclLooseCut) && "mOut/ptOut > 0.8";
TCut runs = "run == 153191";
TCut nuclCut = "isNucl && (tkDxy[0] > 0.3 || tkDxy[0] < -0.3) && (tkDxy[1] > 0.3 || tkDxy[1] < -0.3) && mOut > 0.7 && evt_NofflineVtx < 2.1";//  && angle < 6";// && (nOutTkStep67Poor + nOutTkStep67Good == 0)";
TCut nuclLooseCut = "isNuclLoose && (tkDxy[0] > 0.3 || tkDxy[0] < -0.3) && (tkDxy[1] > 0.3 || tkDxy[1] < -0.3) && mOut > 0.7 && evt_NofflineVtx < 2.1";
TCut generalCut =  (nuclCut || nuclLooseCut); // && "mOut/ptOut*sin(thetaOut) > 0.25")
TCut cutFAKE = "isAssoc==0";
// TCut generalCut = "";
TCut BarrelCut = "TMath::Abs(z) < 1000";
TCut TIBCut = "TMath::Abs(z) < 20 && rho > 17";
TCut FPIXCut = "rho < 19";

TCut RailCut = "!( (phiOut > -2*TMath::Pi()/3 && phiOut < -1*TMath::Pi()/3) || (phiOut > TMath::Pi()/3 && phiOut < 2*TMath::Pi()/3) )";



 TH1F* numRecVertex1 = new TH1F();
 TH2F* numRecVertex2 = new TH2F();
TFile *f1, *f2, *write;

bool bDATA = false;

 TCanvas* Canvas  = new TCanvas("Canvas", "",  500, 500);

TTree* R2S;

void ProduceNuclearHistos_BEAMPIPE(){

 

  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/CMSSW_358p3/NuclearSkim_CMSSW358p3_goodcoll7TeV_R2S_20100525_HighPurity.root";  bDATA = true;

  //  string s1 = "NuclearSkim_CMSSW358p3_goodcoll7TeV_R2S_20100604_HighPurity.root";  bDATA = true;

  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/CMSSW_358p3/NuclearSkim_CMSSW358p3_minbias7TeV_R2S_20100604_HighPurity.root";  bDATA = false;

  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/CMSSW_358p3/NuclearSkim_CMSSW358p3_minbias7TeV_R2S_20100604_HighPurity_v2.root";  bDATA = false;

  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/CMSSW_358p3/NuclearSkim_CMSSW358p3_goodcoll7TeV_R2S_20100604_HighPurity.root";  bDATA = true;
  //    string s1 = "~sguazz/public/xLloyd/ntuple_nuclint_HIRun2010_4T.root";  bDATA = true;
  //  string s1 = "/tmp/mgouzevi/ntuple_nuclint.root"; bDATA = false;
 
//  string s1 = "/afs/cern.ch/user/s/sguazz/public/xLloyd/ntuple_nuclint_HIRun2010_0T_10k.root";
//  string s1 = "~sguazz/public/xLloyd/ntuple_nuclint_HIRun2010_0T_20k.root";

  string s_file = "2011_4T_isNucl_before2T_wVtx.root";
  //  string s_file = "2011_MC_2T_isNucl.root";

  //string s_file = "2011_4T_isNucl_after2T.root";
  // string s_file = "2011_4T_isNucl_before2T.root";

  //  string s1 = "/raid/sguazz/Run2011A_pre2T_412/20110531_ntuple_nuclint.root"
  
  string s1 = "/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/4T/20110531_ntuple_nuclint.root"; bDATA = false;

  // string s1 = "/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/ntuple_nuclint_HIRun2010.root"; bDATA = false;
  // string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/ntuple_nuclint_3.root";  bDATA = false;
  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/2T/ntuple_nuclint_MinBiasMC_altTrig_smallstats.root";

  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/2T/LARGE/ntuple_nuclint_MinBiasMC_2cm.root";

  //  string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/2T/LARGE/ntuple_nuclint_2T_MB0_newNPlizer.root";

  //string s1 = "rfio:/castor/cern.ch/user/s/sguazz/MaterialNtuples/ntuple_nuclint_pre2T_MB.root";
  //  string s1 = "rfio:/castor/cern.ch/user/s/sguazz/MaterialNtuples/ntuple_nuclint_post2T_MB.root";

  //  string s1 = "rfio:/castor/cern.ch/user/s/sguazz/MaterialNtuples/ntuple_nuclint_2T_MB.root";


  // string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi//cmst3/CMSSW_DOMENICO_STEPS/ntuple_Total_wDomenicoStep.root";
  //string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi//cmst3/CMSSW_DOMENICO_STEPS/ntuple_Total_wDomenicoStep.root";


  // string s1 = "rfio:/castor/cern.ch/user/s/sguazz/MaterialNtuples/2T/ntuple_nuclint_MinBiasMC_2cm.root";
  // string s1 = "rfio:/castor/cern.ch/user/m/mgouzevi/cmst3/CMSSW_BEAMPIPE/0T/ntuple_nuclint.root";
  //  string s1 = "ntuple_nuclint_2TExpress.root";
  

  //  string s1 = "/tmp/mgouzevi/ntuple_nuclint_CMSSW356_minbias7TeV.root";

  f1  = TFile::Open(s1.data());

 //f1 = TFile::Open(s1.data());



  //  TTree* ntupleR2S = (TTree*) f1->Get("ntupleR2S;1");

  R2S = ntupleR2S->CopyTree(generalCut);

  // R2S = ntupleR2S;

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

 R2S->SetAlias("x_minus_700", "-0.07");
 R2S->SetAlias("x_plus_700", "+0.07");
 R2S->SetAlias("y_minus_700",  "-0.07");
 R2S->SetAlias("y_plus_700", "+0.07");



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

 R2S->SetAlias("rhoShiftBeam_xminus_700", "sqrt( (x-BEAM_x_shift_minus_700)*(x-BEAM_x_shift_minus_700)+(y-BEAM_y)*(y-BEAM_y) )");
 R2S->SetAlias("rhoShiftBeam_xplus_700", "sqrt( (x-BEAM_x_shift_plus_700)*(x-BEAM_x_shift_plus_700)+(y-BEAM_y)*(y-BEAM_y) )");
 R2S->SetAlias("rhoShiftBeam_yminus_700", "sqrt( (x-BEAM_x)*(x-BEAM_x)+(y-BEAM_y_shift_minus_700)*(y-BEAM_y_shift_minus_700) )");
 R2S->SetAlias("rhoShiftBeam_yplus_700", "sqrt( (x-BEAM_x)*(x-BEAM_x)+(y-BEAM_y_shift_plus_700)*(y-BEAM_y_shift_plus_700) )");



 R2S->SetAlias("rhoBeam_xminus", "sqrt( (x-x_minus)*(x-x_minus)+y*y )");
 R2S->SetAlias("rhoBeam_xplus", "sqrt( (x-x_plus)*(x-x_plus)+y*y )");
 R2S->SetAlias("rhoBeam_yminus", "sqrt( x*x+(y-y_minus)*(y-y_minus) )");
 R2S->SetAlias("rhoBeam_yplus", "sqrt( x*x+(y-y_plus)*(y-y_plus) )");

 R2S->SetAlias("rhoBeam_xminus_700", "sqrt( (x-x_minus_700)*(x-x_minus_700)+y*y )");
 R2S->SetAlias("rhoBeam_xplus_700", "sqrt( (x-x_plus_700)*(x-x_plus_700)+y*y )");
 R2S->SetAlias("rhoBeam_yminus_700", "sqrt( x*x+(y-y_minus_700)*(y-y_minus_700) )");
 R2S->SetAlias("rhoBeam_yplus_700", "sqrt( x*x+(y-y_plus_700)*(y-y_plus_700) )");

  write  = new TFile(s_file.data(), "RECREATE");

 //PSFile = new TPostScript(psFileName, 112);

// ================ BEGINING OF REC STUDY ================ //




//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = -10, max = min + nbins*0.1;
 plotName  = "z_BeamSpot";
 histo_title = "z_BeamSpot";
 xaxis_title = "z(BeamSpot)";
 variable = "bsz0";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = -10, max = min + nbins*0.1;
 plotName  = "x_BeamSpot";
 histo_title = "x_BeamSpot";
 xaxis_title = "x(BeamSpot)";
 variable = "bsx0";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = -10, max = min + nbins*0.1;
 plotName  = "y_BeamSpot";
 histo_title = "y_BeamSpot";
 xaxis_title = "y(BeamSpot)";
 variable = "bsy0";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();







//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 20; 
 min = 0, max = min + nbins*0.1;
 plotName  = "M_Out_over_Pout";
 histo_title = "M_Out/Pout";
 xaxis_title = "M_Out/Pout";
 variable = "mOut/ptOut*sin(thetaOut)";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 10; 
 min = -0.5, max = min + nbins*1;
 plotName  = "tkAlgo_beamPipe";
 histo_title = "tkAlgo_beamPipe";
 xaxis_title = "tkAlgo_beamPipe";
 variable = "tkAlgo";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = -10, max = min + nbins*0.1;
 plotName  = "dxy_beamPipe";
 histo_title = "dxy_beamPipe";
 xaxis_title = "dxy_beamPipe";
 variable = "tkDxy";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = 0, max = min + nbins*0.3;
 plotName  = "angle_beamPipe";
 histo_title = "angle_beamPipe";
 xaxis_title = "angle_beamPipe";
 variable = "angle";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 40; 
 min = 0, max = min + nbins*0.5;
 nbins1 = 100; 
 min1 = 2.5, max1 = min1 + nbins1*0.01;
 plotName  = "angle_vs_RhoShifted_beamPipe_m5z5";
 histo_title = "angle_beamPipe";
 yaxis_title = "#rho Shifted beampipe (cm)";
 xaxis_title = "angle_{io}";
  variable = "rhoShiftBeam"; variable1 = "angle";
 cut0 = "z < 5 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = -10, max = min + nbins*0.1;
 plotName  = "dz_beamPipe";
 histo_title = "dz_beamPipe";
 xaxis_title = "dz_beamPipe";
 variable = "tkDz";
 cut0 = "rho < 3.2 && rho > 2.8";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 200; 
 min = -10, max = min + nbins*0.1;
 plotName  = "dxy";
 histo_title = "dxy";
 xaxis_title = "dxy";
 variable = "tkDxy";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 50; 
 min = 0, max = min + nbins*0.2;
 plotName  = "M_Out";
 histo_title = "M_Out";
 xaxis_title = "M_Out";
 variable = "mOut";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 50; 
 min = 0, max = min + nbins*0.2;
 plotName  = "M_Out_over_Pout_BeamPipe";
 histo_title = "mOut/ptOut*sin(thetaOut)";
 xaxis_title = "mOut/ptOut*sin(thetaOut)";
 variable = "mOut/ptOut*sin(thetaOut)";
 cut0 = "rho < 3.5 && rho > 2.5";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 50; 
 min = 0, max = min + nbins*0.2;
 plotName  = "M_Out_BeamPipe";
 histo_title = "M_Out";
 xaxis_title = "M_Out";
 variable = "mOut";
 cut0 = "rho < 3.5 && rho > 2.5";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 0, max = min + nbins*0.2;
 plotName  = "P_Out";
 histo_title = "P_Out";
 xaxis_title = "P_Out";
 variable = "ptOut/sin(thetaOut)";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 0, max = min + nbins*0.01;
 plotName  = "SinTheta_Out";
 histo_title = "sin (#theta_Out)";
 xaxis_title = "sin(#theta_Out)";
 variable = "sin(thetaOut)";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 40; 
 min = 0, max = min + nbins*0.1;
 plotName  = "Theta_Out";
 histo_title = "#theta_Out";
 xaxis_title = "#theta_Out";
 variable = "thetaOut";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_xplus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_xminus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_yminus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YPLUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_yplus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5., max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.1;
 plotName  = "RHO_BARREL_SHIFT_Pixel";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShift";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_xplus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_xminus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_yminus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YPLUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoShiftBeam_yplus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();






















//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_xplus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_XMINUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_xminus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_YMINUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_yminus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_YPLUS";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_yplus";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();




//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_XPLUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_xplus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_XMINUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_xminus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_YMINUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_yminus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_YPLUS_700";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rhoBeam_yplus_700";
 cut0 = "";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



















//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.5, max = min + nbins*0.01;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = BarrelCut;
 cut = cut0&&generalCut;
 
 PlottiPlotta();




//--------------------------------------//
//------------- Canvas 1.1 -------------//
//-------------  isBeamPipe ------------//
//--------------------------------------//

 nbins = 2; 
 min = -0.5, max = min + 1*nbins;
 plotName  = "isBEAMPIPE_SHIFTBEAM";
 histo_title = "isBeamPipe";
 xaxis_title = "isBeamPipe";
 variable = "1";
 cut0 = "(rhoShiftBeam > 2.85) && (rhoShiftBeam < 3.05)";
 cut = cut0&&generalCut;
 
 PlottiPlotta();

//--------------------------------------//
//------------- Canvas 1.1 -------------//
//-------------  isBeamPipe ------------//
//--------------------------------------//

 nbins = 2; 
 min = -0.5, max = min + 1*nbins;
 plotName  = "isBEAMPIPE";
 histo_title = "isBeamPipe";
 xaxis_title = "isBeamPipe";
 variable = "1";
 cut0 = "(rho > 2.85) && (rho < 3.05)";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 60; 
 min = -30, max = min + nbins*1;
 nbins1 = 30; 
 min1 = 1., max1 = min1 + nbins1*0.1;
 plotName = "RHO_SHIFT_vs_Z";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "Mass Out/P out (GeV)";
 variable1 = "z";  variable = "rhoShiftBeam";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();



//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 30; 
 min = 1, max = min + nbins*0.1;
 nbins1 = 50; 
 min1 = 0, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_MASS";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "Mass Out/PT out (GeV)";
 variable = "mOut/ptOut*sin(thetaOut)";  variable1 = "rhoShiftBeam";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();





//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 150; 
 min = 1, max = min + nbins*10;
 nbins1 = 20; 
 min1 = 2.5, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_NTracks";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "nTracks";
 variable1 = "evt_nTracks";  variable = "rhoShiftBeam";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 20; 
 min = 1, max = min + nbins*1;
 nbins1 = 20; 
 min1 = 2.5, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_NVtx";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "n Primary Vtx";
 variable1 = "evt_NofflineVtx";  variable = "rhoShiftBeam";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();



//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 20; 
 min = 1, max = min + nbins*1;
 nbins1 = 20; 
 min1 = 2.5, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_NSecVtx";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "n Displaced Vtx";
 variable1 = "evt_NdispVtx";  variable = "rhoShiftBeam";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();








//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 150; 
 min = 1, max = min + nbins*10;
 nbins1 = 20; 
 min1 = 2.5, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_NTracks_m5z5";
 histo_title = "XY Nucl PIX BARREL_m5z5";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "nTracks";
 variable1 = "evt_nTracks";  variable = "rhoShiftBeam";
 cut0 =   "z < 5 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 20; 
 min = 1, max = min + nbins*1;
 nbins1 = 20; 
 min1 = 2.5, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_NVtx_m5z5";
 histo_title = "XY Nucl PIX BARREL_m5z5";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "n Primary Vtx";
 variable1 = "evt_NofflineVtx";  variable = "rhoShiftBeam";
 cut0 =   "z < 5 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();



//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 20; 
 min = 1, max = min + nbins*1;
 nbins1 = 20; 
 min1 = 2.5, max1 = min1 + nbins1*0.05;
 plotName = "RHO_SHIFT_vs_NSecVtx_m5z5";
 histo_title = "XY Nucl PIX BARREL_m5z5";
 xaxis_title = "rho_shift(cm)"
 yaxis_title = "n Displaced Vtx";
 variable1 = "evt_NdispVtx";  variable = "rhoShiftBeam";
 cut0 =  "z < 5 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();














//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2.0, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_35z40";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 40 && z > 35";
 cut = cut0&&generalCut;
 
 PlottiPlotta();




//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_30z35";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 35 && z > 30";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_25z30";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 30 && z > 25";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_20z25";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 25 && z > 20";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_15z20";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 20 && z > 15";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_10z15";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 15 && z > 10";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_5z10";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 10 && z > 5";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_0z5";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 5 && z > 0";
 cut = cut0&&generalCut;
 
 PlottiPlotta();






//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m5z0";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < 0 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m10z5";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -5 && z > -10";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m15z10";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -10 && z > -15";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m20z15";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -15 && z > -20";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m25z20";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -20 && z > -25";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m30z25";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -25 && z > -30";
 cut = cut0&&generalCut;
 
 PlottiPlotta();


//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m35z30";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -30 && z > -35";
 cut = cut0&&generalCut;
 
 PlottiPlotta();



//--------------------------------------//
//------------- Canvas 1.2 --------------//
//------------- Rho Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 100; 
 min = 2, max = min + nbins*0.02;
 plotName  = "RHO_BARREL_ZOOM_BEAMPIPE_m40z35";
 histo_title = "#rho Nucl";
 xaxis_title = "#rho Nucl (cm)";
 variable = "rho";
 cut0 = "z < -35 && z > -40";
 cut = cut0&&generalCut;
 
 PlottiPlotta();













//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_35z40";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 40 && z > 35";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_30z35";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 35 && z > 30";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_25z30";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 30 && z > 25";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_20z25";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 25 && z > 20";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_15z20";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 20 && z > 15";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();



//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_10z15";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 15 && z > 10";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_5z10";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 10 && z > 5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_0z5";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 5 && z > 0";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m5z0";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 0 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m5z5";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 5 && z > -5";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m10z5";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -5 && z > -10";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m15z10";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -10 && z > -15";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m20z15";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -15 && z > -20";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m25z20";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -20 && z > -25";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m30z25";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -25 && z > -30";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m35z30";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -30 && z > -35";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m40z35";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -35 && z > -40";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();


//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 180; 
 min = -4.5, max = min + nbins*0.05;
 nbins1 = 180; 
 min1 = -4.5, max1 = min1 + nbins1*0.05;
 plotName = "XY_PIX_BARREL_ZOOM_m45z40";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < -40 && z > -45";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 400; 
 min = -20, max = min + nbins*0.1;
 nbins1 = 400; 
 min1 = -20, max1 = min1 + nbins1*0.1;
 plotName = "XY_PIX_BARREL_ZOOM";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 360; 
 min = -4.5, max = min + nbins*0.025;
 nbins1 = 360; 
 min1 = -4.5, max1 = min1 + nbins1*0.025;
 plotName = "XY_PIX_BARREL_ZOOM";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 360; 
 min = -4.5, max = min + nbins*0.025;
 nbins1 = 360; 
 min1 = -4.5, max1 = min1 + nbins1*0.025;
 plotName = "XY_PIX_BARREL_PLUS";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z > 0";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();

//--------------------------------------//
//------------- Canvas 1.1 --------------//
//------------- XY Barrel Nucl ----------------//
//--------------------------------------//

 nbins = 360; 
 min = -4.5, max = min + nbins*0.025;
 nbins1 = 360; 
 min1 = -4.5, max1 = min1 + nbins1*0.025;
 plotName = "XY_PIX_BARREL_MINUS";
 histo_title = "XY Nucl PIX BARREL";
 xaxis_title = "x (cm)"
 yaxis_title = "y (cm)";
 variable = "y";  variable1 = "x";
 cut0 =  "z < 0";
 cut = cut0&&generalCut;
 
 PlottiPlotta2D();
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

