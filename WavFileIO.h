#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "waveHeader.h"

/// Handles all the input and output of the wav files
/** Is responsible for input and output of the files as well as data storage */
class WavFileIO
{
    private:
        std::string filePath;                   ///< Holds the provided file path

        struct WaveHeader waveHeader;           ///< Holds the file header

        std::vector<float> soundDataRight;      ///< Right channel audio data in stereo, also used if mono
        std::vector<float> soundDataLeft;       ///< Left channel audio data in stereo


    public:
        bool validateFile(std::string inputFilePath);

        bool ingestFile (std::string inputFilePath);

        bool validateName(std::string providedName);

        std::string constructName(std::string providedName);

        float maxElement(std::vector<float> input);
        void updateHeader();
        bool exportFile(std::string intendedFileName);

        // Gets the sample rate
        int getSampleRate();

        // Gets number of channels
        int getNumberOfChannels();

        // Sets and Gets for the audio channels 
        std::vector<float> getSoundDataRight();
        std::vector<float> getSoundDataLeft();
        void setSoundDataRight (std::vector<float> inputData);
        void setSoundDataLeft (std::vector<float> inputData);

        std::string assembleString(char input[]);
        void printHeader();
};