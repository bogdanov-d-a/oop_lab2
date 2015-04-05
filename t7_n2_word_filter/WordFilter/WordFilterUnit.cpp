#include "stdafx.h"
#include "WordFilterUnit.h"

using namespace std;

typedef function<void(char)> SendCharFunction;
typedef function<void(string const&)> SendStringFunction;

const set<char> WHITESPACE_SET = {
	' ', '\t', '\n', ':', ',', '-', '!', '.', '?', ';', '/', '\\',
	'%', '^', '*', '+', '=', '(', ')', '[', ']', '{', '}', '<', '>'
};

void FlushBuffer(string &buffer, SendStringFunction callback)
{
	if (!buffer.empty())
	{
		callback(buffer);
		buffer.clear();
	}
}

void SplitWords(istream &input, SendCharFunction whitespaceCallback, SendStringFunction wordCallback)
{
	string buffer;

	char curChar;
	while (input.get(curChar))
	{
		if (WHITESPACE_SET.find(curChar) != WHITESPACE_SET.cend())
		{
			FlushBuffer(buffer, wordCallback);
			whitespaceCallback(curChar);
		}
		else
		{
			buffer.push_back(curChar);
		}
	}

	FlushBuffer(buffer, wordCallback);
}

string ToLower(string const& str)
{
	string result;
	result.resize(str.length());
	transform(str.cbegin(), str.cend(), result.begin(), tolower);
	return result;
}

void FilterStream(istream &input, ostream &output, StringSet const& filterSet)
{
	SplitWords(input, [&output](char c){ output << c; },
		[&output, &filterSet](string const& str)
	{
		if (filterSet.find(ToLower(str)) == filterSet.cend())
		{
			output << str;
		}
	});
}
