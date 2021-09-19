#include "binary_search.hpp"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <limits>



double linear_interp (double x1, double y1, double x2, double y2, double x)
{

	double y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
	return y;
}

class bi_interp
{
	private:
		std::set<double> setx, sety;
		std::vector<double>  fvec;
		std::vector<double> vecx;
		std::vector<double> vecy;
		int size_x;
		int size_y;

	public:
		bi_interp(std::set<double> &setx_arg, std::set<double> &sety_arg, std::vector<double> &fvec_arg)
		{
			fvec = fvec_arg;
			setx = setx_arg;
			sety = sety_arg;
			
			size_y   = sety.size();
			size_x   = setx.size();

			vecx.reserve(size_x);
			for (auto it = setx.begin(); it != setx.end(); ) {
					vecx.push_back(std::move(setx.extract(it++).value()));
			}
			
			vecy.reserve(size_y);
			for (auto it = sety.begin(); it != sety.end(); ) {
					vecy.push_back(std::move(sety.extract(it++).value()));
			}

		}
		double interp(double x, double y)
		{
			//std::cout << "Hi_In" << std::endl;

			int index_x2 = binarySearch_nearest( vecx, 0, size_x - 1, x);
			int index_y2 = binarySearch_nearest( vecy, 0, size_y - 1, y);
			if (x == vecx.at(0) && y == vecy.at(0))
			{
				return fvec.at(0);
			}

			if (x < vecx.at(0) || x > vecx.at(size_x - 1))
			{
				std::cout << "x shoud be > " << vecx.at(0) << ", and < " << vecx.at(size_x-1) << std::endl;
				return std::numeric_limits<double>::quiet_NaN();	
			} 
			if (y < vecy.at(0) || y > vecy.at(size_y - 1))
			{
				std::cout << "y should be > " << vecy.at(0) << ", and < " << vecy.at(size_y-1) << std::endl;
				return std::numeric_limits<double>::quiet_NaN();	
			} 


			int index_x1 = index_x2 - 1;
			int index_y1 = index_y2 - 1;

			if(index_x1 < 0)
			{
				index_x1++;
			}
			if(index_y1 < 0)
			{
				index_y1++;
			}

			////////////////////////////////////////////////////////
			double x1    = vecx.at(index_x1);
			double x2    = vecx.at(index_x2);
			double y1    = vecy.at(index_y1);
			double y2    = vecy.at(index_y2);
			////////////////////////////////////////////////////////
			double fx1y1 = fvec.at(index_x1 * size_y + index_y1); 
			double fx1y2 = fvec.at(index_x1 * size_y + index_y2); 
			double fx2y1 = fvec.at(index_x2 * size_y + index_y1); 
			double fx2y2 = fvec.at(index_x2 * size_y + index_y2); 
			////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////
			double fxy1  = linear_interp(x1, fx1y1, x2, fx2y1, x);
			double fxy2  = linear_interp(x1, fx1y2, x2, fx2y2, x);

			double fxy   = linear_interp(y1, fxy1, y2, fxy2, y);

			if (x1 == x2 && x1 == vecx.at(0))
			{
				return linear_interp(y1, fx1y1, y2, fx1y2, y);
			}

			if (x1 == x2 && x1 == vecx.at(size_x - 1))
			{
				return linear_interp(y1, fx2y1, y2, fx2y2, y);
			}

			if (y1 == y2 && y1 == vecy.at(0))
			{
				return linear_interp(x1, fx1y1, x2, fx2y1, x);
			}

			if (y1 == y2 && y1 == vecy.at(size_y - 1))
			{
				return linear_interp(x1, fx1y2, x2, fx2y2, x);
			}
			return fxy;
		}

};

/*
double bil_interp(std::set<double> setx, std::set<double> sety, std::vector<double>  fvec, double x, double y )
{
	int size_y   = sety.size();
	int size_x   = setx.size();

	std::vector<double> vecx;
	std::vector<double> vecy;
	vecx.reserve(size_x);
	for (auto it = setx.begin(); it != setx.end(); ) {
		    vecx.push_back(std::move(setx.extract(it++).value()));
	}
	
	vecy.reserve(size_y);
	for (auto it = sety.begin(); it != sety.end(); ) {
		    vecy.push_back(std::move(sety.extract(it++).value()));
	}

	int index_x2 = binarySearch_nearest( vecx, 0, size_x - 1, x);
	int index_y2 = binarySearch_nearest( vecy, 0, size_y - 1, y);

	if (x == vecx.at(0) && y == vecy.at(0))
	{
		return fvec.at(0);
	}

	if (x < vecx.at(0) || x > vecx.at(size_x - 1))
	{
		std::cout << "x shoud be > " << vecx.at(0) << ", and < " << vecx.at(size_x-1) << std::endl;
		return std::numeric_limits<double>::quiet_NaN();	
	} 
    if (y < vecy.at(0) || y > vecy.at(size_y - 1))
    {
    	std::cout << "y should be > " << vecy.at(0) << ", and < " << vecy.at(size_y-1) << std::endl;
    	return std::numeric_limits<double>::quiet_NaN();	
    } 


	int index_x1 = index_x2 - 1;
	int index_y1 = index_y2 - 1;

	if(index_x1 < 0)
	{
		index_x1++;
	}
	if(index_y1 < 0)
	{
		index_y1++;
	}

	////////////////////////////////////////////////////////
	double x1    = vecx.at(index_x1);
	double x2    = vecx.at(index_x2);
	double y1    = vecy.at(index_y1);
	double y2    = vecy.at(index_y2);
	////////////////////////////////////////////////////////
	double fx1y1 = fvec.at(index_x1 * size_y + index_y1); 
	double fx1y2 = fvec.at(index_x1 * size_y + index_y2); 
	double fx2y1 = fvec.at(index_x2 * size_y + index_y1); 
	double fx2y2 = fvec.at(index_x2 * size_y + index_y2); 
	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////
	double fxy1  = linear_interp(x1, fx1y1, x2, fx2y1, x);
	double fxy2  = linear_interp(x1, fx1y2, x2, fx2y2, x);

	double fxy   = linear_interp(y1, fxy1, y2, fxy2, y);

	//std::cout << x1 << " " << x2 << " " << fxy1 << " " << fxy2 <<  std::endl;
	if (x1 == x2 && x1 == vecx.at(0))
	{
		return linear_interp(y1, fx1y1, y2, fx1y2, y);
	}

	if (x1 == x2 && x1 == vecx.at(size_x - 1))
	{
		return linear_interp(y1, fx2y1, y2, fx2y2, y);
	}

	if (y1 == y2 && y1 == vecy.at(0))
	{
		return linear_interp(x1, fx1y1, x2, fx2y1, x);
	}

	if (y1 == y2 && y1 == vecy.at(size_y - 1))
	{
		return linear_interp(x1, fx1y2, x2, fx2y2, x);
	}
	return fxy;
}
*/