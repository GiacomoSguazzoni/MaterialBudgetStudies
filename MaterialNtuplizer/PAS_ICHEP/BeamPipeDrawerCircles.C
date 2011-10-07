{  
  //  string fileName = "2011_4T_isNucl_before2T_wVtx.root"; 
  string fileName = "2011_2T_isNucl.root"; 


  TFile *f = TFile::Open(fileName.c_str());


  hFIT = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_0z5;1");
  hFIT_1 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m5z0;1");
  hFIT_2 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m10z5;1");
  hFIT_3 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m15z10;1");
  hFIT_4 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_m20z15;1");

  hFIT_5 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_5z10;1");
  hFIT_6 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_10z15;1");
  hFIT_7 = (TH2D*) f->Get("vtx_3XY_PIX_BARREL_ZOOM_15z20;1");




  hFIT->Add(hFIT_1);
  hFIT->Add(hFIT_2);
  hFIT->Add(hFIT_3);
  hFIT->Add(hFIT_4);
  hFIT->Add(hFIT_5);
  hFIT->Add(hFIT_6);
  hFIT->Add(hFIT_7);


  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double rho2 = xbin*xbin + ybin*ybin;
      double rho_shift2 = (xbin-0.1)*(xbin-0.1) + (ybin+0.2)*(ybin+0.2);

      if (rho_shift2 < 2.78*2.78 || rho_shift2 > 3.1*3.1 ) hFIT->SetBinContent(i, j, 0);
    }
  }

  hFIT->Draw();
 

  fileName = "Plots_2T_diffVtx_BeamCorr_Merged/out_Parameters_bkg1_3vtx.root"; 
  TFile *f = TFile::Open(fileName.c_str());

  TGraphErrors* gX = (TGraphErrors*) f->Get("gX;1");
  TGraphErrors* gY = (TGraphErrors*) f->Get("gY;1");
  TGraphErrors* gR = (TGraphErrors*) f->Get("gR;1");

  for (int i = 0; i < gX->GetN(); i++){
    
    double x, y , R, temp;

    gX->GetPoint(i, temp, x);
    gY->GetPoint(i, temp, y);
    gR->GetPoint(i, temp, R);

    TEllipse* L = new TEllipse(x, y, R, R);  
    L->SetLineColor(i+2);
    L->SetLineStyle(2);
    L->SetLineWidth(4);
    L->SetFillStyle(0);
    L->DrawClone();
  }


}
