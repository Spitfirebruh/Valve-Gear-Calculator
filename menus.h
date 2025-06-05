/*
 * File: menus.h
 * Copyright 2025 Deaven S. Garcia
 * Author: Deaven Garcia (https://github.com/Spitfirebruh)
 * Created: 5/31/25
 * Last Updated: 6/4/25
 *
 * Description:
 *   Declares the `Menu` class, which encapsulates all user‐interaction menus for:
 *   - Calculator (calculate, manual input, file input, file output, exit)
 *   - Help (input guidance, file formatting guidance, exit)
 *   - Settings (stub for future options)
 *   - Saves (checks for computed results, then triggers saving)
 */

#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <sstream>
#include <fstream>

class commonFunctions; // forward‐declare to avoid circular include
class Maths;

class Menu {
public:
    // Easter Egg for a bug that exists
    int yesIKnowThisIsAnIssue = 1;
    // Display the calculator menu and handle user choices
    void calculator(commonFunctions& common, Maths& maths);

    // Display the help menu (input descriptions, file format, exit)
    void help(commonFunctions& common);

    // Within Help: show input descriptions and wait for “Enter anything”
    void inputs(commonFunctions& common);

    // Within Help: show file formatting instructions (placeholder)
    void files(commonFunctions& common);

    // Display the settings menu (currently a placeholder)
    void settings(commonFunctions& common);

    // Check if results exist; if so, call saveFile(), else warn user
    void saves(commonFunctions& common, Maths& maths);
};

#endif // MENUS_H
