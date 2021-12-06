#include <vector>
#ifndef ECHO_H
#define ECHO_H

class Echo
{
    public:
        std::vector<float> applyModule(const std::vector<float>& input, float gain, int delay);
};

#endif