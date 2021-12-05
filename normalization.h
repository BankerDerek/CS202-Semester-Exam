//by Sultan
//normalization.h

#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include <iostream>
#include <vector>

class Normalization{
	float largestValue = 0;
    float multiplier;
	std::vector<float> modefiedData;
public:
	float findMaxVal(std::vector<float>, float);
    float findMultiplier(float, float);
	std::vector<float> normalizeData(std::vector <float>, float);
};

#endif //NORMALIZATION_H