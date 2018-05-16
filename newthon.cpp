#include<iostream>
#include<cmath>

typedef double c_num;

c_num newthon(c_num (*f)(long), c_num (*d)(long), c_num TOL, c_num po){
	c_num p = 0;
	for(int i = 0;; ++i){
		if(fabs(po-p) < TOL)
			break;
		p = po -f(po)/d(po);
		po = p;
		std::cout << i << " " << p << std::endl; 
	}
	return p;
}

c_num f1(long x){
	return pow(x,3)+4*pow(x,2)-10;
}
c_num d1(long x){
	return 3*pow(x,2)+8*x;
}
c_num f2(long x){
	return pow(x,2)/2+x+1-exp(x);
}
c_num d2(long x){
	return x+1-exp(x);
}


main(){
	std::cout << newthon(f2,d2,0.00000001,1.0) << std::endl;
	return 0;
}
