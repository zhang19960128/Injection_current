#include "readqebands.h"
#include "constant.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "indexref.h"
void readbands(double** bands,int kpoints,int bandnumber,std::string nscf){
  std::fstream fs;
  fs.open(nscf.c_str(),std::fstream::in);
  int count=0;
  std::string temp;
  while(getline(fs,temp)){
    if(temp.find("bands (ev):")!=std::string::npos){
      getline(fs,temp);
      for(size_t i=0;i<bandnumber;i++){
        fs>>bands[count][i];
        bands[count][i]=bands[count][i]/sci_const::ev2j;
      }
      count=count+1;
    }
  }
  fs.close();
}
void readoccupation(double** occupationnumber,int kpoints,int bandnumber,std::string nscf){
  std::fstream fs;
  fs.open(nscf.c_str(),std::fstream::in);
  int count=0;
  std::string temp;
  while(getline(fs,temp)){
    if(temp.find("occupation numbers")!=std::string::npos){
      for(size_t i=0;i<bandnumber;i++){
        fs>>occupationnumber[count][i];
      }
      count=count+1;
    }
  }
  fs.close();
}
void readvmatrix(double*** kpoint_product,int kpoints,int bandnumber,std::string pmat){
 std::fstream fs;
 std::stringstream ss;
 fs.open(pmat.c_str(),std::fstream::in);
 std::string temp;
 int m,n;
 while(getline(fs,temp)){
   ss.clear();
   ss.str(temp);
   ss>>kpoints;
   ss>>m;
   ss>>n;
   for(size_t i=0;i<3;i++){
      ss>>kpoint_product[i][kpoints-1][findindex(m-1,n-1,bandnumber)*2];
      ss>>kpoint_product[i][kpoints-1][findindex(m-1,n-1,bandnumber)*2+1];
   }
 }
fs.close();
}
void readkpoints(double** kpoints,double* kweight,int kpoints_count,double& volume,std::string outnscf){
  std::fstream fs;
  fs.open(outnscf.c_str(),std::fstream::in);
  std::string temp;
  std::stringstream ss;
  std::string useless;
  double kx,ky,kz;
  double alat;
  while(getline(fs,temp)){
    if(temp.find("lattice parameter (alat)")!=std::string::npos){
    ss.clear();
      ss.str(temp);
      for(size_t i=0;i<4;i++){
      ss>>useless;
      }
      ss>>alat;
    }
    if(temp.find("unit-cell volume")!=std::string::npos){
    ss.clear();
    ss.str(temp);
    ss>>useless;
    ss>>useless;
    ss>>useless;
    ss>>volume;
    volume=volume*sci_const::rbohr*sci_const::rbohr*sci_const::rbohr;
    std::cout<<"the volume is: "<<volume<<std::endl;
    ss.clear();
    }
    if(temp.find("cart. coord. in units 2pi/alat")!=std::string::npos){
    for(size_t i=0;i<kpoints_count;i++){
        getline(fs,temp);
        ss.clear();
        ss.str(temp);
        for(size_t j=0;j<4;j++){
          ss>>useless;
        }
        ss>>kx;
        ss>>ky;
        ss>>kz;
        kpoints[i][0]=kx*2*sci_const::PI/(alat*sci_const::rbohr);
        kpoints[i][1]=ky*2*sci_const::PI/(alat*sci_const::rbohr);
        kpoints[i][2]=kz*2*sci_const::PI/(alat*sci_const::rbohr);
        ss>>useless;
        ss>>useless;
        ss>>useless;
        ss>>kweight[i];
      }
    }
  }
  fs.close();
}
void readdimension(int& kpoints,int& bandnumber,std::string pmat){
  std::fstream fs;
  fs.open(pmat.c_str(),std::fstream::in);
  std::string temp;
  std::stringstream ss;
  while(getline(fs,temp)){
    ss.clear();
    ss.str(temp);
    ss>>kpoints;
    ss>>bandnumber;
    ss>>bandnumber;
  }
  fs.close();
  std::cout<<"the kpoints are: "<<kpoints<<"the band numbers are: "<<bandnumber<<std::endl;
}
