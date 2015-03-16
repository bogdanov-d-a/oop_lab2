#include "stdafx.h"
#include "WordFilterUnit.h"

void WordFilter::SplitWords(std::istream &istream,
	SendCharFunction whitespaceCallback, SendStringFunction wordCallback)
{
	std::string buffer;

	char tmpChar;
	while (istream.get(tmpChar))
	{
		if (whitespaceSet.find(tmpChar) != whitespaceSet.cend())
		{
			FlushBuffer(buffer, wordCallback);
			whitespaceCallback(tmpChar);
		}
		else
		{
			buffer.push_back(tmpChar);
		}
	}

	FlushBuffer(buffer, wordCallback);
}

void WordFilter::FilterText(std::istream &istream,
	std::ostream &ostream, StringSet const& filterSet)
{
	SplitWords(istream, [&ostream](char c){ ostream << c; },
		[&ostream, &filterSet](std::string const& str)
	{
		if (filterSet.find(str) == filterSet.cend())
		{
			ostream << str;
		}
	}
	);
}

void WordFilter::FlushBuffer(std::string &buffer, SendStringFunction wordCallback)
{
	if (!buffer.empty())
	{
		wordCallback(buffer);
		buffer.clear();
	}
}
