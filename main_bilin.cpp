#include <iostream>
#include <cmath>
#include "bilinear_interpolation.hpp"
#include <vector>
#include <set>

using namespace std;



int main()
{

	set<double> setx;
	set<double> sety;
	vector<double> fvec;


	for( double x = 2; x < 99; x++)
	{
				
		for( double y = 2; y < 99; y++)
		{
			double z = x * x + y * y;
			setx.insert(x);
			sety.insert(y);
			fvec.push_back(z);
		}
	}

	for (double x = 2; x < 6; x++)
	{
		for (double y = 2; y< 6; y++)
		{
			cout << x << " " << y << " " <<bil_interp(setx, sety, fvec, x, y) << endl;
		}
	}


	return 0;

}
