// ExtraSpaceRemoverTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../ExtraSpaceRemover/RemoveExtraSpacesMachine.h"

bool CheckConversion(std::string const& in, std::string const& out)
{
	return CRemoveExtraSpacesMachine::RemoveExtraSpaces(in) == out;
}

bool StringDoesNotChange(std::string const& a)
{
	return CheckConversion(a, a);
}

BOOST_AUTO_TEST_CASE(SpacelessString)
{
	BOOST_CHECK(StringDoesNotChange("no-spaces-here"));
}

BOOST_AUTO_TEST_CASE(ModerateSpacesString)
{
	BOOST_CHECK(StringDoesNotChange("moderate spaces here"));
}

BOOST_AUTO_TEST_CASE(WideSpacesString)
{
	BOOST_CHECK(CheckConversion("wide      spaces                here", "wide spaces here"));
}

BOOST_AUTO_TEST_CASE(SpacesOnStart)
{
	BOOST_CHECK(CheckConversion("     str", "str"));
}

BOOST_AUTO_TEST_CASE(SpacesOnEnd)
{
	BOOST_CHECK(CheckConversion("str     ", "str"));
}

BOOST_AUTO_TEST_CASE(MixedString)
{
	BOOST_CHECK(CheckConversion("     too   much     data   to remove         ", "too much data to remove"));
}
