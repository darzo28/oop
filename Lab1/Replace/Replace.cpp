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

int FindFirstIndexOfString(string line, string substring)
{
	int index;
	if (auto it = search(line.begin(), line.end(),
			substring.begin(), substring.end());
		it != line.end())
	{
		index = it - line.begin();
	}
	else
	{
		index = -1;
	}

	return index;
}

void Replace(ifstream& input, ofstream& output, string searchString, string replaceString)
{
	string oldLine;
	size_t strLength = searchString.size();

	while (getline(input, oldLine))
	{
		string newLine = "";
		int pos = 0;
		size_t lineLength = oldLine.size();

		for (auto i = 0; i < lineLength; i += pos + strLength)
		{
			string subLine = oldLine.substr(i);
			pos = FindFirstIndexOfString(subLine, searchString);
			if (pos != -1)
			{
				newLine += subLine.substr(0, pos) + replaceString;
			}
			else
			{
				newLine += subLine;
				break;
			}
		}

		output << newLine << "\n";
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}

	if (args->searchString.empty())
	{
		cout << "Search string shouldn't be empty\n";
		return 1;
	}
	Replace(input, output, args->searchString, args->replaceString);

	if (input.bad())
	{
		cout << "Failed to read data from input file\n";
		return 1;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		return 1;
	}
}
