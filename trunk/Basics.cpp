#include "Basics.h"
#include "math.h"
#include <cmath>
#include <iostream>
//#include "Global Constants.h" (not included in SVN repository - not necessary at this stage of the game, and besides it only defines PI and EPSILON.

//#include <vector>

using namespace std;

double sec(double argument){	return 1 / cos(argument);}
double csc(double argument){	return 1 / sin(argument);}
double cot(double argument){	return 1 / tan(argument);}
int NumericalStatistics::GCD(int a, int b)
{
	while(true)
	{
		a = a % b;
		if( a == 0 )
			return b;
		b = b % a;
		if( b == 0 )
			return a;
    }
}

long int NumericalStatistics::LCM(int a, int b)
{
	long int value = ( a * b ) / GCD( a, b );
	if(value < 0)
		return -1;
	return value;
}

void Ratio::Display( void )
{
	printf("  Numerator: %i\n", this->numerator);
	printf("Denominator: %i\n", this->denominator);
}

void Ratio::Reduce( void )
{
	int thisGCD = NumericalStatistics::GCD(this->numerator, this->denominator);
	  this->numerator /= thisGCD;
	this->denominator /= thisGCD;
}

double Ratio::Evaluate( void )
{
	return ((double)this->numerator / (double)this->denominator);
}

/*Number struct*/

double Number::ToDouble()
{
	return this->value;
}
