#include "readqebands.h"
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
