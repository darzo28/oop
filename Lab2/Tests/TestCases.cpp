#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../Vector/ProcessVector.h"

TEST_CASE("ChangeVector test: should be empty array")
{
	std::vector<double> inputVector = {};
	std::vector<double> outputVector = {};

	ChangeVector(inputVector);
	CHECK(inputVector == outputVector);
}

TEST_CASE("ChangeVector test: array should contains 25")
{
	std::vector<double> inputVector = { 5 };
	std::vector<double> outputVector = { 25 };

	ChangeVector(inputVector);
	CHECK(inputVector == outputVector);
}

TEST_CASE("ChangeVector test: array should contains")
{
	std::vector<double> inputVector = { 0, 1.1, 2, -2.5, -2 };
	std::vector<double> outputVector = { 0, -2.75, -5, 6.25, -12.5 };

	ChangeVector(inputVector);
	CHECK(inputVector == outputVector);
}
