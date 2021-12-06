#ifndef WAVFILEIO_H
#define WAVFILEIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "waveHeader.h"
#include "WavFileIO.h"


std::string filePath;                   // Holds the provided file path

struct WaveHeader waveHeader;           // Holds the file header

std::vector<float> soundDataRight;     // Right channel audio data in stereo, also used if mono
std::vector<float> soundDataLeft;      // Left channel audio data in stereo

/// Makes sure the file is valid
///
/// Returns true if the file exists and has a ".wav" extension at the end
/// @param "string inputFilePath" Contains the location of the file to validate
/// @return Returns the state of the file. 
bool WavFileIO::validateFile(std::string inputFilePath)
{
    std::ifstream infile(inputFilePath);
    return (infile.good() && inputFilePath.substr(inputFilePath.find_last_of(".") + 1) == "wav");
}

bool WavFileIO::ingestFile (std::string inputFilePath)
{
    // Checks if the file exists and has a ".wav" extension
    if (!WavFileIO::validateFile(inputFilePath))
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

// std::string WavFileIO::constructName(std)


// Get's the sample rate
int WavFileIO::getSampleRate()
{
    return waveHeader.sample_rate;
}

// Gets the number of audio channels
int WavFileIO::getNumberOfChannels()
{
    return waveHeader.num_channels;
}

// Sets and Gets for the audio channels 
std::vector<float> WavFileIO::getSoundDataRight() 
{
    return soundDataRight;
}
std::vector<float> WavFileIO::getSoundDataLeft() 
{
    return soundDataLeft;
}
void WavFileIO::setSoundDataRight (std::vector<float> inputData)
{
    soundDataRight.clear();
    soundDataRight = inputData;
}
void WavFileIO::setSoundDataLeft (std::vector<float> inputData)
{
    soundDataLeft.clear();
    soundDataLeft = inputData;
}

void WavFileIO::printHeader()
{
    std::cout << "riff_header: " << waveHeader.riff_header[0] << waveHeader.riff_header[1] << waveHeader.riff_header[2] << waveHeader.riff_header[3] << std::endl;
    std::cout << "wav_size: " << waveHeader.wav_size << std::endl;       
    std::cout << "wave_header: " << waveHeader.wave_header << std::endl;      

    std::cout << "fmt_header: " << waveHeader.fmt_header[0] << waveHeader.fmt_header[1] << waveHeader.fmt_header[2] << waveHeader.fmt_header[3] << std::endl;      
    std::cout << "fmt_chunk_size: " << waveHeader.fmt_chunk_size << std::endl;      
    std::cout << "audio_format: " << waveHeader.audio_format << std::endl;      
    std::cout << "num_channels: " << waveHeader.num_channels << std::endl;      
    std::cout << "sample_rate: " << waveHeader.sample_rate << std::endl;      
    std::cout << "byte_rate: " << waveHeader.byte_rate << std::endl;      
    std::cout << "sample_alignment: " << waveHeader.sample_alignment << std::endl;      
    std::cout << "bit_depth: " << waveHeader.bit_depth << std::endl;      

    std::cout << "data_header: " << waveHeader.data_header[0] << waveHeader.data_header[1] << waveHeader.data_header[2] << waveHeader.data_header[3] << std::endl;      
    std::cout << "data_bytes: " << waveHeader.data_bytes << std::endl;
}
#endif