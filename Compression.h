//Connor Riche
//Compression.cpp file

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <vector>

class Compression{
private:
    int compFactor = 2;
    std::vector<float> finalData;
public:
    std::vector<float> compressData(std::vector<float> waveOriginal);
    void setCompFactor(int newFactor);
};

#endif