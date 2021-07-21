#include <iostream>
#include <vector>
#include <stdlib.h>


int binarySearch_nearest(std::vector<double> vec, int left, int right, double x)
{

	bool found = false;
	int middle = 0;
	int output = 0;

	if( x < vec.at(left))
	{
		std::cout << "x is not in the range of available data, the range is: ("
		<< vec.at(0) <<", " << vec.at(vec.size()-1) << " )" << std::endl;
		abort;
	}
	else if( x > vec.at(right))
	{
		std::cout << "x is not in the range of available data, the range is: ("
		<< vec.at(0) <<", " << vec.at(vec.size()-1) << " )" << std::endl;
		abort;
	}

	else
	{
		while (left < right)
		{
			middle = left + (right - left)/2;
			if(x == vec.at(middle))
			{
				found = true;
				output = middle;
				break;
			}

			else if ( x < vec[middle])
			{
				right = middle - 1;
			}

			else
			{
				left = middle + 1;
			}
		}

		if( found == false && x < vec[middle] )
		{
			output =  middle;
		}
		if ( found == false && x > vec[middle])
		{
			output = middle + 1;
		}		
	}
	return output;

}