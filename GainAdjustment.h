//GainAdjustment.h file
#include <iostream>
#include <vector>
using namespace std;

class GainAdjustment{
private:
    int adjustNumber;
public:
    vector<double> adjustVector(vector<double> waveOriginal);
    double adjustment(double value, int adjustNumber);
    void setAdjustNumber(int adjust);
};
