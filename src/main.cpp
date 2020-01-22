#include <constant.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "readqebands.h"
#include "indexref.h"
int main(){
  int kpointscount,bandnumber;
  readdimension(kpointscount,bandnumber,"pmat.dat");
  double*** kpoint_product=new double** [3];
  double** bands=new double* [kpointscount];
  double** occupation=new double* [kpointscount];
  double** kpoints=new double* [kpointscount];
  for(size_t i=0;i<kpointscount;i++){
  kpoints[i]=new double[3];
  }
  for(size_t i=0;i<kpointscount;i++){
    bands[i]=new double[bandnumber];
    occupation[i]=new double[bandnumber];
  }
  for(size_t i=0;i<3;i++){
    kpoint_product[i]=new double* [kpointscount];
  }
  for(size_t i=0;i<3;i++){
    for(size_t j=0;j<kpointscount;j++){
      kpoint_product[i][j]=new double[bandnumber*(bandnumber-1)/2*2];
    }
  }
  readbands(bands,kpointscount,bandnumber,"out_nscf");
  readkpoints(kpoints,kpointscount,"out_nscf");
  readoccupation(occupation,kpointscount,bandnumber,"out_nscf");
  readvmatrix(kpoint_product,kpointscount,bandnumber,"pmat.dat");
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
