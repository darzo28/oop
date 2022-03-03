#pragma once

int FindFirstIndexOfString(std::string line, std::string substring);

void Replace(std::ifstream& input, std::ofstream& output, std::string searchString, std::string replaceString);