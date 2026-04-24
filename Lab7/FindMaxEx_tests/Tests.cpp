#define CATCH_CONFIG_MAIN
#include "../FindMaxEx/FindMax.h"
#include "../FindMaxEx/Sportsman.h"
#include "../../catch.hpp"

TEST_CASE("Sportsman")
{
	Sportsman sportsman1{ "Nathan", 179.2, 78.1 };
	Sportsman sportsman2{ "David", 170.6, 85.5 };
	Sportsman sportsman3{ "Richard", 192.1, 90.7 };

	std::vector<Sportsman> sportsmanVector{ sportsman1, sportsman2, sportsman3};

	SECTION("Max height has 3 sportsman")
	{
		Sportsman sportsmanMaxHeight;
		CHECK(FindMax(sportsmanVector, sportsmanMaxHeight, CompareHeight) == true);
		CHECK(sportsmanMaxHeight.name == sportsman3.name);
		CHECK(sportsmanMaxHeight.height == sportsman3.height);
		CHECK(sportsmanMaxHeight.weight == sportsman3.weight);
	}

	SECTION("Max weight has 3 sportsman")
	{
		Sportsman sportsmanMaxWeight;
		CHECK(FindMax(sportsmanVector, sportsmanMaxWeight, CompareWeight) == true);
		CHECK(sportsmanMaxWeight.name == sportsman3.name);
		CHECK(sportsmanMaxWeight.height == sportsman3.height);
		CHECK(sportsmanMaxWeight.weight == sportsman3.weight);
	}

	SECTION("Max name has 3 sportsman")
	{
		Sportsman sportsmanMaxWeight;
		CHECK(FindMax(sportsmanVector, sportsmanMaxWeight, CompareName) == true);
		CHECK(sportsmanMaxWeight.name == sportsman3.name);
		CHECK(sportsmanMaxWeight.height == sportsman3.height);
		CHECK(sportsmanMaxWeight.weight == sportsman3.weight);
	}
}

TEST_CASE("Empty vector")
{
	SECTION("CompareHeight")
	{
		Sportsman sportsman;
		std::vector<Sportsman> emptyVector{};
		CHECK(FindMax(emptyVector, sportsman, CompareHeight) == false);
		CHECK_NOTHROW(FindMax(emptyVector, sportsman, CompareHeight));
	}

	SECTION("CompareWeight")
	{
		Sportsman sportsman;
		std::vector<Sportsman> emptyVector{};
		CHECK(FindMax(emptyVector, sportsman, CompareWeight) == false);
		CHECK_NOTHROW(FindMax(emptyVector, sportsman, CompareWeight));
	}

	SECTION("CompareName")
	{
		Sportsman sportsman;
		std::vector<Sportsman> emptyVector{};
		CHECK(FindMax(emptyVector, sportsman, CompareName) == false);
		CHECK_NOTHROW(FindMax(emptyVector, sportsman, CompareWeight));
	}
}
