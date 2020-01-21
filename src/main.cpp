#include <constant.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
int main(){
  std::fstream fs;
  fs.open("pmat.dat",std::fstream::in);
  std::string temp;
  int kpoints,bandnumber;/*this number could be connected with Liang's Code Pmat.f90. for convenience now, we just use some brute force to get it*/
  std::stringstream ss;
  while(getline(fs,temp)){
    ss.clear();
    ss.str(temp);
    ss>>kpoints;
    ss>>bandnumber;
    ss>>bandnumber;
  }
  std::cout<<"the kpoints are: "<<kpoints<<" the band numbers are:  "<<bandnumber<<std::endl;
  double** kpoint_product=new double* [kpoints];
  for(size_t i=0;i<kpoints;i++){
    kpoint_product[i]=new double[bandnumber*(bandnumber-1)/2];
  }
}
