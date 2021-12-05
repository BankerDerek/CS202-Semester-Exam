#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <utility>

#include "LowPassFilter.h"      // Connor
#include "GainAdjustment.h"     // Connor
// #include "Normalization.h"      // Sultan
// #include "Compression.h"        // Sultan
#include "Echo.h"               // Derek

#include "waveHeader.h"         // Header struct

using namespace std;

class WavFileIO
{
    private:
        string filePath;                    // Holds the provided file path
        
        struct WaveHeader waveHeader;       // Holds the file header

        vector<double> soundDataRight;      // Right channel audio data in stereo, also used if mono
        vector<double> soundDataLeft;       // Left channel audio data in stereo

        bool mono;                          // True if file is mono

        


    public: 
        WavFileIO ()
        {}

        bool ingestFile (string inputFilePath)
        {
            // Checks if the file exists and has a ".wav" extension
            if (!validateFile(inputFilePath))
            {
                return false; 
            }    

            // Opens the file
            std::ifstream file(inputFilePath, std::ios::binary | std::ios::in);

            short* buffer;
            if (file.is_open())
            {
                file.read((char*)&waveHeader, sizeof(waveHeader));

                if (waveHeader.riff_header != "RIFF")
                {
                    return false;
                } 

                buffer = new short[waveHeader.data_bytes];
                file.read((char*)buffer, waveHeader.data_bytes);

                if (waveHeader.num_channels == 1)
                {
                    if (waveHeader.bit_depth == 8)
                    {
                        for (int i = 0; i < waveHeader.data_bytes / waveHeader.sample_alignment; i++ )
                        {
                            soundDataRight.push_back((float)buffer[i] / INT_FAST8_MAX);
                        }
                    }
                    if (waveHeader.bit_depth == 16)
                    {
                        for (int i = 0; i < waveHeader.data_bytes / waveHeader.sample_alignment; i++ )
                        {
                            soundDataRight.push_back((float)buffer[i] / INT_FAST16_MAX);
                        }
                    }
                }
                else
                {
                    if (waveHeader.bit_depth == 8)
                    {
                        for (int i = 0; i < (waveHeader.data_bytes / waveHeader.sample_alignment) / 2; i++ )
                        {
                            soundDataRight.push_back((float)buffer[i] / INT_FAST8_MAX);
                        }
                        for (int i = (waveHeader.data_bytes / waveHeader.sample_alignment) / 2; i < waveHeader.data_bytes / waveHeader.sample_alignment; i++ )
                        {
                            soundDataLeft.push_back((float)buffer[i] / INT_FAST8_MAX);
                        }
                    }
                    if (waveHeader.bit_depth == 16)
                    {
                        for (int i = 0; i < (waveHeader.data_bytes / waveHeader.sample_alignment) / 2; i++ )
                        {
                            soundDataRight.push_back((float)buffer[i] / INT_FAST16_MAX);
                        }
                        for (int i = (waveHeader.data_bytes / waveHeader.sample_alignment) / 2; i < waveHeader.data_bytes / waveHeader.sample_alignment; i++ )
                        {
                            soundDataLeft.push_back((float)buffer[i] / INT_FAST16_MAX);
                        }
                    }
                }
                
                delete buffer;
                file.close();   
            }
            return false;
        }

        

        
        // Sets and Gets for the audio channels 
        vector<double> getSoundDataRight() 
        {
            return soundDataRight;
        }
        vector<double> getSoundDataLeft() 
        {
            return soundDataLeft;
        }
        void setSoundDataRight (vector<double> inputData)
        {
            soundDataRight.clear();
            soundDataRight = inputData;
        }
        void setSoundDataLeft (vector<double> inputData)
        {
            soundDataLeft.clear();
            soundDataLeft = inputData;
        }

        void printHeader()
        {
            cout << "riff_header: " << waveHeader.riff_header[0] << waveHeader.riff_header[1] << waveHeader.riff_header[2] << waveHeader.riff_header[3] << endl;
            cout << "wav_size: " << waveHeader.wav_size << endl;       
            cout << "wave_header: " << waveHeader.wave_header << endl;      

            cout << "fmt_header: " << waveHeader.fmt_header[0] << waveHeader.fmt_header[1] << waveHeader.fmt_header[2] << waveHeader.fmt_header[3] << endl;      
            cout << "fmt_chunk_size: " << waveHeader.fmt_chunk_size << endl;      
            cout << "audio_format: " << waveHeader.audio_format << endl;      
            cout << "num_channels: " << waveHeader.num_channels << endl;      
            cout << "sample_rate: " << waveHeader.sample_rate << endl;      
            cout << "byte_rate: " << waveHeader.byte_rate << endl;      
            cout << "sample_alignment: " << waveHeader.sample_alignment << endl;      
            cout << "bit_depth: " << waveHeader.bit_depth << endl;      

            cout << "data_header: " << waveHeader.data_header[0] << waveHeader.data_header[1] << waveHeader.data_header[2] << waveHeader.data_header[3] << endl;      
            cout << "data_bytes: " << waveHeader.data_bytes << endl;
        }

        bool validateFile(string inputFilePath)
        {
            std::ifstream infile(inputFilePath);
            return (infile.good() && inputFilePath.substr(inputFilePath.find_last_of(".") + 1) == "wav");
        }




}; 

main(int argc, char *argv[])
{
    // Class inintalizations
    WavFileIO audioFile;
    
    
    // Intoduction
    cout << endl << "Initializing Audio Editor..." << endl;
    
    // Asks the user to open the menu or quit
    char* userInput;
    cout << "Type 'e' to exit the program. Type 'm' to go to the menu" << endl;
    while (true)
    {
        cout << "\tInput: ";
        cin >> userInput;

        if (userInput[0] == 'e')
        {
            cout << "\tExiting program..." << endl;
            return 0;
        }    
        if (userInput[0] == 'm')
        {
            cout << endl << "Entering Menu..." << endl;
            break;
        }
        cout << "\tInvalid input. Please try again" << endl;
    }

    // Asks for file and checks if valid
    cout << "Please provide the path of the file you wish to load." << endl;
    while (true)
    {
        cout << "\tFile path: ";
        cin >> userInput;
        // cout << "UserInput: \"" << userInput << "\"" << endl;
        if (audioFile.ingestFile(userInput))
        {
            cout << "\tFile loaded successfully." << endl << endl;
            break;
        }
        cout << endl << "\tFile failed to load. Please try a different file." << endl;
    }
    
    // Module selection
    cout << "Input the number of the module you would like to apply." << endl;
    cout << "\t1 : Normalization" << endl;
    cout << "\t2 : Echo" << endl;
    cout << "\t3 : GainAdjustment" << endl;
    cout << "\t4 : LowPassFilter" << endl;
    cout << "\t5 : Compression" << endl;

    


    
}
