#pragma once
#include <iostream>
#include "Car.h"

void ExecuteCommand(std::istream& input, std::ostream& output, CCar& car);

void PrintInfo(std::ostream& output, CCar& car);
bool ParseNumber(std::istream& input, int& number);
void SetGearMode(std::istream& input, std::ostream& output, CCar& car);
void SetSpeedMode(std::istream& input, std::ostream& output, CCar& car);

const int GEAR_REVERSE = -1;
const int GEAR_FIFTH = 5;

const int SPEED_MIN = 0;
const int SPEED_MAX = 150;