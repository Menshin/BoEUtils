#include "Scenario.hpp"

Scenario::Scenario(Arguments *args){
    scenFile.open(args->filename,std::fstream::in | std::fstream::binary);

    if(!scenFile.good()){
        status = ScenFileStatus::ErrorReadingFile;
        scenFile.close();
        return;
    }

    status = ScenFileStatus::Ok;

    if(!ReadScenarioHeader(args->options)){
        status = ScenFileStatus::InvalidScenarioFile;
        scenFile.close();
        return;
    }

    ReadScenarioOutdoors(args->options);
    ReadScenarioTowns(args->options);
    scenFile.close();
}

Scenario::~Scenario(){
}

/*
 * Returns false on invalid scenario file
 */

bool Scenario::ReadScenarioHeader(int extractOptions){

    //first let's validate the file and check the endianness
    uint32_t scenFormatFlags;

    scenFile.read(reinterpret_cast<char*>(&scenFormatFlags), 4);

    switch(scenFormatFlags){
        case 0x281e140a: //Scen is BigEndian, platform is LittleEndian
            isDifferentEndianness = true;
            break;

        case 0x14283c50: //Scen is LittleEndian, platform is BigEndian
            isDifferentEndianness = true;
            break;

        case 0x503c2814: //Scen is BigEndian, platform is BigEndian
            isDifferentEndianness = false;
            break;

        case 0x0a141e28: //Scen is LittleEndian, platform is LittleEndian
            isDifferentEndianness = false;
            break;

        default: //error file is not a valid scenario
            return false;
            break;
    }

    //read misc scenario data
    scenFile.read(reinterpret_cast<char*>(&scenData.scenVersion),3);
    scenFile.seekg(4,std::fstream::cur);
    scenFile.read(reinterpret_cast<char*>(&scenData.numberOfTowns),1);
    scenFile.read(reinterpret_cast<char*>(&scenData.outdoorsDims),2);

    //read the size of all the towns of the scenario
    scenFile.seekg(3, std::fstream::cur);
    for(int i = 0; i < scenData.numberOfTowns; ++i){
        unsigned char buf;
        scenFile.read(reinterpret_cast<char*>(&buf),1);
        scenData.townsSize.push_back(buf);
    }

    //get terrains templates picture info
    scenFile.seekg(terTypesOffset, std::fstream::beg);
    for(int i = 0 ; i < 256 ; ++i){
        scenFile.read(reinterpret_cast<char*>(&scenData.terrainsPictures[i]),2);
        if(isDifferentEndianness)
            scenData.terrainsPictures[i] = Flip16BytesValue(scenData.terrainsPictures[i]);
        scenFile.seekg(14, std::fstream::cur);
    }

    //get scenario strings lengths to skip over that section
    scenFile.seekg(scenStrLensOffset, std::fstream::beg);
    for(int i = 0 ; i < 300 ; ++i){
        scenFile.read(reinterpret_cast<char*>(&scenData.strLens[i]),1);
    }

    //skip to the scenario strings section
    scenFile.seekg(scenStringsOffset, std::fstream::beg);

    //grab the scenario name while we're here
    char buffer[256];
    buffer[scenData.strLens[0]] = '\0';
    scenFile.read(buffer,scenData.strLens[0]);
    scenData.scenName = std::string{buffer};

    //skip the others scenario strings
    int lengthToSkip = 0;
    for(int i = 1 ; i < 300 ; ++i)
        lengthToSkip += scenData.strLens[i];
    scenFile.seekg(lengthToSkip, std::fstream::cur);

    return true;
}

void Scenario::ReadScenarioOutdoors(int extractOptions){
    //get outdoors terrain chunks
    for(int idx = 0 ; idx <scenData.outdoorsDims[0] * scenData.outdoorsDims[1] ; ++idx){
        OutdoorChunk currentOutdoorChunk;
        if(extractOptions & optsExtractOutdoors){
            scenFile.read(reinterpret_cast<char*>(&currentOutdoorChunk.outdoorChunk),48*48);
        }
        else{//still needs to skip over the outdoor section
            scenFile.seekg(48*48, std::fstream::cur);
        }

        //read the outdoor string lengths
        scenFile.seekg(outdoorStrLensOffset, std::fstream::cur);
        unsigned char outdoorsStrLens[180];
        scenFile.read(reinterpret_cast<char*>(&outdoorsStrLens),180);

        //jump to the outdoor strings section
        scenFile.seekg(sizeOfSpecialNodeType * 60, std::fstream::cur);

        if(extractOptions & optsExtractOutdoors){
            //get the outdoor chunk name
            char buffer[256];
            buffer[outdoorsStrLens[0]]='\0';
            scenFile.read(&buffer[0],outdoorsStrLens[0]);
            //purely cosmetic, some strings have a lot of useless trailing spaces in the original scenarios
            RemoveTrailingSpaces(buffer, outdoorsStrLens[0]);

            currentOutdoorChunk.chunkName = std::string{buffer};
            scenData.outdoorsChunks.push_back(currentOutdoorChunk);
        }
        else{
             scenFile.seekg(outdoorsStrLens[0], std::fstream::cur);
        }

        //skip the rest of the outdoor strings section
        int lengthToSkip = 0;
        for(int idx = 1 ; idx < 180 ; ++idx)
            lengthToSkip += outdoorsStrLens[idx];
        scenFile.seekg(lengthToSkip, std::fstream::cur);
    }
}

void Scenario::ReadScenarioTowns(int extractOptions){
    if(!(extractOptions & optsExtractTowns))
        return;

    for(int i = 0; i < scenData.numberOfTowns ; ++i){
        //get town strings lengths and skip to town terrain
        scenFile.seekg(townStrLensOffset, std::fstream::cur);
        unsigned char townStrLens[180];
        scenFile.read(reinterpret_cast<char*>(&townStrLens),180);
        scenFile.seekg(townStrLensToEndOffset, std::fstream::cur);

        //load town terrain
        int currentTownSize = scenData.townsSize[i];
        int currentTownTerrainSize = townTypesSizes[currentTownSize];
        TownData currentTownData(i, currentTownSize);

        for(int j = 0; j < currentTownTerrainSize*currentTownTerrainSize ; ++j){
            unsigned char buffer;
            scenFile.read(reinterpret_cast<char*>(&buffer), 1);
            currentTownData.townTerrain.push_back(buffer);
        }

        //skip to the end of the TownTrSize structure
        scenFile.seekg(townTerrainToEndOffset[currentTownSize],std::fstream::cur);

        //get the town name
        char buffer[256];
        buffer[townStrLens[0]]='\0';
        scenFile.read(&buffer[0],townStrLens[0]);
        //purely cosmetic, some strings have a lot of useless trailing spaces in the original scenarios
        RemoveTrailingSpaces(buffer, townStrLens[0]);

        currentTownData.townName = std::string{buffer};

        //all data gathered, save the record
        scenData.townsData.push_back(currentTownData);

        //skip the others town strings
        int lengthToSkip = 0;
        for(int idx = 1 ; idx < 180 ; ++idx)
            lengthToSkip += townStrLens[idx];
        scenFile.seekg(lengthToSkip, std::fstream::cur);


        //finally skip the talking strings
        unsigned char talkingStrLens[200];
        scenFile.read(reinterpret_cast<char*>(&talkingStrLens), 200);
        scenFile.seekg(talkingStrLenToEndOffset,std::fstream::cur);

        lengthToSkip = 0;
        for(int idx = 0 ; idx < 200 ; ++idx)
            lengthToSkip += talkingStrLens[idx];
        scenFile.seekg(lengthToSkip, std::fstream::cur);
    }
}

std::string Scenario::GetError(){
    switch(status){
        case ScenFileStatus::ErrorReadingFile:
            return "Couldn't read the scenario file.";
        break;

        case ScenFileStatus::InvalidScenarioFile:
            return "Invalid scenario file.";
        break;

        default:
            return "REPORT: GetError() shouldn't be called when state is Ok.";
        break;
    }
}

void RemoveTrailingSpaces(char *str, int strSize){
    for(int i = strSize-1 ; i >= 0 ; --i){
        if(!isspace(str[i]))
            return;
        str[i] = '\0';
    }
}
