#include "Generator.h"

using namespace std;

bool StrToUpperBound(const string& str, int& number)
{
	try
	{
		number = stoi(str);
	}
	catch (const invalid_argument&)
	{
		cout << "Upper bound must be number\n";
		return false;
	}
	catch (const out_of_range&)
	{
		cout << "Invalid value\n";
		return false;
	}

	if (number > MAX_BOUND)
	{
		cout << "Upper bound must be less than " << MAX_BOUND << '\n';
		return false;
	}

	return true;
}

vector<bool> GetSieve(int upperBound)
{
	if (upperBound < 2)
	{
		return vector<bool>{};
	}

	vector<bool> boolVector((size_t)upperBound + 1, true);
	boolVector[0] = false;
	boolVector[1] = false;
	size_t maxDivider = (size_t)sqrt(boolVector.size());

	for (size_t i = 2; i <= maxDivider; i++)
	{
		if (boolVector[i])
		{
			for (size_t j = 2; i * j < boolVector.size(); j++)
			{
				boolVector[i * j] = false;
			}
		}
	}
	return boolVector;
}

set<size_t> SieveToSet(const vector<bool>& boolVector)
{
	set<size_t> numbersSet;
	for (size_t i = 0; i < boolVector.size(); i++)
	{
		if (boolVector[i])
		{
			numbersSet.insert(numbersSet.end(), i);
		}
	}
	return numbersSet;
}

set<size_t> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> arePrimeNumbers = GetSieve(upperBound);
	return SieveToSet(arePrimeNumbers);
}