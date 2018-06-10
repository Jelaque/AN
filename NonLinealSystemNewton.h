#include "plu.h"
#include "/home/jesus/AnalisisNumerico/parser.h"

typedef std::vector< std::vector<MathExpression> > d_jacobian;
typedef std::vector< MathExpression > v_functions;

void CreateJacobian(d_jacobian &JB, c_len n){
  JB.resize(n);
  for(auto it = JB.begin(); it != JB.end(); ++it)
    it->resize(n);
}
c_number Norm(results &A, results &B){
  c_number cur, max = 0;
  auto it1 = A.begin();
  for(auto it2 = B.begin(); it2 != B.end(); ++it2, ++it1){
    cur = fabs(*it2 - *it1);
    if(cur > max)
      max = cur;
  }
  return max;
}
void Resolve_Jacobi(d_jacobian &JB, matrix &M, container &y, c_len n){
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      M[i][j] = JB[i][j].Value(y);
}
void Resolve_Function(v_functions &F, results &Y, container &y, c_len n){
  for(int i = 0; i < n; ++i)
    Y[i] = F[i].Value(y);
}
void fillVariables(container &V, results &X){
  auto it2 = X.begin();
  for(auto it1 = V.begin(); it1 != V.end(); ++it1, ++it2)
    it1->second = *it2;
}
void RestVectors(results &A, results &B){
  auto it1 = A.begin();
  for(auto it2 = B.begin(); it2 != B.end(); ++it2, ++it1)
    *it1 -= *it2;
}
void MetNewtonSystem(d_jacobian &JB, v_functions &F, results &X, double TOL, c_len n){
  results H,Y;
  matrix M;
  CreateMatrix(M,n,n);
  container V = *(F.begin()->variables);
  for(int i = 1;;++i){
    std::cout << "------ Iteration " << i << " ------"<< '\n';
    fillVariables(V,X);
    H = Y = X;
    Resolve_Jacobi(JB,M,V,n);
    printMatrix(M,n,n);
    Resolve_Function(F,H,V,n);
    PrintVector(H,n);
    ResolverSistemaEcuaciones(M,H,n);
    RestVectors(X,H);
    if(Norm(X,Y) < TOL)
      return;
  }
}
