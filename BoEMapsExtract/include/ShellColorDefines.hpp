/*
 * Optional fancy colors for shell output
 */

#ifndef SHELL_COLOR_DEFINES_HPP
#define SHELL_COLOR_DEFINES_HPP

#include <iostream>

void PrintRed(std::string message, bool endLine);
void PrintYellow(std::string message, bool endLine);
void PrintGray(std::string message, bool endLine);
void PrintCyan(std::string message, bool endLine);
void PrintGreen(std::string message, bool endLine);

#endif // SHELL_COLOR_DEFINES_HPP
