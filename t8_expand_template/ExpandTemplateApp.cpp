// ExpandTemplateApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct
{
	size_t start;
	size_t end;
}
Range;

size_t GetRangeLength(Range const& range)
{
	assert(range.end >= range.start);
	return (range.end - range.start);
}

typedef std::map<std::string, std::string> ReplaceDict;

ReplaceDict::const_iterator TryFindKeySubstr(
	std::string const& src, Range const& srcRange, ReplaceDict const& map)
{
	for (size_t substrSize = GetRangeLength(srcRange); substrSize > 0; --substrSize)
	{
		const ReplaceDict::const_iterator foundResult =
			map.find(src.substr(srcRange.start, substrSize));

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

	Range buffer = {0, 0};
	std::string resultStr;

	while (buffer.end != tpl.length())
	{
		if (GetRangeLength(buffer) < maxBufferLength)
		{
			++buffer.end;
		}
		else
		{
			assert(GetRangeLength(buffer) == maxBufferLength);

			const ReplaceDict::const_iterator foundSubstrIter =
				TryFindKeySubstr(tpl, buffer, params);

			if (foundSubstrIter != params.cend())
			{
				resultStr += foundSubstrIter->second;
				buffer.start += foundSubstrIter->first.length();
			}
			else
			{
				resultStr.push_back(tpl[buffer.start]);
				++buffer.start;
			}
		}
	}

	ReplaceDict::const_iterator lastFoundIter;

	while (GetRangeLength(buffer) > 0 &&
		(lastFoundIter = TryFindKeySubstr(tpl, buffer, params)) != params.cend())
	{
		resultStr += lastFoundIter->second;
		buffer.start += lastFoundIter->first.length();
	}

	if (GetRangeLength(buffer) > 0)
	{
		resultStr += tpl.substr(buffer.start);
	}

	return resultStr;
}

void PrintUsage(const char programName[])
{
	std::cout << "Usage: " << programName <<
		"<input file> <output file> [<param> <value> [<param> <value> ...]]\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc % 2 == 0 || argc < 3)
	{
		assert(argc > 0);
		PrintUsage(argv[0]);
		return 1;
	}

	ReplaceDict dict;

	int srcArgInd, repArgInd;
	for (srcArgInd = 3, repArgInd = 4; repArgInd < argc; srcArgInd += 2, repArgInd += 2)
	{
		dict[argv[srcArgInd]] = argv[repArgInd];
	}

	std::string inFileName(argv[1]);
	std::string outFileName(argv[2]);

	std::ifstream inFileStream(inFileName);
	std::ofstream outFileStream(outFileName);

	std::string curStr;
	while (getline(inFileStream, curStr))
	{
		outFileStream << ExpandTemplate(curStr, dict);
	}

	return 0;
}
