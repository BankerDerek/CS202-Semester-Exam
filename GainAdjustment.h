//GainAdjustment.h file
#include <iostream>
#include <vector>
#include "AudioModule.h"
using namespace std;

class GainAdjustment : AudioModule {
private:
    int adjustNumber;
public:
    vector<double> adjustVector(vector<double> waveOriginal);
    double adjustment(double value, int adjustNumber);
    void setAdjustNumber(int adjust);
};