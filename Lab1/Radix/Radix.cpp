#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	int inputRadix;
	int outputRadix;
	string number;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	int inputRadix, outputRadix;
	if (argc != 4)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: Radix.exe <input radix> <output radix> <number>\n";
		return nullopt;
	}

	try
	{
		inputRadix = stoi(argv[1]);
		outputRadix = stoi(argv[2]);
	}
	catch (const std::invalid_argument&)
	{
		cout << "Radix must be number\n";
		return nullopt;
	}

	Args args;
	args.inputRadix = inputRadix;
	args.outputRadix = outputRadix;
	args.number = argv[3];
	return args;
}

bool IsValidRadix(int radix)
{
	if (radix >= 2 && radix <= 36)
	{
		return true;
	}
	return false;
}

class NumberParsingError : public std::runtime_error
{
public:
	explicit NumberParsingError(char ch)
	: runtime_error(std::string("Invalid character ") + ch + '\n')
		, m_char(ch)
	{}
	char GetChar() const
	{
		return m_char;
	}

private:
	char m_char;
};

int CharToDigit(char ch, int radix)
{
	int digit = 0;

	if (ch >= '0' && ch <= '9')
	{
		digit = ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		digit = ch - 'A' + 10;
	}

	if (digit > radix - 1)
	{
		throw NumberParsingError(ch);
	}

	return digit;
}

int StringToInt(const string& str, int radix) 
{
	int result = 0;
	int digit = 0;
	bool sign = false;

	size_t length = str.length();

	if (!IsValidRadix(radix))
	{
		throw std::out_of_range("Invalid input radix\n");
	}

	for (size_t i = 0; i < length; i++)
	{
		if (i == 0 && str[i] == '-')
		{
			sign = true;
			continue;
		}

		digit = CharToDigit(str[i], radix);

		if (result > (INT_MAX - digit) / radix)
		{
			throw std::out_of_range("Overflow\n");
		}

		result = result * radix + digit;
	}

	if (sign)
	{
		result = -result;
	}

	return result;
}

char DigitToChar(int digit)
{
	char ch;
	if (digit < 10)
	{
		ch = '0' + digit;
	}
	else
	{
		ch = 'A' + digit - 10;
	}
	return ch;
}

string IntToString(int n, int radix)
{
	string number;
	int remainder;
	bool isNegative = false;

	if (!IsValidRadix(radix))
	{
		throw std::out_of_range("Invalid output radix\n");
	}

	if (n < 0)
	{
		n = -n;
		isNegative = true;
	}

	while (n > 0)
	{
		remainder = n % radix;
		number = number + DigitToChar(remainder);
		n = n / radix;
	}

	if (isNegative)
	{
		number += '-';
	}

	reverse(number.begin(), number.end());
	return number;
}

string Convert(int sourceRadix, int destinationRadix, const string& number)
{
	int n = StringToInt(number, sourceRadix);
	return IntToString(n, destinationRadix);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	try
	{
		string outputNumber = Convert(args->inputRadix, args->outputRadix, args->number);
		cout << outputNumber << '\n';
	}
	catch (const std::exception& e)
	{
		cout << e.what();
		return 1;
	}

	return 0;
}
