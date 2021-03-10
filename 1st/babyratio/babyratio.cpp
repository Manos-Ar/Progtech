#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>
#include <stdlib.h>
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


//rational :: rational(const rational &r){
//	nom=r.nom;
//	den=r.den;
//}

rational rational :: add (rational r){
	
	return rational(this->nom * r.den + r.nom * den, this->den * r.den);
//	return r_add;
}

rational rational :: sub (rational r){
	rational r_sub(this->nom * r.den - r.nom * den, this->den * r.den);
	return r_sub;
}

rational rational ::mul (rational r){
	rational r_mul(this->nom *r.nom , this->den * r.den);
	return r_mul;
}

rational rational :: div (rational r){
	rational r_div(this->nom * r.den , this->den * r.nom);
	return r_div;
}


void rational :: print (){
	bool tmp_sign=(this->nom < 0);
	if(tmp_sign)
		cout <<"-"<<abs(this->nom)<<"/" <<this->den;
	else 
		cout <<abs(this->nom)<<"/" <<this->den;
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


int main(){
	
	rational a(1,-2);
	rational b(1,4);
	a.add(b).print();
	cout<<endl;
	a.sub(b).print();
	cout<<endl;
	a.mul(b).print();
	cout<<endl;
	a.div(b).print();
	cout<<endl;
	
}


