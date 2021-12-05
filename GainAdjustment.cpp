//Connor Riche
//GainAdjustment.cpp file
#ifndef GAINADJUSTMENT_H
#define GAINADJUSTMENT_H
#include "GainAdjustment.h"
#include <iostream>
#include <vector>


std::vector<float> GainAdjustment::adjustVector(std::vector<float> waveOriginal){
        std::vector<float> finalWave;
        for(int i=0; i < sizeof(waveOriginal); i++){
            finalWave[i] = adjustment(waveOriginal[i], adjustNumber);
        }
        return finalWave;
    }

    

float GainAdjustment::adjustment(float value, float adjustNumber){
        return value * adjustNumber;
    }    

void GainAdjustment::setAdjustNumber(float adjust){
        adjustNumber = adjust;
    }    

#endif
