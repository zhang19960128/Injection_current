#include "banddot.h"
#include "constant.h"
#include "indexref.h"
#include <cmath>
double* bandot(int kindex1,int kindex2,int bandnum1,int bandnum2,double volume,int bandtotal,double*** kpoint_product,double** occupation,double** bands,double* kweight,double freq){
  double sci=(sci_const::e_q/sci_const::e_mass)*(sci_const::e_q/sci_const::hbar/sci_const::e_mass)*(sci_const::e_q/sci_const::hbar/sci_const::e_mass);
  double prod=sci*kweight[kindex1]*(2*sci_const::PI)*(2*sci_const::PI)*(2*sci_const::PI)/volume*kweight[kindex2](2*sci_const::PI)*(2*sci_const::PI)*(2*sci_const::PI)/volume;
  prod=prod*(occupation[kindex1][bandnum1]-occupation[kindex2][bandnum2])*(-2)*sci_const::PI;
  double omega1=bands[kindex1][bandnum1]/sci_const::hbar;
  double omega2=bands[kindex2][bandnum2]/sci_const::hbar;
  double* P11=new double[3];
  for(size_t i=0;i<3;i++){
    P11[i]=kpoint_product[i][kindex1][bandnum1]
  }
  /*u=+1*/
  double resultplus=prod*smearing(freq,-(omega2-omega1),gaussian::smearing);

}
/*here the smearing represent the sigma, f(x)=1/(sqrt(2*PI)*sigma)*exp(-1/2*((x-center)/sigma)^2)*/
double smearing(double input,double center,double smearing){
  double result=0.0;
  result=-1.0/2.0*((input-center)/smearing)*((input-center)/smearing);
  return 1.0/smearing/sci_const::root2/sci_const::rootpi*exp(result);
}
