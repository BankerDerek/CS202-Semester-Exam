//Connor Riche
//GainAdjustment.h file

#ifndef GAINADJUSTMENT_H
#define GAINADJUSTMENT_H

#include <vector>

///Class to adjust data values by a constant
///
/** GainAdjustment class has a function that changes the data in a wave file. The class can adjust all the values in a data set by a certain amount
 * while keeping them all in proportion with each other. */
class GainAdjustment{
private:
    float adjustNumber = 3;
public:

    ///Adjusts each value in a data section 
    ///Takes a value from the vector and multiplies it by the variable holding the constant value the data set is being adjusted by
    /// @param waveOriginal is the vector holding the data from the wave file
    /// @returns a vector filled with the modified data
    /// @note The adjustment value can be changed with the setter function setAdjustNumber (default number is 3)
    std::vector<float> adjustVector(std::vector<float> waveOriginal);

    ///Multiplication function
    ///Function the adjustVector function uses to change each value. "adjustment" function takes single float value and multiplies it by the "adjust" value
    /// @param value is the specific value at the current location in the vector
    /// @returns the product of the data value and the adjustment value
    /// @note the variable "adjustNumber" can be changed by mentioned setter function
    float adjustment(float value);

    ///Sets a new adjustment value
    ///Takes in a value and replaces the value held by the "adjustNumber" variable
    /// @param adjust holds the new value for adjustNumber to be assigned
    /// @param returns void
    void setAdjustNumber(float adjust);
};

#endif