// PrimeNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrimeNumbersUnit.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		assert(argc > 0);
		printf("Usage: %s <upper bound>\n", argv[0]);
		return 1;
	}

	try
	{
		PrimeNumbers::NumberSet primeNumberSet = PrimeNumbers::GeneratePrimeNumbersSet(std::stoi(argv[1]));
		std::for_each(primeNumberSet.cbegin(), primeNumberSet.cend(),
			[](PrimeNumbers::Number a){ std::cout << a << " "; });
		return 0;
	}
	catch (std::invalid_argument const& e)
	{
		(void)e;
		puts("Incorrect upper bound format");
		return 2;
	}
}
