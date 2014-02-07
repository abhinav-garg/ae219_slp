#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef vector <float> float_vector;

float dist(float a, float b)	{
	return (a - b > 0) ? (a - b) : (b - a);
}

void brute_force(int size, float locations[], float radius, float neighbours[][7])	{
	int i, j, k;
	for (i = 0; i < size; i++)	{
		k = 0; 	// Keep count of neighbours for the i-th particle
		for (j = 0; j < size; j++)	{
			if (dist(locations[i], locations[j]) <= radius)	{
				neighbours[i][k] = j;	// Store the index corresponding to that particle
				k++;	// Record that a particle in the nrighbourhood has been found 
			}
		}
		// Set the rest to -1
		for (; k < size; k++)	{
			neighbours[i][k] = -1;
		}
	}

		// Print out the neighbours list
	for (int i = 0; i < size; i++)	{
		cout << i << "# ";
		for (int j = 0; j < size; j++)	{
			cout << neighbours[i][j] << " ";
		}
		cout << endl;
	}
}

void print_vectorOfvector(vector <float_vector> vect)	{
	// cout << "PRINTING VECTOR OF VECTOR" << endl;
	for (int i = 0; i < vect.size(); i++)	{
		cout << i << "# "; 
		for (int j = 0; j < vect[i].size(); j++)	{
			cout << vect[i].at(j) << " ";
		}
		cout << endl;
	}
}

void print_vector(vector <float> vect)	{
	// cout << "PRINTING VECTOR" << endl;
	for (int i = 0; i < vect.size(); i++)	{
		cout << vect[i] << " ";
	}
	cout << endl;
}

vector <float_vector> cell_list(int n_elements, float array_locations[], float radius, float xMax)	{
		// Store locations' array into a vector - May be unnecessary
	// vector <float> locations (array_locations, array_locations + sizeof(array_locations) / sizeof(float));	
	vector <float> locations;

	for (int i = 0; i < n_elements; i++)	{
		locations.push_back(array_locations[i]);
	}

	// print_vector(locations);
	
	vector <float_vector> cells;	// Vector of vectors
	float_vector temp;	// For temporary (storing) purposes

	vector <int> particle_cell;	// Stores cells corresponding to each particle

	vector <float_vector> neighbours;	// Stores neighbours corresponding to each particle

	int n_cells = int(floor(xMax/radius));
	
	// cout << "Number of cells " << n_cells << endl;

	for (int i = 0; i <= n_cells; i++)	{
		cells.push_back(temp);
	}
	// Populated cells vector with the required number of empty vectors

	int current_cell;

	for (int i = 0; i < locations.size(); i++)	{
		current_cell = int(floor(locations[i]/radius));
		cells[current_cell].push_back(i);	
	}
	// Stored the particles in corresponding cells

	// print_vectorOfvector(cells);

	for (int i = 0; i < locations.size(); i++)	{
		current_cell = int(floor(locations[i]/radius));
		particle_cell.push_back(current_cell);	// Store the cell - referring to particle indices	
	}
	// Stored cells corresponding to each particle

	int near_cells[] = {-1, 0, 1};	// Truncating the sample to these cells

	for (int i = 0; i < locations.size(); i++)	{
		neighbours.push_back(temp);		// Initialize with an empty vector corresponding to each particle
	}
	// Initialized the neighbours vector

	int size = locations.size();
	int near_cell;

	for (int i = 0; i < locations.size(); i++)	{
		current_cell = particle_cell[i];
		for (int c = 0; c < 3; c++)	{
			near_cell = current_cell + near_cells[c];
			// Check out of bound errors
			if (near_cell >= 0 && near_cell < size)	{
				for (int j = 0; j < cells[near_cell].size(); j++)	{
					if (dist(locations[i], locations[cells[near_cell][j]]) <= radius)	{
						neighbours[i].push_back(cells[near_cell][j]);
					}
				}
			}
		}
	}

	print_vectorOfvector(neighbours);
	// Printed the values to console
	
	return neighbours;
	// Return the neighbours vector	
}

int main(int argc, char *argv[]) {
	float locations[7] = {0.0, 6.0, 2.0, 5.0, 1.0, 7.0, 10.0};
	float xMax = 10.0;
	float radius = 4.0;
	float neighbours[7][7];
	int size = 7;
	brute_force(size, locations, radius, neighbours);
	cout << endl << "Next algorithm" << endl << endl;
	cell_list(size, locations, radius, xMax);
	return 0;
}