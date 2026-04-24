#include "Car.h"

CCar::CCar()
	: m_engine(false)
	, m_speed(0)
	, m_gear(Gear::NEUTRAL)
{
}

bool CCar::IsTurnedOn() const
{
	return m_engine;
}

Direction CCar::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::FORWARD;
	}
	if (m_speed < 0)
	{
		return Direction::BACK;
	}
	return Direction::STOP;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	if (!m_engine)
	{
		m_engine = true;
	}

	return m_engine;
}

bool CCar::TurnOffEngine()
{
	if (m_engine && m_speed == 0 && 
		m_gear == Gear::NEUTRAL)
	{
		m_engine = false;
	}

	return !m_engine;
}

bool CCar::SetGearCheck(int gear, GearSpeed gearSpeed)
{
	if (m_speed >= gearSpeed.m_minSpeed && m_speed <= gearSpeed.m_maxSpeed)
	{
		m_gear = Gear(gear);
		return true;
	}
	return false;
}

bool CCar::SetGear(int gear)
{
	if (!m_engine)
	{
		if (gear == 0)
		{
			m_gear = Gear::NEUTRAL;
			return true;
		}
		return false;
	}

	if (m_gear == Gear(gear))
	{
		return true;
	}

	if (m_gear == Gear::REVERSE && gear == 1)
	{
		if (m_speed == 0)
		{
			m_gear = Gear::FIRST;
			return true;
		}
		return false;
	}

	if (m_gear == Gear::NEUTRAL && gear == 1 && m_speed == 0)
	{
		if (m_direction == Direction::BACK)
		{
			m_direction = Direction::STOP;
		}
		else
		{
			m_gear = Gear::FIRST;
			return true;
		}

		return false;
	}

	switch (gear)
	{
	case -1:
		return SetGearCheck(-1, SPEED_STOP);
	case 0:
		m_gear = Gear::NEUTRAL;
		return true;
	case 1:
		return SetGearCheck(1, FIRST_SPEED);
	case 2:
		return SetGearCheck(2, SECOND_SPEED);
	case 3:
		return SetGearCheck(3, THIRD_SPEED);
	case 4:
		return SetGearCheck(4, FOURTH_SPEED);
	case 5:
		return SetGearCheck(5, FIFTH_SPEED);
	default:
		return false;
	}
}

bool CCar::SetSpeedCheck(int speed, GearSpeed gearSpeed)
{
	if (speed >= gearSpeed.m_minSpeed && speed <= gearSpeed.m_maxSpeed)
	{
		m_speed = speed;
		return true;
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_engine)
	{
		if (speed == 0)
		{
			m_speed = speed;
			return true;
		}
		return false;
	}

	switch (m_gear)
	{
	case Gear::REVERSE:
		return SetSpeedCheck(speed, SPEED_STOP) || SetSpeedCheck(speed, REVERSE_SPEED_NOT_NULL);
	case Gear::NEUTRAL:
		return SetSpeedCheck(speed, SPEED_STOP);
	case Gear::FIRST:
		return SetSpeedCheck(speed, SPEED_STOP) || SetSpeedCheck(speed, FIRST_SPEED_NOT_NULL);
	case Gear::SECOND:
		return SetSpeedCheck(speed, SECOND_SPEED);
	case Gear::THIRD:
		return SetSpeedCheck(speed, THIRD_SPEED);
	case Gear::FOURTH:
		return SetSpeedCheck(speed, FOURTH_SPEED);
	case Gear::FIFTH:
		return SetSpeedCheck(speed, FIFTH_SPEED);
	default:
		return false;
	}
}