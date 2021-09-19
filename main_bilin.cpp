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


	for( double x = 2; x < 15; x++)
	{
				
		for( double y = 2; y < 15; y++)
		{
			double z = x * x + y * y;
			setx.insert(x);
			sety.insert(y);
			fvec.push_back(z);
		}
	}
	bi_interp f1 = bi_interp(setx, sety, fvec);

	for (double x = 2; x < 10; x++)
	{
		for (double y = 2; y < 10; y++)
		{
			cout << x << " " << y << " " << f1.interp(x, y) << endl;
		}
	}


	return 0;

}
