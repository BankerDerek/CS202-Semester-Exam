#include <vector>

class Echo
{
    public:
        std::vector<float> applyModule(const std::vector<float>& input, float gain, int delay);
};
