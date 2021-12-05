//GainAdjustment.h file
#include <iostream>
#include <vector>

class GainAdjustment{
private:
    float adjustNumber;
public:
    std::vector<float> adjustVector(std::vector<float> waveOriginal);
    float adjustment(float value, float adjustNumber);
    void setAdjustNumber(float adjust);
};
