#ifndef WAVFILEIO_H
#define WAVFILEIO_H

#include <vector>

#include "Echo.h"

std::vector<float> Echo::applyModule(const std::vector<float>& input, float gain, int delay)
{
    std::vector<float> result;
    result.reserve(input.size());
    for (int i = 0; i < input.size(); i++)
    {
        if (i > delay)
        {
            result.push_back(input[i] + gain*result[i - delay]);
        }
        else
        {
            result.push_back(input[i]);
        }
    }
    return result;
}
#endif