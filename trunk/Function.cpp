#include "Function.h"
#include <cmath>
#include <sstream>

Function::Function(char definition[], char parameter)
{
	this->parameter = parameter; // perform char validation  -  cannot be a number 
	this->definition = definition;
}
Function::Function(string definition, char parameter)
{
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

	//needs to replace val for var

	this->StripWhiteSpace(); // 2 x, 2 ( x + 5 ) -> 2x, 2(x+5)
	this->Display(); //debugging

	this->ParseImpliedMultiplication(); //2x, 2(x+5) -> 2*x, 2*(x+5)
	this->Display(); //debugging

	this->PerformFunctions(); // sin, cos, tan, etc.
	this->Display(); //debugging

	this->PerformParanthesis(); // recursive; 2*(5+8(4)) -> 2*41
	this->Display(); //debugging

	this->PerformExponentiation(); // 5^2, 5^3 -> 5*5, 5*5*5
	this->Display(); //debugging

	this->PerformMultiplicationAndDivision(); // 4*8 -> 32
	this->Display(); //debugging

	this->PerformAdditionAndSubtraction(); // 2+2 -> 4
	this->Display(); //debugging

	return this->value;
}
void Function::Display(void)
{
	printf("\nFunction: ");
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		printf("%c", this->definition[index]);
	}
	printf("\n");
}
bool Function::Validate(void)
{
	printf ("Character count: %i\n", this->definition.length());
	return true; //just for now
}

void Function::StripWhiteSpace(void)
{
	printf("\nEntered White Space Stripper");
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		if(this->definition[index] == ' ')
		{
			this->definition.erase(index, 1);
			index--;
		}
	}
}

void Function::ParseImpliedMultiplication(void)
{
	printf("\nEntered Implied Multiplication Parser");
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		if(this->definition[index] == this->parameter)
		{
			if(index==0) // if at the beginning
			{
				if(this->definition[index+1] == LPAREN || isdigit(this->definition[index+1])) // if the next char is ( or a digit
				{
					if(this->definition[index] != MULTIPLY) // if the previous char is not MULTIPLY
					{
						this->definition.insert(index+1, "" + MULTIPLY); // insert an asterisk
						index--;
					}
				}
			}
			else // if somewhere in the middle
			{
				if(this->definition[index-1] != MULTIPLY)
				{
					this->definition.insert(index, "*");
					//index++;
				}
				if(this->definition[index+1] == LPAREN || isdigit(this->definition[index+1]))
				{ // always throws a 'subcript out of range' error - can't seem to fix.
					this->definition.insert(index+1, "*");
					index--;
				} 
				if(this->definition[index+1] == RPAREN && isdigit(this->definition[index+2]))
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
	printf("\nEntered Functions Parser");
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
	printf("\nEntered Parenthesis Parser");
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
	printf("\nEntered Exponentiation Parser");
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
	
    printf("\nEntered Multiplication and Division Parser\n");
    int ArgumentEndIndex(0);
    for(unsigned int i = 0; i < this->definition.length(); i++)
    {
		if(this->definition[i] == MULTIPLY || this->definition[i] == DIVIDE)
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
} // COMPLETE

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
	printf("\nEntered Addition and Subtraction Parser\n");
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