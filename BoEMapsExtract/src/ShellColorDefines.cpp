#include "ShellColorDefines.hpp"

#ifdef WIN32
    #include <windows.h>
    HANDLE g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

void PrintRed(std::string message, bool endLine){
    #ifdef COLORFUL_OUTPUT
        #ifdef WIN32
            SetConsoleTextAttribute(g_hConsole,12);
            std::cout << message;
            SetConsoleTextAttribute(g_hConsole, 7);
        #else
            std::cout << "\033[1;31m" << message << "\033[0m";
        #endif
    #else
        std::cout << message;
    #endif

    if(endLine)
        std::cout << std::endl;
}

void PrintGreen(std::string message, bool endLine){
   #ifdef COLORFUL_OUTPUT
        #ifdef WIN32
            SetConsoleTextAttribute(g_hConsole, 2);
            std::cout << message;
            SetConsoleTextAttribute(g_hConsole, 7);
        #else
            std::cout << "\033[0;32m" << message << "\033[0m";
        #endif
    #else
        std::cout << message;
    #endif
    if(endLine)
        std::cout << std::endl;
}

void PrintYellow(std::string message, bool endLine){
    #ifdef COLORFUL_OUTPUT
        #ifdef WIN32
            SetConsoleTextAttribute(g_hConsole, 14);
            std::cout << message;
            SetConsoleTextAttribute(g_hConsole, 7);
        #else
            std::cout << "\033[1;33m" << message << "\033[0m";
        #endif
    #else
        std::cout << message;
    #endif
    if(endLine)
        std::cout << std::endl;
}

void PrintGray(std::string message, bool endLine){
   #ifdef COLORFUL_OUTPUT
        #ifdef WIN32
            SetConsoleTextAttribute(g_hConsole, 8);
            std::cout << message;
            SetConsoleTextAttribute(g_hConsole, 7);
        #else
            std::cout << "\033[0;37m" << message << "\033[0m";
        #endif
    #else
        std::cout << message;
    #endif
    if(endLine)
        std::cout << std::endl;
}

void PrintCyan(std::string message, bool endLine){
   #ifdef COLORFUL_OUTPUT
        #ifdef WIN32
            SetConsoleTextAttribute(g_hConsole, 3);
            std::cout << message;
            SetConsoleTextAttribute(g_hConsole, 7);
        #else
            std::cout << "\033[0;36m" << message << "\033[0m";
        #endif
    #else
        std::cout << message;
    #endif
    if(endLine)
        std::cout << std::endl;
}

