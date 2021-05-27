/*
 * Handles the commandline arguments parsing and passing
 */

#ifndef ARGUMENTS_HANDLER_HPP
#define ARGUMENTS_HANDLER_HPP

#include <iostream>
#include "ShellColorDefines.hpp"

//Arguments.options constants
constexpr int optsExtractOutdoors = (1 << 0);
constexpr int optsExtractTowns    = (1 << 1);
constexpr int optsUseMacGraphics  = (1 << 2);
constexpr int optsForceBMPOutput  = (1 << 3);
constexpr int optsMergeOutdoors   = (1 << 4);
constexpr int optsExtractAll      = (optsExtractOutdoors | optsExtractTowns);

/*
 * Used to pass arguments around
 */
struct Arguments{
    int options;
    std::string filename;
};

int HandleArguments(int argc, char* argv[], Arguments* args);
void PrintUsage();

#endif // ARGS_HANDLER_HPP
