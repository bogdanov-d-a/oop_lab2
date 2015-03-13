// WordStat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CWordStat.h"

void GenerateWordStat(std::istream &istream, CWordStat::Dict &dict)
{
	CWordStat wordStat(dict);

	char tmpChar;
	while (istream.get(tmpChar))
	{
		wordStat.SendChar(tmpChar);
	}
}

void PrintWordStat(CWordStat::Dict const& dict, std::ostream &ostream)
{
	std::for_each(dict.cbegin(), dict.cend(),
		[&ostream](CWordStat::Dict::value_type dictValue)
		{
			ostream << dictValue.first << " " << dictValue.second << "\n";
		});
}

int _tmain(int argc, _TCHAR* argv[])
{
	CWordStat::Dict dict;
	GenerateWordStat(std::cin, dict);
	PrintWordStat(dict, std::cout);

	return 0;
}
