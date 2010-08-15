#include "Function.h"
#include <cmath>
#include <sstream>
//utilities

/* not really needed - used once
string replace(string original, string replace, string with)
{
	int pos = 0;
	while ((pos = original.find(replace, pos)) != -1) 
	{ 
	   original.erase(pos, replace.length());
	   original.insert(pos, with);
	}
	return original;
}*/

Function::Function(char definition[], char parameter)
{
	this->parameter = parameter; // perform char validation  -  cannot be a number 
	this->definition = definition;
}
Function::Function(string definition, char parameter)
{
	// Set protected
	this->parameter = parameter;
	this->definition = definition;
}

Function::~Function(void)
{
}

double Function::Evaluate(double argument)
{
	//this->value = 0;
	this->argument = argument;
	if(!this->Validate())
	{
		printf("There was an error. Disregard value given (0) and try again.");
		return 0;
	}

	this->StripWhiteSpace();
	this->Display(); //debugging

	this->InsertArgument();
	this->Display(); //debugging

	this->ParseImpliedMultiplication();
	this->Display(); //debugging

	this->PerformFunctions();
	this->Display(); //you get the idea...

	this->PerformParanthesis();
	this->Display();

	this->PerformExponentiation();
	this->Display();

	this->PerformMultiplicationAndDivision();
	this->Display();

	this->PerformAdditionAndSubtraction();
	this->Display();

	printf("\n");

	return this->value;
}
void Function::Display(void)
{
	printf("\nFunction: %s\n", this->definition.c_str());
}
bool Function::Validate(void)
{
	printf ("Character count: %i\n", this->definition.length());
	return true; //just for now
}

void Function::StripWhiteSpace(void)
{
	printf("\nEntering White Space Stripper");
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		if(this->definition[index] == ' ')
		{
			this->definition.erase(index, 1);
			index--;
		}
	}
}

void Function::InsertArgument(void)
{
	char arg[256];
	sprintf(arg, "(%15.10f)", this->argument); // need to improve preservation of the integrity of the argument (double => float)
	//this->definition = replace(this->definition, "x", arg);
	int pos = 0;
	while ((pos = this->definition.find(this->parameter, pos)) != -1) 
	{ 
	   this->definition.erase(pos, 1);
	   this->definition.insert(pos, arg);
	}
}

void Function::ParseImpliedMultiplication(void)
{
	printf("\nEntering Implied Multiplication Parser");
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		if(this->definition[index] == this->parameter)
		{
			if(index==0) // if at the beginning
			{
				if(this->definition[index+1] == '(' || isdigit(this->definition[index+1])) // if the next char is ( or a digit
				{
					if(this->definition[index] != '*') // if the previous char is not MULTIPLY
					{
						this->definition.insert(index+1, "*"); // insert an asterisk
						index--;
					}
				}
			}
			else // if somewhere in the middle
			{
				if(this->definition[index-1] != '*')
				{
					this->definition.insert(index, "*");
					index++; 
				}
				if(index+1==this->definition.length())
					return; // here is the snippet of corrective code - but this project would still benefit from a complete makeover.
				if(this->definition[index+1] == '(' || isdigit(this->definition[index+1]))
				{ // always throws a 'subcript out of range' error - can't seem to fix.
					this->definition.insert(index+1, "*");
					index--;
				} 
				if(this->definition[index+1] == ')' && isdigit(this->definition[index+2]))
				{
					this->definition.insert(index+2, "*");
					index--;
				}
			}
		}
	}
}

void Function::PerformFunctions(void)
{
	printf("\nEntering Functions Parser");
	/*
	Supported Functions:
	sin csc
	cos sec
	tan cot
	log
	ln
	*/
	for(unsigned int index = 0; index < this->definition.length(); index++);
}

void Function::PerformParanthesis(void)
{
	printf("\nEntering Parenthesis Parser");
	string Param;
	int IndexOfLParen(-1), IndexOfRParen(-1);
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		if(this->definition[index] == LPAREN)
			IndexOfLParen = index;
		if(this->definition[index] == RPAREN)
			IndexOfRParen = index;
	}
	if(IndexOfLParen || IndexOfRParen) // if no parens were found
		return;
	Param = this->definition.substr(IndexOfLParen + 1, IndexOfRParen - 2);
	Function InsideStuff(Param, this->parameter);
	InsideStuff.Evaluate(this->argument); // To err is human, to recurse is divine
}

void Function::PerformExponentiation(void)
{
	printf("\nEntering Exponentiation Parser");
	//for(unsigned int index = 0; index < this->definition.length(); index++)
}

void Function::PerformMultiplicationAndDivision(void)
{
	//printf("\nEntered Multiplication and Division Parser");
	//int ArgumentStartIndex(0), ArgumentEndIndex(0);
	//for(unsigned int index = 0; index < this->definition.length(); index++)
	//{
	//	if(this->definition[index] == MULTIPLY || this->definition[index] == DIVIDE)
	//	{
	//		double LParam, RParam;
	//		string Left, Right;
	//		int temp(0);
	//		for(unsigned int index2 = index - 1; index2 > 0; index2--)
	//		{
	//			if(!(isdigit(this->definition[index2]) || this->definition[index2] == '.')) break;
	//			Left.insert(0, &this->definition[index2], 1);
	//			temp = index2;
	//		}
	//		if(temp != 0) ArgumentStartIndex = temp - 1;
	//		else ArgumentStartIndex = temp;
	//		Left.insert(0, &this->definition[ArgumentStartIndex], 1);
	//		for(unsigned int index2 = index + 1; index2 < this->definition.length(); index2++)
	//		{
	//			if(!(isdigit(this->definition[index2]) || this->definition[index2] == '.')) break;
	//			Right.append(&this->definition[index2], 1);
	//			ArgumentEndIndex = index2;
	//		}
	//		LParam = strtod(Left.c_str(), NULL);
	//		RParam = strtod(Right.c_str(), NULL);
	//		ostringstream ValueOfArgument;
	//		if(this->definition[index] == MULTIPLY) ValueOfArgument << LParam * RParam << this->definition[ArgumentEndIndex + 1];
	//		if(this->definition[index] == DIVIDE) ValueOfArgument << LParam / RParam << this->definition[ArgumentEndIndex + 1];
	//		this->definition.replace(ArgumentStartIndex, ArgumentEndIndex - ArgumentStartIndex + 1, ValueOfArgument.str());
	//		//                       The argument start index here must be revised - also in {+,-}
	//		index--;
	//	}
	//}
	
    printf("\nEntering Multiplication and Division Parser");
    int ArgumentEndIndex(0);
    for(unsigned int i = 0; i < this->definition.length(); i++)
    {
		if(this->definition[i] == MULTIPLY || this->definition[i] == DIVIDE)
		{
			double LParam, RParam; string Left, Right;
			for(unsigned int j = i - 1; j > 0; j--) //see next comment
			{
				if(!(isdigit(this->definition[j]) || this->definition[j] == DECIMAL)) break;
				Left.insert(0, &this->definition[j], 1);
			}
			Left.insert(0, &this->definition[0], 1); //otherwise we get a member out of range error because j was decremented when it j==0 already...
			for(unsigned int j = i + 1; j < this->definition.length(); j++)
			{
				if(!(isdigit(this->definition[j]) || this->definition[j] == DECIMAL)) break;
				Right.append(&this->definition[j], 1);
				ArgumentEndIndex = j;
			}
			cout << "Left = " << Left << endl;
			cout << "Right = " << Right << endl;

			LParam = strtod(Left.c_str(), NULL);
			RParam = strtod(Right.c_str(), NULL);

			ostringstream ValueOfArgument;
			ValueOfArgument.setf(ios_base::fixed);

			if(this->definition[i] == MULTIPLY) 
				ValueOfArgument << LParam * RParam;
			if(this->definition[i] == DIVIDE) 
				ValueOfArgument << LParam / RParam;
			this->definition.replace(0, ArgumentEndIndex + 1, ValueOfArgument.str());
			i = ValueOfArgument.str().length() - 1;

			cout << "ValueOfArgument = " << ValueOfArgument.str() << endl;
			cout << "ops = " << this->definition << endl << endl;
		}
	}
}

void Function::PerformAdditionAndSubtraction(void)
{
	//printf("\nEntered Addition and Subtraction Parser");
	//int ArgumentStartIndex, ArgumentEndIndex;
	//for(unsigned int index = 0; index < this->definition.length(); index++)
	//{
	//	if(this->definition[index] == ADD || this->definition[index] == SUBTRACT)
	//	{
	//		double LParam, RParam;
	//		string Left, Right;
	//		int temp(0);
	//		for(unsigned int index2 = index - 1; index2 > 0; index2--)
	//		{
	//			if(!(isdigit(this->definition[index2]) || this->definition[index2] == '.')) break;
	//			Left.insert(0, &this->definition[index2], 1);
	//			temp = index2;
	//		}
	//		if(temp != 0) ArgumentStartIndex = temp - 1;
	//		else ArgumentStartIndex = temp;
	//		Left.insert(0, &this->definition[ArgumentStartIndex], 1);
	//		for(unsigned int index2 = index + 1; index2 < this->definition.length(); index2++)
	//		{
	//			if(!(isdigit(this->definition[index2]) || this->definition[index2] == '.')) break;
	//			Right.append(&this->definition[index2], 1);
	//			ArgumentEndIndex = index2;
	//		}
	//		LParam = strtod(Left.c_str(), NULL);
	//		RParam = strtod(Right.c_str(), NULL);
	//		ostringstream ValueOfArgument;
	//		if(this->definition[index] == ADD) ValueOfArgument << LParam + RParam << this->definition[ArgumentEndIndex + 1];
	//		if(this->definition[index] == SUBTRACT) ValueOfArgument << LParam - RParam << this->definition[ArgumentEndIndex + 1];
	//		this->definition.replace(ArgumentStartIndex, ArgumentEndIndex - ArgumentStartIndex + 1, ValueOfArgument.str());
	//		//                       The argument start index here must be revised - also in {*,/}
	//		index--;
	//	}
	//}
	printf("\nEntering Addition and Subtraction Parser");
    int ArgumentEndIndex(0);
    for(unsigned int i = 0; i < this->definition.length(); i++)
    {
		if(this->definition[i] == ADD || this->definition[i] == SUBTRACT)
		{
			double LParam, RParam;
			string Left, Right;
			for(unsigned int j = i - 1; j > 0; j--) //see next comment
			{
				if(!(isdigit(this->definition[j]) || this->definition[j] == DECIMAL)) break;
				Left.insert(0, &this->definition[j], 1);
			}
			Left.insert(0, &this->definition[0], 1); //otherwise we get a member out of range error because j was decremented when it j==0 already...
			for(unsigned int j = i + 1; j < this->definition.length(); j++)
			{
				if(!(isdigit(this->definition[j]) || this->definition[j] == DECIMAL)) break;
				Right.append(&this->definition[j], 1);
				ArgumentEndIndex = j;
			}
			cout << "Left = " << Left << endl;
			cout << "Right = " << Right << endl;
			LParam = strtod(Left.c_str(), NULL);
			RParam = strtod(Right.c_str(), NULL);
			ostringstream ValueOfArgument;
			ValueOfArgument.setf( ios_base::fixed);
			if(this->definition[i] == ADD) ValueOfArgument << LParam + RParam;
			if(this->definition[i] == SUBTRACT) ValueOfArgument << LParam - RParam;
			this->definition.replace(0, ArgumentEndIndex + 1, ValueOfArgument.str());
			i = ValueOfArgument.str().length() - 1;
			cout << "ValueOfArgument = " << fixed << ValueOfArgument.str() << endl;
			cout << "ops = " << this->definition << endl << endl;
		}
	}
}
