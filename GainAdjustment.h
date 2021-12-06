//Connor Riche
//GainAdjustment.h file

#ifndef GAINADJUSTMENT_H
#define GAINADJUSTMENT_H

#include <vector>

class GainAdjustment{
private:
    float adjustNumber;
public:
    std::vector<float> adjustVector(std::vector<float> waveOriginal);
    float adjustment(float value);
    void setAdjustNumber(float adjust);
};

#endif