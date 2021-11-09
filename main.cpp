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
        FileIO (string inputFilepath)
        {

        }
    
        vector<string> getMetaData ()
        {

        }

        void importFile ()
        {

        }

        void exportFile (vector<double> wavFileData, string filePath, vector<string> )
        {

        }
        vector<double> getOriginal() 
        {

        }
        


    private:
        bool fileCheck()
        {
            std::ifstream infile(filePath);
            return (infile.good() && filePath.substr(filePath.find_last_of(".") + 1) == "wav");
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
