//Connor Riche
//Compression.cpp file
#include "Compression.h"

std::vector<float> Compression::compressData(std::vector<float> waveOriginal){
    int j = 0;
    for(int i = 0; i < sizeof(waveOriginal); i + compFactor){
        finalData[j] = waveOriginal[i];
        j = j + 1;       
    }
    return finalData;
}

void Compression::setCompFactor(int newFactor){
    compFactor = newFactor;
}