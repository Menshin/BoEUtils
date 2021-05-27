#include <iostream>
#include "Scenario.hpp"
#include "MapExtractor.hpp"
#include "BitUtils.hpp"

int main(int argc, char* argv[])
{
    Arguments args;
    if(!HandleArguments(argc, argv, &args)){
        PrintUsage();
        return 0;
    }

    Scenario scenario{&args};
    if(!scenario.IsOk()){
        PrintRed("  [!] Scenario error: ", false);
        std::cout << scenario.GetError() << std::endl;
        return 1;
    }

    PrintCyan("  [*] Found scenario: ", true);
    std::cout << "\t " << scenario.scenData.scenName << " (v"
              << static_cast<unsigned>(scenario.scenData.scenVersion[0]) << "."
              << static_cast<unsigned>(scenario.scenData.scenVersion[1]) << "."
              << static_cast<unsigned>(scenario.scenData.scenVersion[2]) << ")" << std::endl;


    MapExtractor mapExtractor(&scenario.scenData, &args);
    if(!mapExtractor.IsOk()){
        PrintRed("  [!] Map extractor error: ", false);
        std::cout << mapExtractor.GetError() << std::endl;
        return 2;
    }

    mapExtractor.Extract();
    if(!mapExtractor.IsOk()){
        PrintRed("  [!] Map extractor error: ", false);
        std::cout << mapExtractor.GetError() << std::endl;
        return 3;
    }

    PrintGreen("  Extraction successful.", true);

    return 0;
}
