#ifndef BANDDOT_H
#define BANDDOT_H
double* bandot(int kindex1,int kindex2,int bandnum1,int bandnum2,double volume,int bandtotal,double*** kpoint_product,double** occupation,double** bands,double* kweight);
double smearing(double input,double center,double smearing);
#endif
