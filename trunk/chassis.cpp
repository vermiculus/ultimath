#include "ultimath.h"
// This chassis would be pointless without it.
// This header file is a collection of the seperate components of the Ultimath Engine.

int main( void )
{
	cout << "Testing has begun.\n";

	Function test("2 x", 'x');
	test.Display();
	test.Evaluate(2);

	cin.sync();
	cout << "Please press enter to exit.";
	cin.ignore();
	return 0;
}
