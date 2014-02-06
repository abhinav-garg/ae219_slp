#include <iostream>
#include <cmath>

float distance(float a, float b)	{
	return (a - b > 0) ? (a - b) : (b - a);
}

void brute_force(int size, float locations[], float radius, float neighbours[][7])	{
	int i, j, k;
	for (i = 0; i < size; i++)	{
		k = 0; 	// Keep count of neighbours for the i-th particle
		for (j = 0; j < size; j++)	{
			if (distance(locations[i], locations[j]) <= radius)	{
				neighbours[i][k] = j;	// Store the index corresponding to that particle
				k++;	// Record that a particle in the nrighbourhood has been found 
			}
		}
		// Set the rest to -1
		for (; k < size; k++)	{
			neighbours[i][k] = -1;
		}
	}
}

int main(int argc, char *argv[]) {
	float locations[7] = {0.0, 6.0, 2.0, 5.0, 1.0, 7.0, 10.0};
	float xMax = 10.0;
	float radius = 4.0;
	float neighbours[7][7];
	int size = 7;
	brute_force(size, locations, radius, neighbours);

	for (int i = 0; i < size; i++)	{
		for (int j = 0; j < size; j++)	{
			std::cout << neighbours[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}