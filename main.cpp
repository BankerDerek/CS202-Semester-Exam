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

main(int argc, char *argv[])
{
    // Class initializations
    WavFileIO audioFile;
    LowPassFilter low_pass_filter;
    GainAdjustment gain_adjustment;
    Normalization normalization; 
    // Compression compression;
    Echo echo;

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
    // cout << "\t5 : Compression" << endl;

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
            audioFile.setSoundDataRight(normalization.normalizeData(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(normalization.normalizeData(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(normalization.normalizeData(audioFile.getSoundDataLeft()));
        }
        break;

    case '2': // Echo
        cout << "Selected: Echo" << endl;
        float gain;
        int delay;

        cout << "Please provide a gain > 1." << endl;
        while (true)
        {
            cout << "Gain: ";
            cin >> userInput;
            if (atof(userInput) < 1)
            {
                gain = atof(userInput);
                break;
            }
        }
        cout << "Please provide a delay in miliseconds" << endl;
        while (true)
        {
            cout << "delay: ";
            cin >> userInput;
            if (atoi(userInput) > 0)
            {
                delay = atoi(userInput);
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
        cout << "Selected: GainAdjustment" << endl;
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
        cout << "Selected: LowPassFilter" << endl;
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

    // case '5': // Compression
    //     cout << "Selected: Compression" << endl;
    //     if (audioFile.getNumberOfChannels() == 1)
    //     {
    //         audioFile.setSoundDataRight(compression.applyModule(audioFile.getSoundDataRight()));
    //     }
    //     else
    //     {
    //         audioFile.setSoundDataRight(compression.applyModule(audioFile.getSoundDataRight()));
    //         audioFile.setSoundDataLeft(compression.applyModule(audioFile.getSoundDataLeft()));
    //     }
    //     break;

    
    default:
        break;
    }


    
}
