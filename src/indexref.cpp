#include "indexref.h"
#include <stdlib.h>
//<m|P|n>=<m|P^{+}|n>=<n|P|m>*
int findindex(int m,int n,int band){
  //enforce m<n
  if(m>=n){
    std::cout<<"Call Inner Product function Wrong, should always enforce m<n"<<std::endl;
    std::cout<<" if you want to see the m>=n situation, please use complex conjugate"<<std::endl;
    EXIT(EXIT_FAILURE);
  }
  else{
    return (2*band-m-1)*m/2+(n-m)-1;
  }
}
