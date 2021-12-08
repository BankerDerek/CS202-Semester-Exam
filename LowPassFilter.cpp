//Connor Riche
//Sultonbek Kholmatov
//LowPassFilter.cpp file

#include "LowPassFilter.h"

std::vector<float> LowPassFilter::lowPassVector(std::vector<float> waveOriginal){
	sample = delaySignal(waveOriginal);
	for(int i = 0; i < waveOriginal.size(); i++){
		finalWave.push_back(multiply(waveOriginal[i], sample[i]));
		finalWave.push_back(add(waveOriginal[i], finalWave[i]));
	}
	return finalWave;
}  

std::vector<float> LowPassFilter::delaySignal(std::vector<float> waveOriginal){
	std::vector<float> delayedSignal;
	for(int i = 0; i < waveOriginal.size(); i++){
		if(i < delay){
			delayedSignal.push_back(0);
		}
	i = i + delay;
	delayedSignal.push_back(waveOriginal[i]);
	}
	return delayedSignal;
}

float LowPassFilter::multiply(float currentWave, float currentSample){
	return currentWave * (currentSample * gain);
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