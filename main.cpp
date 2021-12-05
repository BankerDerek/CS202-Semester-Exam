#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <ctype.h>

#include "LowPassFilter.h"      // Connor
#include "GainAdjustment.h"     // Connor
#include "Normalization.h"      // Sultan
// #include "Compression.h"        // Sultan
#include "Echo.h"               // Derek

#include "waveHeader.h"         // Header struct
#include "WavFileIO.h"          // File IO class

using namespace std;


main(int argc, char *argv[])
{
    // Class initializations
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
