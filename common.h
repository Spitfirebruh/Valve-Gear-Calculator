/*
 * File: common.h
 * Copyright 2025 Deaven S. Garcia
 * Author: Deaven Garcia (https://github.com/Spitfirebruh)
 * Created: 5/31/25
 * Last Updated: 6/4/25
 *
 * Description:
 *   Defines `commonFunctions`, which provides:
 *   - `print()`      : typewriter‐style printing (character by character with a delay)
 *   - `clearPreviousLines()`: clear a specified number of console lines using ANSI escape codes
 *   - `delayEffect()`: pause for a given number of milliseconds
 *   - `saveFile()`   : write all inputs and outputs to `inputs/inputs.txt` and `outputs/outputs.txt`
 *   - `loadFile()`   : read “valve.txt”, parse lines by label, and update mathInput map
 *   - `ensureDirectoriesExist()`: create “inputs/” and “outputs/” folders if they don’t already exist
 * 
 * Developer Notes:
 *  - loadFile's logic is AI-generated, to allow for file inputs (could've written it myself, but I am far too tired for all that).
 *  - ensureDirectoriesExist is also AI-generated, though only because I've apparently been writing using C++14 the entire time, so I had no idea filesystem stuff even existed.
 *  - handlingBadInput is taken from Stack Overflow, but is edited for the purposes of this program.
 */

#ifndef COMMON_H
#define COMMON_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>   // for loadFile’s vector of lines
#include <sstream>  // for parsing numbers from strings
#include "maths.h"

class commonFunctions {
public:
    bool playerHasSave = false; // indicates if a saved “valve.txt” was successfully loaded

    // Print a message one character at a time, waiting speedMS milliseconds between characters.
    void print(std::string message, int speedMS) {
        for (char c : message) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(speedMS));
        }
    }

    // Use ANSI escape codes to move cursor up and clear lines in the console.
    // linesUsed = number of lines to erase.
    void clearPreviousLines(int linesUsed) {
        for (int i = 0; i < linesUsed; i++) {
            std::cout << "\x1b[1F"; // Move cursor up one line
            std::cout << "\x1b[2K"; // Clear entire line
        }
    }

    // Pause for the specified number of milliseconds.
    void delayEffect(int delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    // Write inputs and outputs to text files in the “inputs/” and “outputs/” directories.
    // Format: “Label: Value” on each line.
    void saveFile(Maths& maths) const {
        // Make sure subfolders exist before trying to write
        // (caller should already have called ensureDirectoriesExist)

        // Save inputs
        std::ofstream inputsFile("inputs/inputs.txt");
        if (inputsFile.is_open()) {
            for (int i = 1; maths.mathInput.find(i) != maths.mathInput.end(); i++) {
                auto& lookfor = maths.mathInput[i];
                inputsFile << lookfor.inputName << ": " << lookfor.input << std::endl;
            }
            inputsFile.close();
        }
        else {
            std::cout << "Error saving inputs file.\n";
        }

        // Save outputs
        std::ofstream outputsFile("outputs/outputs.txt");
        if (outputsFile.is_open()) {
            for (int i = 1; maths.mathOutput.find(i) != maths.mathOutput.end(); i++) {
                auto& lookfor = maths.mathOutput[i];
                outputsFile << lookfor.outputName << ": " << lookfor.output << std::endl;
            }
            outputsFile.close();
        }
        else {
            std::cout << "Error saving outputs file.\n";
        }
    }

    // Load “valve.txt” (if it exists) and parse each line as “<Label>: <Number>”,
    // matching Label to mathInput[i].inputName, and storing the parsed number in mathInput[i].input.
    void loadFile(Maths& math) {
        std::ifstream inFile("inputs/inputs.txt");
        if (!inFile.is_open()) {
            std::cout << "No file found.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            clearPreviousLines(1);
            playerHasSave = false;
            return;
        }

        // Read all lines into a vector<string>
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();

        // For each entry in mathInput, look for a matching “Label:” at the start of a line
        for (auto& [key, input] : math.mathInput) {
            std::string searchLabel = input.inputName + ":";

            for (const auto& fileLine : lines) {
                if (fileLine.find(searchLabel) == 0) {
                    // Found the line. Extract everything after the colon and parse as double.
                    size_t colonPos = fileLine.find(':');
                    if (colonPos != std::string::npos) {
                        std::string numberStr = fileLine.substr(colonPos + 1);
                        // Trim leading spaces
                        size_t start = numberStr.find_first_not_of(" \t");
                        if (start != std::string::npos)
                            numberStr = numberStr.substr(start);

                        std::istringstream iss(numberStr);
                        double value = 0;
                        iss >> value;
                        input.input = value;
                    }
                    break; // stop searching lines once we’ve matched this label
                }
            }
        }

        playerHasSave = true;
    }

    // Ensure that “inputs/” and “outputs/” folders exist next to the executable.
    // If they don’t, create them. Otherwise, do nothing.
    void ensureDirectoriesExist() {
        namespace fs = std::filesystem;
        if (!fs::exists("inputs")) {
            if (!fs::create_directory("inputs")) {
                std::cerr << "Error: couldn’t create folder inputs/\n";
            }
        }
        if (!fs::exists("outputs")) {
            if (!fs::create_directory("outputs")) {
                std::cerr << "Error: couldn’t create folder outputs/\n";
            }
        }
    }

    // Borrowed from https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input
    void handlingBadInput() {
        //executes loop if the input fails (e.g., no characters were read)
        if (std::cin.fail()) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        }
    }
};

#endif // COMMON_H
