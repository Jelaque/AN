#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

typedef double c_var;
typedef vector< vector<c_var> > c_matrix;
typedef vector< c_var > c_vector;
typedef int c_len;

/*c_var norma(c_var m, c_len n){ //este es el valor absoluto mas grande
	return pow(pow(m,n),1/n);
}*/

c_var Norma(const c_vector &v1, const c_vector& v2){
	c_var value = 0;
	for(int  i = 0; i < v1.size(); ++i)
		value += pow(v1[i] - v2[i], 2);
	return sqrt(value);
}

void printVector(c_vector &v, c_len n);

void MetGaussSeidel(const c_matrix &A,const c_vector &B, c_vector &XO, c_var TOL, c_len n){
	c_var x = TOL + 1; // x > TOL
	c_var sum;
	c_vector XI(n);
	for(int i = 0; i < n; ++i)
		XI[i] = 0;
	for(int k = 1; x > TOL; ++k){
		cout << k << ": ";
		for(c_len i = 0; i < n; ++i){
			sum = 0;
			for(c_len j = 1; j < i; ++j)
				sum -= A[i][j]*XI[j];
			for(c_len j = i+1; j < n; ++j)
				sum -= A[i][j]*XO[j];
			sum += B[i];
			sum /= A[i][i];
			XI[i] = sum;
		}
		printVector(XI,n);
		x = Norma(XI,XO);
		cout << "Norma: " << x << endl;
		XO = XI;
	}
}

void MetJacobi(const c_matrix &A,const c_vector &B, c_vector &XO, c_var TOL, c_len n){
	c_var x = TOL + 1; // x > TOL
	c_var sum;
	c_vector XI(n);
	for(int i = 0; i < n; ++i)
		XI[i] = 0;
	for(int k = 1; x > TOL; ++k){
		cout << k << ": ";
		for(c_len i = 0; i < n; ++i){
			sum = 0;
			for(c_len j = 0; j < n; ++j)
				if(i != j)
					sum -= A[i][j]*XO[j];
			sum += B[i];
			sum /= A[i][i];
			XI[i] = sum;
		}
		x = Norma(XI,XO);
		printVector(XI,n);
		cout << "Norma: " << x << endl;
		XO = XI;
	}
}

void printVector(c_vector &v, c_len n){
	for(int i = 0; i < n; ++i)
		cout << v[i] << " ";
	//cout << endl;
}

main(){
	c_matrix A = {{1,4,-1},{-3,1,-1},{1,1,-4}};
	c_vector B = {4,1,-2};
	c_vector XO = {0,0,0};
	MetGaussSeidel(A,B,XO,0.001,3);
	return 0;
}
