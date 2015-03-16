// WordFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordFilterUnit.h"

void ReadStreamWordsToSet(std::istream &istream, WordFilter::StringSet &set)
{
	assert(set.empty());
	WordFilter::SplitWords(istream, [](char c){},
		[&set](std::string const& str){ set.insert(WordFilter::ToLower(str)); });
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		assert(argc > 0);
		std::cout << "Usage: " << argv[0] << " <blacklist file>\n";
		return 1;
	}

	std::ifstream blacklistFileStream(argv[1]);
	if ((blacklistFileStream.rdstate() & std::ifstream::failbit) != 0)
	{
		std::cout << "Blacklist file open error\n";
		return 2;
	}

	WordFilter::StringSet filterSet;
	ReadStreamWordsToSet(blacklistFileStream, filterSet);

	WordFilter::FilterText(std::cin, std::cout, filterSet);
	return 0;
}
