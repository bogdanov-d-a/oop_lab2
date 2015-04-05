// WordFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordFilterUnit.h"

using namespace std;

StringSet ReadStreamWordsToSet(istream &input)
{
	StringSet result;
	SplitWords(input, [](char c){},
		[&result](string const& str){ result.insert(ToLower(str)); });
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		assert(argc > 0);
		cout << "Usage: " << argv[0] << " <blacklist file>\n";
		return 1;
	}

	ifstream blacklistFileStream(argv[1]);
	if ((blacklistFileStream.rdstate() & ifstream::failbit) != 0)
	{
		cout << "Blacklist file open error\n";
		return 2;
	}

	FilterStream(cin, cout, ReadStreamWordsToSet(blacklistFileStream));
	return 0;
}
