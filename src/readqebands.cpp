#include "readqebands.h"
#include <string>
#include <iostream>
#include <fstream>
void readbands(double** bands,int kpoints,int bandnumber,std::string nscf){
  std::fstream fs;
  fs.open(nscf,std::fstream::in);
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
void readoccupation(int** occupationnumber,int kpoints,int bandnumber,std::string nscf){
  std::fstream fs;
  fs.open(nscf,std::fstream::in);
  int count=0;
  std::string temp;
  while(getline(fs,temp)){
    if(temp.find("bands (ev):")!=std::string::npos){
      getline(fs,temp);
      for(size_t i=0;i<bandnumber;i++){
        fs>>occupationnumber[count][i];
      }
      count=count+1;
    }
  }
}
