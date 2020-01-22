#include "banddot.h"
#include <iostream>
#include "constant.h"
#include "indexref.h"
#include <cmath>
#include <complex>
double* bandot(int kindex1,int kindex2,int bandnum1,int bandnum2,double volume,int bandtotal,double*** kpoint_product,double** occupation,double** bands,double* kweight,double freq){
  double sci=(sci_const::e_q/sci_const::e_mass)*(sci_const::e_q/sci_const::hbar/sci_const::e_mass)*(sci_const::e_q/sci_const::hbar/sci_const::e_mass);
  double prod=sci*kweight[kindex1]*(2*sci_const::PI)*(2*sci_const::PI)*(2*sci_const::PI)/volume*kweight[kindex2]*(2*sci_const::PI)*(2*sci_const::PI)*(2*sci_const::PI)/volume;
  prod=prod*(occupation[kindex1][bandnum1]-occupation[kindex2][bandnum2])*(-2)*sci_const::PI;
  double omega1=bands[kindex1][bandnum1]/sci_const::hbar;
  double omega2=bands[kindex2][bandnum2]/sci_const::hbar;
  double* P11=new double[3];
  double* result=new double[3];
  for(size_t i=0;i<3;i++){
    result[i]=0.0;
  }
  if(kindex1!=kindex2){
   return result;
  }
  int tempindex;
  for(size_t i=0;i<3;i++){
    tempindex=findindex(bandnum1,bandnum1,bandtotal);
    P11[i]=kpoint_product[i][kindex1][2*tempindex];
  }
  std::complex<double>* P12=new std::complex<double> [3];
  for(size_t i=0;i<3;i++){
    tempindex=findindex(bandnum1,bandnum2,bandtotal);
    P12[i].real(kpoint_product[i][kindex1][2*tempindex]);
    P12[i].imag(kpoint_product[i][kindex1][2*tempindex+1]);
  }
  std::complex<double>* P21=new std::complex<double> [3];
  for(size_t i=0;i<3;i++){
    tempindex=findindex(bandnum1,bandnum2,bandtotal);
    P12[i].real(kpoint_product[i][kindex1][2*tempindex]);
    P12[i].imag(-1*kpoint_product[i][kindex1][2*tempindex+1]);
  }
  /*u=+1*/
  double* result1=new double[3];
  std::complex<double> tempcomplex;
  double resultplus=prod*smearing(freq,-(omega2-omega1),gaussian::smearing);
  for(size_t i=0;i<3;i++){
    tempcomplex=std::complex<double>(0,1.0)*(1.0)*sin(light::delta)*light::Ax*light::Az*(P12[0]*P21[2]-P21[0]*P12[2]);
    result1[i]=resultplus*tempcomplex.real()*P11[i];
  }
  /*u=-1*/
  double* result2=new double[3];
  resultplus=prod*smearing(freq,(omega2-omega1),gaussian::smearing);
  for(size_t i=0;i<3;i++){
    tempcomplex=std::complex<double>(0,1.0)*(-1.0)*sin(light::delta)*light::Ax*light::Az*(P12[0]*P21[2]-P21[0]*P12[2]);
    result2[i]=resultplus*tempcomplex.real()*P11[i];
  }
  for(size_t i=0;i<3;i++){
    result[i]=result1[i]+result2[i];
  }
  delete [] result1;
  delete [] result2;
  delete [] P12;
  delete [] P21;
  delete [] P11;
  return result;
}
/*here the smearing represent the sigma, f(x)=1/(sqrt(2*PI)*sigma)*exp(-1/2*((x-center)/sigma)^2)*/
double smearing(double input,double center,double smearing){
  double result=0.0;
  result=-1.0/2.0*((input-center)/smearing)*((input-center)/smearing);
  return 1.0/smearing/sci_const::root2/sci_const::rootpi*exp(result);
}
