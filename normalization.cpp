//by Sultan
//normalization.cpp

#include "Normalization.h"

//Finds the largest value in the data
void Normalization::findMaxVal(std::vector<float> data){
    largestValue = 0;
    for(unsigned int i = 0; i < data.size(); i++){
        if(largestValue < data[i]){
            largestValue = data[i];
        }
    }
    //return largestValue;
}
//Find the multiplier using the largest value
void Normalization::findMultiplier(){
    multiplier = 1 / largestValue;
    //return multiplier;
}
//Multiplies all the values in the data by the multiplier value to Normalize the data
std::vector<float> Normalization::normalizeData(std::vector<float> data){
    findMaxVal(data);
    findMultiplier();
    for(unsigned int i = 0; i < data.size(); i++){
        modifiedData[i] = data[i] * multiplier;
    }
    return modifiedData;
}

