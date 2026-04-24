#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../HTMLDecode/HTMLDecode.h"

using namespace std;

TEST_CASE("HTMLDecode test: empty string")
{
	string inputStr = "";
	string outputStr = "";
	CHECK(HtmlDecode(inputStr) == outputStr);
}

TEST_CASE("HTMLDecode test quotes")
{
	string inputStr = "&quot;Hello&quot;";
	string outputStr = "\"Hello\"";
	CHECK(HtmlDecode(inputStr) == outputStr);
}

TEST_CASE("HTMLDecode test: apostrophe and ampersand")
{
	string inputStr = "M&amp;M&apos;s";
	string outputStr = "M&M's";
	CHECK(HtmlDecode(inputStr) == outputStr);
}

TEST_CASE("HTMLDecode test: less and greater")
{
	string inputStr = "&lt;tag&gt;";
	string outputStr = "<tag>";
	CHECK(HtmlDecode(inputStr) == outputStr);
}

TEST_CASE("HTMLDecode test: multiple ampersand")
{
	string inputStr = "&&&&&&quot;&&&&amp; Meow &&&&&quot;";
	string outputStr = "&&&&&\"&&&& Meow &&&&\"";
	CHECK(HtmlDecode(inputStr) == outputStr);
}

TEST_CASE("HTMLDecode test: html")
{
	string inputStr = "&lt;!DOCTYPE html&gt;&lt;html&gt;&lt;body&gt;&lt;/body&gt;&lt;/html&gt;";
	string outputStr = "<!DOCTYPE html><html><body></body></html>";
	CHECK(HtmlDecode(inputStr) == outputStr);
}