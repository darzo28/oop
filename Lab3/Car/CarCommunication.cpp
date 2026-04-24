#include "CarCommunication.h"
#include "Messages.h"

using namespace std;

void PrintInfo(ostream& output, CCar& car)
{
	output << ENGINE_CONDITION_INFO << car.GetEngine() << endl;
	switch (m_direction)
	{
	case Direction::FORWARD:
		return "FORWARD";
	case Direction::BACK:
		return "BACK";
	case Direction::STOP:
		return "STOP";
	default:
		return "Unknown direction";
	}
	output << DIRECTION_INFO << car.GetDirection() << endl;
	output << SPEED_INFO << car.GetSpeed() << endl;
	output << GEAR_INFO << car.GetGear() << endl;
}

bool ParseNumber(istream& input, int& number)
{
	try
	{
		string str;
		input >> str;
		number = std::stoi(str);
		return true;
	}
	catch (const invalid_argument&)
	{
		return false;
	}
}

void SetGearMode(istream& input, ostream& output, CCar& car)
{
	int number;

	if (!ParseNumber(input, number))
	{
		output << ERROR_NON_NUMBER;
	}
	else if (number < GEAR_REVERSE || number > GEAR_FIFTH)
	{
		output << ERROR_SET_GEAR_NUMBER;
	}
	else
	{
		if (car.SetGear(number))
		{
			output << SET_GEAR << number << endl;
		}
		else
		{
			output << ERROR_SET_GEAR;
		}
	}
}

void SetSpeedMode(istream& input, ostream& output, CCar& car)
{
	int number;

	if (!ParseNumber(input, number))
	{
		output << ERROR_NON_NUMBER;
	}
	else if (number < SPEED_MIN || number > SPEED_MAX)
	{
		output << ERROR_SET_SPEED_NUMBER;
	}
	else
	{
		if (car.SetSpeed(number))
		{
			output << SET_SPEED << number << endl;
		}
		else
		{
			output << ERROR_SET_SPEED;
		}
	}
}

void ExecuteCommand(istream& input, ostream& output, CCar& car)
{
	string str;

	while (input >> str)
	{
		if (str == INFO_MODE)
		{
			PrintInfo(output, car);
		}
		else if (str == ENGINE_ON_MODE)
		{
			output << (car.TurnOnEngine() ? ENGINE_ON : ERROR_ENGINE_ON);
		}
		else if (str == ENGINE_OFF_MODE)
		{
			output << (car.TurnOffEngine() ? ENGINE_OFF : ERROR_ENGINE_OFF);
		}
		else if (str == SET_GEAR_MODE)
		{
			SetGearMode(input, output, car);
		}
		else if (str == SET_SPEED_MODE)
		{
			SetSpeedMode(input, output, car);
		}
		else
		{
			output << UNKNOWN_MODE;
		}

		output << endl;
	}
}