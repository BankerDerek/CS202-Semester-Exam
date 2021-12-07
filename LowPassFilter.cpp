//Connor Riche
//LowPassFilter.cpp file
#include "LowPassFilter.h"
#include <iostream>
#include <vector>

std::vector<float> LowPassFilter::lowPassVector(std::vector<float> waveOriginal){
    sample = delaySignal(waveOriginal);
    for(int i=0; i < sizeof(waveOriginal); i++){
        finalWave[i] = multiply(waveOriginal[i], sample[i]);
        finalWave[i] = multGain(finalWave[i]);
        finalWave[i] = add(waveOriginal[i], finalWave[i]);
    }
    return finalWave;
}  

std::vector<float> LowPassFilter::delaySignal(std::vector<float> waveOriginal){
    std::vector<float> delayedSignal;
    for(int i=0; i < sizeof(waveOriginal); i++){
        if(i < delay){
            delayedSignal[i]=0;
        }
        delayedSignal[i+delay] = waveOriginal[i];
    }
    return delayedSignal;
}

float LowPassFilter::multiply(float currentWave, float currentSample){
    return currentWave*(currentSample*gain);
}    

float LowPassFilter::multGain(float currentWave){
    return currentWave * gain;
}

float LowPassFilter::add(float originalWave, float currentWave){
    return originalWave + currentWave;
}    

/*
void LowPassFilter::setSample(std::vector<float> newSample){
    sample = newSample;
}
*/

void LowPassFilter::setGain(float newGain){
    gain = newGain;
}

void LowPassFilter::setDelay(float newDelay){
    delay = newDelay;
}
    

