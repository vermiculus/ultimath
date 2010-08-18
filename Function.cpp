#include "Function.h"
#include <cmath>
#include <sstream>

Function::Function(char definition[], char parameter)
{
	if(isalpha(parameter))
		this->parameter = parameter;
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
	/*
	do some things like test that the number of LPARENs matches RPARENs
	test for side-by-side operators (4**5+1--8)
	make sure every binary operator has to arguments (1+2+3+45+)
	*/
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
	sprintf(arg, "(%f)", this->argument);
	int pos = 0;
	while ((pos = this->definition.find(this->parameter, pos)) != -1) 
	{ 
	   this->definition.erase(pos, 1);
	   this->definition.insert(pos, arg);
	}
}

void Function::ParseImpliedMultiplication(void)
{ // instead of if/then - perhaps switches would be better. That way it will loop again once the command is complete.
	printf("\nEntering Implied Multiplication Parser");
	/*
	Pseudocode

	BUFFERS PREVIOUS_CHAR, THIS_CHAR, NEXT_CHAR
	SWITCHES INSERT_BEFORE, INSERT_AFTER, DO_NOTHING
	
	While iterating through the characters in the definition
	{
		If THIS_CHAR is MULTIPLY
			skip
		If this char is a DIGIT
			If PREVIOUS_CHAR is a DIGIT and NEXT_CHAR is a DIGIT
				DO_NOTHING
			If PREVIOUS_CHAR is NOT a DIGIT and NEXT_CHAR is a DIGIT
				INSERT_BEFORE
			If PREVIOUS_CHAR is a DIGIT and NEXT_CHAR is NOT a DIGIT
				INSERT_AFTER
			If PREVIOUS_CHAR is an RPAREN
				INSERT_BEFORE
			If NEXT_CHAR is an LPAREN
				INSERT_AFTER
		If THIS_CHAR is PARAMETER
			If THIS_CHAR is not FIRST
				If PREVIOUS CHAR is a RPAREN, DIGIT
					INSERT_BEFORE
			If THIS_CHAR is not LAST
				If NEXT CHAR is a LPAREN, DIGIT
					INSERT_AFTER
		If INSERT_BEFORE
			Insert a MULTIPLY before THIS_CHAR
			DECREMENT ITERATOR
		If INSERT_AFTER
			Insert a MULTIPLY after THIS_CHAR
		If DO_NOTHING
			Skip this char
	}
	*/

	// Since apparantly we need a constant to compare against. This statement is explained later in the function.
	// char parameter(this->parameter);

	// Here we set up a basic string iterater. What that means is this 'for' loop is using it's index to point to a character in the string.
	// but in the conditional section (the middle part) we post the condition that the index must be less than the length of our string,
	// otherwise we will start referencing characters that simply aren't there - you can see where that would have a porblem compiling. :)
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		// Here we declare some variables - you will see their use later on in the function.
		char prevchar(' '), thischar(this->definition[index]), nextchar(' ');
		bool insert_before(false), insert_after(false), do_nothing(false);

		// This line sets "thischar" to the character located at the index of the loop.
		thischar = this->definition[index];
		// As long as this isn't the first character in the string (i.e. the index isn't zero), we give the value of the previous character to "prevchar"
		if(index != 0) prevchar = this->definition[index-1];
		// As long as this isn't the last character in the string, we give the value of the next character to "nextchar"
		if(index != this->definition.length() - 1) nextchar = this->definition[index+1];

		// If this character is an operator, skip the character. We are only interested in numbers and variables.
		if( thischar == OPERATOR::ADD ||
			thischar == OPERATOR::DECIMAL ||
			thischar == OPERATOR::DIVIDE ||
			thischar == OPERATOR::EXPONENT ||
			thischar == OPERATOR::FACTORIAL ||
			thischar == OPERATOR::LPAREN ||
			thischar == OPERATOR::MODULUS ||
			thischar == OPERATOR::MULTIPLY ||
			thischar == OPERATOR::RPAREN ||
			thischar == OPERATOR::SUBTRACT)
			continue;

		// If this character is a digit (0, 1, 2, ..., 9), perform additional tests. (See comments below)
		if(isdigit(thischar))
		{
			// If both the previous character and the next character are digits (such as the substring "123"), set "do_nothing" to true.
			if(isdigit(prevchar) && isdigit(nextchar))
				do_nothing = true;
			// If only the next char is a digit (such as the substring "x23"), set "insert_before" to true.
			if(!isdigit(prevchar) && isdigit(nextchar))
				insert_before = true;
			// If only the previous char is a digit (such as the substring "12x"), set "insert_after" to true.
			if(isdigit(prevchar) && !isdigit(nextchar))
				insert_after = true;
			// If only the previous char is a right parens (such as the substring ")23"), set "insert_before" to true.
			if(prevchar == OPERATOR::RPAREN)
				insert_before = true;
			// If only the next char is a left parens (such as the substring "12("), set "insert_after" to true.
			if(nextchar == OPERATOR::LPAREN)
				insert_after = true;
		}

		// if this character is the Function's parameter, perform additional tests. (See comments below)
		if(thischar==this->parameter)
		{
			// If this is not the first character...
			if(index != 0)
				// If the previous character is an RPAREN or a DIGIT...
				if(prevchar == OPERATOR::RPAREN || isdigit(prevchar))
					// set "insert_after+ to true
					insert_after = true;
			// If this is not the last character...
			if(index != this->definition.length() - 1)
				// If the next character is an LPAREN or a DIGIT...
				if(nextchar == OPERATOR::LPAREN || isdigit(nextchar))
					// set "insert_before" to true
					insert_before = true;
		}
		
		// Finally, we take action
		if(do_nothing)
			continue;
		if(insert_before)
			this->definition.insert(index, "*");
		if(insert_after)
			this->definition.insert(index+1, "*");
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

/*
Binary Operator Parser (+, -, *, /, ^, more?)

SWITCH CONTINUE(TRUE)

While CONTINUE
{
	While iterating through the characters in a string
		if this is the last character
			CONTINUE = FALSE
		if this character is an operator (this should never be the last character per the Function::Validate() function)
			iterate left until a non-digit is found
			store index of last digit found [LINDEX]
			convert the substring from ([LINDEX] up to but not including the operator [INDEX-1]) to a double [LARGUMENT]
			iterate right until a non-digit is found
			store index of last digit found [RINDEX]
			convert the substring from ([RINDEX] up to but not including the operator [INDEX+1]) to a double [RARGUMENT]
			perform desired operation on [LARGUMENT] and [RARGUMENT] and convert the result to a string
			remove the substring from [LINDEX] to [RINDEX] and replace it with the resulted string [at INDEX]
}
*/
void Function::PerformMultiplicationAndDivision(void)
{ // does not reflect new algorithm
	printf("\nEntered Multiplication and Division Parser");
	int ArgumentStartIndex(0), ArgumentEndIndex(0);
	for(unsigned int index = 0; index < this->definition.length(); index++)
	{
		if(this->definition[index] == MULTIPLY || this->definition[index] == DIVIDE)
		{
			double LParam, RParam;
			string Left, Right;
			int temp(0);
			for(unsigned int index2 = index - 1; index2 > 0; index2--)
			{
				if(!(isdigit(this->definition[index2]) || this->definition[index2] == '.')) break;
				Left.insert(0, &this->definition[index2], 1);
				temp = index2;
			}
			if(temp != 0) ArgumentStartIndex = temp - 1;
			else ArgumentStartIndex = temp;
			Left.insert(0, &this->definition[ArgumentStartIndex], 1);
			for(unsigned int index2 = index + 1; index2 < this->definition.length(); index2++)
			{
				if(!(isdigit(this->definition[index2]) || this->definition[index2] == '.')) break;
				Right.append(&this->definition[index2], 1);
				ArgumentEndIndex = index2;
			}
			LParam = strtod(Left.c_str(), NULL);
			RParam = strtod(Right.c_str(), NULL);
			ostringstream ValueOfArgument;
			if(this->definition[index] == MULTIPLY) ValueOfArgument << LParam * RParam << this->definition[ArgumentEndIndex + 1];
			if(this->definition[index] == DIVIDE) ValueOfArgument << LParam / RParam << this->definition[ArgumentEndIndex + 1];
			this->definition.replace(ArgumentStartIndex, ArgumentEndIndex - ArgumentStartIndex + 1, ValueOfArgument.str());
			//                       The argument start index here must be revised - also in {+,-}
			index--;
		}
	}
	
    printf("\nEntering Multiplication and Division Parser");
    ArgumentEndIndex = 0;
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
