// ExpandTemplateApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct
{
	size_t start;  // inclusive
	size_t end;  // not inclusive
}
Range;

size_t GetRangeLength(Range const& range)
{
	assert(range.end >= range.start);
	return (range.end - range.start);
}

typedef std::map<std::string, std::string> ReplaceDict;

ReplaceDict::const_iterator FindLongestPrefixInMapKeys(
	std::string const& src, Range const& srcRange, ReplaceDict const& map)
{
	for (size_t prefixLength = GetRangeLength(srcRange); prefixLength > 0; --prefixLength)
	{
		const ReplaceDict::const_iterator foundResult =
			map.find(src.substr(srcRange.start, prefixLength));

		if (foundResult != map.cend())
		{
			return foundResult;
		}
	}

	return map.cend();
}

size_t FindMaxKeyLength(ReplaceDict const& map)
{
	const ReplaceDict::const_iterator maxKeyLengthIter =
		std::max_element(map.cbegin(), map.cend(),
		[](ReplaceDict::value_type a, ReplaceDict::value_type b)
	{
		return (a.first.length() < b.first.length());
	});

	assert(maxKeyLengthIter != map.cend());
	return maxKeyLengthIter->first.length();
}

size_t Min(size_t a, size_t b)
{
	return ((a <= b) ? a : b);
}

std::string ExpandTemplate(std::string const& tpl, ReplaceDict const& params)
{
	if (params.empty())
	{
		return tpl;
	}

	const size_t maxBufferLength = FindMaxKeyLength(params);

	if (maxBufferLength == 0)
	{
		return tpl;
	}

	std::string resultStr;
	Range buffer = { 0, 0 };

	while (buffer.end != tpl.length() || GetRangeLength(buffer) > 0)
	{
		buffer.end = Min(tpl.length(), buffer.start + maxBufferLength);
		assert(GetRangeLength(buffer) > 0);
		assert(GetRangeLength(buffer) <= maxBufferLength);

		const ReplaceDict::const_iterator foundPrefixIter =
			FindLongestPrefixInMapKeys(tpl, buffer, params);

		if (foundPrefixIter != params.cend())
		{
			resultStr += foundPrefixIter->second;
			buffer.start += foundPrefixIter->first.length();
		}
		else
		{
			resultStr.push_back(tpl[buffer.start]);
			++buffer.start;
		}
	}

	return resultStr;
}

bool ArgumentAmountIsCorrect(int argc)
{
	return (argc % 2 != 0 && argc >= 3);
}

void ForEachArgumentPair(int argc, _TCHAR* argv[],
	std::function<void(const char a[], const char b[])> statement)
{
	assert(ArgumentAmountIsCorrect(argc));

	int aIndex, bIndex;
	for (aIndex = 3, bIndex = 4; bIndex < argc; aIndex += 2, bIndex += 2)
	{
		statement(argv[aIndex], argv[bIndex]);
	}
}

bool NotifyAboutFileOpenError(std::ios const& stream, const char msg[])
{
	const bool fileOpenError = ((stream.rdstate() & std::ios::failbit) != 0);

	if (fileOpenError)
	{
		std::cout << msg << "\n";
	}

	return fileOpenError;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (!ArgumentAmountIsCorrect(argc))
	{
		assert(argc > 0);
		std::cout << "Usage: " << argv[0] <<
			"<input file> <output file> [<param> <value> [<param> <value> ...]]\n";
		return 1;
	}

	ReplaceDict dict;
	ForEachArgumentPair(argc, argv,
		[&dict](const char a[], const char b[]){ dict[a] = b; });

	std::ifstream inFile(static_cast<std::string>(argv[1]));
	if (NotifyAboutFileOpenError(inFile, "Input file open error"))
	{
		return 2;
	}

	std::ofstream outFile(static_cast<std::string>(argv[2]));
	if (NotifyAboutFileOpenError(outFile, "Output file open error"))
	{
		return 3;
	}

	std::string curStr;
	while (getline(inFile, curStr))
	{
		outFile << ExpandTemplate(curStr, dict) << "\n";
	}

	return 0;
}
