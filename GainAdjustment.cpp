//GainAdjustment.cpp file
#ifndef GAINADJUSTMENT_H
#define GAINADJUSTMENT_H
#include "GainAdjustment.h"
#include <iostream>
#include <vector>
using namespace std;

vector<double> GainAdjustment::adjustVector(vector<double> waveOriginal){
        vector<double> finalWave;
        for(int i=0; i < sizeof(waveOriginal); i++){
            finalWave[i] = adjustment(waveOriginal[i], adjustNumber);
        }
        return finalWave;
    }

    

double GainAdjustment::adjustment(double value, int adjustNumber){
        return value * adjustNumber;
    }    

void GainAdjustment::setAdjustNumber(int adjust){
        adjustNumber = adjust;
    }    

#endif
