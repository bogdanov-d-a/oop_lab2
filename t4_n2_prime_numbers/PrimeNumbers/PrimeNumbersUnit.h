#pragma once

namespace PrimeNumbers
{
	typedef std::vector<bool> BitVector;
	typedef int Number;
	typedef std::set<Number> NumberSet;

	void FillBitVector(BitVector &bitVector, bool fillBit, size_t count);
	size_t Sqr(size_t a);
	void GenerateWithEratosthenesSieve(size_t upperBound, BitVector &bitVector);
	NumberSet GeneratePrimeNumbersSet(Number upperBound);
}
