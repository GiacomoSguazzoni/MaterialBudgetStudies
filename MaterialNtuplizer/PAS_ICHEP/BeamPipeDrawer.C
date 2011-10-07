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
      if (rho2 < 2.6*2.6 || rho2 > 3.2*3.2 ) hFIT->SetBinContent(i, j, 0);
    }
  }

  hFIT->Draw("LEGO");
 
  TH2D* hFIT_REW = new TH2D();

  hFIT->Copy(*hFIT_REW);

  

  TCanvas* c3 = new TCanvas();
 
  for (int i = 1; i< hFIT_REW->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT_REW->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT_REW->GetYaxis()->GetNbins()+1; j++){
      double ybin = hFIT_REW->GetYaxis()->GetBinCenter(j);
      double rho2 = xbin*xbin + ybin*ybin;
           if (rho2 < 2.6*2.6 || rho2 > 3.2*3.2 ) {
      	continue;
           }
      
      double solidAngle =  (rho2)/9.;

      hFIT_REW->SetBinContent(i, j, hFIT->GetBinContent(i,j)*solidAngle);
      
    }
  }

  c3->cd();

  hFIT_REW->Draw("LEGO");
  

}
