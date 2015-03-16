// WordFilterTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../WordFilter/WordFilterUnit.h"

std::string FilterString(std::string const& str,
	WordFilter::StringSet const& filterSet)
{
	std::istringstream scrStream(str);
	std::ostringstream targStream;
	WordFilter::FilterText(scrStream, targStream, filterSet);
	return targStream.str();
}

BOOST_AUTO_TEST_CASE(EmptyString)
{
	BOOST_CHECK_EQUAL(FilterString("", { "bad" }), "");
}

BOOST_AUTO_TEST_CASE(NoMatches)
{
	BOOST_CHECK_EQUAL(FilterString("some random words", { "bad" }), "some random words");
}

BOOST_AUTO_TEST_CASE(OneMatch)
{
	BOOST_CHECK_EQUAL(FilterString("bad random words", { "bad" }), " random words");
}

BOOST_AUTO_TEST_CASE(CaseInsensitiveMatches)
{
	BOOST_CHECK_EQUAL(FilterString("BAD bad BaD bAD", { "bad" }), "   ");
}

BOOST_AUTO_TEST_CASE(MultipleMatches)
{
	BOOST_CHECK_EQUAL(FilterString("bad random words", { "bad", "words" }), " random ");
}
