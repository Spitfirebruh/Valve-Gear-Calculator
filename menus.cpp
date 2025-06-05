/*
 * File: menus.cpp
 * Copyright 2025 Deaven S. Garcia
 * Author: Deaven Garcia (https://github.com/Spitfirebruh)
 * Created: 5/31/25
 * Last Updated: 6/4/25
 *
 * Description:
 *   Implements all menu‐driven user‐interaction routines for:
 *   - Calculator: choose between calculating now, manual input, file input, file output, or exit.
 *   - Help: show “Getting the right input values” or “Formatting files” info screens.
 *   - Input/Files/Settings: stub functions that display instructional text until fully implemented.
 *   - Saves: checks whether any outputs exist, and if so, calls commonFunctions::saveFile().
 *
 * Developer Note: Some code is duplicated across menus (e.g., stalling for “Enter anything to exit”),
 *               so future refactoring could DRY it up.
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "menus.h"
#include "common.h"
#include "maths.h"

 // The main calculator menu loop:
 // 1. Calculate → calls maths.breakItDown()
 // 2. Manual Input → calls maths.takeInputs()
 // 3. File Input → calls common.loadFile()
 // 4. File Output → calls saves()
 // 5. Exit → break loop
void Menu::calculator(commonFunctions& common, Maths& maths) {
    int input = 0;       // menu choice
    std::string input2; // Variable that handles error input.
    int loop = 1;        // continue flag

    while (loop == 1) {
        std::cout << "| Calculator |.\n"
            << "1. Calculate\n"
            << "2. Manual Input\n"
            << "3. File Input\n"
            << "4. File Output\n"
            << "5. Exit\n> ";
        std::cin >> input;
        common.handlingBadInput();
        switch (input) {
        case 1:
            maths.breakItDown(common, *this);
            common.clearPreviousLines(30);
            break;
        case 2:
            maths.takeInputs();
            common.clearPreviousLines(30);
            break;
        case 3:
            common.loadFile(maths);
            common.clearPreviousLines(30);
            break;
        case 4:
            saves(common, maths);
            break;
        case 5:
            common.clearPreviousLines(30);
            loop = 0;
            break;
        default:
            std::cout << "[Invalid option]\n"
                << "Please select one from the list using the number.\n"
                << "Enter anything to continue.\n> ";
            std::cin >> input2;
            common.handlingBadInput();
            common.clearPreviousLines(12);
            break;
        }
    }
}

// The Help menu loop:
// 1. Getting the right input values → calls inputs()
// 2. Formatting files → calls files()
// 3. Exit → break loop
void Menu::help(commonFunctions& common) {
    int input = 0;
    std::string input2; // Variable that handles error input.
    int loop = 1;
    common.clearPreviousLines(50);
    while (loop == 1) {
        std::cout << "| Help |.\n"
            << "1. Getting the right input values.\n"
            << "2. Formatting files for the calculator.\n"
            << "3. Program Info\n"
            << "4. Exit.\n> ";
        std::cin >> input;
        common.handlingBadInput();
        switch (input) {
        case 1:
            inputs(common);
            break;
        case 2:
            files(common);
            break;
        case 3:
            std::cout << "| Valve Gear Calculator |\n"
                << "[Program Information]\n"
                << "Version: 1.0\n"
                << "Date Published: 6/4/25\n"
                << "Language Standard: C++20\n\n"
                << "Developer: Deaven Garcia\n"
                << " - Github: https://github.com/Spitfirebruh\n"
                << " - Discord: spitfirebruh\n\n"
                << "Developer Note: Hi! Thanks for checking out my program, it's not the greatest, but I'm still learning C++,\n"
                << "    so it'll get better in the future (at the time of writing this I'm 9 months into C++).\n"
                << "   Hope you enjoy the program! Feel free to message me on discord for any suggestions or requests you have\n"
                << "    for this project, and any other projects in the future. :D\n\n"
                << "Copyright 2025 Deaven S. Garcia\n\n"
                << "Enter anything to exit.\n> ";
            std::cin >> input;
            common.handlingBadInput();
            common.clearPreviousLines(30);
            break;
        case 4:
            common.clearPreviousLines(30);
            loop = 0;
            break;
        default:
            std::cout << "[Invalid option]\n"
                << "Please select one from the list using the number.\n"
                << "Enter anything to continue.\n> ";
            std::cin >> input2;
            common.handlingBadInput();
            common.clearPreviousLines(12);
        }
    }
}

// Display detailed descriptions of each required input parameter.
// Wait for any user input to return.
void Menu::inputs(commonFunctions& common) {
    std::string input;
    std::cout
        << "--------------------------------------------------------------------------------------------------------\n"
        << "* Drive Wheel Diameter\n"
        << "  - Measured as the distance between rim to rim; listed on most blueprints as the 'driver'.\n"
        << "* Piston Stroke\n"
        << "  - Measured as distance the piston travels in one direction; listed on most blueprints as the 'stroke'.\n"
        << "* Bore\n"
        << "  - Measured as diameter of the cylinder the piston moves in; listed on most blueprints as the 'bore'.\n"
        << "* Lead\n"
        << "  - Measured as port opening at dead center; listed on most blueprints as a 'design tuning parameter'.\n"
        << "* Lap\n"
        << "  - Measured as how much the valve overlaps the port; not usually listed on blueprints.\n"
        << "* Valve Travel\n"
        << "  - Measured as the distance the valve travels; assumed most of the time to be between 5.5\" and 7.5\".\n"
        << "* Port Width\n"
        << "  - Measured as the width of the port; not often listed on blueprints, assumed between 16\" and 20\".\n"
        << "--------------------------------------------------------------------------------------------------------\n"
        << "Enter anything to Exit.\n> ";
    std::cin >> input;      // Pause until user hits a key
    common.handlingBadInput();
    common.clearPreviousLines(30);
}

// Placeholder “Files” menu: for future file‐format instructions.
// Waits for any user input to return.
void Menu::files(commonFunctions& common) {
    std::string input;
    std::cout
        << "File formatting is easy! Here's a mini tutorial on how to format your files and where to put them :)\n"
        << "1. Example of file format:\n"
        << "----------------------------\n"
        << "Drive Wheel Diameter: 66\n"
        << "Piston Stroke : 26\n"
        << "Bore : 20.5\n"
        << "Lead : 0.858\n"
        << "Lap : 3.39\n"
        << "Valve Travel : 5.5\n"
        << "Port Width : 18\n"
        << "----------------------------\n"
        << "Copy & pasting what's within the lines here should work just fine as a template for input files.\n\n"

        << "2. Example of file location:\n"
        << "----------------------------\n"
        << "<DIR> Valve Gear Calculator\n"
        << "    | valvegearcalculator.exe\n"
        << "    | <DIR> inputs\n"
        << "        | inputs.txt \n"
        << "    | <DIR> outputs\n"
        << "----------------------------\n"
        << "Where \"inputs.txt\" is found here is where you should place your file, please note that:\n"
        << " - You HAVE to name your file \"inputs.txt\", otherwise it won't be recognized by the program (will be fixed in a later version).\n\n"
        << "And that's the end of the mini tutorial! Feel free to copy and paste this entire thing into ChatGPT or other chatbots,\n"
        << "they can assist you much better than a hardcoded tutorial like this can. :v\n\n"
        << "Enter anything to Exit.\n> ";
    if (yesIKnowThisIsAnIssue >= 3 && yesIKnowThisIsAnIssue <= 9) {
        std::cout << "\n(Yes I am aware of the UI bug that exists here, it will be fixed in a later version too, until then have fun spamming it.)\n";
        std::cout << "(You seem to enjoy that considering you've done this " << yesIKnowThisIsAnIssue << " times).\n";
    }
    if (yesIKnowThisIsAnIssue >= 10 && yesIKnowThisIsAnIssue <= 19) {
        std::cout << "\n(why must my 5 AM overlooked program bugs be your fulfillment and enjoyment)\n";
    }
    if (yesIKnowThisIsAnIssue == 20) {
        std::cout << "\n(some may ask, if you had this much energy and time to implement this easter egg,"
        << " why not just fix the issue itself? and to that, I say: I don't even know why the problem exists,"
        << " let alone how to fix it. Plus implementing this text trick is a lot easier than you might think,"
        <<" in fact it's only 13 extra lines of code.)\n";
    }
    if (yesIKnowThisIsAnIssue == 21) {
        std::cout << "\n(Well now it's 16 because you're addicted to this.)\n";
    }
    if (yesIKnowThisIsAnIssue == 22) {
        std::cout << "\n(Well, enjoy your infinite counter I suppose, that's the last message here.)\n";
    }
    if (yesIKnowThisIsAnIssue >= 23 && yesIKnowThisIsAnIssue <= 99) {
        std::cout << "\n" << yesIKnowThisIsAnIssue << "\n";
    }
    if (yesIKnowThisIsAnIssue == 100) {
        std::cout << "\n(alright I'm stopping you now, go do literally anything else with your time, you goober.)\n";
    }
    std::cin >> input;     // Pause until user hits a key
    common.handlingBadInput();
    yesIKnowThisIsAnIssue += 1;
    common.clearPreviousLines(40);
}

// Placeholder “Settings” menu: for future unit‐system or UI settings.
// Waits for any user input to return.
void Menu::settings(commonFunctions& common) {
    std::string input; // Variable that handles error input.
    std::cout
        << "---------------------------------------------------\n"
        << "Settings have yet to be implemented.\n"
        << "Until then, all measurements are done in the imperial system, inches.\n"
        << "Enjoy your freedom units.\n"
        << "---------------------------------------------------\n"
        << "Enter anything to Exit.\n> ";
    std::cin >> input;     // Pause until user hits a key
    common.handlingBadInput();
    common.clearPreviousLines(30);
}

// If no outputs have been computed (mathOutput[1]==0.0), warn the user.
// Otherwise, call commonFunctions::saveFile() to write files.
void Menu::saves(commonFunctions& common, Maths& maths) {
    std::string input; // Variable that handles error input.
    if (maths.mathOutput[1].output == 0.0) {
        std::cout << "No valid data found; cannot save until calculations have been made.\n"
            << "Enter anything to Exit.\n> ";
        std::cin >> input;
        common.handlingBadInput();
    }
    else {
        common.saveFile(maths);
    }
    common.clearPreviousLines(30);
}
