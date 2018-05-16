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

c_var Norma(const c_vector &v){
	c_var value = 0;
	for(auto it = v.begin(); it != v.end(); ++it)
		value += fabs(*it);
	return value;
}

void printVector(c_vector &v, c_len n);

void MetJacobi(const c_matrix &A,const c_vector &B, c_vector &XO, c_var TOL, c_len n){
	c_var x = TOL + 1; // x > TOL
	c_var sum;
	c_vector XI(n);
	for(int k = 1; x > TOL; ++k){
		cout << k << " ";
		printVector(XO,n);
		for(c_len i = 0; i < n; ++i){
			sum = 0;
			for(c_len j = 0; j < n; ++j)
				if(i != j)
					sum -= A[i][j]*XO[j];
			sum += B[i];
			sum /= A[i][i];
			XI[i] = sum;
		}
		x = fabs(Norma(XI)-Norma(XO));
		XO = XI;
	}
}

void printVector(c_vector &v, c_len n){
	for(int i = 0; i < n; ++i)
		cout << v[i] << " ";
	cout << endl;
}

main(){
	c_matrix A = {{5,-2,1,1},{-1,4,1,-1},{2,-2,7,-1},{0,1,3,-6}};
	c_vector B = {1,2,3,4};
	c_vector XO = {0,0,0,0};
	MetJacobi(A,B,XO,0.001,4);
	return 0;
}
