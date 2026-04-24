#pragma once
#include <vector>

//default std::less
template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto max = arr.begin();

	for (auto it = max + 1; it != arr.end(); it++)
	{
		if (less(*max, *it))
		{
			max = it;
		}
	}
	maxValue = *max;

	return true;
}
