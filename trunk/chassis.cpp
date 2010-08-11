// Welcome to the Ultimath Test Chassis.
// Please take a moment to view the comments.

#include "ultimath.h" // This chassis would be pointless without it. This header file is a collection of the seperate components of the Ultimath Engine.

int main( void )
{
	printf("Commence testing.\n\n");

	Function test("2 x", 'x');
	test.Display();
	test.Evaluate(2);

	system("PAUSE"); // Feel free to contact me with a better option :P
	return 0;
}