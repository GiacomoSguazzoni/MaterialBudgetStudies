

void Riemann(){
  
  double xg = 0, yg = 0, zg = 0, p2g = 0;

  double N = 0;

  TMatrix M(1,3);
  TMatrix Mg(1,3);
  TMatrix A(3,3);

  double u0 = 800, v0 = 500;
  double rho0 = 1000;

  for (int j = 1; j< 100; j++){

    double xP = cos(j*1.0)*rho0+u0;
    double yP = sin(j*1.0)*rho0+v0;

    double R2 = xP*xP+yP*yP;

    double R = sqrt(R2);
    double p = (1+R2);

    double x = xP/p;
    double y = yP/p;

//    double x = xP/p;
//    double y = yP/p;
    double z = R2/p;

    cout << "x = " << x << " y = " << y << " z = " << z << endl;
      
    //   p = sqrt(p);
    p = 1;

    Mg[0][0] += p*p*x;
    Mg[0][1] += p*p*y;
    Mg[0][2] += p*p*z;
    p2g += p*p;
    N ++;

  }

  Mg *= 1./p2g;
  /*

  for(int i = 0; i < 3; i++){
      cout << " " << Mg[0][i];
    cout << " is Mg "<<endl;
  }


  for(int i = 0; i < 3; i++){
      cout << " " << M[0][i];
    cout << " is M "<<endl;
  }

  */

  TGraph* g = new TGraph(100);

  for (int j = 1; j< 100; j++){
   
    double xP = cos(j*1.0)*rho0+u0;
    double yP = sin(j*1.0)*rho0+v0;

    g->SetPoint(j-1, xP, yP);

    cout << "xP = " << xP << " yP = " << yP << endl;

    double R2 = xP*xP+yP*yP;

    double R = sqrt(R2);
    double p = (1+R2);
 
 
    double x = xP/p;
    double y = yP/p;

    //   double x = xP/p;
    //  double y = yP/p;
    double z = R2/p;

    cout << "x = " << x << " y = " << y << " z = " << z << " mG = " << Mg[0][2] << endl;
    
    TMatrix K(1,3);

    K[0][0] = (x-Mg[0][0]);
    K[0][1] = (y-Mg[0][1]);
    K[0][2] = (z-Mg[0][2]);
    
    
    TMatrix ntR = K;
    TMatrix tR = K.Transpose(K);

    TMatrix F = tR*ntR;
  

    for(int m = 0; m < 3; m++){
      for(int l = 0; l < 3; l++)
	cout << " " << F[m][l];
      cout << " is F"<<endl;
    }
    //    p = sqrt(p);
    p = 1;
    A += p*p*F;
    
  }

  TH1D* PLOTTER = new TH1D("", "", 1, -3, 3);
  PLOTTER->SetMaximum(3);
  PLOTTER->SetMinimum(-3);
  PLOTTER->Draw();
  //  g->SetMarkerSize(1);
  g->SetMarkerStyle(20);
  g->Draw();

  

  /*

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double R2 = ybin*ybin + xbin*xbin;
      double R = sqrt(R2);
      double p = (1+R2);

      if (R < 2.5 || R > 3.3 ) continue;

      double cosPhi = xbin/R;
      double sinPhi = ybin/R;
      double x = R*R*cosPhi*cosPhi/p;
      double y = R*R*sinPhi*sinPhi/p;
      double z = R2/p;

      M[0][0] += p*x*hFIT->GetBinContent(i, j);
      M[0][1] += p*y*hFIT->GetBinContent(i, j);
      M[0][2] += p*z*hFIT->GetBinContent(i, j);
      
      Mg[0][0] += p*p*x*hFIT->GetBinContent(i, j);
      Mg[0][1] += p*p*y*hFIT->GetBinContent(i, j);
      Mg[0][2] += p*p*z*hFIT->GetBinContent(i, j);
      p2g += p*p*hFIT->GetBinContent(i, j);
      N += hFIT->GetBinContent(i, j);

    }

  }

  Mg *= 1./p2g;

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
         double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double R2 = ybin*ybin + xbin*xbin;
      double R = sqrt(R2);
      double p = (1+R2);

      if (R < 2.5 || R > 3.3 ) continue;

      M -= p*Mg;
      
    }

  }
  */

  
  cout << "N = " << N << endl;
  
  for(int i = 0; i < 3; i++){
      cout << " " << M[0][i];
    cout << ""<<endl;
  }

  
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

  cout << "Norm = " << n[0][0]*n[0][0] + n[1][0]*n[1][0] + n[2][0]*n[2][0] << endl;

  for(int i = 0; i < 3; i++){
      cout << " " << Mg[0][i];
  }
  cout << " is Mg" << endl; 

  double xg = Mg[0][0], yg = Mg[0][1], zg = Mg[0][2];
  double n0 = n[0][0], n1 = n[1][0], n2 = n[2][0];

  double c = -1*( xg*n0 + yg*n1 + zg*n2);

  cout << "c = " << c << endl;



  double x0 = -1.0/2 * n0/(c+n2);
  double y0 = -1* n[1][0]/(2*(c+n[2][0]));
  double R02 = ( n[0][0]*n[0][0] + n[1][0]*n[1][0] - 4*c*(c+n[2][0]) )/(4*(c+n[2][0]) * (c+n[2][0]));
  cout << "x0 = " << x0 << " y0 = " << y0 << " r0 = " << sqrt(R02) << endl;
  /*
 for (int j = 1; j< 100; j++){
   
    double xP = cos(j*1.0)*rho0+u0;
    double yP = sin(j*1.0)*rho0+v0;

    g->SetPoint(j-1, xP, yP);

    cout << "xP = " << xP << " yP = " << yP << endl;

    cout << "rho0 = " << sqrt((xP-u0)*(xP-u0) + (yP-v0)*(yP-v0)) << endl;

    double R2 = xP*xP+yP*yP;

    double R = sqrt(R2);
    double p = (1+R2);
 
 
    double x = xP/p;
    double y = yP/p;

    //   double x = xP/p;
    //  double y = yP/p;
    double z = R2/p;

    cout << "x = " << x << " y = " << y << " z = " << z << " mG = " << Mg[0][2] << endl;
  
    cout << " 0 = " << n0*x + n1*y + n2*z + c << endl;
  
    
  }
*/

}
