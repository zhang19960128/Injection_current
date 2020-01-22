#ifndef READQEBANDS_H
#define READQEBANDS_H
#include <string>
#include <iostream>
void readbands(double** bands,int kpoints,int bandnumber,std::string nscf);
void readoccupation(double** occupationnumber,int kpoints,int bandnumber,std::string nscf);
void readvmatrix(double*** kpoint_product,int kpoints,int bandnumber,std::string pmat);
void readkpoints(double** kpoints,int kpoints_count,std::string outnscf);
void readdimension(int& kpoints,int& bandnumber,std::string pmat);
#endif
