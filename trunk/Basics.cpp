#include "Basics.h"
#include "math.h"
#include <cmath>
#include <iostream>
#include "Global Constants.h"

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


//Function::Function(string definition, char variable)
//{
//	this->definition = definition;
//	this->variable = variable;
//	this->working_definition = definition;
//}
//
//void Function::Reset( void )
//{
//	this->working_definition = definition;
//}
//
//bool Function::Validate( void )
//{
//	for(unsigned int index = 0; index < this->definition.length(); index++)
//	{
//		if(isdigit(this->definition[index]))
//			continue;
//		else if( this->definition[index] == '.' || 
//			this->definition[index] == '^' || 
//			this->definition[index] == '(' || 
//			this->definition[index] == ')' || 
//			this->definition[index] == '*' || 
//			this->definition[index] == '-' || 
//			this->definition[index] == '!' || 
//			this->definition[index] == '~' /*make negate*/ ) 
//			continue;
//		else
//			return false;
//	}
//	return true;
//}
//
//double Function::Evaluate(double parameter)
//{
//	this->parameter = parameter;
//	this->PerformMultiplicationAndDivision();
//	//this->parameter = parameter;
//	//double value(EPSILON);
//
//	//string working_definition = this->definition;
//	//string working_substring;
//	//string term;
//	//char *term_end;
//	//for(unsigned int index = 0; index < this->definition.length(); index++)
//	//{
//	//	char current = working_definition[index];
//	//	if(index > 0)
//	//		char previous = working_definition[index-1];
//	//	if(index < working_definition.length())
//	//		char next = working_definition[index+1];
//
//	//	if(isdigit(current))
//	//	{
//	//		cout << "Char: " << index << endl;
//	//		cout << "Digit found\n\n";
//	//	}
//	//	if(current == this->variable)
//	//	{
//	//		cout << "Char: " << index << endl;
//	//		cout << "Variable found\n"
//	//			<< "Previous char: ";
//	//		if(index > 0)
//	//		{
//	//		    char previous = working_definition[index-1]; // work this whole variable assignment thing out
//	//			cout << previous << endl;
//	//			cout << "0-based index of previous char: " << index - 1 << endl;
//	//			cout << "Evaluation of previous term: \n";
//	//			term = working_definition.substr(0, index);
//	//			cout << term << endl;
//	//			value = strtod(term.c_str(), &term_end) * parameter;
//	//		}
//	//		else
//	//		{
//	//			cout << "None";
//	//		}
//	//		cout << endl << endl;
//	//	}
//	//	if(current == '+')
//	//	{
//	//		cout << "'+' operator found!\n";
//	//	}
//	//	if(current == '-')
//	//	{
//	//		cout << "'-' operator found!\n";
//	//	}
//	//	if(current == '*')
//	//	{
//	//		cout << "'*' operator found!\n";
//	//	}
//	//	if(current == '/')
//	//	{
//	//		cout << "'/' operator found!\n";
//	//	}
//	//}
//	//if(value == EPSILON) cout << "unchanged!\n\n";
//	return this->val_at_parameter;
//}
//
//void Function::PerformMultiplicationAndDivision( void )
//{
//	//double value(EPSILON);
//
//	string working_definition = this->definition;
//	string working_substring;
//	string term;
//	char *term_end; // required for strtod() (string to double)
//
//	for(unsigned int index = 0; index < this->definition.length(); index++) // iterate through each character in the string (the function)
//	{
//		cout << "Char: " << index << endl; // Report
//
//		char current = working_definition[index]; //set a variable to make it easier... typing current is easier than... ? working_definition[index]
//		if(index > 0)
//			char previous = working_definition[index-1]; // if there is a previous char, then set its shortcut
//		if(index < working_definition.length())
//			char next = working_definition[index+1]; // if there is a posterior char, then set its shortcut
//		
//		if(isdigit(current))
//		{
//			cout << "Digit found\n\n"; // Report
//		}
//		if(current == this->variable)
//		{
//			cout << "Variable found\n\n" // Report
//				<< "Char: " << index - 1 << ": ";
//			if(index > 0)
//			{
//			    char previous = working_definition[index-1]; // work this whole variable assignment thing out
//				cout << previous << endl; // Report
//				cout << "Evaluation of previous term: \n";
//				unsigned int term_start;
//				for(unsigned int index_level2 = index; index_level2 >= 0; index--)
//				{
//					if(!isdigit(working_definition[index_level2]))
//					{
//						term_start = index_level2;
//						break;
//					}
//				}
//				term = working_definition.substr(term_start-1, index); // needs to be redone
//				cout << term << endl;
//				this->val_at_parameter = strtod(term.c_str(), &term_end) * parameter;
//			}
//			else
//			{
//				cout << "None"; // Report
//			}
//			cout << endl << endl;
//		}
//		if(current == '*')
//		{
//			cout << "'*' operator found!\n\n";
//			    char previous = working_definition[index-1]; // work this whole variable assignment thing out
//				cout << previous << endl; // Report
//				cout << "Evaluation of previous term: \n";
//				unsigned int term_start;
//				for(unsigned int index_level2 = index; index_level2 >= 0; index--)
//				{
//					if(!isdigit(working_definition[index_level2]))
//					{
//						term_start = index_level2;
//						break;
//					}
//				}
//				term = working_definition.substr(term_start-1, index); // needs to be redone
//				cout << term << endl;
//				this->val_at_parameter = strtod(term.c_str(), &term_end) * parameter;
//		}
//	}
//	if(this->val_at_parameter == EPSILON) cout << "unchanged!\n\n";
//	//this->val_at_parameter = value;
//	//return value;
//}
//
//void Function::PerformAdditionAndSubtraction( void )
//{
//	string mydef = this->definition;
//}