#ifndef ULTIMATH_H_
#define ULTIMATH_H_

#include "Basics.h"
#include "Function.h"
/*
SPECIAL GOALS

Add basic variable-base arithmetic (octal math, binary math, etc.)

*/
/*
Welcome to Ultimath, the Open Source Number-Crunching,
String-Parsing, Jello-Eating, Coffee-Drinking Engine.

Hopefully posting this to Google Code and DreamInCode
will get it some collaborative activity.

This header file is going to tie in all the sub-header files,
such as Function, Physics, Calculus, Geometry, etc.

It is also going to contain this block of comments
to introduce users to the engine, and give them
basic instruction on how to use it.

OUTLINE
Chassis.cpp
	int main(void)

Basics.h
	struct Vector2
	struct Vector3
	namespace NumericalStatistics
		int GCD(int a, int b);
		long int LCM(int a, int b);
		int Factors(int number);
		int GetFactors( void );

Function.h
	double sec(double argument);
	double csc(double argument);
	double cot(double argument);
	double log(double argument);
	class Function
		public:
			Function(string definition, char parameter);
			Function(char definition[], char parameter);
			~Function(void);
			string definition;
			char parameter;
			double Evaluate(double argument);
			double argument;
			double value;
			void Display();
		private:
			const enum OPERATOR
			enum FUNCTION
			string working_definition;
			bool Validate();
			void StripWhiteSpace();
			void InsertArgument();
			void ParseImpliedMultiplication();
			void PerformFunctions();
			void PerformParanthesis();
			void PerformExponentiation();
			void PerformMultiplicationAndDivision();
			void PerformAdditionAndSubtraction();
*/

#endif
