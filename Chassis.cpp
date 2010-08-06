//#include <iostream>
//#include <sstream>
//#include <string>
//using namespace std;
//
//#define MULTIPLY '*'
//#define DIVIDE '/'
//
//void PerformMultiplicationAndDivision( string ops )
//{
//    printf("\nEntered Multiplication and Division Parser\n");
//    int ArgumentEndIndex(0);
//    for(unsigned int i = 0; i < ops.length(); i++)
//    {
//		if(ops[i] == MULTIPLY || ops[i] == DIVIDE)
//		{
//				double LParam, RParam;
//				string Left, Right;
//				for(unsigned int j = i - 1; j > 0; j--) //see next comment
//			{
//				if(!(isdigit(ops[j]) || ops[j] == '.')) break;
//				Left.insert(0, &ops[j], 1);
//			}
//			Left.insert(0, &ops[0], 1); //otherwise we get a member out of range error because j was decremented when it j==0 already...
//			for(unsigned int j = i + 1; j < ops.length(); j++)
//			{
//				if(!(isdigit(ops[j]) || ops[j] == '.')) break;
//				Right.append(&ops[j], 1);
//				ArgumentEndIndex = j;
//			}
//			cout << "Left = " << Left << endl;
//			cout << "Right = " << Right << endl;
//			LParam = strtod(Left.c_str(), NULL);
//			RParam = strtod(Right.c_str(), NULL);
//			ostringstream ValueOfArgument;
//			if(ops[i] == MULTIPLY) ValueOfArgument << LParam * RParam;
//			if(ops[i] == DIVIDE) ValueOfArgument << LParam / RParam;
//			ops.replace(0, ArgumentEndIndex + 1, ValueOfArgument.str());
//			i = ValueOfArgument.str().length() - 1;
//			cout << "ValueOfArgument = " << ValueOfArgument.str() << endl;
//			cout << "ops = " << ops << endl;
//		}
//	}
//}
//
//int main () {
//        string expr;
//        cout << "enter an expression with * and/or / \n";
//        cin >> expr;
//        PerformMultiplicationAndDivision( expr );
//		system("PAUSE");
//}

#define GAMEOVER {printf("\n\n\n");	system("PAUSE");}
#define HOLDIT system("PAUSE");

#include <iostream>
#include "Ultimath.h"

using namespace std;

const int CHARS = 1000;

int main( void )
{
	//string function_buffer;
	//double myparam;
	//cout << "f(x)=";
	//cin  >> function_buffer;
	//cout << "x=";
	//cin  >> myparam;
	//Function func(function_buffer, 'x');
	//cout << "The function " << func.definition << " evaluated at " << myparam << " equals " << func.Evaluate(myparam);

	//cout << Calculus::Integrals::SimpsonsRule(4, -1, 1);
	//string thistring;
	//char * str;
	//cin >> (str = new char);
	//char str[100];
	//char * pch;
	//printf ("Splitting string \"%s\" into tokens:\n",str);
	//pch = strtok (str," ,.- str");
	//while (pch != NULL)
	//{
	//printf ("%s\n",pch);
	//pch = strtok (NULL, " ,.- str");
	//}
	char MyString[CHARS];
	printf("f(x)=");
	gets_s(MyString); // gets() has deprecated
	Function myFunc(MyString, 'x');
	printf("\n\nThe value of the function evaluated at 5 = %d", myFunc.Evaluate(5));
	GAMEOVER;
	return 0;
}
//
//#include<iostream> 
//#include<conio.h> 
//#define max 5 
//#include 
//using namespace std;
//
//class stack 
//{ 
//	int top; 
//	int stackarray[max]; 
//	public : 
//
//	//Constructor 
//	stack() 
//	{ 
//		top=0; 
//	} 
//	//Push function used to put item in the stack. 
//	void push(int item) 
//	{ 
//		if(top==max) 
//			cout<<"Data over flow\n"; 
//		else 
//		{ 
//			stackarray[++top]=item; 
//			cout<<"The item "<<item<<" is pushed in "<<top<<"\n"; 
//		} 
//	} 
//
//	//pop function is used to delete or take out item from the stack. 
//	void pop() 
//	{ 
//		if(top==0) 
//			cout<<"Data under flow\n"; 
//		else 
//		{ 
//			cout<<"The item "<<stackarray[top]<<" is poped from	"<<top--<<"\n"; 
//		} 
//
//	} 
//	//This function is used to check weather the stack is empty or not. 
//	int isempty() 
//	{ 
//		if (top==0) 
//			return 1; 
//		else 
//			return 0; 
//	} 
//
//}; 
//
//int main() 
//{ 
//	//stack stk; 
//	//if(stk.isempty()) 
//	//	cout<<"The stack is empty\n"; 
//	//for(int l=1;l<=10;l++) 
//	//	stk.push(l); 
//	//for(int l=0;l<=9;l++) 
//	//	stk.pop(); 
//	
//	GAMEOVER;
//	return 0;
//} 