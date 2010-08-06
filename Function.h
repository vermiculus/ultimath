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
	Function(char definition[], char parameter);
	Function(string definition, char parameter);
	~Function(void);
	string definition;
	char parameter; // the variable of the function
	double Evaluate(double argument); // evaluates the function at given argument

	double argument; // a value passed to the function
	double value; // the value of the function at the argument
private:
	enum OPERATOR {
		ADD = '+',
		SUBTRACT = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		EXPONENT = '^',
		MODULUS = '%',
		FACTORIAL = '!'
	};
	//enum FUNCTION { // is there any way to make an enumeration of strings or char[] ?
	//	SINE, // = "sin",
	//	COSINE, // = "cos",
	//	TANGENT, // = "tan",
	//	SECANT, // = "sec",
	//	COSECANT, // = "csc",
	//	COTANGENT, // = "cot"
	//};

	string working_definition;
	// recurse all of these to eliminate all occurances
	bool Validate();
	void StripWhiteSpace();
	void ParseImpliedMultiplication();
	void PerformFunctions();
	void PerformParanthesis();
	void PerformExponentiation();
	void PerformMultiplicationAndDivision();
	void PerformAdditionAndSubtraction();

	void DisplayFunction();
};
