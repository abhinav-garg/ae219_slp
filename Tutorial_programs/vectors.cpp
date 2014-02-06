#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])	{
	vector <float> example;		// Empty vector that stores floats
		// <vector>.push_back(<element>) adds an element at the end of the vector
	example.push_back(3.334);
	example.push_back(4.567);
	example.push_back(34.55);
	// Random access without bounds checking
	for (int i = 0; i < example.size(); i++)	{
		cout << example[i] << endl;
	}
	// Access with bounds checking - More expensive though
	for (int i = 0; i < example.size(); i++)	{
		cout << example.at(i) << endl;
	}

	float array[5] = {0.0, 1.0, 2.0, 3.0, 4.0};
		// Vector constructor
	vector <float> blah (array, array + sizeof(array) / sizeof(float));
	for (int i = 0; i < blah.size(); i++)	{
		cout << blah.at(i) << endl;
	}
}