#include <vector>
#ifndef ECHO_H
#define ECHO_H

///Class for Echo
///
/**Class that holds a function that adds an echo effect to a sound file. The Function takes in a vector and then passes each element in the vector through a process. The process
        looks at if the iteration is greater then the preset delay value. If the iteration is greater than the delay variable, the value entered
        in the output vector is the original value in a specific vector location multiplied by the gain variable. */
class Echo
{
    public:
        ///Function adds an Echo
        /// Takes in a vector and changes values to give the resulting sound an echo
        /// @param input is the original vector
        /// @param gain is the predetermined value to be multiplied with vector elements that are chosen to produce and echo
        /// @param delay is the amount of vector spaces chosen to reinsert a value to produce the echo
        std::vector<float> applyModule(const std::vector<float>& input, float gain, int delay);
};

#endif