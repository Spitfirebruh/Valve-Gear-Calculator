/*
 * File: main.h
 * Copyright 2025 Deaven S. Garcia
 * Author: Deaven Garcia (https://github.com/Spitfirebruh)
 * Created: 5/31/25.
 * Last Updated: 6/4/25.
 *
 * Description:
 *   Entry point for the Valve Gear Calculator application.
 *   - Instantiates Menu, commonFunctions, and Maths objects.
 *   - Ensures necessary subdirectories (“inputs/”, “outputs/”) exist.
 *   - Displays the top‐level menu in a loop:
 *       1) Input Values (calculator submenu)
 *       2) Settings        (placeholder)
 *       3) Help            (input descriptions, file format info)
 *       4) Exit
 *   - When user chooses “Exit,” the loop ends and the program returns 0.
 * 
 * Developer Notes:
 *  - Most comments and descriptions are AI generated.
 *  - They're accurate to my code, just obviously not my own descriptions.
 *  - The rest of the code here (with the exclusion of three specific functions found in common.h) is written by me.
 *  - By me and I, who's referred to is Deaven Garcia.
 *  - When compiling, make sure to use C++17 or later.
 */

#include <string>
#include <random>
#include <iostream>
#include "menus.h"
#include "common.h"
#include "maths.h"

int main() {
	Menu menus;
	commonFunctions common;
	Maths maths;

	common.ensureDirectoriesExist();

	int input = 0; // Variable that handles user input.
	std::string input2; // Variable that handles error input.
	int loop = 1; // Flag that allows for exiting.
	while (loop == 1) {
		input = 0; // Reset flag to avoid looping.
		std::cout << "|\\\\\\\\\\\\\\\\\\\\\---//////////|\n"
			<< "| Valve Gear Calculator |\n"
			<< "|                       |\n"
			<< "|  [   Version 1.0   ]  |\n"
			<< "|  [Released 6/4/2025]  |\n"
			<< "|//////////---\\\\\\\\\\\\\\\\\\\\\|\n"
			<< "1. Input Values\n"
			<< "2. Settings\n"
			<< "3. Help\n"
			<< "4. Exit\n> ";
		std::cin >> input; // Menu choice
		common.handlingBadInput();
		switch (input) {
		case 1: // Calculator
			common.clearPreviousLines(20);
			menus.calculator(common, maths);
			break;
		case 2: // Settings
			common.clearPreviousLines(20);
			menus.settings(common);
			break;
		case 3: // Help
			common.clearPreviousLines(20);
			menus.help(common);
			break;
		case 4: // Exit
			loop = 0; // Loop flag set to 0, exiting program.
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
	return 0;
}