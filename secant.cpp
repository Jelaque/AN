#include<iostream>
#include<cstdio>
#include<cmath>
#include<bits/stdc++.h>
#include"exprtk.hpp"
typedef double t_type;
typedef int it;
enum Typef {type1,type2,type3} typef;
t_type secant(t_type a, t_type b, exprtk::expression<t_type>& func, t_type& TOL,t_type& x, Typef tp){
	t_type p;
	t_type fa,fp,fb;
	x = a;
	fa = func.value();
	x = b;
	fb = func.value();
	p = b - fb*(b-a)/(fb-fa); 
	std::ofstream file;
	file << std::setprecision(12) << std::fixed;
	if (tp == type1){
		file.open("data1.csv");
		file << "ITERACIONES\n";
		file << "k,a,b,r,f(r)\n";
		for(int i = 1; i <= TOL; ++i){
    	x = a;
    	fa = func.value();
    	x = p;
    	fp = func.value();
    	file << i << "," << a << "," << b << "," << p << "," << fp << "\n";
    	if (fa == fp)
				break;
			else if (fa*fp < 0)
      	b = p;
    	else
      	a = p;
    	p = b - fb*(b-a)/(fb-fa);
  	}	
	}
	else if (tp == type2){
		file.open("data2.csv");
		file << "TOLERANCIA\n";
    file << "k,a,b,r,|f(r)|\n";
		x = p;
		fp = func.value();
    for(int i = 1;fabs(fp) > TOL; ++i){
      x = a;
      fa = func.value();
      x = p;
      fp = func.value();
      file << i << "," << a << "," << b << "," << p << "," << fabs(fp) << "\n";
      if (fa == fp)
        break;
			else if (fa*fp < 0)
        b = p;
      else
        a = p;
    	p = b - fb*(b-a)/(fb-fa);
    }
	}
	else if(tp == type3){
		file.open("data3.csv");
		file << "DISTANCIA ENTRE EXTREMOS\n";
    file << "k,pr,r,|r-ra|,f(r)\n";
		t_type pf = a;
    for(int i = 1;fabs(p-pf) > TOL; ++i){
      x = a;
      fa = func.value();
      x = p;
      fp = func.value();
			file << i  << "," << pf << "," << p << "," << fabs(p-pf) << "," << fp << "\n";
      pf = p;
			if (fa == fp)
        break;
			else if (fa*fp < 0)
        b = p;
      else
        a = p;
      p = b - fb*(b-a)/(fb-fa);
    }
	}
	file.close();
	return p;
}

void parse_function(std::string& expression_string, t_type& a, t_type& b, t_type& tol, Typef tp){
  typedef exprtk::symbol_table<t_type> symbol_table_t;
  typedef exprtk::expression<t_type>     expression_t;
  typedef exprtk::parser<t_type>             parser_t;
	t_type x;
  symbol_table_t symbol_table;
  symbol_table.add_variable("x",x);
  symbol_table.add_constants();

  expression_t expression;
  expression.register_symbol_table(symbol_table);

  parser_t parser;
  parser.compile(expression_string,expression);
	std::cout << secant(a,b,expression,tol,x,tp);
}

main(){
	std::string expression = "(x ^ 3) + (3 * (x ^ 2) * cos(x)) - 1";
	t_type a,b,tol;
	//std::cout << "Enter your function: f(x):";
	//std::cin>>expression;
	std::cout << "Enter the interval: ";
	std::cin>>a>>b;
	//std::cout << "Enter the number of iterations";
	//std::cin>>tol;
	//parse_function(expression,a,b,tol,type1);
	//std::cout << "Enter the Tolerance";
	//std::cin>>tol;
	//parse_function(expression,a,b,tol,type2);
	std::cout << "Enter the tolerance: ";		
	std::cin>>tol;
	parse_function(expression,a,b,tol,type3);
	return 0;
}
