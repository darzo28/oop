#pragma once

size_t FindFirstIndexOfString(std::string line, std::string substring);

string ReplaceString(const string& subject, const string& searchStr, const string& replaceStr);

void FindAndReplaceString(ifstream& input, ofstream& output, const string& searchString, const string& replaceString);