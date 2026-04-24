#pragma once
#include<string>

enum class Direction
{
	FORWARD,
	BACK,
	STOP
};

enum class Gear
{
	REVERSE = -1,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

class CCar
{
public:
	CCar();

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:

	struct GearSpeed
	{
		int m_minSpeed;
		int m_maxSpeed;
	};

	// статические константы или вынести
	// вынести в массив
	const GearSpeed SPEED_STOP = { 0, 0 };
	const GearSpeed REVERSE_SPEED_NOT_NULL = { 1, 20 };
	const GearSpeed FIRST_SPEED = { 0, 30 };
	const GearSpeed FIRST_SPEED_NOT_NULL = { 1, 30 };
	const GearSpeed SECOND_SPEED = { 20, 50 };
	const GearSpeed THIRD_SPEED = { 30, 60 };
	const GearSpeed FOURTH_SPEED = { 40, 90 };
	const GearSpeed FIFTH_SPEED = { 50, 150 };

	// доработать
	bool SetGearCheck(int gear, GearSpeed gearOfSpeed);
	bool SetSpeedCheck(int speed, GearSpeed gearOfSpeed);

	bool m_engine;
	int m_speed;
	Gear m_gear;
};

