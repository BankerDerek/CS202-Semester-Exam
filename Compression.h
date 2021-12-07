//Connor Riche
//Compression.cpp file

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <vector>

///The compression class compresses a sound file
///
/**The class takes a vector with the data from a sound file and compresses it. 
It does this by taking certain, evenly spaced data points and putting them into a new vector.
By essentially removing a lot of data points, the sound file becomes smaller and so, compressed. */
class Compression{
private:
    int compFactor = 2;
    std::vector<float> finalData;
public:
    ///Compress the vector
    ///Returns a smaller vector the original vector was compressed into
    ///@param waveOriginal vector taken in is the original vector representing the sound file
    ///@returns a vector made up of the data points the function narrowed the original vector down to
    ///@note how much the vector is compressed to is determined by the compFactor variable, a factor of two (the default) cuts the vector in half
    std::vector<float> compressData(std::vector<float> waveOriginal);

    ///This is a setter designed to change the variable compFactor
    ///Changes the variable used to dictate how much the given vector in the comprss Data class is compressed by
    /// @param newFactor is the intiger value replacing the compFactor variable
    /// @returns void
    void setCompFactor(int newFactor);
};

#endif