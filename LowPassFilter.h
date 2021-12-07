//Connor Riche
//LowPassFilter.h file
#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include <iostream>
#include <vector>

///Class that contains a low pass filter
/**The class contains a function that conducts running a vector of data through a low pass filter. It does this by multiplying the original 
 * vector by a slightly delayed version of that vector. It then runs the resulting vector through a gain and then recombines the modified vector with 
 * the original vector. */
class LowPassFilter{
private:
    std::vector<float> finalWave;
    std::vector<float> sample;
    float gain = 1;
    float delay = 1;
public:
    ///Runs a wave through a low pass filter
    ///Takes a vector and modifies it based on a low pass filter diagram. This involves multiplying the wave by the delayed version of itself and adding it back to the original wave.
    /// @param waveOriginal is the inputed wave in the form of a vector
    /// @returns a vector of the wave that has passed throught the entire low pass filter
    std::vector<float> lowPassVector(std::vector<float> waveOriginal);

    ///Creates the delayed sample
    ///Function that takes in the original wave vector and delays it by a predetermined amount. The wave is then returned to be used in the low pass filter.
    /// @param waveOriginal is the original wave that is to be turned into a delayed sample
    /// @returns a vector that holds the delayed sample
    /// @note the delay can be modified for different results using the getter for the "delay" variable
    std::vector<float> delaySignal(std::vector<float> waveOriginal);

    ///Multiplication in low pass filter
    ///Multiplies the delayed sample of the vector by the original vector
    /// @param currentWave is a value from the original form of the vector
    /// @param currentSample is the value from the version of the vector that has been delayed by a certain amount
    /// @returns the next value for the next version of the vector that is ready to by multiplied by the gain
    float multiply(float currentWave, float currentSample);

    ///Multiplication of filter gain
    ///Multiplies the vector in the state it is in within the low pass filter by the predetermined gain
    /// @param currentWave is the iterated place value in the vector currently in one of the branches of the low pass filter
    /// @returns a float value of the multiplied value with the gain variable
    /// @note the "gain" variable can be changed around by a setter for different results
    float multGain(float currentWave);

    ///Addition of heavily modified values to the original values
    ///Multiplies the value from the vector that went through the delay sample and the gain with a value from the original vector
    /// @param originalWave is a value from the unedited vector
    /// @param currentWave is the value from the modified vector
    float add(float originalWave, float currentWave);

    //void setSample(vector<double> newSample);

    ///Sets a new gain value
    ///Takes in a value and replaces the value held by the "gain" variable
    /// @param newGain holds the new value for gain to be assigned
    /// @param returns void
    void setGain(float newGain);

    ///Sets a new delay value
    ///Takes in a value and replaces the value held by the "delay" variable
    /// @param newDelay holds the new value for delay to be assigned
    /// @param returns void
    void setDelay(float newDelay);
};

#endif