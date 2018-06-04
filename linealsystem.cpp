#include<iostream>
#include<array>
#include<cmath>
typedef double c_matrix;
typedef int c_len;
template<int n>
void printMatriz(c_matrix (&Arr)[n][n+1]){
	for(c_len i = 0; i < n; ++i){
		for(c_len j = 0; j < n + 1; ++j)
			std::cout << Arr[i][j] << " ";
		std::cout << "\n";
	}
}
template<int n>
void Escalona(c_matrix (&Arr)[n][n+1]){
	c_matrix m;
	for(c_len i = 0; i < n - 1; ++i){
		for(c_len j = i; j < n - 1; ++j){
			m = Arr[j+1][i] / Arr[i][i];
			std::cout << m << " ";
			for(c_len k = i; k < n + 1; ++k)
				Arr[j+1][k] = Arr[j+1][k] - (m * Arr[i][k]);
		}
		std::cout << std::endl;
	}
}
template<int n>
void SusRegresiva(c_matrix (&Arr)[n][n+1]){
	c_matrix R[n] = {n*0}, t = 0;
	for(c_len i = n-1; i > -1; --i){
		t = Arr[i][n];
		for(c_len j = n-1; j > i; --j){
			t = t - Arr[i][j]*R[j];
		}
		R[i] = t/Arr[i][i];
	}
	for(c_len i = n-1; i > -1; --i)
		std::cout << "x" << i << ": "  << R[i] << std::endl;
}
template<int n>
void MetGauss(c_matrix (&Arr)[n][n+1]){
	Escalona<n>(Arr);
	SusRegresiva<n>(Arr);
}
template<int n>
void swap_rows(c_matrix (&Arr1)[n], c_matrix (&Arr2)[n]){
	c_matrix temp = 0;
  for(c_len i = 0; i < n; ++i){
    temp = Arr1[i];
    Arr1[i] = Arr2[i];
    Arr2[i] = temp;
  }
}
template<int n>
void EscalonaPiv(c_matrix (&Arr)[n][n+1]){
	c_matrix m, max = 0;
	c_len row = 0;
	std::cout << "escalonamiento con pivoteo" << std::endl;
  for(c_len i = 0; i < n - 1; ++i){
		max = Arr[i][i];
		for(c_len c = i + 1; c < n; ++c){
			if(max < fabs(Arr[c][i])){
				max = Arr[c][i];
				row = c;
			}
		}
		if (i != row)
			swap_rows<n+1>(Arr[i],Arr[row]);
    for(c_len j = i; j < n - 1; ++j){
      m = Arr[j+1][i] / Arr[i][i];
      for(c_len k = i; k < n + 1; ++k)
        Arr[j+1][k] = Arr[j+1][k] - (m * Arr[i][k]);
    }
		std::cout << "paso: " << i << std::endl;
		printMatriz<4>(Arr);
  }
}
template<int n>
void MetGaussPiv(c_matrix (&Arr)[n][n+1]){
	EscalonaPiv<n>(Arr);
	SusRegresiva<n>(Arr);
}

main(){
	//c_matrix Arr[4][5] = {{2,3,4,-5,7},{-3,4,-5,7,2},{5,1,-1,6,5},{7,9,-13,17,21}};
	//c_matrix Ar[4][5] = {{2,3,4,-5,7},{-3,4,-5,7,2},{5,1,-1,6,5},{7,9,-13,17,21}};
	c_matrix Arr[4][5] = {{2,-1,-1,1,1},{1,-1,-1,1,2},{3,2,-1,3,-2},{2,1,-2,-1,5}};
	//MetGauss<4>(Arr);
	printMatriz<4>(Arr);
	MetGaussPiv<4>(Arr);
	return 0;
}
