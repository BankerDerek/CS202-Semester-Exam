//Connor Riche
//GainAdjustment.h file
#include <vector>

class GainAdjustment{
private:
    float adjustNumber;
public:
    std::vector<float> adjustVector(std::vector<float> waveOriginal);
    float adjustment(float value);
    void setAdjustNumber(float adjust);
};
