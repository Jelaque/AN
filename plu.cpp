#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef double c_matrix;
typedef int c_len;
typedef vector< vector<c_matrix> > matrix;
typedef vector<c_matrix> results;
void CreateMatrix(matrix *&Arr, c_len n, c_len m){
  Arr = new matrix(n);
  for(int i = 0; i < n; ++i)
    (*Arr)[i].resize(m);
}

matrix *ProductMatrix(matrix *&A, matrix *&B, c_len n){
  matrix * R;
  CreateMatrix(R,n,n);
  c_matrix m = 0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      for(int k = 0; k < n; ++k)
        (*R)[i][j] += (*A)[i][k] * ((*B)[k][j]);
  return R;
}

void Identity(matrix *&Arr, c_len n){
  CreateMatrix(Arr,n,n);
  for(int i = 0; i < n; ++i)
    (*Arr)[i][i] = 1;
}

void SusRegresivaDown(matrix *&L, results *&y, results *&b, c_len n){
  c_matrix t;
	for(c_len i = 0; i < n; ++i){
		t = (*b)[i];
		for(c_len j = i-1; j > -1; --j){
			t = t - (*L)[i][j] * ((*y)[j]);
		}
		(*y)[i]=t;
	}
}

void SusRegresivaUpper(matrix *&U, results *&y, results *&b, c_len n){
	c_matrix t;
	for(c_len i = n-1; i > -1; --i){
		t = (*y)[i];
		for(c_len j = n-1; j > i; --j)
			t = t - (*U)[i][j] * ((*b)[j]);
		(*b)[i] = t / (*U)[i][i];
	}
}

void printMatrix(const matrix *L,c_len w, c_len h){
	for(c_len i = 0; i < w; ++i){
		for(c_len j = 0; j < h; ++j)
			cout << (*L)[i][j] << " ";
		cout << "\n";
	}
}

void MatrixCopy(matrix *&A, matrix *&B, c_len n){
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      (*A)[i][j] = (*B)[i][j];
}

//////////////////////////////////////////////////

bool DescompLU(matrix *&U, matrix *&L, c_len n){
  c_matrix m;
	for(c_len i = 0; i < n - 1; ++i){
    if((*U)[i][i] == 0)
      return 0;
		for(c_len j = i; j < n - 1; ++j){
			m = (*U)[j+1][i] / (*U)[i][i];
      (*L)[j+1][i] = m;
			for(c_len k = i; k < n; ++k)
        (*U)[j+1][k] = (*U)[j+1][k] - (m * ((*U)[i][k]));
		}
	}
  return 1;
}

void DescompPLU(matrix *&U, matrix *&L, matrix *&P, c_len n){
  matrix *A;
  CreateMatrix(A,n,n);
  MatrixCopy(A,U,n);
  results v;
  for(int i = 0; i < n; i++)
    v.push_back(i);
  c_matrix m, max = 0;
	c_matrix row = 0;
  for(c_len i = 0; i < n - 1; ++i){
		max = (*U)[i][i];
    row = i;
		for(c_len c = i + 1; c < n; ++c){
			if(max < fabs((*U)[c][i])){
				max = (*U)[c][i];
				row = c;
			}
		}
		if (i != row){
			(*U)[i].swap((*U)[row]);
      swap(v[i],v[row]);
    }
    for(c_len j = i; j < n - 1; ++j){
      m = (*U)[j+1][i] / (*U)[i][i];
      //(*L)[j+1][i] = m;
      for(c_len k = i; k < n; ++k)
        (*U)[j+1][k] = (*U)[j+1][k] - (m * ((*U)[i][k]));
    }
  }
  for(int i = 0; i < n; ++i)
    swap((*P)[i][v[i]],(*P)[i][i]);
  A = ProductMatrix(P,A,n);
  MatrixCopy(U,A,n);
  A->clear();
}

bool LU(matrix *&Arr, matrix *&L, results *&b, results *&y,c_len n){
  if(DescompLU(Arr,L,n)==false)
    return false;
  y = new results(n);
  SusRegresivaDown(L,y,b,n);
  SusRegresivaUpper(Arr,y,b,n);
  return true;
}
bool PLU(matrix *&Arr, matrix *&L, results *&b, results *&y, c_len n){
  matrix *P;
  Identity(P,n);
  DescompPLU(Arr,L,P,n);
  LU(Arr,L,b,y,n);
}
void PrintVector(const results *v, c_len n){
  for(int i = 0; i < n; ++i)
    cout << "x" << i << ": "<< (*v)[i] << ", ";
  cout << endl;
}
void ResolverSistemaEcuaciones(matrix*&A, results *&b, c_len n){
  matrix *L;
  Identity(L,n);
  matrix *C;
  CreateMatrix(C,n,n);
  MatrixCopy(C,A,n);
  results *y;
  y = new results(n);
  if(LU(C,L,b,y,n)){
    PrintVector(b,n);
    cout << "Sistema Resuelto por LU" << endl;
    C->clear();
  }
  else{
    cout << "Sistema no puede resolverse por LU" << endl;
    PLU(A,L,b,y,n);
    PrintVector(b,n);
  }
}

main(){
  c_len n = 4;
  matrix *A;
  results *b;
  b = new results(n);
  (*b)[0]=1;
  (*b)[1]=2;
  (*b)[2]=3;
  (*b)[3]=4;
  CreateMatrix(A,n,n);
  (*A)[0][0] = 1;
  (*A)[0][1] = 2;
  (*A)[0][2] = 3;
  (*A)[0][3] = 4;
  (*A)[1][0] = 5;
  (*A)[1][1] = 6;
  (*A)[1][2] = 7;
  (*A)[1][3] = 8;
  (*A)[2][0] = 9;
  (*A)[2][1] = 10;
  (*A)[2][2] = 11;
  (*A)[2][3] = 12;
  (*A)[3][0] = 13;
  (*A)[3][1] = 14;
  (*A)[3][2] = 15;
  (*A)[3][3] = 16;
  ResolverSistemaEcuaciones(A,b,n);
  return 0;
}
