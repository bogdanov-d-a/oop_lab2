#include "stdafx.h"
#include "VectorProcessor.h"

void ProcessVector(std::vector<double> &vector)
{
	if (!vector.empty())
	{
		double vectorMultiplier = *std::min_element(vector.begin(), vector.end()) *
			*std::max_element(vector.begin(), vector.end());

		std::transform(vector.begin(), vector.end(), vector.begin(),
			[vectorMultiplier](double value){ return ((value < 0) ? value * vectorMultiplier : value); });
	}
}
