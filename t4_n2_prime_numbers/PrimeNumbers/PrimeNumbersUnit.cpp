#include "stdafx.h"
#include "PrimeNumbersUnit.h"

void PrimeNumbers::FillBitVector(BitVector &bitVector, bool fillBit, size_t count)
{
	assert(bitVector.empty());
	bitVector.reserve(count);
	for (size_t i = 0; i < count; ++i)
	{
		bitVector.push_back(fillBit);
	}
}

size_t PrimeNumbers::Sqr(size_t a)
{
	return a * a;
}

void PrimeNumbers::GenerateWithEratosthenesSieve(size_t upperBound, BitVector &bitVector)
{
	assert(upperBound > 1);
	assert(bitVector.empty());

	FillBitVector(bitVector, true, upperBound - 1);
	size_t maxLookupValue = static_cast<size_t>(sqrt(upperBound));

	for (size_t lookupValue = 2; lookupValue <= maxLookupValue; ++lookupValue)
	{
		if (bitVector[lookupValue - 2])
		{
			for (size_t deleteValue = Sqr(lookupValue); deleteValue <= upperBound; deleteValue += lookupValue)
			{
				bitVector[deleteValue - 2] = false;
			}
		}
	}
}

PrimeNumbers::NumberSet PrimeNumbers::GeneratePrimeNumbersSet(Number upperBound)
{
	if (upperBound > 1)
	{
		BitVector primeNumberBitVector;
		GenerateWithEratosthenesSieve(upperBound, primeNumberBitVector);

		NumberSet primeNumberSet;
		for (size_t index = 0; index < primeNumberBitVector.size(); ++index)
		{
			if (primeNumberBitVector[index])
			{
				primeNumberSet.insert(index + 2);
			}
		}

		primeNumberBitVector.clear();
		return primeNumberSet;
	}
	else
	{
		return NumberSet();
	}
}
