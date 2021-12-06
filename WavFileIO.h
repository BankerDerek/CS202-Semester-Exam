#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "waveHeader.h"

/// Handles all the input and output of the wav files
class WavFileIO
{
    private:
        std::string filePath;                    // Holds the provided file path

        struct WaveHeader waveHeader;           // Holds the file header

        std::vector<float> soundDataRight;      // Right channel audio data in stereo, also used if mono
        std::vector<float> soundDataLeft;       // Left channel audio data in stereo


    public:
        bool validateFile(std::string inputFilePath);

        bool ingestFile (std::string inputFilePath);

        std::string constructName(std::string providedName);

        // Gets the sample rate
        int getSampleRate();

        // Gets number of channels
        int getNumberOfChannels();

        // Sets and Gets for the audio channels 
        std::vector<float> getSoundDataRight();
        std::vector<float> getSoundDataLeft();
        void setSoundDataRight (std::vector<float> inputData);
        void setSoundDataLeft (std::vector<float> inputData);

        void printHeader();
};