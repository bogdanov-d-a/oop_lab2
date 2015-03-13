// WordStatTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../WordStat/CWordStat.h"

bool RunTest(std::string const& str, CWordStat::Dict const& dict)
{
	CWordStat::Dict result;
	CWordStat wordStat(result);

	for_each(str.cbegin(), str.cend(),
		[&wordStat](char c){ wordStat.SendChar(c); });

	wordStat.EndDataStream();
	return (result == dict);
}

BOOST_AUTO_TEST_CASE(EmptyString)
{
	BOOST_CHECK(RunTest("", CWordStat::Dict()));
}

BOOST_AUTO_TEST_CASE(OneWord)
{
	BOOST_CHECK(RunTest("word",
	{
		{ "word", 1 } 
	}));
}

BOOST_AUTO_TEST_CASE(DifferentWords)
{
	BOOST_CHECK(RunTest("word1 word2 word3",
	{
		{ "word1", 1 },
		{ "word2", 1 },
		{ "word3", 1 }
	}));
}

BOOST_AUTO_TEST_CASE(SameWordLowerCase)
{
	BOOST_CHECK(RunTest("hello hello hello hello hello",
	{
		{ "hello", 5 }
	}));
}

BOOST_AUTO_TEST_CASE(SameWordDifferentCase)
{
	BOOST_CHECK(RunTest("hellO HEllO hEllO hello HeLLo",
	{
		{ "hello", 5 }
	}));
}

BOOST_AUTO_TEST_CASE(MultipleWords)
{
	BOOST_CHECK(RunTest("HEllO world hEllO WORlD hello word HeLLo WORD",
	{
		{ "hello", 4 },
		{ "world", 2 },
		{ "word", 2 }
	}));
}
