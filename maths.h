/*
 * File: maths.h
 * Copyright 2025 Deaven S. Garcia
 * Author: Deaven Garcia (https://github.com/Spitfirebruh)
 * Created: 6/4/25
 * Last Updated: 6/4/25
 *
 * Description:
 *   Defines the `Maths` class, which holds all input parameters and output results for
 *   valve‐gear calculations.
 *   - `takeInputs()`: Prompt user for each input (Diameter, Stroke, Bore, etc.).
 *   - `breakItDown()`: Validate inputs, then run `theActualMath()` and `visualMath()` before optionally saving.
 *   - `visualMath()`: Show a simple ASCII progress bar for each output, then print the final value.
 *   - `theActualMath()`: Perform the core formulas (wheel speed, piston speed, bore area, etc.).
 */

#ifndef MATHS_H
#define MATHS_H

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <map>

 // Forward declarations to avoid circular includes:
class commonFunctions;
class Menu;

// Represents a single input parameter.
struct Input {
    std::string inputLetter;       // e.g. "D" for Drive Wheel Diameter
    std::string inputName;         // e.g. "Drive Wheel Diameter"
    std::string inputDescription;  // Short text prompting the user
    double inputExample = 0.0;     // Example value shown to the user
    double input = 0.0;            // The actual numeric value entered
};

// Represents a single computed output parameter.
struct Output {
    std::string outputLetter;  // e.g. "WS" for Wheel Speed
    std::string outputName;    // e.g. "Wheel Speed"
    double output = 0.0;       // The computed numeric result
};

class Maths {
public:
    // Maps integer keys (1..7) to Input structs (Diameter, Stroke, ...).
    std::map<int, Input> mathInput;

    // Maps integer keys (1..9) to Output structs (Wheel Speed, Piston Speed, ...).
    std::map<int, Output> mathOutput;

    // Constructor: initializes mathInput and mathOutput with default names, letters, and example values.
    Maths() {
        // Input fields (index → {letter, name, description, example, initial value})
        mathInput[1] = Input{ "D", "Drive Wheel Diameter", "The drive wheel diameter.", 66, 0.0 };
        mathInput[2] = Input{ "S", "Piston Stroke",       "The piston stroke.",       26, 0.0 };
        mathInput[3] = Input{ "B", "Bore",                 "The bore.",                20.5, 0.0 };
        mathInput[4] = Input{ "L", "Lead",                 "The lead.",                0.858, 0.0 };
        mathInput[5] = Input{ "A", "Lap",                  "The lap (covering port at mid).", 3.39, 0.0 };
        mathInput[6] = Input{ "T", "Valve Travel",         "The valve travel.",        5.5, 0.0 };
        mathInput[7] = Input{ "W", "Port Width",           "The port width.",          18, 0.0 };

        // Output fields (index → {letter, name, initial value})
        mathOutput[1] = Output{ "WS", "Wheel Speed",               0.0 };
        mathOutput[2] = Output{ "FPM", "Piston Speed",             0.0 };
        mathOutput[3] = Output{ "BA", "Bore Area",                 0.0 };
        mathOutput[4] = Output{ "VPM", "Volume Swept per Minute",   0.0 };
        mathOutput[5] = Output{ "PA", "Port Area",                 0.0 };
        mathOutput[6] = Output{ "PH", "Port Height",               0.0 };
        mathOutput[7] = Output{ "HT", "Half Travel",               0.0 };
        mathOutput[8] = Output{ "TM", "Travel Margin",             0.0 };
        mathOutput[9] = Output{ "CLL", "Combination Lever Length",  0.0 };
    }

    // Prompt the user to enter each numeric input in mathInput.
    void takeInputs();

    // Validate inputs; if everything > 0, run theActualMath() and visualMath(), then ask to save.
    void breakItDown(commonFunctions& common, Menu& menu);

    // Show a brief ASCII “loading bar” for each output, then print the numeric result.
    void visualMath(commonFunctions& common);
    bool wasSuccessful;

    // Perform all engineering formulas to fill mathOutput[*].output fields.
    void theActualMath();
};

#endif // MATHS_H
