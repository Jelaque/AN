#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef double c_number;
typedef int c_len;
typedef vector< vector<c_number> > matrix;
typedef vector<c_number> results;
void CreateMatrix(matrix &Arr, c_len n, c_len m){
  Arr.resize(n);
  for(int i = 0; i < n; ++i)
    Arr[i].resize(m);
}
void PrintVector(const results &v, c_len n){
  for(int i = 0; i < n; ++i)
    cout << "x" << i << ": "<< v[i] << endl;
}
matrix ProductMatrix(matrix &A, matrix &B, c_len n){
  matrix R;
  CreateMatrix(R,n,n);
  c_number m = 0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      for(int k = 0; k < n; ++k)
        R[i][j] += A[i][k] * (B[k][j]);
  return R;
}
void Identity(matrix &Arr, c_len n){
  CreateMatrix(Arr,n,n);
  for(int i = 0; i < n; ++i)
    Arr[i][i] = 1;
}
void SusRegresivaDown(matrix &L, results &y, results &b, c_len n){
  c_number t;
	for(c_len i = 0; i < n; ++i){
		t = b[i];
		for(c_len j = i-1; j > -1; --j){
			t = t - L[i][j] * (y[j]);
		}
		y[i] = t;
	}
  //PrintVector(y,n);
}
void SusRegresivaUpper(matrix &U, results &y, results &b, c_len n){
	c_number t;
	for(c_len i = n-1; i > -1; --i){
		t = y[i];
		for(c_len j = n-1; j > i; --j)
			t = t - U[i][j] * (b[j]);
		b[i] = t / U[i][i];
	}
  //PrintVector(b,n);
}
void printMatrix(const matrix &L,c_len w, c_len h){
	for(c_len i = 0; i < w; ++i){
		for(c_len j = 0; j < h; ++j)
			cout << L[i][j] << " ";
		cout << "\n";
	}
}
void MatrixCopy(matrix &A, matrix &B, c_len n){
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      A[i][j] = B[i][j];
}

//////////////////////////////////////////////////

bool DescompLU(matrix &U, matrix &L, c_len n){
  c_number m;
	for(c_len i = 0; i < n - 1; ++i){
    if(U[i][i] == 0)
      return 0;
		for(c_len j = i; j < n - 1; ++j){
			m = U[j+1][i] / U[i][i];
      L[j+1][i] = m;
			for(c_len k = i; k < n; ++k)
        U[j+1][k] = U[j+1][k] - (m * (U[i][k]));
		}
	}
  //cout << "L" << '\n';
  //printMatrix(L,n,n);
  //cout << "U" << '\n';
  //printMatrix(U,n,n);
  return 1;
}

void DescompPLU(matrix &U, matrix &L, matrix &P, c_len n){
  matrix A;
  CreateMatrix(A,n,n);
  MatrixCopy(A,U,n);
  results v;
  for(int i = 0; i < n; i++)
    v.push_back(i);
  c_number m, max = 0;
	c_number row = 0;
  for(c_len i = 0; i < n - 1; ++i){
		max = U[i][i];
    row = i;
		for(c_len c = i + 1; c < n; ++c){
			if(max < fabs(U[c][i])){
				max = U[c][i];
				row = c;
			}
		}
		if (i != row){
			U[i].swap(U[row]);
      swap(v[i],v[row]);
    }
    for(c_len j = i; j < n - 1; ++j){
      m = U[j+1][i] / U[i][i];
      //(*L)[j+1][i] = m;
      for(c_len k = i; k < n; ++k)
        U[j+1][k] = U[j+1][k] - (m * (U[i][k]));
    }
  }
  for(int i = 0; i < n; ++i)
    swap(P[i][v[i]],P[i][i]);
  //printMatrix(P, n, n);
  A = ProductMatrix(P,A,n);
  MatrixCopy(U,A,n);
  //printMatrix(U,n,n);
}

bool LU(matrix &Arr, matrix &L, results &b, results &y,c_len n){
  if(DescompLU(Arr,L,n)==false)
    return false;
  SusRegresivaDown(L,y,b,n);
  SusRegresivaUpper(Arr,y,b,n);
  return true;
}
bool PLU(matrix &Arr, matrix &L, results &b, results &y, c_len n){
  matrix P;
  Identity(P,n);
  DescompPLU(Arr,L,P,n);
  LU(Arr,L,b,y,n);
}
void ResolverSistemaEcuaciones(matrix &A, results &b, c_len n){
  matrix L;
  Identity(L,n);
  matrix C;
  CreateMatrix(C,n,n);
  MatrixCopy(C,A,n);
  results y(n);
  if(LU(C,L,b,y,n)){
    PrintVector(b,n);
    cout << "Sistema Resuelto por LU" << endl;
  }
  else{
    cout << "Sistema no puede resolverse por LU" << endl;
  PLU(A,L,b,y,n);
  PrintVector(b,n);
  }
}
