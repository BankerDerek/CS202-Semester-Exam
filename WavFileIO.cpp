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

/// Reads in the files data
/** Parses the provided files headed data to the waveHeader struct and stores the sound data in vector<float>s depending on how many channels. */
/// @param "string inputFilePath" Contains the location of the file to validate
/// @return Returns the state of the operation. 
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

        // Reads the sound data from single channel files
        if (waveHeader.num_channels == 1)
        {
            // Reads the sound data from 8 bit files
            if (waveHeader.bit_depth == 8)
            {
                for (int i = 0; i < waveHeader.data_bytes / waveHeader.sample_alignment; i++ )
                {
                    soundDataRight.push_back((float)buffer[i] / INT_FAST8_MAX);
                }
            }
            // Reads the sound data from 16 bit files
            if (waveHeader.bit_depth == 16)
            {
                for (int i = 0; i < waveHeader.data_bytes / waveHeader.sample_alignment; i++ )
                {
                    soundDataRight.push_back((float)buffer[i] / INT_FAST16_MAX);
                }
            }
        }
        // Reads the sound data from dual channel files
        else
        {
            // Reads the sound data from 8 bit files
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
            // Reads the sound data from 16 bit files
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

/// Makes sure the attempted file name is valid
/** Scans the attempted file name for any invald characters. */
/// @param "string providedName" Is the name the the user is attempting to provide.
/// @return Returns the state of providedName.
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

/// Creates the string for the file location
/** Takes the file name off the original file path and adds the new name and the ".wav" extension. */
/// @param "string providedName" Is the name the user has provided.
/// @return Returns the string of the export file path.
std::string WavFileIO::constructName(std::string providedName)
{
    return filePath.substr(0,filePath.find_last_of("\\") + 1) + providedName + ".wav";
}

/// Finds the max element in a given vector<float>
/** Finds the max element in a given vector<float> by comparing the abs of all items  */
/// @param "vector<float> input" the vector to be examined.
/// @return Returns the largest item
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

/// Updates the header to new channel sizes.
void WavFileIO::updateHeader()
{
    waveHeader.sample_alignment = soundDataRight.size();
    waveHeader.data_bytes = waveHeader.sample_alignment * waveHeader.bit_depth;
}

/// Exports the updated sound data to a file
/** Takes the provided name and exports the header and sound data to the file */
/// @note it doesn't actually work, I tried so hard, it makes the file it just doesn't have any data somehow.
/// @param "string intendedFileName" The the name of the resulting file.
/// @return Returns the state of the opperation.
bool WavFileIO::exportFile(std::string intendedFileName)
{
    // Opens the file to write to
    std::ofstream result(constructName(intendedFileName), std::ios::out | std::ios::binary);
    if (result.is_open())
    {
        updateHeader();

        // Handles single channel files
        if (waveHeader.num_channels == 1)
        {
            short* buffer;

            // Handles 8 bit files
            if (waveHeader.bit_depth == 8)
            {
                float maxValue = maxElement(soundDataRight);
                for (int i = 0; i < soundDataRight.size(); i++)
                {
                    soundDataRight[i] = soundDataRight[i] / maxValue;
                    buffer[i] = (short) soundDataRight[i] * INT_FAST8_MAX;
                }
            }
            // Handles 16 bit files
            if (waveHeader.bit_depth == 16)
            {
                float maxValue = maxElement(soundDataRight);
                for (int i = 0; i < soundDataRight.size(); i++)
                {
                    soundDataRight[i] = soundDataRight[i] / maxValue;
                    buffer[i] = (short) soundDataRight[i] * INT_FAST16_MAX;
                }
            }

            // The final writing to the file
            result.write((char*) &waveHeader, sizeof(waveHeader));
            result.write((char*) &buffer, waveHeader.data_bytes);
        }
        // Handles dual channel files
        if (waveHeader.num_channels == 2)
        {
            short* bufferRight;
            short* bufferLeft;

            /// Handles 8 bit files
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
            // Handles 16 bit files
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

            // The final writing to the file
            result.write((char*) &waveHeader, sizeof(waveHeader));
            result.write((char*) &bufferRight, waveHeader.data_bytes / 2);
            result.write((char*) &bufferLeft, waveHeader.data_bytes / 2);
        }
     
        result.close();
        return true;
    }
    return false;
 }

/// Get's the sample rate
int WavFileIO::getSampleRate()
{
    return waveHeader.sample_rate;
}

/// Gets the number of audio channels
int WavFileIO::getNumberOfChannels()
{
    return waveHeader.num_channels;
}

/// Gets the right channel data 
std::vector<float> WavFileIO::getSoundDataRight() 
{
    return soundDataRight;
}
/// Gets the left channel data 
std::vector<float> WavFileIO::getSoundDataLeft() 
{
    return soundDataLeft;
}
/// Sets the right channel data 
void WavFileIO::setSoundDataRight (std::vector<float> inputData)
{
    soundDataRight.clear();
    soundDataRight = inputData;
}
/// Sets the left channel data 
void WavFileIO::setSoundDataLeft (std::vector<float> inputData)
{
    soundDataLeft.clear();
    soundDataLeft = inputData;
}


/// Converts a char[] into a string
/// @note This does throw a warning because of "sizeof" but that is accounted for and can be ignored.
/// @param "char input[]" The provided char array.
/// @return returns a string with the elements of input[].
std::string WavFileIO::assembleString(char input[])
{
    std::string result;
    for (int i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {
        std::cout << input[i]; 
    }
    return result;
} 

/// Simply prints the data in waveHeader to the console
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
