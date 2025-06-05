/*
 * File: maths.cpp
 * Copyright 2025 Deaven S. Garcia
 * Author: Deaven Garcia (https://github.com/Spitfirebruh)
 * Created: 6/4/25
 * Last Updated: 6/4/25
 *
 * Description:
 *   Implements the core valve‐gear calculations for the “Valve Gear Calculator” tool.
 *   - takeInputs(): Prompts the user for each required geometric parameter (Drive Wheel Diameter, Piston Stroke, etc.) and stores their values.
 *   - breakItDown(): Validates that all inputs have been provided; if so, runs the actual math and shows a simple progress animation before asking to save results.
 *   - visualMath(): Displays a brief ASCII “loading bar” for each computed output, then prints the final numeric value.
 *   - theActualMath(): Performs all engineering formulas to compute wheel speed, piston speed, bore area, volume swept per minute, port area, port height, half travel, travel margin, and combination lever length.
 */

#define _USE_MATH_DEFINES   // for M_PI
#include <iostream>
#include <string>
#include <cmath>
#include "maths.h"
#include "common.h"
#include "menus.h"

 // Prompts the user to enter each numeric input in mathInput (by iterating through the map).
void Maths::takeInputs() {
    int input;
    std::string input2;
    for (int i = 1; mathInput.find(i) != mathInput.end(); i++) {
        auto& lookfor = mathInput[i];
        // Show the label (letter), description, and example value
        std::cout << "[" << lookfor.inputLetter << "] "
            << lookfor.inputDescription << "\n"
            << "Example: [" << lookfor.inputExample << "\"]\n";

        // Read the user's numeric input into lookfor.input
        std::cin >> lookfor.input;
        if (std::cin.fail()) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            std::cout << "Input for [" << lookfor.inputName << "] is invalid."
                << "\nEnter anything to continue.\n> ";
            std::cin >> input2;
            break;
        }
    }
}

// Checks that every required input is positive (nonzero). If any input is missing or invalid,
// prompts the user to re‐enter. Once all inputs are valid, calls theActualMath() and visualMath(),
// then asks the user if they want to save results to files.
void Maths::breakItDown(commonFunctions& common, Menu& menu) {
    int input;
    std::string input2;
    bool doThing = true;

    // Validate each required input
    for (int i = 1; mathInput.find(i) != mathInput.end(); i++) {
        auto& lookfor = mathInput[i];
        if (lookfor.input <= 0.0) {
            std::cout << "Input for [" << lookfor.inputName << "] is either invalid "
                << "or not entered yet.\nEnter anything to continue.\n> ";
            std::cin >> input2;
            common.handlingBadInput();
            doThing = false;
            break;
        }
        // Echo back the current value
        common.print(lookfor.inputName + " [" + lookfor.inputLetter + "] = ", 5);
        common.delayEffect(300);
        std::cout << lookfor.input << "\"\n";
    }

    if (doThing) {
        // Small delay, clear the previous prompts, then run the math and show a loading bar
        common.delayEffect(1000);
        common.clearPreviousLines(30);

        theActualMath();
        visualMath(common);
        if (wasSuccessful == true) {
            std::cout << "Calculations completed successfully.\n"
                << "Export to files?\n"
                << "[1] Yes\n"
                << "[2] No\n";
            std::cin >> input;
            common.handlingBadInput();

            if (input == 1) {
                // If user chooses to save, call the menu's save routine
                menu.saves(common, *this);
            }
        }
    }

    // Clear any remaining lines before returning to the caller
    common.clearPreviousLines(30);
}

// For each output in mathOutput, display a simple ASCII “loading bar” animation, then print the numeric result.
void Maths::visualMath(commonFunctions& common) {
    std::string input2;
    for (int i = 1; mathOutput.find(i) != mathOutput.end(); i++) {
        auto& lookfor = mathOutput[i];
        // Show “computing <outputName>…” message, one character at a time
        common.print(lookfor.outputName + "...\n", 5);

        // Basic ASCII progress bar growing from [     ] to [|||||]
        std::cout << "[     ]\n";
        common.delayEffect(100);
        common.clearPreviousLines(1);

        std::cout << "[|    ]\n";
        common.delayEffect(100);
        common.clearPreviousLines(1);

        std::cout << "[||   ]\n";
        common.delayEffect(100);
        common.clearPreviousLines(1);

        std::cout << "[|||  ]\n";
        common.delayEffect(100);
        common.clearPreviousLines(1);

        std::cout << "[|||| ]\n";
        common.delayEffect(100);
        common.clearPreviousLines(1);

        std::cout << "[|||||]\n";
        common.delayEffect(100);
        common.clearPreviousLines(2);

        // Finally, print the numeric value of this output
        common.print(lookfor.outputName + ": " + std::to_string(lookfor.output) + "\n", 5);

        if (lookfor.output < 0) {
            std::cout << "Output for [" << lookfor.outputName << "] is invalid, please re-enter your values, and ensure they're correct.\nEnter anything to continue.\n> ";
            std::cin >> input2;
            common.handlingBadInput();
            wasSuccessful = false;
            break;
        } else {
            wasSuccessful = true;
        }
    }
}

// Contains all the engineering formulas. Each mathOutput[index].output field is computed from mathInput values
void Maths::theActualMath() {
    // 1. Wheel Speed (WS) = (Drive Wheel Diameter × π × 336 × 60) / 12
    mathOutput[1].output = (mathInput[1].input * M_PI * 336 * 60) / 12;

    // 2. Piston Speed (FPM) = (336 × 2 × Piston Stroke) / 12
    mathOutput[2].output = (336 * 2 * mathInput[2].input) / 12;

    // 3. Bore Area (BA) = π × (Bore / 2)²
    mathOutput[3].output = (M_PI * pow((mathInput[3].input / 2), 2));

    // 4. Volume Swept per Minute (VPM) = (Piston Speed × Bore Area) / 144
    mathOutput[4].output = (mathOutput[2].output * mathOutput[3].output) / 144;

    // 5. Port Area (PA) = VPM / 7874
    mathOutput[5].output = mathOutput[4].output / 7874;

    // 6. Port Height (PH) = (Port Area × 12) / Port Width
    mathOutput[6].output = (mathOutput[5].output * 12.0) / mathInput[7].input;

    // 7. Half Travel (HT) = Lap + Lead + Port Height
    mathOutput[7].output = mathInput[5].input + mathInput[4].input + mathOutput[6].output;

    // 8. Travel Margin (TM) = Valve Travel – (Lap + Lead)
    mathOutput[8].output = mathInput[6].input - (mathInput[5].input + mathInput[4].input);

    // 9. Combination Lever Length (CLL) = (Piston Stroke × HT) / (2 × ((Lap + Lead) / 2))
    mathOutput[9].output =
        (mathInput[2].input * mathOutput[7].output) /
        (2.0 * ((mathInput[5].input + mathInput[4].input) / 2.0));
}
