#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "waveHeader.h"

class WavFileIO
{
    private:
        std::string filePath;                    // Holds the provided file path

        struct WaveHeader waveHeader;           // Holds the file header

        std::vector<double> soundDataRight;      // Right channel audio data in stereo, also used if mono
        std::vector<double> soundDataLeft;       // Left channel audio data in stereo


    public:
        bool validateFile(std::string inputFilePath);

        bool ingestFile (std::string inputFilePath);

        int getNumberOfChannels();

        // Sets and Gets for the audio channels 
        std::vector<double> getSoundDataRight();
        std::vector<double> getSoundDataLeft();
        void setSoundDataRight (std::vector<double> inputData);
        void setSoundDataLeft (std::vector<double> inputData);

        void printHeader();
};