#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <iostream>
#include <vector>

const float rate = 1.2;

class Compression{
    std::vector<float> compressedData;
public:
    std::vector<float> compressData(std::vector<float>);
};

#endif //COMPRESSION_H