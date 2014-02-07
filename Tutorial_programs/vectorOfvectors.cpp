#include <iostream>
#include <vector>

using namespace std;

typedef vector <float> float_vector;

int main(int argc, char *argv[])	{
	vector <float_vector> big_vector;
	vector <float> temp;
	for (int i = 0; i < 10; i++)	{
		for (int j = 0; j < 10; j++)	{
			temp.push_back(j);
		}
		big_vector.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < big_vector.size(); i++)	{
		for (int j = 0; j < big_vector[i].size(); j++)	{
			cout << big_vector[i][j] << " ";
		}
		cout << endl;
	}
}