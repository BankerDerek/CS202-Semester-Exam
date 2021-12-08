#ifndef WAVFILEIO_H
#define WAVFILEIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "waveHeader.h"
#include "WavFileIO.h"


std::string filePath;                   //< Holds the provided file path

struct WaveHeader waveHeader;           //< Holds the file header

std::vector<float> soundDataRight;     //< Right channel audio data in stereo, also used if mono
std::vector<float> soundDataLeft;      //< Left channel audio data in stereo

/// Makes sure the file is valid
/** Returns true if the file exists and has a ".wav" extension at the end */
/// @param "string inputFilePath" Contains the location of the file to validate
/// @return Returns the state of the file. 
bool WavFileIO::validateFile(std::string inputFilePath)
{
    std::ifstream infile(inputFilePath);
    if (!infile.good())
    {
        std::cout << "\tERROR: File does not exist or cannot open." << std::endl;
        return false; 
    }
    if (inputFilePath.substr(inputFilePath.find_last_of(".") + 1).compare("wav") != 0)
    {
        std::cout << "\tERROR: File does not have \".wav\" extension." << std::endl;
        return false; 
    }
    return true;
}

bool WavFileIO::ingestFile (std::string inputFilePath)
{
    // Checks if the file exists and has a ".wav" extension
    if (!WavFileIO::validateFile(inputFilePath))
    {
        return false; 
    }

    filePath = inputFilePath;     

    // Opens the file
    std::ifstream file(inputFilePath, std::ios::binary | std::ios::in);

    short* buffer;

    if (file.is_open())
    {
        file.read((char*)&waveHeader, sizeof(waveHeader));

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
        return true;
    }
    std::cout << "\tERROR: could not open file." << std::endl;
    return false;
}

bool WavFileIO::validateName(std::string providedName)
{
    char nonValidCharacter[] = {'<','>',':','"','/','\\','|','?','*'};
    for (int i = 0; i < providedName.length(); i++)
    {
        for (int j = 0; j < sizeof(nonValidCharacter); j++)
        {
            if (providedName[i] == nonValidCharacter[j])
            {
                return false;
            }
        }
    }
    return true;
}

std::string WavFileIO::constructName(std::string providedName)
{
    return filePath.substr(0,filePath.find_last_of("\\") + 1) + providedName + ".wav";
}

float WavFileIO::maxElement(std::vector<float> input)
{
    float result = input[0];
    for (int i = 1; i < input.size(); i++)
    {
        if (fabs(result) < fabs(input[i]))
        {
            result = input[i];
        }
    }
    return result;
}

void WavFileIO::updateHeader()
{
    waveHeader.sample_alignment = soundDataRight.size();
    waveHeader.data_bytes = waveHeader.sample_alignment * waveHeader.bit_depth;
}

bool WavFileIO::exportFile(std::string intendedFileName)
{
    std::ofstream result(constructName(intendedFileName), std::ios::out | std::ios::binary);
    if (result.is_open())
    {
        updateHeader();

        if (waveHeader.num_channels == 1)
        {
            short* buffer;

            if (waveHeader.bit_depth == 8)
            {
                float maxValue = maxElement(soundDataRight);
                for (int i = 0; i < soundDataRight.size(); i++)
                {
                    soundDataRight[i] = soundDataRight[i] / maxValue;
                    buffer[i] = (short) soundDataRight[i] * INT_FAST8_MAX;
                }
            }
            if (waveHeader.bit_depth == 16)
            {
                float maxValue = maxElement(soundDataRight);
                for (int i = 0; i < soundDataRight.size(); i++)
                {
                    soundDataRight[i] = soundDataRight[i] / maxValue;
                    buffer[i] = (short) soundDataRight[i] * INT_FAST16_MAX;
                }
            }

            result.write((char*) &waveHeader, sizeof(waveHeader));
            result.write((char*) &buffer, waveHeader.data_bytes);
        }
        if (waveHeader.num_channels == 2)
        {
            short* bufferRight;
            short* bufferLeft;

            if (waveHeader.bit_depth == 8)
            {
                float maxValueRight = maxElement(soundDataRight);
                for (int i = 0; i < soundDataRight.size(); i++)
                {
                    soundDataRight[i] = soundDataRight[i] / maxValueRight;
                    bufferRight[i] = (short) soundDataRight[i] * INT_FAST8_MAX;
                }
                float maxValueLeft = maxElement(soundDataLeft);
                for (int i = 0; i < soundDataLeft.size(); i++)
                {
                    soundDataLeft[i] = soundDataLeft[i] / maxValueLeft;
                    bufferLeft[i] = (short) soundDataLeft[i] * INT_FAST8_MAX;
                }
            }
            if (waveHeader.bit_depth == 16)
            {
                float maxValueRight = maxElement(soundDataRight);
                for (int i = 0; i < soundDataRight.size(); i++)
                {
                    soundDataRight[i] = soundDataRight[i] / maxValueRight;
                    bufferRight[i] = (short) soundDataRight[i] * INT_FAST16_MAX;
                }
                float maxValueLeft = maxElement(soundDataLeft);
                for (int i = 0; i < soundDataLeft.size(); i++)
                {
                    soundDataLeft[i] = soundDataLeft[i] / maxValueLeft;
                    bufferLeft[i] = (short) soundDataLeft[i] * INT_FAST16_MAX;
                }
            }

            result.write((char*) &waveHeader, sizeof(waveHeader));
            result.write((char*) &bufferRight, waveHeader.data_bytes / 2);
            result.write((char*) &bufferLeft, waveHeader.data_bytes / 2);
        }
     
        result.close();
        return true;
    }
    return false;
 }

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

std::string WavFileIO::assembleString(char input[])
{
    std::string result;
    for (int i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        std::cout << input[i]; 
    }
    return result;
} 

void WavFileIO::printHeader()
{
    std::cout << "riff_header: " << assembleString(waveHeader.riff_header) << std::endl;

    std::cout << "wav_size: " << waveHeader.wav_size << std::endl;       
    std::cout << "wave_header: " << waveHeader.wave_header << std::endl;      

    std::cout << "fmt_header: " << assembleString(waveHeader.fmt_header) << std::endl;      
    std::cout << "fmt_chunk_size: " << waveHeader.fmt_chunk_size << std::endl;      
    std::cout << "audio_format: " << waveHeader.audio_format << std::endl;      
    std::cout << "num_channels: " << waveHeader.num_channels << std::endl;      
    std::cout << "sample_rate: " << waveHeader.sample_rate << std::endl;      
    std::cout << "byte_rate: " << waveHeader.byte_rate << std::endl;      
    std::cout << "sample_alignment: " << waveHeader.sample_alignment << std::endl;      
    std::cout << "bit_depth: " << waveHeader.bit_depth << std::endl;      

    std::cout << "data_header: " << assembleString(waveHeader.data_header)<< std::endl;      
    std::cout << "data_bytes: " << waveHeader.data_bytes << std::endl;
    std::cout << std::endl;
}
#endif


// C:\TEMP\yes-16-bit-mono.wav