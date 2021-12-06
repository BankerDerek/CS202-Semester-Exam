//Connor Riche
//LowPassFilter.h file
#include <iostream>
#include <vector>

class LowPassFilter{
private:
    std::vector<float> finalWave;
    std::vector<float> sample;
    float gain = 1;
    float delay = 1;
public:
    std::vector<float> lowPassVector(std::vector<float> waveOriginal);
    std::vector<float> delaySignal(std::vector<float> waveOriginal);
    float multiply(float currentWave, float currentSample);
    float add(float originalWave, float currentWave);
    //void setSample(vector<double> newSample);
    void setGain(float newGain);
    void setDelay(float newDelay);
};
