#include "Sportsman.h"

bool CompareHeight(const Sportsman& firstSportsman, const Sportsman& secondSportsman)
{
	return firstSportsman.height < secondSportsman.height;
}

bool CompareWeight(const Sportsman& firstSportsman, const Sportsman& secondSportsman)
{
	return firstSportsman.weight < secondSportsman.weight;
}

bool CompareName(const Sportsman& firstSportsman, const Sportsman& secondSportsman)
{
	return firstSportsman.name < secondSportsman.name;
}
