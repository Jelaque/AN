#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef double c_num;
typedef int c_len;
typedef vector< vector<c_num> > matrix;
typedef vector<c_num> results;
void CreateMatrix(matrix *&Arr, c_len n, c_len m){
  Arr = new matrix(n);
  for(int i = 0; i < n; ++i)
    (*Arr)[i].resize(m);
}

matrix *ProductMatrix(matrix *&A, matrix *&B, c_len n){
  matrix * R;
  CreateMatrix(R,n,n);
  c_num m = 0;
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
  c_num t;
	cout << "Vector de Resultados" << endl;
	for(c_len i = 0; i < n; ++i){
		t = (*b)[i];
		for(c_len j = i-1; j > -1; --j){
			t = t - (*L)[i][j] * ((*y)[j]);
		}
		(*y)[i]=t;
		cout<< t << " ";
	}
	cout << endl;
}

void SusRegresivaUpper(matrix *&U, results *&y, results *&b, c_len n){
	c_num t;
	cout << "Resultados" <<  endl;
	for(c_len i = n-1; i > -1; --i){
		t = (*y)[i];
		for(c_len j = n-1; j > i; --j)
			t = t - (*U)[i][j] * ((*b)[j]);
		(*b)[i] = t / (*U)[i][i];
		cout << (*b)[i] << " ";
	}
	cout << endl;
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
  c_num m;
	cout << "Descomposicion LU" << endl;
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
	cout << "Matrix L" << endl;
	printMatrix(L,n,n);
	cout << "Matrix U" << endl;
	printMatrix(U,n,n);
  return 1;
}

void DescompPLU(matrix *&U, matrix *&L, matrix *&P, c_len n){
  matrix *A;
  CreateMatrix(A,n,n);
  MatrixCopy(A,U,n);
  results v;
  for(int i = 0; i < n; i++)
    v.push_back(i);
  c_num m, max = 0;
	c_num row = 0;
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
	results *w;
	w = new results(n);
	for (int i = 0; i < n; ++i)
		(*w)[i] = (*b)[i];
  y = new results(n);
  if(LU(C,L,b,y,n)){

    //PrintVector(b,n);
    cout << "Sistema Resuelto por LU" << endl;
    C->clear();
  }
  else{
    cout << "Sistema no puede resolverse por LU" << endl;
    PLU(A,L,b,y,n);
    PrintVector(b,n);
  }
}

/*main(){
  c_len n = 4;
  matrix *A;
  results *b;
  b = new results(n);
  (*b)[0]=1;
  (*b)[1]=2;
  (*b)[2]=-2;
  (*b)[3]=5;
  CreateMatrix(A,n,n);
  (*A)[0][0] = 2;
  (*A)[0][1] = -1;
  (*A)[0][2] = -1;
  (*A)[0][3] = 1;
  (*A)[1][0] = 1;
  (*A)[1][1] = -1;
  (*A)[1][2] = -1;
  (*A)[1][3] = 1;
  (*A)[2][0] = 3;
  (*A)[2][1] = 2;
  (*A)[2][2] = -1;
  (*A)[2][3] = 3;
  (*A)[3][0] = 2;
  (*A)[3][1] = 1;
  (*A)[3][2] = -2;
  (*A)[3][3] = -1;
  ResolverSistemaEcuaciones(A,b,n);
  return 0;
}*/
