#include "ultimath.h"
// This chassis would be pointless without it.
// This header file is a collection of the seperate components of the Ultimath Engine.

int main( void )
{
	cout << "Testing has begun.\n";

	//Insert code here :)
	Function test("2(4)",'x');
	test.Evaluate(0);

	cin.sync();
	cout << "Please press enter to exit.";
	cin.ignore();

	// Did you know? Some DIC member (I forget who at the moment) did a benchmark test
	// to see which was faster, and printf() is almost twice as fast.
	// I suppose it doesn't matter - because engines don't output anything visually anyway lol

	return 0;
}
