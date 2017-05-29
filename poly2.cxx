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
    head_ptr=new polynode(0.0,0,NULL,NULL);
    if(exponent==0){
      head_ptr->set_coef(c);
      tail_ptr=head_ptr;
      recent_ptr=head_ptr;
      current_degree=0;
    }
    else{
      polynode*  newexp=new polynode(c,exponent,NULL,head_ptr);
      head_ptr->set_fore(newexp);
      //newexp->set_back(head_ptr);
      tail_ptr=newexp;
      recent_ptr=newexp;
      current=exponent;
    }
  }

  polynomial::polynomial(const polynomial& source){
    polynode* newpn=new polynode(0.0,0,NULL,NULL);
    head_ptr=newpn;
    tail_ptr=newpn;
    int i=0;
    polynode* trv=head_ptr;
    trv->set_coef(source.coefficient(0));
    if(source.degree()!=0){
    while(i<=source.degree()){
      polynode* newtrv=new polynode(0,0,NULL,trv);
      newtrv->set_exponent(source.next_term(trv->exponent()));
      newtrv->set_coef(source.coefficient(source.next_term(trv->exponent())));
      trv->set_fore(newtrv);
      tail_ptr=newtrv;
      trv=newtrv;
      i=newtrv->exponent();
    }
    }
    current_degree=source.degree();
    recent_ptr=tail_ptr;
  }

  polynomial::~polynomial(){
    polynode* trv=head_ptr;
    do{
       polynode* trv1=trv;
       trv=trv1->fore();
       delete trv1;
    }while(trv->fore()!=NULL);
    current_degree=0;
    recent_ptr=NULL;
  }

  void polynomial::add_to_coef(double amount,unsigned int exponent){
    if(current_degree==0 && exponent==0){
      head_ptr->set_coef(amount+head_ptr->coef());
    }
    if(exponent>current_degree && amount!=0){
      polynode* newn=new polynode(amount,exponent,NULL,tail_ptr);
      tail_ptr->set_fore(newn);
      tail_ptr=newn;
      current_degree=exponent;
    }
    if(exponent==current_degree){
      if(amount+tail_ptr->coef()!=0){
	tail_ptr->set_coef(amount+tail_ptr->coef());
      }
      else{
	current_degree=previous_term(current_degree);
	tail_ptr=tail_ptr->back();
	delete tail_ptr->fore();
	recent_ptr=tail_ptr;
      }
    }
    if(exponent>0 && exponent<head_ptr->fore()->exponent()){
      polynode *newn=new polynode(amount,exponent,head_ptr->fore(),head_ptr);
      head_ptr->fore()->set_back(newn);
      head_ptr->set_fore(newn);
    }
    polynode* trv=head_ptr;
    while(exponent>=next_term(trv->exponent())){
      trv=trv->fore();
    }
    if(exponent==trv->exponent() && amount+trv->coef()!=0){
      trv->set_coef(amount+trv->coef());
    }
    else if(exponent==try->exponent() && amount+trv->coef()==0){
      trv->back()->set_fore(trv->fore());
      trv->fore()->set_back(trv->back());
      delete trv;
    }
    else if(amount!=0){
      polynode* newn=new polynode(amount,exponent,trv->fore(),trv);
      trv->set_fore(newn);
      newn->fore()->set_back(newn);
      recent_ptr=newn;
    }
  }

  unsigned int polynomial::next_term(unsigned int e)const{
    if(e>=current_degree){
      return 0;
    }
    else{
      polynode* trv=head_ptr;
      while(e>=trv->fore()->exponent()){
	trv=trv->fore();
      }
      return trv->fore()->exponent();
    }
  }

  unsigned int polynomial::previous_term(unsigned int e)const{
    if(e==0 || current_degree==0){
      return UINT_MAX;
    }
    if(head_ptr->coef()==0 && e<=head_ptr->fore()->exponent()){
      return UINT_MAX;
    }
    if(e>current_degree){
      return current_degree;
    }
    polynode* trv=head_ptr;
    while(e>trv->fore()->exponent()){
      trv=trv->fore();
    }
    return trv->exponent();
  }

  
      
    
      
      
      
      
