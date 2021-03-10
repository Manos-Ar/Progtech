#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

rational :: rational (int n, int d){
	int tmp, sign;
	
	if(n<0 && d<0)
		sign=1;
	else if(n<0 || d<0)
		sign=-1;
	else sign=1;
		
	n=abs(n);
	d=abs(d);

	tmp=gcd(n,d);
	
	n=sign*n;
	
	this->nom = n/tmp;
	this->den = d/tmp;
}

rational operator + (const rational &x, const rational &y){
	return rational(x.nom * y.den + y.nom * x.den, x.den * y.den);
}

rational operator - (const rational &x, const rational &y){
	return rational(x.nom * y.den - y.nom * x.den, x.den * y.den);
}

rational operator * (const rational &x, const rational &y){
	return rational(x.nom * y.nom, x.den * y.den);
}

rational operator / (const rational &x, const rational &y){
	return rational(x.nom * y.den, x.den * y.nom);
}

ostream & operator<<(ostream &out, const rational &x) {
	out << x.nom << "/" << x.den;
	return out;
}

int rational :: gcd (int x, int y){
	while (x > 0 && y > 0){
		if (x > y) 
			x = x % y;	
		else 
			y = y % x;
	}	 
	return x + y;
}

// int main(){
	
// 	rational a(1,2),b(3,4),c(5,6);
// 	cout << a+b-c<<endl;
// 	cout<<a<<" should still be 1/2"<<endl;
// }


