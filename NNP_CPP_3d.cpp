#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

typedef std::vector<float> float_vector;

// Type definitions required for constructing cells
typedef std::vector<int> Cells;
typedef std::vector<Cells> RowOfCells;
typedef std::vector<RowOfCells> PlaneOfCells;
typedef std::vector<PlaneOfCells> SpaceOfCells;


class Particle	{
// A generic class to hold a particle with coordinates in 3 dimensional space
	float x, y, z;
	public:
	Particle()	{
		x = 0; y = 0; z = 0;
	}
	Particle(float X, float Y, float Z)	{
		x = X; y = Y; z = Z;
	}
	void setCoords(float X, float Y, float Z)	{
		x = X; y = Y; z = Z;
	}
	float getX()	{
		return x;
	}
	float getY()	{
		return y;
	}
	float getZ()	{
		return z;
	}
	float distanceSquared(Particle b)	{
		float x1 = b.getX();
		float y1 = b.getY();
		float z1 = b.getZ();
		float xDiff = x - x1;
		float yDiff = y - y1;
		float zDiff = z - z1;
		return xDiff * xDiff + yDiff * yDiff + zDiff * zDiff;
	}
	bool withinDistance(Particle b, float r)	{
		bool check = this->distanceSquared(b) <= (r * r);
		return check;
	}
	void print()	{
		std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
	}
}	;

class ParticleAggregation	{
// A generic class to hold an aggregation of particles 
// Vector based implementation
	std::vector<Particle> P;
	public:
	int size()	{
		return P.size();
	}
	Particle particleNumber(int i)	{
		return P[i];
	}
	void add_particle(Particle p)	{
		P.push_back(p);
	}
	void print()	{
		for(int i = 0; i < P.size(); i++)	{
			P[i].print();
		}
	}
	void loadValues(std::string fileLocation, int MAX)	{
		std::string coordsString, coordString;
		std::ifstream inputFile;
		Particle p;
		std::stringstream ss;
		float coord[3];
		int i = 0, count = 0;
		inputFile.open(fileLocation.c_str());
		if (inputFile.is_open())	{
			while(getline(inputFile, coordsString))	{
				ss << coordsString;
				while(getline(ss, coordString, ','))	{
					coord[i] = atof(coordString.c_str());
					i++;
				}
				ss.str("");		// Flushes the string stream buffer
				ss.clear();		// Clears the EOF flag
				i = 0;
				p.setCoords(coord[0], coord[1], coord[2]);
				P.push_back(p);
				count++;
				if(count >= MAX)	break;
			}
		}
		inputFile.close();
	}
}	;

class Space		{
// A class to define the space with which we're working
	public:
	float xMax, xMin;
	float yMax, yMin;
	float zMax, zMin;
	Space()	{
		xMax = 0; xMin = 0;
		yMax = 0; yMin = 0;
		zMax = 0; zMin = 0;
	}
	void set(Particle max, Particle min)	{
		xMax = max.getX(); xMin = min.getX();
		yMax = max.getY(); yMin = min.getY();
		zMax = max.getZ(); zMin = min.getZ();
	}
}	;

class IndexCell	{
	public:
	int a, b, c;
	void set (int x, int y, int z)	{
		a = x; b = y; c = z;
	}
	void print()	{
		std::cout << std::endl << a << " " << b << " " << c << std::endl;
	}
}	;

class CellGrid		{
// A generic class to split the space into a grid of cells as per a given distance
public:
	int cellXMax, cellYMax, cellZMax;	// The number of cells required along each axis

	Cells cell;		// The cell
	RowOfCells row;		// A grid of N3 cells
	PlaneOfCells plane;		// A grid of N2 X N3 cells
	SpaceOfCells space;		// A grid of N1 X N2 X N3 cells
	
	std::vector<IndexCell> partCell;	// A list of cell indices corresponding to each particle index

	void initialize(Space S, float radius)	{
	// Initialize an N1 X N2 X N3 grid of cells, each cell being a vector/list/array	
		// Initialize with the number of cells required along each axis
		cellXMax = (int)(S.xMax / radius) + 1;
		cellYMax = (int)(S.yMax / radius) + 1;
		cellZMax = (int)(S.zMax / radius) + 1;
		
			// Create a row of 3 cells
		for(int k = 0; k < cellZMax; k++)	{
			row.push_back(cell);
		}

			// Create a plane of 3 rows, therefore a 3 X 3 grid of cells
		for(int j = 0; j < cellYMax; j++)	{
			plane.push_back(row);
		}

			// Create a space of 3 rows, therefore a 3 X 3 X 3 grid of cells
		for(int i = 0; i < cellXMax; i++)	{
			space.push_back(plane);
		}
		// Therefore, space[][][] will give you a vector or (in loose terms) a list
	} 

	void populate(ParticleAggregation P, float radius)	{
	// Populate the cell grid with particle indices
		int cellX, cellY, cellZ;
		Particle part;
		
		IndexCell ic;

		for(int i = 0; i < P.size(); i++)	{
			part = P.particleNumber(i);
			cellX = (int) (part.getX()/radius);
			cellY = (int) (part.getY()/radius);
			cellZ = (int) (part.getZ()/radius);
			space[cellX][cellY][cellZ].push_back(i);	// Push Back the particle indices, not the particles themselves

			ic.set(cellX, cellY, cellZ);
			partCell.push_back(ic);
		}
	}
}	;

std::vector<int> cellList(int particleIndex, ParticleAggregation P, CellGrid C, float radius)	{
	std::vector<int> neighbours;
	// C.partCell[particleIndex] will give you a tuple of the cell indices corresponding to that particle index
	// std::cout << "Checkpoint - Function called" << std::endl;
	IndexCell ic = C.partCell[particleIndex];
	for(int i = -1; i <= 1; i++)	{
		for(int j = -1; j <= 1; j++)	{
			for(int k = -1; k <= 1; k++)	{
				if(ic.a + i >= 0 && ic.a + i < C.cellXMax)	{
					if(ic.b + j >= 0 && ic.b + j < C.cellYMax)	{
						if(ic.c + k >= 0 && ic.c + k < C.cellZMax)	{
							// std::cout << "Checkpoint - cells located" << std::endl;
							for(int p = 0; p < C.space[ic.a + i][ic.b + j][ic.c + k].size(); p++)	{
								// C.space[ic.a + i][ic.b + j][ic.c + k][p] will loop through the particle indices in the cell i, j, k
								if(P.particleNumber(particleIndex).withinDistance(P.particleNumber(C.space[ic.a + i][ic.b + j][ic.c + k][p]), radius))	{
									neighbours.push_back(C.space[ic.a + i][ic.b + j][ic.c + k][p]);
								}
							}
						}	
					}
				}
			}
		}
	}
	return neighbours;
}

std::vector<int> brute_force(int particleIndex, ParticleAggregation P, float radius)	{
// A brute force algorithm
// Works in O(n-squared)
	int j, k;
	std::vector<int> neighbours;
	for (j = 0; j < P.size(); j++)	{
		if (P.particleNumber(particleIndex).withinDistance(P.particleNumber(j), radius))	{
			neighbours.push_back(j);	// Store the index corresponding to that particle
		}
	}
	return neighbours;
}

void print_vector(std::vector<int> v)	{
	for(int i = 0; i < v.size(); i++)	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

void unit_test()	{
	ParticleAggregation P;
	Space S;
	float radius = 1.0;
	CellGrid C;
	Particle p1(0.0,0.0,0.0);
	Particle p2(1.0,1.0,1.0);
	Particle p3(0.0,1.0,0.0);
	Particle p4(2.0,0.0,0.0);
	std::vector<int> check[4];
	check[0].push_back(0); check[0].push_back(2);
	check[1].push_back(1);
	check[2].push_back(0); check[2].push_back(2);
	check[3].push_back(3);
	P.add_particle(p1);
	P.add_particle(p2);
	P.add_particle(p3);
	P.add_particle(p4);
	Particle max(10,10,10);
	Particle min(0,0,0);
	S.set(max,min);
	C.initialize(S,radius);
	C.populate(P, radius);
	std::vector<int> v1, v2;
	for(int i = 0; i < 4; i++)	{
		v1 = brute_force(i, P, radius);
		std::sort(v1.begin(), v1.end());
		v2 = cellList(i, P, C, radius);
		std::sort(v2.begin(), v2.end());
		if(v1!=check[i] && v1!=v2)	{
			std::cout << "Unit test FAIL" << std::endl;
			break;
		}
	}
	
}

int main(int argc, char *argv[]) {
	
	float radius = 1.5;
	int MAX = 1000;
	ParticleAggregation P;
	Space S;
	CellGrid C;
	
	Particle max(10, 10, 10);
	Particle min(0, 0, 0);
	
	S.set(max, min);
	
	P.loadValues("testSampleFile.txt", MAX);	// Contains a total of 1000000 (1 million) points
	
	C.initialize(S, radius);
	C.populate(P, radius);
	
	std::vector<int> v;
	
	clock_t t;
	float diffTime;

	unit_test();

	std::cout << "Brute Force" << std::endl;
	// Brute Force
	t = clock();
	for(int i = 0; i < MAX; i++)	{
		v =	brute_force(i, P, radius);
	}
	t = clock() - t;
	diffTime = (float)t/CLOCKS_PER_SEC;
	std::cout << diffTime << std::endl;
	
	std::cout << "Cell List" << std::endl;
	t = clock();
	// Cell List
	for(int i = 0; i < MAX; i++)	{
		v = cellList(i, P, C, radius);
	}	
	t = clock() - t;
	diffTime = (float)t/CLOCKS_PER_SEC;
	std::cout << diffTime << std::endl;
	
	return 0;
}