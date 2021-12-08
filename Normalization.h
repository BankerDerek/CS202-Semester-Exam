//Sultonbek Kholmatov
//Normalization.h file

#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include <vector>

///The Normalization class normalizes a sound file
///
///The class takes a vector with the data from a sound file and normalizes it.
///It does this by finding the largest value in the data which is used to find a constant value. Then every single value in the data is multiplied by that constant value.
///This will essentially normalize the audio file by maximizing the amplitude of the final waveform.
class Normalization{
private:
	float largestValue = 0;
	float multiplier;
	std::vector<float> normalizedData;
public:
	///Normalize the vector
	///
	///Returns a normalized vector by taking in
	///@param inputData vector of floats which represents the original sound data
	///@returns a vector normalized version of the original
	std::vector<float> normalize(std::vector<float> inputData);
};

#endif //NORMALIZATION_H
