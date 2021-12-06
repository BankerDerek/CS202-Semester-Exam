#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "waveHeader.h"         // Header struct
#include "WavFileIO.h"          // File IO class

#include "LowPassFilter.h"      // Connor
#include "GainAdjustment.h"     // Connor
#include "Normalization.h"      // Sultan
#include "Compression.h"        // Sultan
#include "Echo.h"               // Derek

using namespace std;

main(int argc, char *argv[])
{
    // Class initializations
    WavFileIO audioFile;
    LowPassFilter low_pass_filter;
    GainAdjustment gain_adjustment;
    Normalization normalization; 
    Compression compression;
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
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(normalization.applyModule(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(normalization.applyModule(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(normalization.applyModule(audioFile.getSoundDataLeft()));
        }
        break;

    case '2': // Echo
        //TODO parameter input
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(echo.applyModule(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(echo.applyModule(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(echo.applyModule(audioFile.getSoundDataLeft()));
        }
        break;

    case '3':
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(gain_adjustment.applyModule(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(gain_adjustment.applyModule(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(gain_adjustment.applyModule(audioFile.getSoundDataLeft()));
        }
        break;

    case '4':
        if (audioFile.getNumberOfChannels() == 1)
        {
            audioFile.setSoundDataRight(low_pass_filter.applyModule(audioFile.getSoundDataRight()));
        }
        else
        {
            audioFile.setSoundDataRight(low_pass_filter.applyModule(audioFile.getSoundDataRight()));
            audioFile.setSoundDataLeft(low_pass_filter.applyModule(audioFile.getSoundDataLeft()));
        }
        break;

    // case '5':
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
