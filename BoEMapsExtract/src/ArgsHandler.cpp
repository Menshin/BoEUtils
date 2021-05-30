#include "ArgsHandler.hpp"

 /* returns : 0 on invalid argument/option and display usage
  *           1 on successful parsing
  */
int HandleArguments(int argc, char* argv[], Arguments* args){
    if(argc != 3)
        return 0;

    std::string options{argv[1]};
    if(options[0] != '-')
        return 0;

    args->options = 0;
    for(char c : options.substr(1)){
        switch(c){
            case 'a':
                args->options |= optsExtractAll;
                break;
            case 't':
                args->options |= optsExtractTowns;
                break;
            case 'o':
                args->options |= optsExtractOutdoors;
                break;
            case 'd':
                args->options |= optsUseMacGraphics;
                break;
            case 'b':
                args->options |= optsForceBMPOutput;
                break;
            case 'm':
                args->options |= optsMergeOutdoors;
                break;
            default:
                return 0;
        }
    }

    //should have at least one valid argument
    if(!(args->options & optsExtractAll))
        return 0;

    args->filename = std::string{argv[2]};

    return 1;
}

void PrintUsage(){
    std::cout << "Usage: " << std::endl;
    std::cout << "\t BoEMapsExtract -a|o|t|d|b|m filename.exs" << std::endl;
    std::cout << "Assets:" << std::endl;
    std::cout << "\t BoE base image files should be located in a ./ressources folder" << std::endl;
    std::cout << "Argument:" << std::endl;
    std::cout << "\t -a extract all (superseeds -o and -t)" << std::endl;
    std::cout << "\t -o extract outdoors only" << std::endl;
    std::cout << "\t -t extract towns only" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t -d use Mac (darker) graphics" << std::endl;
    std::cout << "\t -b force BMP output" << std::endl;
    std::cout << "\t -m Merge all outdoors in a single (large!) image" << std::endl;
}
