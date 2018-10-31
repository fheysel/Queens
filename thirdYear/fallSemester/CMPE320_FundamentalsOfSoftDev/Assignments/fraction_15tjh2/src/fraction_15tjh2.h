//============================================================================
// 		Name: fraction_15tjh2.h
// 		Author:Tom Heysel
//		Net Id: 15tjh2
//      Student #: 20000838
//============================================================================

#pragma once
#include <iostream>


class Fraction{
public:
	//Constructors
	Fraction();//sets 0 as top and 1 as bottom
	Fraction(const int& num);//sets num as top and 1 as bottom
	Fraction(std::string theFrac);//parses string into num and denom and calls two-int constructor
	Fraction(const int& num, const int& denom);//takes a num and denom and sets top and bottom while checking for a gcd

	//Accessors
	int numerator() const;
	int denominator() const;

	//Mutators (only used in >> operator overloading)
	void setNum(int newTop);
	void setDenom(int newBottom);

	//Overloaded unary operators
	Fraction& operator-();//negation
	Fraction& operator++();//pre-increment
	Fraction operator++(int);//post-increment
	Fraction& operator--();//pre-decrement
	Fraction operator--(int);//post-decrement
	Fraction& operator+=(const Fraction& right);//plus equals


private:
	//Members
	int top; //numerator
	int bottom; //denominator

	//Functions
	int findGCD(int num, int denom);//calculate greatest common divisor
};

//Overloaded non-member operators

//BINARY OPERATORS
//Addition/Subtraction
Fraction operator+(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& left, const Fraction& right);

//Multiplication/Division
Fraction operator*(const Fraction& left, const Fraction& right);
Fraction operator/(const Fraction& left, const Fraction& right);

//Addition and Assignment
Fraction operator+=(const Fraction& accumulator, const Fraction& aFrac);

//Comparisons
bool operator<(const Fraction& left, const Fraction& right);
bool operator<=(const Fraction& left, const Fraction& right);
bool operator>(const Fraction& left, const Fraction& right);
bool operator>=(const Fraction& left, const Fraction& right);

bool operator==(const Fraction& left, const Fraction& right);
bool operator!=(const Fraction& left, const Fraction& right);

//File IO stream operators
std::ostream& operator<<(std::ostream& out, const Fraction& aFrac);
std::istream& operator>>(std::istream& in, Fraction& aFrac);


class FractionException{
public:
	//constructors
	FractionException();
	FractionException(std::string statement);

	//accessor
	std::string &what();
private:
	std::string message;
};


