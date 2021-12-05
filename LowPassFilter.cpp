//LowPassFilter.cpp file
#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include "LowPassFilter.h"
#include <iostream>
#include <vector>
using namespace std;

vector<double> LowPassFilter::lowPassVector(vector<double> waveOriginal){
    sample = delaySignal(waveOriginal);
    for(int i=0; i < sizeof(waveOriginal); i++){
        finalWave[i] = multiply(waveOriginal[i], sample[i]);
        finalWave[i] = add(waveOriginal[i], finalWave[i]);
    }
    return finalWave;
}  

vector<double> LowPassFilter::delaySignal(vector<double> waveOriginal){
    vector<double> delayedSignal;
    for(int i=0; i < sizeof(waveOriginal); i++){
        if(i < delay){
            delayedSignal[i]=0;
        }
        delayedSignal[i+delay] = waveOriginal[i];
    }
    return delayedSignal;
}

double LowPassFilter::multiply(double currentWave, double sample){
    return currentWave*(sample*gain);
}    

double LowPassFilter::add(double originalWave, double currentWave){
    return originalWave + currentWave;
}    

/*
void LowPassFilter::setSample(vector<double> newSample){
    sample = newSample;
}
*/

void LowPassFilter::setGain(double newGain){
    gain = newGain;
}

void LowPassFilter::setDelay(double newDelay){
    delay = newDelay;
}
    

#endif
