#include <iostream>
using namespace std;

int main(int argc, char *argv[])	{
	// argc stands for argument count
	// argv stands for argument vector
	// Both of these are used for passing command line arguments
	// The first argument is the program name
	// Compile the file, and pass arguments to the executable when running it

	int i;
	for (i = 0; i < argc; i++)	{
		cout << argv[i] << endl;
	}

}