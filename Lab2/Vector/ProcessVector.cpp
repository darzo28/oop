#include "ProcessVector.h"

void ChangeVector(std::vector<double>& array)
{
	if (array.size() != 0)
	{
		auto minElement = min_element(array.begin(), array.end()); 

		for (auto& item : array)
		{
			item *= *minElement;
		}
	}
}

void PrintVector(const std::vector<double> array)
{
	copy(array.begin(), array.end(), std::ostream_iterator<double>(std::cout, " "));
}