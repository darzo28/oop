#include "ProcessVector.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<double> inputVector(istream_iterator<double>(cin), (istream_iterator<double>()));

	ChangeVector(inputVector);
	sort(inputVector.begin(), inputVector.end());
	PrintVector(inputVector);

	return 0;
}
