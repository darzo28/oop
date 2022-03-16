#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

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

string ReplaceString(const string& subject, const string& searchStr, const string& replaceStr)
{
	string line;
	string::const_iterator searchPos;
	size_t strLength = searchStr.size();
	boyer_moore_searcher searcher(searchStr.begin(), searchStr.end());

	if (searchStr.empty())
	{
		return subject;
	}
	else
	{
		auto startPos = subject.begin();

		while (startPos != subject.end())
		{
			searchPos = search(startPos, subject.end(), searcher);
			line.append(startPos, searchPos);

			if (searchPos != subject.end())
			{
				line.append(replaceStr);
				startPos = searchPos + strLength;
			}
			else
			{
				startPos = subject.end();
			}
		}

		return line;
	}
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

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		return false;
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

	if (!Replace(args->inputFileName, args->outputFileName, args->searchString, args->replaceString))
	{
		return 1;
	}

	return 0;
}
