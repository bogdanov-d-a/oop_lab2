// PrimeNumbersTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../PrimeNumbers/PrimeNumbersUnit.h"

bool RunTest(PrimeNumbers::Number upperBound, PrimeNumbers::NumberSet const& primeNumberSet)
{
	return (PrimeNumbers::GeneratePrimeNumbersSet(upperBound) == primeNumberSet);
}

BOOST_AUTO_TEST_CASE(EmptySet)
{
	BOOST_CHECK(RunTest(1, PrimeNumbers::NumberSet()));
}

BOOST_AUTO_TEST_CASE(UpToHundred)
{
	BOOST_CHECK(RunTest(100, {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
		43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
	}));
}
