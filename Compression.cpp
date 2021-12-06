#include "Compression.h"

std::vector<float> Compression::compressData(std::vector<float> original){
    for(unsigned int i = 0; i < original.size(); i++){
        compressedData[i] = original[i] * rate;
    }
    return compressedData;
}