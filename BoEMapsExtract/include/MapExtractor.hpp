/*
 * Receives the data from the scenario and use it to build the maps images
 * Requires : SDL2 and SDL2_image
 */

#ifndef MAP_EXTRACTOR_HPP
#define MAP_EXTRACTOR_HPP

#include <iostream>
#include <vector>
#include "SDL.h"
#ifdef WIN32
    #include <string> //needed for std:to_string for MSVC
    #include "SDL_image.h"
#else
    #include "SDL2/SDL_image.h"
#endif
#include "ArgsHandler.hpp" //options defines
#include "Scenario.hpp"

enum class MapExtractorStatus{Ok, SDLInitializationError, IMGInitializationError,
                              ErrorLoadingTerrains, ErrorCreatingExtractedMap, ErrorTerrainsPictures};

class MapExtractor{
    public:
        MapExtractor(ScenData *_scenData, Arguments *args);
        ~MapExtractor();

        void Extract();

        bool IsOk(){return status == MapExtractorStatus::Ok;}
        std::string GetError();

    private:
        void MergeOutdoors(int xSize, int ySize);
        void ExtractOutdoors(int xSize, int ySize);
        void ExtractTowns(int townNums, std::vector<TownData> &townInfos);
        bool DrawOneTile(int dx, int dy, int pictNum);
        void WriteMapFile(std::string &outputFile);

        MapExtractorStatus status;
        ScenData *scenData; //pointer to the data served by the Scenario class
        std::string scenFilename;
        int extractOptions; //Arguments.options constants

        bool LoadBaseGraphics();
        SDL_Surface* LoadCustomGraphics(std::string filename);
        bool customGraphicsLoaded;

        //SDL specific data
        SDL_Surface *AllocateExtractedMapSurface(int xSize, int ySize);

        SDL_Surface *baseTerrainSurface;
        SDL_Surface *animTerrainSurface;
        SDL_Surface *customTerrainSurface;
        SDL_Rect destRect{0,0,28,36};
        SDL_Rect srcRect{0,0,28,36};
        SDL_Surface *extractedMap; //surface on which to build the map
};

#endif // MAP_EXTRACTOR_HPP

