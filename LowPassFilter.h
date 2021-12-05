//LowPassFilter.h file
#include <iostream>
#include <vector>
#include "AudioModule.h"
using namespace std;

class LowPassFilter : AudioModule {
private:
    vector<double> finalWave;
    vector<double> sample;
    int gain = 1;
    int delay = 1;
public:
    vector<double> lowPassVector(vector<double> waveOriginal);
    vector<double> delaySignal(vector<double> waveOriginal, int delay);
    double multiply(double currentWave, double sample, int gain);
    double add(double originalWave, double currentWave);
    //void setSample(vector<double> newSample);
    void setGain(int newGain);
    void setDelay(int newDelay);
};
