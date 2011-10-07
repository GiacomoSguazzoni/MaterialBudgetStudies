void makeNice(TString fileName, TString nice = "nicePlot"){

  TFile *f = TFile::Open(fileName);
  //  TFile *f = TFile::Open("out_Parameters_bkg1_3vtx.root");
  TGraphErrors * gRgre = (TGraphErrors*)f->Get("gR");
  TGraphErrors * gXgre = (TGraphErrors*)f->Get("gX");
  TGraphErrors * gYgre = (TGraphErrors*)f->Get("gY");

  TGraphErrors * rRgre = (TGraphErrors*)f->Get("rR");
  TGraphErrors * rXgre = (TGraphErrors*)f->Get("rX");
  TGraphErrors * rYgre = (TGraphErrors*)f->Get("rY");



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
   PLOTTERX->SetMinimum(-0.19);
   PLOTTERX->SetMaximum(+0.19);
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
   PLOTTERX->GetYaxis()->SetTitle("x_{0} [cm] ");
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
   
   gXgre->SetFillColor(kBlack);
   gXgre->SetMarkerStyle(20);
   gXgre->SetMarkerColor(kBlack);
   gXgre->SetLineColor(kBlack);
   gXgre->GetListOfFunctions()->RemoveLast(); //to remove parameters panel...
   gXgre->GetListOfFunctions()->RemoveLast(); //...and old fit
   gXgre->SetLineWidth(2);
   gXgre->Draw("P");

   rXgre->SetFillColor(kBlue);
   rXgre->SetMarkerStyle(20);
   rXgre->SetMarkerColor(kBlue);
   rXgre->SetLineColor(kBlue);
   rXgre->GetListOfFunctions()->RemoveLast(); //to remove parameters panel...
   rXgre->GetListOfFunctions()->RemoveLast(); //...and old fit
   rXgre->SetLineWidth(2);
   rXgre->Draw("P");

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
   PLOTTERY->SetMinimum(-0.29);
   PLOTTERY->SetMaximum(+0.09);
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
   PLOTTERY->GetYaxis()->SetTitle("y_{0} [cm] ");
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
   
   gYgre->SetFillColor(kBlack);
   gYgre->SetMarkerStyle(20);
   gYgre->SetMarkerColor(kBlack);
   gYgre->SetLineColor(kBlack);
   gYgre->GetListOfFunctions()->RemoveLast(); //to remove parameters panel...
   gYgre->GetListOfFunctions()->RemoveLast(); //...and old fit
   gYgre->SetLineWidth(2);
   gYgre->Draw("P");

   rYgre->SetFillColor(kBlue);
   rYgre->SetMarkerStyle(20);
   rYgre->SetMarkerColor(kBlue);
   rYgre->SetLineColor(kBlue);
   rYgre->GetListOfFunctions()->RemoveLast(); //to remove parameters panel...
   rYgre->GetListOfFunctions()->RemoveLast(); //...and old fit
   rYgre->SetLineWidth(2);
   rYgre->Draw("P");

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
   PLOTTERR->SetMinimum(2.87);
   PLOTTERR->SetMaximum(2.97);
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
   PLOTTERR->GetYaxis()->SetTitle("R [cm] ");
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
   
   gRgre->SetFillColor(kBlack);
   gRgre->SetMarkerStyle(20);
   gRgre->SetMarkerColor(kBlack);
   gRgre->SetLineColor(kBlack);
   gRgre->GetListOfFunctions()->RemoveLast(); //to remove parameters panel...
   gRgre->GetListOfFunctions()->RemoveLast(); //...and old fit
   gRgre->SetLineWidth(2);
   gRgre->Draw("P");

   rRgre->SetFillColor(kBlue);
   rRgre->SetMarkerStyle(20);
   rRgre->SetMarkerColor(kBlue);
   rRgre->SetLineColor(kBlue);
   rRgre->GetListOfFunctions()->RemoveLast(); //to remove parameters panel...
   rRgre->GetListOfFunctions()->RemoveLast(); //...and old fit
   rRgre->SetLineWidth(2);
   rRgre->Draw("P");

   TLatex *CMSPrel = new TLatex(-37.0,PLOTTERR->GetMaximum()-0.025,"CMS Preliminary 2011");
   CMSPrel->SetTextSize(0.06);
   //   CMSPrel->Draw();
   c1_n2_3->Modified();
   c1_n2->cd();
 
   

   TF1* fX = new TF1("fX", "[0]+[1]*x", -35, 35); 
   TF1* fY = new TF1("fY", "[0]+[1]*x", -35, 35); 
   TF1* fR = new TF1("fR", "[0]+[1]*x", -35, 35); 

   fX->SetParameter(0, 0.1);
   fX->SetParameter(1, -0.0007);

   fY->SetParameter(0, -0.2);
   fY->SetParameter(1, +0.0007);

   fR->SetParameter(0, 2.94);
   fR->SetParameter(1, 0.0);

   gXgre->Fit(fX);
   gYgre->Fit(fY);
   gRgre->Fit(fR);

   //
   c1_n2->cd();
   c1_n2->Modified();
   c1_n2->cd();
   c1_n2->SetSelected(c1_n2);

   c1_n2->SaveAs(nice+".png"); //!Serve!!!!
   c1_n2->SaveAs(nice+".gif");
   c1_n2->SaveAs(nice+".png");


}
