#include <fstream>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	string startPosition;
	string fragmentSize;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: Extract.exe <input file> <output file> <start position> <fragment size>\n";
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.startPosition = argv[3];
	args.fragmentSize = argv[4];
	// конвертация в size_t?
	// где отлавливать ошибки с размером?
	return args;
}

void Read()
{
	
	// читать порционно
}

bool Extract(const string& inputFileName, const string& outputFileName, const string& startPosition, const string& fragmentSize)
{
	// fragment size 
	// size position
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

	if (!args || !Extract(args->inputFileName, args->outputFileName, args->startPosition, args->fragmentSize))
	{
		return 1;
	}

	return 0;
}
