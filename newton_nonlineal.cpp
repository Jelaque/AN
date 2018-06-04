#include "plu.h"
//c_num for double
//c_len for size
//matrix for Matrix
//results for Vector

/*typedef std::vector< std::vector<c_num (*)(c_num, c_num)> > m_jacobian2;
typedef std::vector< std::vector<c_num (*)(c_num, c_num, c_num)> > m_jacobian3;
typedef std::vector< c_num (*)(c_num, c_num) > v_function;
*/
c_num f1(c_num x, c_num y){return (x*x) + (y*y) - 2;}
c_num f2(c_num x, c_num y){return x - y - 1;}
c_num jf1x(c_num x, c_num y){return 2*x;}
c_num jf1y(c_num x, c_num y){return 2*y;}
c_num jf2x(c_num x, c_num y){return 1;}
c_num jf2y(c_num x, c_num y){return -1;}

void sumVectors(results *&v1, results *&v2){

}

c_num Norm(results *&V){}

void fillM2(matrix *&M, results *&V){
  c_num a,b;
  a = (*V)[0];
  b = (*V)[1];
  (*M)[0][0] = jf1x(a,b);
  (*M)[0][1] = jf1y(a,b);
  (*M)[1][0] = jf2x(a,b);
  (*M)[1][1] = jf2y(a,b);
}
void fillV2(results *&V, results *&x){
  (*V)[0] = f1((*x)[0],(*x)[1]);
  (*V)[1] = f2((*x)[0],(*x)[1]);
}
void fillM3(matrix *&M, results *&V){
  /*fill*/
}
void fillV3(results *&V, results *&x){
  /*fill*/
}

void NonLinealSystem(results *&x, c_num tol, c_len n){
  matrix *M;
  CreateMatrix(M,n,n);
  void (*j)(matrix*&,results*&);
  void (*g)(results*&,results*&);
  if(n == 2){
    j = &fillM2;
    g = &fillV2;
  }
  else{
    j = &fillM3;
    g = &fillV3;
  }
  results *y = new results(n);
  for(int i = 0;Norm(x)>tol;++i){
    j(M,x);
    g(y,x);
    ResolverSistemaEcuaciones(M, y, n);
    sumVectors(x,y);
  }
}

main(){

}
