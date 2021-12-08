//Connor Riche
//GainAdjustment.cpp file

#include "GainAdjustment.h"
#include <vector>


std::vector<float> GainAdjustment::adjustVector(std::vector<float> waveOriginal){
        std::vector<float> finalWave;
        for(int i=0; i < sizeof(waveOriginal); i++){
            finalWave.push_back(adjustment(waveOriginal[i]));
        }
        return finalWave;
    }

    

float GainAdjustment::adjustment(float value){
        return value * adjustNumber;
    }    

void GainAdjustment::setAdjustNumber(float adjust){
        adjustNumber = adjust;
    }    

