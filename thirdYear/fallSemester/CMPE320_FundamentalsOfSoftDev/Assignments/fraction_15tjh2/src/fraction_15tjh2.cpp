//============================================================================
// 		Name: fraction_15tjh2.cpp
// 		Author: Fiona Heysel
//		Net Id: 15tjh2
//      Student #: 20000838
//============================================================================
#include "fraction_15tjh2.h"
#include <iostream>
using namespace std;

Fraction::Fraction(){//default constructor
	top = 0;
	bottom = 1;
}

Fraction::Fraction(const int& num){
	top = num;
	bottom = 1;
}

Fraction::Fraction(const int& num, const int& denom){
	if(denom == 0){
		throw FractionException("Denominator cannot be zero");
	}

	if(num == 0){
		top = 0;
		bottom = 1;
		return;
	}

	int GCD = findGCD(num, denom);

	if(denom < 0){
		bottom = abs(denom);
		top = num * -1;
	}else{
		top = num;
		bottom = denom;
	}

	top /= GCD;
	bottom /= GCD;
}

//Accessors
int Fraction::numerator() const{
	return top;
}

int Fraction::denominator() const{
	return bottom;
}

//Mutators
void Fraction::setNum(int newTop){
	top = newTop;
}

void Fraction::setDenom(int newBottom){
	bottom = newBottom;
}

//find the greatest common divisor of two numbers
int Fraction::findGCD(int n, int m){
	n = abs(n);
	m = abs(m);

	if((m <= n) && (n%m == 0)){
		return m;
	}else if(n < m){
		return findGCD(m, n);
	}else{
		return findGCD(m, n%m);
	}
}

//UNARY OPERATOR OVERLOADING ALL MEMBER FUNCTIONS
Fraction& Fraction::operator-(){
	*this = *this * -1;
	return(*this);
}

Fraction& Fraction::operator++(){//pre-increment
	*this = *this + 1;
	return(*this);
}

Fraction Fraction::operator++(int unused){//post-increment
	Fraction clone(top, bottom);
	*this = *this + 1;
	return clone;
}

Fraction& Fraction::operator--(){//pre-increment
	*this = *this -1;
	return(*this);
}

Fraction Fraction::operator--(int unused){
	Fraction clone(top, bottom);
	*this = *this - 1;
	return clone;
}

Fraction& Fraction::operator+=(const Fraction& right){
	*this = *this + right;
	return *this;
}

//BINARY OPERATORS NON-MEMBER FUNCTIONS

Fraction operator+(const Fraction& left, const Fraction& right){
	int num1 = left.numerator()*right.denominator();
	int num2 = left.denominator()*right.numerator();
	int denom = left.denominator()*right.denominator();

	return Fraction(num1+num2, denom);
}

Fraction operator-(const Fraction& left, const Fraction& right){
	int num1 = left.numerator()*right.denominator();
	int num2 = left.denominator()*right.numerator();
	int denom = left.denominator()*right.denominator();

	return Fraction(num1-num2, denom);
}

Fraction operator*(const Fraction& left, const Fraction& right){
	return Fraction(left.numerator() * right.numerator(), left.denominator() * right.denominator());
}

Fraction operator/(const Fraction& left, const Fraction& right){
	return Fraction(left.numerator() * right.denominator(), left.denominator() * right.numerator());
}


bool operator<(const Fraction& left, const Fraction& right){
	Fraction temp = left - right;
	if(temp.numerator() < 0){
		return true;
	}
	else
		return false;
}

bool operator<=(const Fraction& left, const Fraction& right){
	Fraction temp = left - right;
	if(temp.numerator() <= 0){
		return true;
	}
	else
		return false;
}

bool operator>(const Fraction& left, const Fraction& right){
	Fraction temp = right - left;
	if(temp.numerator() < 0){
		return true;
	}
	else
		return false;
}

bool operator>=(const Fraction& left, const Fraction& right){
	Fraction temp = right - left;
	if(temp.numerator() <= 0){
		return true;
	}
	else
		return false;
}

bool operator==(const Fraction& left, const Fraction& right){
	Fraction temp = left - right;
	if(temp.numerator() == 0){
		return true;
	}
	else
		return false;
}

bool operator!=(const Fraction& left, const Fraction& right){
	return(!(left == right));
}


//FILE IO OVERLOADING
ostream& operator<<(ostream& out, const Fraction& aFrac){
	out << aFrac.numerator() << "/" << aFrac.denominator();
	return out;
}

istream& operator>>(istream& in, Fraction& aFrac){
	string num;
	string denom;
	string fraction;

	in >> fraction;
	size_t partition = fraction.find("/");
	size_t length = fraction.length();

	if(partition != string::npos){
		for(size_t i=0; i<partition; i++)
			num += fraction.at(i);
		for(size_t i=partition+1; i<length;i++)
			denom += fraction.at(i);
		aFrac.setNum(stoi(num));
		aFrac.setDenom(stoi(denom));
	}
	else{
		aFrac.setNum(stoi(fraction));
		aFrac.setDenom(1);
	}
	return in;
}

FractionException::FractionException(){
	message = "Fraction Exception";
}

FractionException::FractionException(string statement){
	message = statement;
}

string& FractionException::what(){
	return message;
}


