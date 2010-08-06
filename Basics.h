#include <string>


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
{
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
//struct Function
//{
//	Function(std::string definition, char variable); // constructor
//	std::string definition;
//	char variable;
//	void GetValues();
//	double Evaluate(double parameter);
//private:
//	std::string working_definition;
//	double parameter;
//	double val_at_parameter;
//	// recurse all of these to eliminate all occurances
//	bool Validate();
//	void PerformFunctions();
//	void PerformParanthesis();
//	void PerformExponentiation();
//	void PerformMultiplicationAndDivision();
//	void PerformAdditionAndSubtraction();
//
//	void Reset();
//};

//struct Function_s
//{
//	Function_s(char definition[], char variable); // constructor
//	char definition[];
//	char variable;
//	void GetValues();
//	double Evaluate(double parameter);
//private:
//	char working_definition[];
//	double parameter;
//	double val_at_parameter;
//	// recurse all of these to eliminate all occurances
//	bool Validate();
//	void StripSpaces(); // May need this...
//	void PerformFunctions(); // such as sin(), cot(), log(), ln(), etc.
//	void PerformParanthesis(); // (5+4) * 5 --> 9*5
//	void PerformExponentiation();
//	void PerformMultiplicationAndDivision();
//	void PerformAdditionAndSubtraction();
//
//	void Reset();
//};