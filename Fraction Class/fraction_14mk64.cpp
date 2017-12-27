/*
 * fraction_14mk64.cpp
 *
 *Name: Max Karan
 *Student Number: 10170057
 *Net ID: 14mk64
 */

#include <string>
#include <sstream>
#include "fraction_14mk64.h"

using namespace std;

//Define the Fraction Exception methods
FractionException::FractionException(const string& m) : message(m){}

string FractionException::what() const{
	return message;
}

//Fraction Constructors
Fraction::Fraction(){
	numerator1 = 0;
	denominator1 = 1;
}

//Fraction::Fraction(int num) : numerator1(num), denominator1(1){}

Fraction::Fraction(int num, int denom){//this defaults to a 0/1 fraction if no inputs, and an integer if only one input
	if(denom == 0){//check for illegal input
		throw FractionException("Cannot have a zero denominator!");
	}

	if(denom < 0){ //if denominator is negative
		//if both top and bottom are negative, this will make both positive
		//if only bottom is negative, this will transfer the negative sign to the top
		num *= -1;
		denom *= -1;
	}

	numerator1 = num;
	denominator1 = denom;

	this->gcd(num, denom);
}

//Accessors
int Fraction::numerator(){
	return numerator1;
}

int Fraction::denominator(){
	return denominator1;
}

//define the method to find greatest common divider of the fraction
void Fraction::gcd(int n, int m){
	int gcd;

	//make positive, since we do not need sign for GCD and it deals with a bug
	if(m<0)
		m*=-1;

	if(n<0)
		n*=-1;

	if(m <= n && n%m == 0){
		gcd = m;
		//divide numerator and denominator by the GCD
		numerator1 = numerator1/gcd;
		denominator1 = denominator1/gcd;
	}
	else if(m>n){
		this->gcd(m, n);
	}
	else{
		this->gcd(m,n%m);
	}
}

//Time to override some operators
Fraction operator+ (const Fraction& left, const Fraction& right){
	int newNum = (left.numerator1*right.denominator1) + (right.numerator1*left.denominator1);
	int newDenom = left.denominator1*right.denominator1;

	Fraction ret(newNum, newDenom);
	ret.gcd(ret.numerator(), ret.denominator());
	return ret;
}


Fraction operator- (const Fraction& left, const Fraction& right){
	int newNum = right.numerator1, newDenom = right.denominator1;

	newNum *= left.numerator1;
	newDenom *= left.denominator1;

	newNum = left.numerator1 - right.numerator1;
	newDenom = right.denominator1;

	Fraction ret(newNum, newDenom);
	ret.gcd(ret.numerator(), ret.denominator());
	return ret;
}

Fraction Fraction::operator* (const Fraction& c) const{
	int newNum, newDenom;

	newNum = numerator1 * c.numerator1;
	newDenom = denominator1 * c.denominator1;

	Fraction ret(newNum, newDenom);
	ret.gcd(ret.numerator(), ret.denominator());
	return ret;
}

Fraction Fraction::operator/ (const Fraction& c) const{
	int newNum, newDenom;

	//since division is the same as multiplying by the inverse, simply invert the second fraction
	newNum = this->numerator1 * c.denominator1;
	newDenom = this->denominator1 * c.numerator1;

	Fraction ret(newNum, newDenom);
	ret.gcd(ret.numerator(), ret.denominator());
	return ret;
}

void operator+= (Fraction& left, const Fraction& right){
	left = left + right;
}

Fraction& Fraction::operator++ (){
	numerator1 = numerator() + denominator();
	this->gcd(numerator(), denominator());
	return *this;
}

Fraction Fraction::operator++ (int unused){
	Fraction clone(numerator(), denominator());
	numerator1 = numerator() + denominator();
	return clone;
}

Fraction& Fraction::operator-(){
	numerator1 = numerator() * -1;
	return *this;
}

bool Fraction::operator!=(const Fraction& c) const{
	return (numerator1 != c.numerator1 && denominator1 != c.denominator1);
}

bool Fraction::operator==(const Fraction& c) const{
	return (numerator1 == c.numerator1 && denominator1 == c.denominator1);

}
bool operator<(const Fraction& left, const Fraction& right){
	double doubleRight, doubleLeft;
	doubleRight = (double)right.numerator1/(double)right.denominator1;
	doubleLeft = (double)left.numerator1/(double)left.denominator1;

	return(doubleLeft<doubleRight);
}

bool operator>(const Fraction& left, const Fraction& right){
	double doubleRight, doubleLeft;
	doubleRight = (double)right.numerator1/(double)right.denominator1;
	doubleLeft = (double)left.numerator1/(double)left.denominator1;

	return(doubleLeft>doubleRight);
}

bool Fraction::operator<=(const Fraction& c) const{
	double doubleFraction, doubleC;
	doubleFraction = (double)numerator1/(double)denominator1;
	doubleC = (double)c.numerator1/(double)c.denominator1;

	return(doubleFraction<=doubleC);
}

bool Fraction::operator>=(const Fraction& c) const{
	double doubleFraction, doubleC;
	doubleFraction = (double)numerator1/(double)denominator1;
	doubleC = (double)c.numerator1/(double)c.denominator1;

	return(doubleFraction>=doubleC);
}

ostream& operator<<(ostream& os, Fraction& value)
{
    os << value.numerator() << "/" << value.denominator();
    return os;
}

istream& operator>>(istream& is, Fraction& value){
	string input;
	is >> input;

	string delimiter = "/";
	string tempS(input.substr(0, input.find(delimiter)));
	istringstream temp(tempS);
	temp >> value.numerator1;

	tempS = input.substr(input.find(delimiter)+1, input.size());
	temp >> value.denominator1;
	return is;
}
