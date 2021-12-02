#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

class FileIO
{
    private:
        vector<double> originalWavFile;
        vector<double> newWavFile;

        vector<string> metadata; 

        string filePath;


    public: 

        void importFile (string inputFilePath)
        {
            if (fileCheck(inputFilePath))
            {
                std::ifstream file(inputFilePath, std::ios::binary | std::ios::in);
                if (file.is_open())
                {
                    file.read((char))
                }
            }
            else 
            {
                
            }
        }

        void exportFile (string filePath, vector<string> metaData)
        {

        }

        vector<double> getOriginal() 
        {

        }

         vector<string> getMetaData ()
        {

        }


    private:
        bool fileCheck(string inputFilePath)
        {
            std::ifstream infile(inputFilePath);
            return (infile.good() && inputFilePath.substr(inputFilePath.find_last_of(".") + 1) == "wav");
        }




}; 

class AudioModule
{


};

    // Sultan
    class Normalization : AudioModule  
    {

    };

    // Derek
    class Echo : AudioModule  
    {

    };

    // Connor
    class GainAdjustment : AudioModule  
    {

    };

    // Connor
    class LowPassFilter : AudioModule  
    {

    };

    // Sultan
    class Compression : AudioModule  
    {

    };
