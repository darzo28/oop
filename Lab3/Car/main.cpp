#include "Car.h"
#include "CarCommunication.h"
#include <iostream>

using namespace std;

int main()
{
	CCar car;

	while (!cin.eof())
	{
		ExecuteCommand(cin, cout, car);
	}

	return 0;
}

// на нейтральной передаче скорость можно уменьшать плавно