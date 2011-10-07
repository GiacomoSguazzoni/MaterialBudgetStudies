TGraphErrors * diffGraph(TGraphErrors * g1, TGraphErrors * g2, TGraphErrors * g1L, TGraphErrors * g2L, TGraphErrors * g1H, TGraphErrors * g2H){ // g2 - g1


  Int_t N = g1->GetN();
  TGraphErrors *gre = new TGraphErrors(N);

  
  for (Int_t i=0; i<N; i++){
    
    Double_t x1, y1, x2, y2;
    g1->GetPoint(i, x1, y1); 
    g2->GetPoint(i, x2, y2); 

    Double_t x1L, y1L, x2L, y2L;
    g1L->GetPoint(i, x1L, y1L); 
    g2L->GetPoint(i, x2L, y2L); 

    Double_t x1H, y1H, x2H, y2H;
    g1H->GetPoint(i, x1H, y1H); 
    g2H->GetPoint(i, x2H, y2H); 


    Double_t ex1 = g1->GetErrorX(i); 
    Double_t ey1 = g1->GetErrorY(i); 
    Double_t ey2 = g2->GetErrorY(i); 

    cout << " ex1 ey1 ey2 " << ex1 << " " << ey1 << " " << ey2 << endl;

    Double_t diff = y2-y1;
    Double_t diffL = y2L-y1L;
    Double_t diffH = y2H-y1H;

    Double_t statE2 = ey1*ey1+ey2*ey2;
    Double_t sysE = TMath::Max(TMath::Abs(diff-diffL), TMath::Abs(diff-diffH));

    cout << sysE << endl;

    gre->SetPoint(i,x1,diff);
    gre->SetPointError(i,ex1,sqrt(statE2+sysE*sysE)); 

  }

  return gre;

}

void makeNiceDifference(TString dir1, TString dir2, TString nice = "niceDifferencePlot"){

  TString def("out_Parameters_bkg1_3vtx.root");
  TString sysL("out_Parameters_bkg1_2vtx.root");
  TString sysH("out_Parameters_bkg1_6vtx.root");

  TFile *f1 = TFile::Open(dir1+"/"+def);
  TFile *f1L = TFile::Open(dir1+"/"+sysL);
  TFile *f1H = TFile::Open(dir1+"/"+sysH);

  TFile *f2 = TFile::Open(dir2+"/"+def);
  TFile *f2L = TFile::Open(dir2+"/"+sysL);
  TFile *f2H = TFile::Open(dir2+"/"+sysH);

  TGraphErrors * gR1gre = (TGraphErrors*)f1->Get("gR");
  TGraphErrors * gX1gre = (TGraphErrors*)f1->Get("gX");
  TGraphErrors * gY1gre = (TGraphErrors*)f1->Get("gY");
  TGraphErrors * rR1gre = (TGraphErrors*)f1->Get("rR");
  TGraphErrors * rX1gre = (TGraphErrors*)f1->Get("rX");
  TGraphErrors * rY1gre = (TGraphErrors*)f1->Get("rY");

  TGraphErrors * gR1Lgre = (TGraphErrors*)f1L->Get("gR");
  TGraphErrors * gX1Lgre = (TGraphErrors*)f1L->Get("gX");
  TGraphErrors * gY1Lgre = (TGraphErrors*)f1L->Get("gY");
  TGraphErrors * rR1Lgre = (TGraphErrors*)f1L->Get("rR");
  TGraphErrors * rX1Lgre = (TGraphErrors*)f1L->Get("rX");
  TGraphErrors * rY1Lgre = (TGraphErrors*)f1L->Get("rY");

  TGraphErrors * gR1Hgre = (TGraphErrors*)f1H->Get("gR");
  TGraphErrors * gX1Hgre = (TGraphErrors*)f1H->Get("gX");
  TGraphErrors * gY1Hgre = (TGraphErrors*)f1H->Get("gY");
  TGraphErrors * rR1Hgre = (TGraphErrors*)f1H->Get("rR");
  TGraphErrors * rX1Hgre = (TGraphErrors*)f1H->Get("rX");
  TGraphErrors * rY1Hgre = (TGraphErrors*)f1H->Get("rY");

  TGraphErrors * gR2gre = (TGraphErrors*)f2->Get("gR");
  TGraphErrors * gX2gre = (TGraphErrors*)f2->Get("gX");
  TGraphErrors * gY2gre = (TGraphErrors*)f2->Get("gY");
  TGraphErrors * rR2gre = (TGraphErrors*)f2->Get("rR");
  TGraphErrors * rX2gre = (TGraphErrors*)f2->Get("rX");
  TGraphErrors * rY2gre = (TGraphErrors*)f2->Get("rY");

  TGraphErrors * gR2Lgre = (TGraphErrors*)f2L->Get("gR");
  TGraphErrors * gX2Lgre = (TGraphErrors*)f2L->Get("gX");
  TGraphErrors * gY2Lgre = (TGraphErrors*)f2L->Get("gY");
  TGraphErrors * rR2Lgre = (TGraphErrors*)f2L->Get("rR");
  TGraphErrors * rX2Lgre = (TGraphErrors*)f2L->Get("rX");
  TGraphErrors * rY2Lgre = (TGraphErrors*)f2L->Get("rY");

  TGraphErrors * gR2Hgre = (TGraphErrors*)f2H->Get("gR");
  TGraphErrors * gX2Hgre = (TGraphErrors*)f2H->Get("gX");
  TGraphErrors * gY2Hgre = (TGraphErrors*)f2H->Get("gY");
  TGraphErrors * rR2Hgre = (TGraphErrors*)f2H->Get("rR");
  TGraphErrors * rX2Hgre = (TGraphErrors*)f2H->Get("rX");
  TGraphErrors * rY2Hgre = (TGraphErrors*)f2H->Get("rY");



//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Fri May 27 11:43:08 2011) by ROOT version5.27/06b
   TCanvas *c1_n2 = new TCanvas("c1_n2","c1_n2",700,1500);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   c1_n2->Range(0,0,1,1);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetTickx(1);
   c1_n2->SetTicky(1);
   c1_n2->SetLeftMargin(0.13);
   c1_n2->SetRightMargin(0.05);
   c1_n2->SetTopMargin(0.05);
   c1_n2->SetBottomMargin(0.13);
   c1_n2->SetFrameFillStyle(0);
   c1_n2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c1_n2_1
   TPad *c1_n2_1 = new TPad("c1_n2_1", "c1_n2_1",0.01,0.67,0.99,0.99);
   c1_n2_1->Draw();
   c1_n2_1->cd();
   c1_n2_1->Range(-52.68293,-0.03170732,44.87805,0.2121951);
   c1_n2_1->SetFillColor(0);
   c1_n2_1->SetBorderMode(0);
   c1_n2_1->SetBorderSize(2);
   c1_n2_1->SetTickx(1);
   c1_n2_1->SetTicky(1);
   c1_n2_1->SetLeftMargin(0.12);
   c1_n2_1->SetRightMargin(0.02);
   c1_n2_1->SetTopMargin(0.05);
   c1_n2_1->SetBottomMargin(0.2);
   c1_n2_1->SetFrameFillStyle(0);
   c1_n2_1->SetFrameBorderMode(0);
   c1_n2_1->SetFrameFillStyle(0);
   c1_n2_1->SetFrameBorderMode(0);
   
   TH1D *PLOTTERX = new TH1D("PLOTTERX","",1,-40,40);
   PLOTTERX->SetMinimum(-0.045);
   PLOTTERX->SetMaximum(+0.045);
   PLOTTERX->SetFillColor(63);
   PLOTTERX->SetLineStyle(0);
   PLOTTERX->SetMarkerStyle(20);
   PLOTTERX->GetXaxis()->SetLabelFont(42);
   PLOTTERX->GetXaxis()->SetLabelOffset(0.007);
   PLOTTERX->GetXaxis()->SetLabelSize(0.09);
   PLOTTERX->GetXaxis()->SetTitleSize(0.1);
   PLOTTERX->GetXaxis()->SetTitleOffset(0.9);
   PLOTTERX->GetXaxis()->SetTitleFont(42);
   PLOTTERX->GetXaxis()->SetTitle("z [cm]");
   PLOTTERX->GetYaxis()->SetNdivisions(505);
   PLOTTERX->GetYaxis()->SetTitle("#Deltax_{0} [cm] ");
   PLOTTERX->GetYaxis()->SetLabelFont(42);
   PLOTTERX->GetYaxis()->SetLabelOffset(0.007);
   PLOTTERX->GetYaxis()->SetLabelSize(0.09);
   PLOTTERX->GetYaxis()->SetTitleSize(0.1);
   PLOTTERX->GetYaxis()->SetTitleOffset(0.5);
   PLOTTERX->GetYaxis()->SetTitleFont(42);
   PLOTTERX->GetZaxis()->SetLabelFont(42);
   PLOTTERX->GetZaxis()->SetLabelOffset(0.007);
   PLOTTERX->GetZaxis()->SetLabelSize(0.05);
   PLOTTERX->GetZaxis()->SetTitleSize(0.06);
   PLOTTERX->GetZaxis()->SetTitleFont(42);
   PLOTTERX->Draw("");

   TGraphErrors * gXdiff = diffGraph(gX1gre, gX2gre, gX1Lgre, gX2Lgre, gX1Hgre, gX2Hgre);
   
   gXdiff->SetFillColor(kBlack);
   gXdiff->SetMarkerStyle(20);
   gXdiff->SetMarkerColor(kBlack);
   gXdiff->SetLineWidth(2);
   gXdiff->SetLineColor(kBlack);
   gXdiff->Draw("P");

   TGraphErrors * rXdiff = diffGraph(rX1gre, rX2gre, rX1Lgre, rX2Lgre, rX1Hgre, rX2Hgre);
   
   rXdiff->SetFillColor(kBlue);
   rXdiff->SetMarkerStyle(20);
   rXdiff->SetMarkerColor(kBlue);
   rXdiff->SetLineWidth(2);
   rXdiff->SetLineColor(kBlue);
   rXdiff->Draw("P");

   TLatex *CMSPrel = new TLatex(-37.0,PLOTTERX->GetMaximum()-0.025,"CMS Preliminary 2011");
   CMSPrel->SetTextSize(0.06);
   //   CMSPrel->Draw();
   c1_n2_1->Modified();
   c1_n2->cd();
  
// ------------>Primitives in pad: c1_n2_2
   TPad *c1_n2_2 = new TPad("c1_n2_1", "c1_n2_1",0.01,0.34,0.99,0.66);
   //   TPad *c1_n2_1 = new TPad("c1_n2_1", "c1_n2_1",0.01,0.01,0.99,0.33);
   c1_n2_2->Draw();
   c1_n2_2->cd();
   c1_n2_2->Range(-52.68293,-0.3317073,44.87805,-0.08780488);
   c1_n2_2->SetFillColor(0);
   c1_n2_2->SetBorderMode(0);
   c1_n2_2->SetBorderSize(2);
   c1_n2_2->SetTickx(1);
   c1_n2_2->SetTicky(1);
   c1_n2_2->SetLeftMargin(0.12);
   c1_n2_2->SetRightMargin(0.02);
   c1_n2_2->SetTopMargin(0.05);
   c1_n2_2->SetBottomMargin(0.2);
   c1_n2_2->SetFrameFillStyle(0);
   c1_n2_2->SetFrameBorderMode(0);
   c1_n2_2->SetFrameFillStyle(0);
   c1_n2_2->SetFrameBorderMode(0);
   
   TH1D *PLOTTERY = new TH1D("PLOTTERY","",1,-40,40);
   PLOTTERY->SetMinimum(-0.045);
   PLOTTERY->SetMaximum(+0.045);
   PLOTTERY->SetFillColor(63);
   PLOTTERY->SetLineStyle(0);
   PLOTTERY->SetMarkerStyle(20);
   PLOTTERY->GetXaxis()->SetLabelFont(42);
   PLOTTERY->GetXaxis()->SetLabelOffset(0.007);
   PLOTTERY->GetXaxis()->SetLabelSize(0.09);
   PLOTTERY->GetXaxis()->SetTitleSize(0.1);
   PLOTTERY->GetXaxis()->SetTitleFont(42);
   PLOTTERY->GetXaxis()->SetTitleOffset(0.9);
   PLOTTERY->GetXaxis()->SetTitle("z [cm]");
   PLOTTERY->GetYaxis()->SetNdivisions(505);
   PLOTTERY->GetYaxis()->SetTitle("#Deltay_{0} [cm] ");
   PLOTTERY->GetYaxis()->SetLabelFont(42);
   PLOTTERY->GetYaxis()->SetLabelOffset(0.007);
   PLOTTERY->GetYaxis()->SetLabelSize(0.09);
   PLOTTERY->GetYaxis()->SetTitleSize(0.1);
   PLOTTERY->GetYaxis()->SetTitleOffset(0.5);
   PLOTTERY->GetYaxis()->SetTitleFont(42);
   PLOTTERY->GetZaxis()->SetLabelFont(42);
   PLOTTERY->GetZaxis()->SetLabelOffset(0.007);
   PLOTTERY->GetZaxis()->SetLabelSize(0.05);
   PLOTTERY->GetZaxis()->SetTitleSize(0.06);
   PLOTTERY->GetZaxis()->SetTitleFont(42);
   PLOTTERY->Draw("");
   
   TGraphErrors * gYdiff = diffGraph(gY1gre, gY2gre, gY1Lgre, gY2Lgre, gY1Hgre, gY2Hgre);
   
   gYdiff->SetFillColor(kBlack);
   gYdiff->SetMarkerStyle(20);
   gYdiff->SetMarkerColor(kBlack);
   gYdiff->SetLineWidth(2);
   gYdiff->SetLineColor(kBlack);
   gYdiff->Draw("P");

   TGraphErrors * rYdiff = diffGraph(rY1gre, rY2gre, rY1Lgre, rY2Lgre, rY1Hgre, rY2Hgre);
   
   rYdiff->SetFillColor(kBlue);
   rYdiff->SetMarkerStyle(20);
   rYdiff->SetMarkerColor(kBlue);
   rYdiff->SetLineWidth(2);
   rYdiff->SetLineColor(kBlue);
   rYdiff->Draw("P");

   TLatex *CMSPrel = new TLatex(-37.0,PLOTTERY->GetMaximum()-0.025,"CMS Preliminary 2011");
   CMSPrel->SetTextSize(0.06);
   //   CMSPrel->Draw();
   c1_n2_2->Modified();
   c1_n2->cd();
  

// ------------>Primitives in pad: c1_n2_2
   TPad *c1_n2_3 = new TPad("c1_n2_1", "c1_n2_1",0.01,0.01,0.99,0.33);
   //   TPad *c1_n2_1 = new TPad("c1_n2_1", "c1_n2_1",0.01,0.01,0.99,0.33);
   c1_n2_3->Draw();
   c1_n2_3->cd();
   c1_n2_3->Range(-52.68293,-0.3317073,44.87805,-0.08780488);
   c1_n2_3->SetFillColor(0);
   c1_n2_3->SetBorderMode(0);
   c1_n2_3->SetBorderSize(2);
   c1_n2_3->SetTickx(1);
   c1_n2_3->SetTicky(1);
   c1_n2_3->SetLeftMargin(0.12);
   c1_n2_3->SetRightMargin(0.02);
   c1_n2_3->SetTopMargin(0.05);
   c1_n2_3->SetBottomMargin(0.2);
   c1_n2_3->SetFrameFillStyle(0);
   c1_n2_3->SetFrameBorderMode(0);
   c1_n2_3->SetFrameFillStyle(0);
   c1_n2_3->SetFrameBorderMode(0);
   
   TH1D *PLOTTERR = new TH1D("PLOTTERR","",1,-40,40);
   PLOTTERR->SetMinimum(-.045);
   PLOTTERR->SetMaximum(0.045);
   PLOTTERR->SetFillColor(63);
   PLOTTERR->SetLineStyle(0);
   PLOTTERR->SetMarkerStyle(20);
   PLOTTERR->GetXaxis()->SetLabelFont(42);
   PLOTTERR->GetXaxis()->SetLabelOffset(0.007);
   PLOTTERR->GetXaxis()->SetLabelSize(0.09);
   PLOTTERR->GetXaxis()->SetTitleSize(0.1);
   PLOTTERR->GetXaxis()->SetTitleFont(42);
   PLOTTERR->GetXaxis()->SetTitleOffset(0.9);
   PLOTTERR->GetXaxis()->SetTitle("z [cm]");
   PLOTTERR->GetYaxis()->SetNdivisions(505);
   PLOTTERR->GetYaxis()->SetTitle("#DeltaR [cm] ");
   PLOTTERR->GetYaxis()->SetLabelFont(42);
   PLOTTERR->GetYaxis()->SetLabelOffset(0.007);
   PLOTTERR->GetYaxis()->SetLabelSize(0.09);
   PLOTTERR->GetYaxis()->SetTitleSize(0.1);
   PLOTTERR->GetYaxis()->SetTitleOffset(0.5);
   PLOTTERR->GetYaxis()->SetTitleFont(42);
   PLOTTERR->GetZaxis()->SetLabelFont(42);
   PLOTTERR->GetZaxis()->SetLabelOffset(0.007);
   PLOTTERR->GetZaxis()->SetLabelSize(0.05);
   PLOTTERR->GetZaxis()->SetTitleSize(0.06);
   PLOTTERR->GetZaxis()->SetTitleFont(42);
   PLOTTERR->Draw("");
   
   TGraphErrors * gRdiff = diffGraph(gR1gre, gR2gre, gR1Lgre, gR2Lgre, gR1Hgre, gR2Hgre);
   
   gRdiff->SetFillColor(kBlack);
   gRdiff->SetMarkerStyle(20);
   gRdiff->SetMarkerColor(kBlack);
   gRdiff->SetLineWidth(2);
   gRdiff->SetLineColor(kBlack);
   gRdiff->Draw("P");

   TGraphErrors * rRdiff = diffGraph(rR1gre, rR2gre, rR1Lgre, rR2Lgre, rR1Hgre, rR2Hgre);
   
   rRdiff->SetFillColor(kBlue);
   rRdiff->SetMarkerStyle(20);
   rRdiff->SetMarkerColor(kBlue);
   rRdiff->SetLineWidth(2);
   rRdiff->SetLineColor(kBlue);
   rRdiff->Draw("P");

   TLatex *CMSPrel = new TLatex(-37.0,PLOTTERR->GetMaximum()-0.025,"CMS Preliminary 2011");
   CMSPrel->SetTextSize(0.06);
   //   CMSPrel->Draw();
   c1_n2_3->Modified();
   c1_n2->cd();


   //
   c1_n2->cd();
   c1_n2->Modified();
   c1_n2->cd();
   c1_n2->SetSelected(c1_n2);

   c1_n2->SaveAs(nice+".png"); //!Serve!!!!
   c1_n2->SaveAs(nice+".gif");
   c1_n2->SaveAs(nice+".png");


}
