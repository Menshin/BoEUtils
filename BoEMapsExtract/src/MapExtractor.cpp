#include "MapExtractor.hpp"

MapExtractor::MapExtractor(ScenData *_scenData, Arguments* args){

    //pointer to the served data
    scenData = _scenData;
    if(!scenData->terrainsPictures){
        status = MapExtractorStatus::ErrorTerrainsPictures;
        return;
        }

    //SDL/SDL_image backend initialization
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        status = MapExtractorStatus::SDLInitializationError;
        return;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        status = MapExtractorStatus::IMGInitializationError;
        return;
    }

    //data parsing/assets loading
    scenFilename = args->filename;
    extractOptions = args->options;

    PrintCyan("  [*] Loading graphics", true);
    if(!LoadBaseGraphics()){
        status = MapExtractorStatus::ErrorLoadingTerrains;
        return;
    }
    customTerrainSurface = LoadCustomGraphics(scenFilename.substr(0,scenFilename.length() - 4));
    if(customTerrainSurface == NULL)
        customGraphicsLoaded = false;
    else
        customGraphicsLoaded = true;

    //all good, ready to extract
    status = MapExtractorStatus::Ok;
}

MapExtractor::~MapExtractor(){

    if(baseTerrainSurface)
        SDL_FreeSurface(baseTerrainSurface);

    if(animTerrainSurface)
        SDL_FreeSurface(animTerrainSurface);

    if(customTerrainSurface)
        SDL_FreeSurface(customTerrainSurface);

    IMG_Quit();
    SDL_Quit();
}

void MapExtractor::Extract(){
    if(extractOptions & optsExtractOutdoors){
        if(extractOptions & optsMergeOutdoors)
            MergeOutdoors(scenData->outdoorsDims[0], scenData->outdoorsDims[1]);
        else
            ExtractOutdoors(scenData->outdoorsDims[0], scenData->outdoorsDims[1]);
    }

     if(extractOptions & optsExtractTowns){
        ExtractTowns(scenData->numberOfTowns, scenData->townsData);
    }

}

/*
 * Actual map builders functions
 * Note that BoE terrains are stored by columns rather than rows
 */
void MapExtractor::ExtractTowns(int townNums, std::vector<TownData> &townsData){

    PrintCyan(std::string{"  [*] Found "} + std::to_string(townNums) + " towns", true);
    for(int i = 0; i < townNums ; ++i){
        int currentTownSize = townTypesSizes[townsData[i].townSize];
        std::vector<unsigned char> &townTerrain = townsData[i].townTerrain;

        extractedMap = AllocateExtractedMapSurface(currentTownSize*28,currentTownSize*36);

        if(extractedMap == NULL) {
            status = MapExtractorStatus::ErrorCreatingExtractedMap;
            return;
        }

        std::cout << "       Extracting town " << i << " (";
        PrintGray(townsData[i].townName, false);
        std::cout << ", " << currentTownSize << "x" << currentTownSize << ")...";

        int index = 0;
        for(int j = 0 ; j < currentTownSize ; ++j){
            for(int k = 0 ; k < currentTownSize ; ++k){
                DrawOneTile(j, k,  scenData->terrainsPictures[townTerrain[index++]]);
            }
        }

        std::string outputFile = scenFilename.substr(0,scenFilename.length() - 4) + "_town" + std::to_string(i);
        WriteMapFile(outputFile);
        SDL_FreeSurface(extractedMap);
        PrintGreen(" done", true);
    }
}

/*
 * One file per outdoor chunk
 */
void MapExtractor::ExtractOutdoors(int xSize, int ySize){

    PrintCyan(std::string{"  [*] Found "} + std::to_string(xSize) + "x" + std::to_string(ySize) + " outdoors", true);

    for(int idx = 0 ; idx < xSize * ySize ; ++idx){
        extractedMap = AllocateExtractedMapSurface(28*48, 36*48);
        if(extractedMap == NULL) {
            status = MapExtractorStatus::ErrorCreatingExtractedMap;
            return;
        }

        std::cout << "       Extracting ";
        PrintGray(scenData->outdoorsChunks[idx].chunkName, false);
        std::cout << " (" << idx%xSize << "," << idx/xSize << ")...";

        for(int k = 0 ; k < 48 *48 ; ++k){
            unsigned char terrainId = scenData->outdoorsChunks[idx].outdoorChunk[k];
            DrawOneTile(k/48, k%48, scenData->terrainsPictures[terrainId]);
            }

        std::string outputFile = scenFilename.substr(0,scenFilename.length() - 4) + "_outdoors(" + std::to_string(idx%xSize) + "x" + std::to_string(idx/xSize) + ")";
        WriteMapFile(outputFile);
        SDL_FreeSurface(extractedMap);
        PrintGreen(" done", true);
    }
}

/*
 * One giant file for all outdoors
 */

void MapExtractor::MergeOutdoors(int xSize, int ySize){
    extractedMap = AllocateExtractedMapSurface(xSize*28*48, ySize*36*48);
    if(extractedMap == NULL) {
        status = MapExtractorStatus::ErrorCreatingExtractedMap;
        return;
    }
    PrintCyan(std::string{"  [*] Found "} + std::to_string(xSize) + "x" + std::to_string(ySize) + " outdoors", true);
    std::cout << "       Merging outdoors in one file..." << std::flush;

    for(int idx = 0 ; idx < xSize * ySize ; ++idx){
        for(int k = 0 ; k < 48 *48 ; ++k){
            unsigned char terrainId = scenData->outdoorsChunks[idx].outdoorChunk[k];
            DrawOneTile(k/48+48*(idx%xSize), k%48+48*(idx/xSize), scenData->terrainsPictures[terrainId]);
            }
    }

    std::string outputFile = scenFilename.substr(0,scenFilename.length() - 4) + "_outdoors(merged)";
    WriteMapFile(outputFile);
    SDL_FreeSurface(extractedMap);
    PrintGreen(" done", true);
}

/*
 * Blit the terrain from the source asset file to the extracted map surface
 * Note that, in BoE, the picture number also code the picture type (base, animated, custom, etc)
 */

bool MapExtractor::DrawOneTile(int dx, int dy, int pictNum){
    SDL_Surface *srcSurface;

    //base, non-animated terrain
    if(pictNum < 400){
        srcRect.x = 28 * (pictNum % 10);
        srcRect.y = 36 * (pictNum / 10);
        srcSurface = baseTerrainSurface;
    }
    //animated terrain
    else if(pictNum < 1000){
        srcRect.x = 28 * 4 * ((pictNum-400) / 5);
        srcRect.y = 36 * ((pictNum-400) % 5);
        srcSurface = animTerrainSurface;
    }
    //custom terrain
    else{
        if(!customGraphicsLoaded){
            PrintYellow(std::string{"\n\t [!] Tried to draw a custom graphic ("} + std::to_string(pictNum) +
                        ") with no custom file loaded at (" + std::to_string(dx) + ", " + std::to_string(dy) +")", false);
            return false;
        }
        int customIdentifier = (pictNum < 2000 ? 1000 : 2000);//pictNum >= 2000 are *animated* customs
        srcRect.x = 28 * ((pictNum-customIdentifier) % 10);
        srcRect.y = 36 * ((pictNum-customIdentifier) / 10);
        srcSurface = customTerrainSurface;
    }

    destRect.x = 28 * dx;
    destRect.y = 36 * dy;
    SDL_BlitSurface(srcSurface, &srcRect, extractedMap, &destRect);

    return true;
}

void MapExtractor::WriteMapFile(std::string &outputFile){
    if(extractOptions & optsForceBMPOutput){
        outputFile += ".bmp";
        SDL_SaveBMP(extractedMap, outputFile.c_str());
        }
    else{
        outputFile += ".png";
        IMG_SavePNG(extractedMap, outputFile.c_str());
    }
}

SDL_Surface* MapExtractor::AllocateExtractedMapSurface(int xSize, int ySize){
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        return SDL_CreateRGBSurface(SDL_SWSURFACE, xSize,ySize, 32,
                                   0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    #else
        return SDL_CreateRGBSurface(SDL_SWSURFACE, xSize, ySize, 32,
                                   0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    #endif
}

std::string MapExtractor::GetError(){
    switch(status){
        case MapExtractorStatus::ErrorLoadingTerrains:
            return std::string{"Couldn't load the base terrain files, check the ressources/ folder."};
        break;

        case MapExtractorStatus::SDLInitializationError:
            return std::string{"SDL initialization, "} + SDL_GetError();
        break;

        case MapExtractorStatus::IMGInitializationError:
            return std::string{"IMG initialization, "} + IMG_GetError();
        break;

        case MapExtractorStatus::ErrorCreatingExtractedMap:
            return std::string{"Couldn't create output surface."};
        break;

        case MapExtractorStatus::ErrorTerrainsPictures:
            return std::string{"Couldn't set the scenario terrains <=> pictures correspondance."};
        break;

        default:
            return std::string{"REPORT: GetError() shouldn't be called when state is Ok."};
        break;
    }
}

SDL_Surface* MapExtractor::LoadCustomGraphics(std::string filename){
    /*the ugly .BMP is to handle strangely abundant custom graphic
      files with the capital BMP extension on the Windows version*/
    std::string validExtensions[3] = {".png", ".bmp",".BMP",};

    std::cout << "\t looking for custom graphic file...";
    SDL_Surface *customGraphics;
    for(int i = 0 ; i < 3 ; ++i){
        customGraphics = IMG_Load((filename + validExtensions[i]).c_str());
        if(customGraphics != NULL){
            PrintGreen(" found " + filename + validExtensions[i], true);
            return customGraphics;
        }
    }

    PrintGray(" none found", true);
    return NULL;
}

bool MapExtractor::LoadBaseGraphics(){
    std::string baseGraphicsFile, baseAnimGraphicsFile;
    baseTerrainSurface = animTerrainSurface = customTerrainSurface = NULL;

    if(extractOptions & optsUseMacGraphics){
        baseGraphicsFile = "ressources/ter_mac.png";
        baseAnimGraphicsFile = "ressources/teranim_mac.png";
    }
    else{
        baseGraphicsFile = "ressources/ter_win.png";
        baseAnimGraphicsFile = "ressources/teranim_win.png";
    }

    std::cout << "\t loading " << baseGraphicsFile << "... ";
    baseTerrainSurface = IMG_Load(baseGraphicsFile.c_str());
    if(baseTerrainSurface == NULL){
        PrintRed("not found", true);
        return false;
    }
    PrintGreen("done", true);

    std::cout << "\t loading " << baseAnimGraphicsFile << "... ";
    animTerrainSurface = IMG_Load(baseAnimGraphicsFile.c_str());
    if(animTerrainSurface == NULL){
        PrintRed("not found", true);
        return false;
    }
    PrintGreen("done", true);

    return true;
}
