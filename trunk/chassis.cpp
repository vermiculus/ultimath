#include "ultimath.h"
#include <iostream>
// This chassis would be pointless without it.
// This header file is a collection of the seperate components of the Ultimath Engine.

#include <vector>

using namespace std;

int main( void )
{
	cout << "Testing has begun.\n";

	//shortest Fibonacci sequencer I've ever written 8)
	vector<long unsigned int> collection(2,1);
	for(int index = 2; index < 64; index++)
		collection.insert(collection.end(),
			collection[index-2] + collection[index-1]);

	for(int index = 0; index < collection.size(); index++)
		//cout << collection[index] << " ";
		printf("%10i\n", collection[index]);
	printf("\n\n\n");
	/*_Function f("2*x",'x');
	cout << f.Evaluate(4);
	cin.sync();
	cout << "\n\nPlease press enter to exit.";
	cin.ignore();*/

	// Did you know? Some DIC member (I forget who at the moment) did a benchmark test
	// to see which was faster, and printf() is almost twice as fast.
	// I suppose it doesn't matter - because engines don't output anything visually anyway lol

	return 0;
}
