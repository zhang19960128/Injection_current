#include "banddot.h"
#include <iostream>
#include "constant.h"
#include "indexref.h"
#include <cmath>
#include <complex>
double* bandot(int kindex1,int kindex2,int bandnum1,int bandnum2,double volume,int bandtotal,std::complex<double>*** kpoint_product,double** occupation,double** bands,double* kweight,double freq){
  /*Please refer to my OneNote math constant.*/
  double sci=(sci_const::e_q/sci_const::e_mass);
  sci=sci*sci*sci/sci_const::hbar/sci_const::hbar;
  /*velocity matrix units*/
  sci=sci*(sci_const::hbar)*(sci_const::hbar)*(sci_const::hbar)*(2*sci_const::PI/sci_const::alat)*(2*sci_const::PI/sci_const::alat)*(2*sci_const::PI/sci_const::alat);
  /*Integration over dk'*/
  sci=sci*(2*sci_const::PI/sci_const::alat)*(2*sci_const::PI/sci_const::alat)*(2*sci_const::PI/sci_const::alat)/volume*kweight[kindex2];
  double prod=sci/freq/freq/(sci_const::ev2j/sci_const::hbar)/(sci_const::ev2j/sci_const::hbar);
  prod=sci_const::hbar*sci_const::ev2j*prod;/*this one is to convert the unit in delta function from w to ev to J*/
  /*Integration over dk''*/
  prod=prod*(2*sci_const::PI/sci_const::alat)*(2*sci_const::PI/sci_const::alat)*(2*sci_const::PI/sci_const::alat)/volume*kweight[kindex1];
  prod=prod*(occupation[kindex1][bandnum1]-occupation[kindex2][bandnum2])*(-2)*sci_const::PI*light::time;
  double omega1=bands[kindex1][bandnum1];
  double omega2=bands[kindex2][bandnum2];
  std::complex<double>* P11=new std::complex<double> [3];
  double* result=new double[3];
  for(size_t i=0;i<3;i++){
    result[i]=0.0;
  }
  if(kindex1!=kindex2){
   return result;
  }
  int tempindex;
  for(size_t i=0;i<3;i++){
     P11[i]=indexvmatrix(kindex1,bandnum1,bandnum1,bandtotal,i,kpoint_product);
  }
  std::complex<double>* P12=new std::complex<double> [3];
  for(size_t i=0;i<3;i++){
    P12[i]=indexvmatrix(kindex1,bandnum1,bandnum2,bandtotal,i,kpoint_product);
  }
  std::complex<double>* P21=new std::complex<double> [3];
  for(size_t i=0;i<3;i++){
    P21[i]=indexvmatrix(kindex1,bandnum2,bandnum1,bandtotal,i,kpoint_product);
  }
  /*u=+1*/
  double* result1=new double[3];
  std::complex<double> tempcomplex;
  double resultplus=prod*smearing(freq,-(omega2-omega1),gaussian::smearing_ev);
  for(size_t i=0;i<3;i++){
    tempcomplex=(1.0)*sin(light::delta)*(P12[0]*P21[2]-P21[0]*P12[2]);
    result1[i]=(resultplus*tempcomplex*P11[i]).imag();
  }
  /*u=-1*/
  double* result2=new double[3];
  resultplus=prod*smearing(freq,(omega2-omega1),gaussian::smearing_ev);
  for(size_t i=0;i<3;i++){
    tempcomplex=(-1.0)*sin(light::delta)*(P12[0]*P21[2]-P21[0]*P12[2]);
    result2[i]=(resultplus*tempcomplex*P11[i]).imag();
  }
  for(size_t i=0;i<3;i++){
    result[i]=-1*result1[i]-1*result2[i];
  }
  //std::cout<<result[0]<<" "<<result[1]<<" "<<result[2]<<std::endl;
  delete [] result1;
  delete [] result2;
  delete [] P12;
  delete [] P21;
  delete [] P11;
  return result;
}
double* sumbands(int kpointstotal,int bandstotal,double volume,std::complex<double>*** kpointsproduct,double** occupation,double** bands,double* kweight,double freq){
   double* totalsum=new double[3];
   for(size_t i=0;i<3;i++){
    totalsum[i]=0.0;
   }
   double* tempsum;
   /*sum over kpoints*/
   for(size_t i=0;i<kpointstotal;i++){
    /*sum over n1*/
    for(size_t j=0;j<bandstotal;j++){
    /*sum over n2*/
      for(size_t k=0;k<bandstotal;k++){
          tempsum=bandot(i,i,j,k,volume,bandstotal,kpointsproduct,occupation,bands,kweight,freq);
          for(size_t m=0;m<3;m++){
            totalsum[m]=totalsum[m]+tempsum[m];
          }
          delete [] tempsum;
      }
    }
   }
   return totalsum;
}
/*here the smearing represent the sigma, f(x)=1/(sqrt(2*PI)*sigma)*exp(-1/2*((x-center)/sigma)^2)*/
double smearing(double input,double center,double smearing){
  double result=0.0;
  result=-1.0/2.0*((input-center)/smearing)*((input-center)/smearing);
  return 1.0/smearing/sci_const::root2/sci_const::rootpi*exp(result);
}
