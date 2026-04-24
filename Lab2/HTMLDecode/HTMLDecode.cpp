#include "HTMLDecode.h"

const Symbol QUOTES = { "&quot;", '\"' };
const Symbol APOSTROPHE = { "&apos;", '\'' };
const Symbol LESS = { "&lt;", '<' };
const Symbol GREATER = { "&gt;", '>' };
const Symbol AMPERSAND = { "&amp;", '&' };

const Symbol Symbols[] = { QUOTES, APOSTROPHE, LESS, GREATER, AMPERSAND };

const char START_DECODE = '&';


char DecodeSymbol(std::string const& str, size_t& pos)
{
	for (auto symbol: Symbols)
	{
		if (str.compare(pos, symbol.code.size(), symbol.code) == 0)
		{
			pos += symbol.code.size();
			return symbol.character;
		}
	}
	pos++;

	return str[pos - 1];
}

std::string HtmlDecode(std::string const& html)
{
	std::string result;
	size_t i = 0;

	while (i < html.length()) 
	{
		if (html[i] == START_DECODE)
		{
			result += DecodeSymbol(html, i);
		}
		else
		{
			result += html[i];
			i++;
		}
	}

	return result;
}
