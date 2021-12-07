//Sultonbek Kholmatov
//Normalization.cpp file

#include "Normalization.h"

std::vector<float> Normalization::normalize(std::vector<float> inputData){
	float largestValue = 0;
	float multiplier;
	std::vector<float> normalizedData;

	for(int i = 0; i < inputData.size(); i++){
		if(largestValue < inputData[i]){
			largestValue = inputData[i];
		}
	}

	multiplier = 1 / largestValue;

	for(int i = 0; i < inputData.size(); i++){
		normalizedData.push_back(inputData[i] * multiplier);
	}
	return normalizedData;
}
