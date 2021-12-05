//LowPassFilter.cpp file
#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include "LowPassFilter.h"
#include <iostream>
#include <vector>
using namespace std;

vector<double> LowPassFilter::lowPassVector(vector<double> waveOriginal){
    sample = delaySignal(waveOriginal, delay);
    for(int i=0; i < sizeof(waveOriginal); i++){
        finalWave[i] = multiply(waveOriginal[i], sample[i], gain);
        finalWave[i] = add(waveOriginal[i], finalWave[i]);
    }
    return finalWave;
}  

vector<double> delaySignal(vector<double> waveOriginal, int delay){
    vector<double> delayedSignal;
    for(int i=0; i < sizeof(waveOriginal); i++){
        if(i < delay){
            delayedSignal[i]=0;
        }
        delayedSignal[i+delay] = waveOriginal[i];
    }
}

double multiply(double currentWave, double sample, int gain){
    return currentWave*(sample*gain);
}    

double add(double originalWave, double currentWave){
    return originalWave + currentWave;
}    

/*
void LowPassFilter::setSample(vector<double> newSample){
    sample = newSample;
}
*/

void LowPassFilter::setGain(int newGain){
    gain = newGain;
}

void LowPassFilter::setDelay(int newDelay){
    delay = newDelay;
}
    

#endif