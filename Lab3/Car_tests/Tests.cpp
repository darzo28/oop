#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../Car/Car.h"

void Check()
{

}

TEST_CASE("Car")
{
	SECTION("Car constructor init")
	{
		CCar car;

		SECTION("Engine off")
		{
			CHECK(car.IsTurnedOn() == false);
		}

		SECTION("Direction: stop")
		{
			CHECK(car.GetDirection() == "STOP");
		}

		SECTION("Neutral gear")
		{
			CHECK(car.GetGear() == "NEUTRAL");
		}

		SECTION("Speed equals 0")
		{
			CHECK(car.GetSpeed() == 0);
		}
	}

	SECTION("TurnOnEngine")
	{
		CCar car;
		car.TurnOnEngine();
		//объединить однотипные проверки в функцию
		// проверять обе границы скоростей
		SECTION("Engine on")
		{
			CHECK(car.IsTurnedOn() == true);
		}

		SECTION("Direction: stop")
		{
			CHECK(car.GetDirection() == "STOP");
		}

		SECTION("Neutral gear")
		{
			CHECK(car.GetGear() == "NEUTRAL");
		}

		SECTION("Speed equals 0")
		{
			CHECK(car.GetSpeed() == 0);
		}

		SECTION("Set gear to 1")
		{
			CHECK(car.SetGear(1) == true);
			CHECK(car.SetGear(1) == true);
		}
	}

	SECTION("TurnOffEngine")
	{
		CCar car;

		car.TurnOnEngine();

		SECTION("Set gear to 1 and engine mustn't be off")
		{
			CHECK(car.SetGear(1) == true);
			CHECK(car.TurnOffEngine() == false);
			CHECK(car.GetGear() == "FIRST");
		}

		SECTION("Set speed to 15 and engine mustn't be off")
		{
			CHECK(car.SetGear(1) == true);
			CHECK(car.SetSpeed(15) == true);
			CHECK(car.TurnOffEngine() == false);
			CHECK(car.GetSpeed() == 15);
		}

		SECTION("Set gear to 0 and engine mustn't be off")
		{
			CHECK(car.SetGear(1) == true);
			CHECK(car.SetSpeed(15) == true);
			CHECK(car.SetGear(0) == true);
			CHECK(car.TurnOffEngine() == false);
			CHECK(car.GetSpeed() == 15);
			CHECK(car.GetGear() == "NEUTRAL");
		}

		SECTION("Set speed to 0 and turn off engine")
		{
			CHECK(car.SetSpeed(0) == true);
			CHECK(car.TurnOffEngine() == true);
			CHECK(car.GetSpeed() == 0);
			CHECK(car.GetGear() == "NEUTRAL");
			CHECK(car.IsTurnedOn() == false);
		}
	}

	SECTION("SetGear: Engine off")
	{
		CCar car;
		
		CHECK(car.SetGear(0) == true);
		CHECK(car.SetGear(1) == false);

		CHECK(car.GetDirection() == "STOP");
		CHECK(car.GetGear() == "NEUTRAL");
		CHECK(car.GetSpeed() == 0);
	}

	SECTION("SetSpeed: Engine off")
	{
		CCar car;

		CHECK(car.SetSpeed(0) == true);
		CHECK(car.SetSpeed(1) == false);

		CHECK(car.IsTurnedOn() == false);
		CHECK(car.GetDirection() == "STOP");
		CHECK(car.GetGear() == "NEUTRAL");
		CHECK(car.GetSpeed() == 0);
	}
	// переименовать
	SECTION("SetGear, SetSpeed: Gear REVERSE->NEUTRAL->FIRST")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetGear(-1) == true);
		CHECK(car.SetSpeed(10) == true);
		CHECK(car.SetGear(0) == true);

		CHECK(car.SetGear(1) == false);
		CHECK(car.SetSpeed(0) == true);

		CHECK(car.GetDirection() == "STOP");
		CHECK(car.SetGear(1) == true);
	}

	SECTION("SetGear, SetSpeed: Min Gear REVERSE, Max speed is 20")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.GetSpeed() == 0);
		CHECK(car.SetGear(-1) == true);

		CHECK(car.SetSpeed(20) == true);
		CHECK(car.SetSpeed(21) == false);

		CHECK(car.GetDirection() == "BACK");
		CHECK(car.GetGear() == "REVERSE");
		CHECK(car.GetSpeed() == 20);

		CHECK(car.SetGear(-2) == false);

		CHECK(car.SetGear(1) == false);
		CHECK(car.SetSpeed(0) == true);
		CHECK(car.SetGear(1) == true);
	}

	SECTION("SetGear, SetSpeed: Gear NEUTRAL, Speed can't be increase")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetSpeed(15) == false);
		CHECK(car.SetSpeed(0) == true);
	}

	SECTION("SetGear, SetSpeed: Gear FIRST, Max speed is 30")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(10) == true);

		CHECK(car.SetSpeed(30) == true);
		CHECK(car.SetSpeed(31) == false);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "FIRST");
		CHECK(car.GetSpeed() == 30);
	}

	SECTION("SetGear, SetSpeed: Gear SECOND, Max speed is 50")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(19) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "FIRST");
		CHECK(car.GetSpeed() == 19);

		CHECK(car.SetGear(2) == false);
		CHECK(car.SetSpeed(20) == true);
		CHECK(car.SetGear(2) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "SECOND");
		CHECK(car.GetSpeed() == 20);

		CHECK(car.SetSpeed(50) == true);
		CHECK(car.SetSpeed(51) == false);
		CHECK(car.GetSpeed() == 50);
	}

	SECTION("SetGear, SetSpeed: Gear THIRD, Max speed is 60")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(29) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "FIRST");
		CHECK(car.GetSpeed() == 29);

		CHECK(car.SetGear(3) == false);
		CHECK(car.SetSpeed(30) == true);
		CHECK(car.SetGear(3) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "THIRD");
		CHECK(car.GetSpeed() == 30);

		CHECK(car.SetSpeed(60) == true);
		CHECK(car.SetSpeed(61) == false);
		CHECK(car.GetSpeed() == 60);
	}

	SECTION("SetGear, SetSpeed: Gear FOURTH, Max speed is 90")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(30) == true);
		CHECK(car.SetGear(2) == true);
		CHECK(car.SetSpeed(39) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "SECOND");
		CHECK(car.GetSpeed() == 39);

		CHECK(car.SetGear(4) == false);
		CHECK(car.SetSpeed(40) == true);
		CHECK(car.SetGear(4) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "FOURTH");
		CHECK(car.GetSpeed() == 40);

		CHECK(car.SetSpeed(90) == true);
		CHECK(car.SetSpeed(91) == false);
		CHECK(car.GetSpeed() == 90);
	}

	SECTION("SetGear, SetSpeed: Max Gear FIFTH, Max speed is 150")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.IsTurnedOn() == true);

		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(30) == true);
		CHECK(car.SetGear(2) == true);
		CHECK(car.SetSpeed(49) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "SECOND");
		CHECK(car.GetSpeed() == 49);

		CHECK(car.SetGear(5) == false);
		CHECK(car.SetSpeed(50) == true);
		CHECK(car.SetGear(5) == true);

		CHECK(car.GetDirection() == "FORWARD");
		CHECK(car.GetGear() == "FIFTH");
		CHECK(car.GetSpeed() == 50);

		CHECK(car.SetSpeed(150) == true);
		CHECK(car.SetSpeed(151) == false);
		CHECK(car.GetSpeed() == 150);

		CHECK(car.SetGear(6) == false);
	}
}