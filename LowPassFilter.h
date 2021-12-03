//LowPassFilter.h file
#include <iostream>
#include <vector>
#include "AudioModule.h"
using namespace std;

class LowPassFilter : AudioModule {
private:
    vector<double> sample;
    int gain;
public:
    vector<double> lowPassVector(vector<double> waveOriginal);
    double multiply(double currentWave, double sample, int gain);
    double add(double originalWave, double currentWave);
    void setSample(vector<double> newSample);
    void setGain(int newGain);
};
