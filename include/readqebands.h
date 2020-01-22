#ifndef READQEBANDS_H
#define READQEBANDS_H
#include <string>
#include <iostream>
void readbands(double** bands,int kpoints,int bandnumber,std::string nscf);
void readoccupation(double** occupationnumber,int kpoints,int bandnumber,std::string nscf);
#endif
