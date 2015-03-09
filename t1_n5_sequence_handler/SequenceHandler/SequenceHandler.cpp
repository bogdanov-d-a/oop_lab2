// SequenceHandler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VectorProcessor.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<double> numberVector(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	ProcessVector(numberVector);
	std::copy(numberVector.begin(), numberVector.end(), std::ostream_iterator<double>(std::cout, " "));

	return 0;
}
