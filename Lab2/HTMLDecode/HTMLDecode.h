#pragma once
#include <string>

struct Symbol
{
	std::string code;
	char character;
};


char DecodeSymbol(std::string const& str, size_t& pos);
std::string HtmlDecode(std::string const& html);
