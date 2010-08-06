#include <string>
#pragma once
using namespace std;

namespace Calculus
{
	namespace Derivates
    {
		string Derivate( string function );
		double nDerive( string function, double value );
	}
	namespace Integrals
	{
		double SimpsonsRule( int Partitions, double LowerLimit, double UpperLimit );
		double manuEval( double parameter ); // Use until Function calculator is complete
	}
}