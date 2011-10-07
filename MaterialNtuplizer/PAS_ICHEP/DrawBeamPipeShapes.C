{

  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  c1->SetFillColor(10);

  c1->Divide(2,2);

  c1->cd(2);
  //  TFile *_file0 = TFile::Open("/afs/cern.ch/user/m/mgouzevi/scratch0/CMSSW_3_8_7/Limit/data/MASS_SHAPES_FATJETS_DATA_wR9_to_R17.root");
  //  TFile *_file0 = TFile::Open("2011_4T_isNucl_before2T.root");//2011_2T_isNucl.root");
  TFile *_file0 = TFile::Open("2011_2T_isNucl.root");

  TH1F* Central = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT;1");
  TH1F* Dw_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS;1");
  TH1F* Up_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YPLUS;1");


  Central->SetLineColor(kYellow);
  Central->SetFillColor(kYellow);
  Dw_300->SetLineColor(kRed);
  Up_300->SetLineColor(kBlack);


  Central->Draw("H");
  Dw_300->Draw("SAME");
  Up_300->Draw("SAME");


  TLegend* L = new TLegend(0.5, 0.7, 0.9, 0.9);
  L->AddEntry(Central, "2010 2T", "f");
  L->AddEntry(Dw_300, "2010 2T y0 - 300 #mum", "l");
  L->AddEntry(Up_300, "2010 2T y0 + 300 #mum", "l");
  L->Draw();


  c1->cd(1);

  TH1F* Central = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT;1");
  TH1F* Dw_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS;1");
  TH1F* Up_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS;1");


  Central->SetLineColor(kYellow);
  Central->SetFillColor(kYellow);
  Dw_300->SetLineColor(kRed);
  Up_300->SetLineColor(kBlack);


  Central->Draw("H");
  Dw_300->Draw("SAME");
  Up_300->Draw("SAME");

  TLegend* L1 = new TLegend(0.5, 0.7, 0.9, 0.9);
  L1->AddEntry(Central, "2010 2T", "f");
  L1->AddEntry(Dw_300, "2010 2T x0 - 300 #mum", "l");
  L1->AddEntry(Up_300, "2010 2T x0 + 300 #mum", "l");
  L1->Draw();

  c1->cd(4);
  //  TFile *_file0 = TFile::Open("/afs/cern.ch/user/m/mgouzevi/scratch0/CMSSW_3_8_7/Limit/data/MASS_SHAPES_FATJETS_DATA_wR9_to_R17.root");
  TFile *_file0 = TFile::Open("2011_2T_isNucl.root");

  TH1F* Central = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT;1");
  TH1F* Dw_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YMINUS_700;1");
  TH1F* Up_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_YPLUS_700;1");


  Central->SetLineColor(kYellow);
  Central->SetFillColor(kYellow);
  Dw_300->SetLineColor(kRed);
  Up_300->SetLineColor(kBlack);


  Central->Draw("H");
  Dw_300->Draw("SAME");
  Up_300->Draw("SAME");

  TLegend* L2 = new TLegend(0.5, 0.7, 0.9, 0.9);
  L2->AddEntry(Central, "2010 2T", "f");
  L2->AddEntry(Dw_300, "2010 2T y0 - 700 #mum", "l");
  L2->AddEntry(Up_300, "2010 2T y0 + 700 #mum", "l");
  L2->Draw();

  c1->cd(3);

  TH1F* Central = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT;1");
  TH1F* Dw_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XMINUS_700;1");
  TH1F* Up_300 = (TH1F*) _file0->Get("RHO_BARREL_ZOOM_BEAMPIPE_SHIFT_XPLUS_700;1");


  Central->SetLineColor(kYellow);
  Central->SetFillColor(kYellow);
  Dw_300->SetLineColor(kRed);
  Up_300->SetLineColor(kBlack);


  Central->Draw("H");
  Dw_300->Draw("SAME");
  Up_300->Draw("SAME");

  TLegend* L3 = new TLegend(0.5, 0.7, 0.9, 0.9);
  //  L3->AddEntry(Central, "2010 4T", "f");
  //  L3->AddEntry(Dw_300, "2010 4T x0 - 700 #mum", "l");
  // L3->AddEntry(Up_300, "2010 4T x0 + 700 #mum", "l");
    L3->AddEntry(Central, "2010 2T", "f");
    L3->AddEntry(Dw_300, "2010 2T x0 - 700 #mum", "l");
   L3->AddEntry(Up_300, "2010 2T x0 + 700 #mum", "l");

  L3->Draw();

  c1->SaveAs("2T.png");

}
