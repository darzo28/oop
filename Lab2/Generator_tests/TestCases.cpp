#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../PrimeNumbersGenerator/Generator.h"

TEST_CASE("StrToUpperBound tests")
{
	int number;
	SECTION("Invalid value of upper bound")
	{
		CHECK(StrToUpperBound("abc", number) == false);
		CHECK(StrToUpperBound("100000001", number) == false);
		CHECK(StrToUpperBound("1000000000000", number) == false);
	}

	SECTION("Upper bound is 123")
	{
		StrToUpperBound("123", number);
		CHECK(number == 123);
	}
}

TEST_CASE("GeneratePrimeNumbersSet tests")
{
	SECTION("8 prime numbers in range")
	{
		CHECK(GeneratePrimeNumbersSet(20) == std::set<size_t>{ 2, 3, 5, 7, 11, 13, 17, 19 });
	}

	SECTION("8 prime numbers in range")
	{
		CHECK(GeneratePrimeNumbersSet(19) == std::set<size_t>{ 2, 3, 5, 7, 11, 13, 17, 19 });
	}

	SECTION("No numbers in set")
	{
		CHECK(GeneratePrimeNumbersSet(1) == std::set<size_t>{});
	}

#ifdef NDEBUG

	SECTION("5761455 prime numbers in range up to 100000000")
	{
		CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
	}

#endif
}
