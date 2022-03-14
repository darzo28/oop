#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "Replace.h"

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: Replace.exe <input file> <output file> <search string> <replace string>\n";
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

string::const_iterator FindFirstIndexOfString(
	string::const_iterator first, 
	string::const_iterator last, const string& searchStr)
{
	string::const_iterator index;
	boyer_moore_searcher searcher(searchStr.begin(), searchStr.end());
	if (auto it = search(first, last, searcher); it != last) 
	{
		index = it;
	}
	else
	{
		index = last;
	}

	return index;
}

string ReplaceString(const string& subject, const string& searchStr, const string& replaceStr)
{
	string line = "";
	string::const_iterator pos;
	size_t strLength = searchStr.size();

	if (searchStr.empty())
	{
		line = subject;
	}
	else
	{
		for (auto it = subject.begin(); it != subject.end(); it = pos + strLength)
		{
			pos = FindFirstIndexOfString(it, subject.end(), searchStr);
			if (pos != subject.end())
			{
				line.append(it, pos).append(replaceStr);
			}
			else
			{
				line.append(it, subject.end());
			}
		}
	}

	return line;
}

void FindAndReplaceString(ifstream& input, ofstream& output, const string& searchString, const string& replaceString)
{
	string line;
	string newLine;

	while (getline(input, line))
	{
		newLine = ReplaceString(line, searchString, replaceString);
		output << newLine << "\n";
	}
}

bool Replace(const string& inputFileName, const string& outputFileName, const string& searchString, const string& replaceString)
{
	ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}

	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	FindAndReplaceString(input, output, searchString, replaceString);

	if (input.bad())
	{
		cout << "Failed to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		return 1;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (!Replace(args->inputFileName, args->inputFileName, args->searchString, args->replaceString))
	{
		return 1;
	}
}
