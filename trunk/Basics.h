#pragma once
#include <string>
#include "Function.h"

struct Vector2
{
	double x, y;
};

struct Vector3
{
	double x, y, z;
};

namespace NumericalStatistics
{
	int GCD(int a, int b);
	long int LCM(int a, int b);
	int Factors(int number);
	int GetFactors( void );
}

struct Ratio
{
	int numerator;
	int denominator;
	void Display( void );
	void Reduce( void );
	double Evaluate( void );
};

struct Number
{ // a wrapper if we ever end up needing it -
  // I only wanted to add a stupid exponentiation operater...
	double value;
	Number operator+( Number operand );
	Number operator-( Number operand );
	Number operator*( Number operand );
	Number operator/( Number operand );
	Number operator^( Number operand );
	Number operator+( double operand );
	Number operator-( double operand );
	Number operator*( double operand );
	Number operator/( double operand );
	Number operator^( double operand );
	double ToDouble();
};
