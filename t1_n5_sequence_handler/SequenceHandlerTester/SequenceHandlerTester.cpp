// SequenceHandlerTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../SequenceHandler/VectorProcessor.h"

bool CheckVectorProcessing(std::vector<double> const& in, std::vector<double> const& out)
{
	std::vector<double> tmp(in);
	ProcessVector(tmp);
	return tmp == out;
}

bool VectorDoesNotChange(std::vector<double> const &a)
{
	return CheckVectorProcessing(a, a);
}

BOOST_AUTO_TEST_CASE(EmptyVectorProducesEmptyVector)
{
	BOOST_CHECK(VectorDoesNotChange({}));
}

BOOST_AUTO_TEST_CASE(VectorWithoutNegativesDoesntChangeContent)
{
	BOOST_CHECK(CheckVectorProcessing({ 4, 0, 3 }, { 0, 3, 4 }));
}

BOOST_AUTO_TEST_CASE(VectorWithOneNegativeElement)
{
	BOOST_CHECK(CheckVectorProcessing({ -1, 3 }, { 3, 3 }));
}

BOOST_AUTO_TEST_CASE(VectorWithSeveralNegativeElements)
{
	BOOST_CHECK(CheckVectorProcessing({ -1, -1, 2, -3 }, { 2, 6, 6, 18 }));
}
