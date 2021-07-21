#include "binary_search.hpp"
#include <vector>

double lin_interp(std::vector<double> xd, std::vector<double> yd, double x)
{

	int sized = xd.size();
	if(x == xd.at(0))
	{
		return yd.at(0);
	}

	if(x == xd.at(sized -1))
	{
		return yd.at(sized - 1);
	}

	int index_up = binarySearch_nearest( xd, 0, sized-1, x);
	int index_down = index_up - 1;
	double x1 = xd.at(index_down);
	double x2 = xd.at(index_up);
	double y1 = yd.at(index_down);
	double y2 = yd.at(index_up);
	double m = (y2 - y1)/(x2 - x1);


	return  y1 + m * (x - x1);
}