#include <constant.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <complex>
#include "readqebands.h"
#include "indexref.h"
#include "banddot.h"
int main(){
  int kpointscount,bandnumber;
  readdimension(kpointscount,bandnumber,"pmat.dat");
  std::complex<double>*** kpoint_product=new std::complex<double>** [3];
  double** bands=new double* [kpointscount];
  double** occupation=new double* [kpointscount];
  double** kpoints=new double* [kpointscount];
  double* kweight=new double [kpointscount];
  double volume;
  for(size_t i=0;i<kpointscount;i++){
  kpoints[i]=new double[3];
  }
  for(size_t i=0;i<kpointscount;i++){
    bands[i]=new double[bandnumber];
    occupation[i]=new double[bandnumber];
  }
  for(size_t i=0;i<3;i++){
    kpoint_product[i]=new std::complex<double>* [kpointscount];
  }
  for(size_t i=0;i<3;i++){
    for(size_t j=0;j<kpointscount;j++){
      kpoint_product[i][j]=new std::complex<double>[bandnumber*(bandnumber+1)/2];
    }
  }
  readbands(bands,kpointscount,bandnumber,"out_nscf");
  readkpoints(kpoints,kweight,kpointscount,volume,"out_nscf");
  readoccupation(occupation,kpointscount,bandnumber,"out_nscf");
  readvmatrix(kpoint_product,kpointscount,bandnumber,"pmat.dat");
  double* current_rate;
  for(double photonE=2.0;photonE<8.0;photonE=photonE+0.1){
  current_rate=sumbands(kpointscount,bandnumber,volume,kpoint_product,occupation,bands,kweight,photonE);
  std::cout<<photonE<<" "<<current_rate[0]<<" "<<current_rate[1]<<" "<<current_rate[2]<<std::endl;
  }
  /*deallocate memory*/
  for(size_t i=0;i<kpointscount;i++){
    delete [] bands[i];
    delete [] occupation[i];
  }
  for(size_t i=0;i<3;i++){
    for(size_t j=0;j<kpointscount;j++){
      delete [] kpoint_product[i][j];
    }
  }
  for(size_t i=0;i<3;i++){
    delete [] kpoint_product[i];
  }
}
