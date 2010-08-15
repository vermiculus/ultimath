#pragma once
#include "math.h"
#include <cmath>
#include <iostream>

using namespace std;

//struct CString
//{
//	CString(char string[])
//	{
//		this->value = strdup(string);
//		/*for(unsigned int index = 0; index < strlen(string); ;)
//		{
//			this->value[index] = string;
//		}*/
//	}
//	char value[];
//};

//std::string substring(std::string str, unsigned int start, unsigned int end)
//{
//	int length = str.length();
//	std::string result;
//	for(int index = start - 1; index < end; index++)
//	{
//		result.append(1, str[index]);
//	}
//	return result;
//}

double sec(double argument);
double csc(double argument);
double cot(double argument);
double log(double argument);

class Function
{
public:
	Function(string definition, char parameter);
	Function(char definition[], char parameter); // you never know...
	~Function(void); // does anything really need to be done for this? I'm unsure.

	string definition; // the function itself
	char parameter; // the variable of the function

	double Evaluate(double argument); // evaluates the function at given argument

	double argument; // a value passed to the function
	double value; // the value of the function at the argument

	void Display(); // primarily for debugging purposes
private:
	typedef enum OPERATOR {
		ADD = '+',
		SUBTRACT = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		EXPONENT = '^',
		MODULUS = '%',
		FACTORIAL = '!',
		RPAREN = ')',
		LPAREN = '(',
		DECIMAL = '.'
	};
	/*enum FUNCTION { // is there any way to make an enumeration of strings or char[] ?
		SINE, // = "sin",
		COSINE, // = "cos",
		TANGENT, // = "tan",
		SECANT, // = "sec",
		COSECANT, // = "csc",
		COTANGENT, // = "cot"
	};*/

	string working_definition; // unknown use - leftover possibly from previous versions - will look into this
	// recurse all of these to eliminate all occurances
	bool Validate();
	void StripWhiteSpace(); // 2 x, 2 ( x + 5 ) -> 2x, 2(x+5)
	void InsertArgument(); //2x -> 2(x)
	void ParseImpliedMultiplication(); //2x, 2(x+5) -> 2*x, 2*(x+5)
	void PerformFunctions(); // sin, cos, tan, etc. - will need to recurse the inside argument
	void PerformParanthesis(); // recursive; 2*(5+8(4)) -> 2*41
	void PerformExponentiation(); // 5^2, 5^3 -> 5*5, 5*5*5
	void PerformMultiplicationAndDivision(); // 4*8 -> 32
	void PerformAdditionAndSubtraction(); // 2+2 -> 4

	/*
	let x = 5
	INPUT: 2 sin ( 3x - (1/2) 4 + 9^2 +3)

	 CALC: 2sin(3x-(1/2)4+9^2+3)
	 CALC: 2sin(3(5)-(1/2)4+9^2+3)
	 CALC: 2*sin(3*(5)-(1/2)*4+9^2+3)
	 CALC: 2*sin(3*(5)-(.5)*4+9^2+3)
	 CALC: 2*sin(3*5-.5*4+9^2+3)
	 CALC: 2*sin(3*5-.5*4+81+3)
	 CALC: 2*sin(8-2+81+3)
	 CALC: 2*sin(6+81+3)
	 CALC: 2*sin(87+3)
	 CALC: 2*sin(90)
	 CALC: 2*1
	 CALC: 2

   OUTPUT: 2
	*/

};