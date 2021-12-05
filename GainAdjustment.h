//GainAdjustment.h file
#include <iostream>
#include <vector>
using namespace std;

class GainAdjustment{
private:
    double adjustNumber;
public:
    vector<double> adjustVector(vector<double> waveOriginal);
    double adjustment(double value, double adjustNumber);
    void setAdjustNumber(double adjust);
};
