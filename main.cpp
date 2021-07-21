#include <iostream>
#include <cmath>
#include "linear_interpolation.hpp"
#include <vector>

using namespace std;



int main()
{

	vector<double> vecdx;
	vector<double> vecdy;

	int x = 0;

	for( int i = 0; i < 99; i++)
	{
		x = x + 2;
		vecdx.push_back(x);
		vecdy.push_back(x * x);
	}

	for (double x = 2; x < 20; x++)
	{
		cout << x << " " << lin_interp(vecdx, vecdy, x) << endl;
	}


	return 0;

}
