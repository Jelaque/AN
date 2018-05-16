#include<iostream>
#include<cmath>
typedef double c_num;

c_num converge(c_num (*f)(long),int n, c_num TOL, c_num point){
	c_num r1=0,r2=TOL-1.0,r3=0;
	for(n+=2;fabs(r1-r2) > TOL;++n){
		r2 = r3;
		r1 = (log(fabs(f(n+1)-point))-log(fabs(f(n)-point)))/(log(fabs(f(n)-point))-log(fabs(f(n-1)-point)));
		r3 = log(fabs(f(n+1)-f(n))/fabs(f(n)-f(n-1)))/log(fabs(f(n)-f(n-1))/fabs(f(n-1)-f(n-2)));
		std::cout << n << " " << r1 << " " << r3 << std::endl;
	}
	return r1;
}

c_num f1(long x){
	return 1/pow(3,x);
}
c_num f2(long x){
  return 2/pow(3,pow(2,x));
}
c_num f3(long x){
  return 1/pow(x,2);
}
c_num f4(long x){
	if (x<=2)
		return 2.0;
  return f4(x-1)/2+1/f4(x-1);
}
c_num f5(long x){
  return pow(x,3)+4*(x,2)-10;
}
c_num f6(long x){
  return pow(x,2)/2+x+1-exp(x);
}


main(){
	std::cout << converge(f6,1,0.00001,0.696106) << std::endl;
	return 0;
}
