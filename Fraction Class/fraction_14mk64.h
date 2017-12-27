/*
 * fraction_14mk64.h
 *
 *Name: Max Karan
 *Student Number: 10170057
 *Net ID: 14mk64
 */

#ifndef FRACTION
#define FRACTION

#include <string>
#include <iostream>

using namespace std;

//exception if user attempts to instantiate a fraction with a denominator of 0
class FractionException{
public:
	FractionException(const string&);
	string what() const;
private:
	string message;
};

//main fraction class
class Fraction{
public:
	//constructors
	Fraction();
	//Fraction(int);
	Fraction(int num, int denom = 1);

	//Overloads
	friend Fraction operator+(const Fraction& left, const Fraction& right);      	// overload binary addition
	friend Fraction operator-(const Fraction& left, const Fraction& right);			//overload binary subtraction
	Fraction operator*(const Fraction&) const;
	Fraction operator/(const Fraction&) const;
	friend void operator+=(Fraction& left, const Fraction& right);

	bool operator!=(const Fraction&) const;
	bool operator==(const Fraction&) const;
	friend bool operator<(const Fraction& left, const Fraction& right);
	friend bool operator>(const Fraction& left, const Fraction& right);
	bool operator<=(const Fraction&) const;
	bool operator>=(const Fraction&) const;

	Fraction& operator++();					// Pre-increment
	Fraction operator++(int);				// Post-increment
	Fraction& operator-(); //unary negation
	friend ostream& operator<<(ostream& out, Fraction& value);
	friend istream& operator>>(istream& is, Fraction& value);

	//accessors
	int numerator();
	int denominator();


private:
	int numerator1;
	int denominator1;
	void gcd(int, int); //this method will take a Fraction and normalize it, used internally
};




#endif /* FRACTION */
