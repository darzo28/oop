#include "Generator.h"

using namespace std;

void PrintSet(const set<size_t>& numberSet)
{
	copy(numberSet.begin(), numberSet.end(), ostream_iterator<size_t>(cout, " "));
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: Generator.exe <upper bound>\n";
		return 1;
	}

	int upperBound;
	if (!StrToUpperBound(argv[1], upperBound))
	{
		return 1;
	}

	set<size_t> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintSet(primeNumbers);

	return 0;
}
