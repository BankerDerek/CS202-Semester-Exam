#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "waveHeader.h"         // Header struct
#include "WavFileIO.h"          // File IO class

#include "LowPassFilter.h"      // Connor
#include "GainAdjustment.h"     // Connor
#include "Normalization.h"      // Sultan
#include "Compression.h"        // Sultan
#include "Echo.h"               // Derek
#include "AudioProcessor.h"     //Connor

using namespace std;

int main()
{
    // Class initializations
    WavFileIO audioFile;
    Process low_pass_filter;
    Process gain_adjustment;
    Process normalization; 
    Process compression;
    Process echo;

    // Intoduction
    cout << endl << "Initializing Audio Editor..." << endl;
    
    // Asks the user to open the menu or quit
    string userInput;
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
        cout << "\tFile failed to load. Please try a different file." << endl;
    }
    
    // Module selection
    cout << "Input the number of the module you would like to apply." << endl;
    cout << "\t1 : Normalization" << endl;
    cout << "\t2 : Echo" << endl;
    cout << "\t3 : GainAdjustment" << endl;
    cout << "\t4 : LowPassFilter" << endl;
    cout << "\t5 : Compression" << endl;

    while (true)
    {
        cout << "\tUser Input: ";
        cin >> userInput;
        if (userInput[0] >= '1' && userInput[0] <= '5' )
        {
            break;
        }
        cout << endl << "\tInvalid Input. Please try again." << endl;
    }
    switch (userInput[0])
    {
    case '1': // Normalization
        cout << "Selected: Normalization" << endl;
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(normalization.normalize(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(normalization.normalize(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(normalization.normalize(audioFile.getSoundDataLeft()));
        }
        break;

    case '2': // Echo
        cout << endl << "\tSelected: Echo" << endl;
        float gain;
        int delay;

        cout << "Please provide a gain > 1." << endl;
        while (true)
        {
            cout << "Gain: ";
            cin >> userInput;
            if (stof(userInput) < 1)
            {
                gain = stof(userInput);
                break;
            }
        }
        cout << "Please provide a delay in miliseconds" << endl;
        while (true)
        {
            cout << "delay: ";
            cin >> userInput;
            if (stoi(userInput) > 0)
            {
                delay = stoi(userInput);
                break;
            }
        }

        delay = delay * (audioFile.getSampleRate() / 1000);


        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(echo.applyModule(audioFile.getSoundDataRight(),gain,delay));
        }
        else
        {
            audioFile.setSoundDataRight(echo.applyModule(audioFile.getSoundDataRight(),gain,delay));
            audioFile.setSoundDataLeft(echo.applyModule(audioFile.getSoundDataLeft(),gain,delay));
        }
        break;

    case '3': // GainAdjustment
        cout << endl << "\tSelected: GainAdjustment" << endl;
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(gain_adjustment.adjustVector(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(gain_adjustment.adjustVector(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(gain_adjustment.adjustVector(audioFile.getSoundDataLeft()));
        }
        break;

    case '4': // LowPassFilter
        cout << endl << "\tSelected: LowPassFilter" << endl;
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(low_pass_filter.lowPassVector(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(low_pass_filter.lowPassVector(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(low_pass_filter.lowPassVector(audioFile.getSoundDataLeft()));
        }
        break;

    case '5': // Compression
         cout << endl << "\tSelected: Compression" << endl;
         if (audioFile.getNumberOfChannels() == 1)
         {
             audioFile.setSoundDataRight(compression.compressData(audioFile.getSoundDataRight()));
         }
         else
         {
             audioFile.setSoundDataRight(compression.compressData(audioFile.getSoundDataRight()));
             audioFile.setSoundDataLeft(compression.compressData(audioFile.getSoundDataLeft()));
         }
         break;

    default:
        cout << "You somehow have reached this, it should be possible, but here you are." << endl;
        break;
    }
    cout << "\t Module application complete..." << endl << endl;

    cout << "Please provide a file name" << endl << "Note: file name cannot contain any of the following: \"<>,:/\\|?*\"" << endl;
    while (true)
    {
        cout << "\tFile name: ";
        cin >> userInput;
        if (audioFile.validateName(userInput))
        {
            cout << "\tExporting file to: \"" << audioFile.constructName(userInput) << "\"" << endl;
            break;
        }
    }
    if (audioFile.exportFile(userInput))
    {
        cout << "\tExport: SUCCESSFUL" << endl << "Exiting program...";
    }
    else
    {
        cout << "\tExport: FAILED" << endl << "Exiting program...";
    }

    return 1;
}
