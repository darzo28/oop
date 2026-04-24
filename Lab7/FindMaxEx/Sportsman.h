#pragma once
#include <string>

struct Sportsman
{
	std::string name;
	double height{};
	double weight{};
};

bool CompareHeight(const Sportsman& firstSportsman, const Sportsman& secondSportsman);
bool CompareWeight(const Sportsman& firstSportsman, const Sportsman& secondSportsman);
bool CompareName(const Sportsman& firstSportsman, const Sportsman& secondSportsman);