//LowPassFilter.cpp file
#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include "LowPassFilter.h"
#include <iostream>
#include <vector>
using namespace std;

vector<double> LowPassFilter::lowPassVector(vector<double> waveOriginal){
    vector<double> finalWave;
    for(int i=0; i < sizeof(waveOriginal); i++){
        finalWave[i] = multiply(waveOriginal[i], sample[i], gain);
        finalWave[i] = add(waveOriginal[i], finalWave[i]);
    }
    return finalWave;
}   

double LowPassFilter::multiply(double currentWave, double sample, int gain){
    return currentWave*(sample*gain);
}    

double LowPassFilter::add(double originalWave, double currentWave){
    return originalWave + currentWave;
}    

void LowPassFilter::setSample(vector<double> newSample){
    sample = newSample;
}

void LowPassFilter::setGain(int newGain){
    gain = newGain;
}
    

#endif