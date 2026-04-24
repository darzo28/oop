#pragma once

#include <iostream>
#include <set>
#include <string>
#include <vector>

const int MAX_BOUND = 100000000;

bool StrToUpperBound(const std::string& str, int& number);
std::vector<bool> GetSieve(int upperBound);
std::set<size_t> SieveToSet(const std::vector<bool>& arePrimeNumbers);
std::set<size_t> GeneratePrimeNumbersSet(int upperBound);
