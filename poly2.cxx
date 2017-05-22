#include<cstdlib>
#include<cassert>
#include<cmath>
#include<algorithm>
#include<climits>
#include"poly2.h"

using namespace std;

namespace main_savitch_5
{
  polynomial::polynomial(double c,unsigned int exponent){
    head_ptr=new polynode(0,0,NULL,NULL);
    if(exponent==0){
      head_ptr->set_coef(c);
      tail_ptr=head_ptr;
      recent_ptr=head_ptr;
    }
    else{
      polynode*  newexp=new polynode(c,exponent,NULL,head_ptr);
      head_ptr->set_fore(newexp);
      tail_ptr=newexp;
      recent_ptr=newexp;
    }
  }
    
