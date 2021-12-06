//by Sultan
//normalization.h

#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include <iostream>
#include <vector>

class Normalization{
    float largestValue = 0;
    float multiplier;
    std::vector<float> modifiedData;
public:
    void findMaxVal(std::vector<float> data);
    void findMultiplier();
    std::vector<float> normalizeData(std::vector<float> data);
};

#endif //NORMALIZATION_H
