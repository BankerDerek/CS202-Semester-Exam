//LowPassFilter.h file
#include <iostream>
#include <vector>
using namespace std;

class LowPassFilter{
private:
    vector<double> finalWave;
    vector<double> sample;
    double gain = 1;
    double delay = 1;
public:
    vector<double> lowPassVector(vector<double> waveOriginal);
    vector<double> delaySignal(vector<double> waveOriginal);
    double multiply(double currentWave, double sample);
    double add(double originalWave, double currentWave);
    //void setSample(vector<double> newSample);
    void setGain(double newGain);
    void setDelay(double newDelay);
};
