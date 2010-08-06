#include "Calculus.h"

double Calculus::Integrals::manuEval( double parameter )
{
	return (parameter * parameter) + (2 * parameter) - 5;
}
double Calculus::Integrals::SimpsonsRule( int Partitions, double LowerLimit, double UpperLimit )
{
//	double DeltaX = (UpperLimit - LowerLimit) / Partitions;
//	bool Times4 = true;
//
//	double TimesOne(0), TimesTwo(0), TimesFour(0);
//
//	TimesOne = manuEval(LowerLimit) + manuEval(UpperLimit);
//	int partsleft; double thisval;
//	for(partsleft = Partitions, 
//		thisval = LowerLimit; 
//	partsleft > 0; 
//	partsleft--, 
//		thisval += DeltaX, 
//		Times4 = !Times4)
//		{
//			if(Times4)
//				TimesFour += manuEval(thisval);
//			else // if Times2
//				TimesTwo += manuEval(thisval);
//		}
//	TimesFour *= 2;
//	TimesTwo *= 4; 
//	//return (DeltaX / 3) * (TimesOne + (2*(TimesTwo + (2*(TimesFour)))));
//	return (DeltaX / 3) * (TimesOne + TimesTwo + TimesFour);
	double sum = 0;
	double deltax = (UpperLimit - LowerLimit) / Partitions; 
	double x = LowerLimit;
	for (int index = 1; index<= Partitions-1; index += 2)
	{
		double y = Calculus::Integrals::manuEval( LowerLimit );
		sum += y*deltax;
		x = LowerLimit + index*deltax;
		y = Calculus::Integrals::manuEval( x );
		sum += 4*y*deltax;
		y = Calculus::Integrals::manuEval( x );
		x = LowerLimit + (index+1)*deltax;
		sum += y*deltax;
	}
	sum = sum/3;
	return sum; // need to fix - doesn't work
}
