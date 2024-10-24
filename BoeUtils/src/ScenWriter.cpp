#include "ScenWriter.hpp"

using namespace BoE;

DataWriter::DataWriter(std::string filename, const ScenData &_data): data{_data}{
    //check if we should overwrite an existing file
    if(std::filesystem::exists(filename)){
        char c;

        std::cout << filename << " already exists. Overwrite? (Y/n)" << std::endl;

        std::cin >> c;
        if(c != 'Y'){
            status = WriterStatus::DontOverwriteFile;
            return;
        }
    }

    WriteScenario(filename);
}


BoE::DataWriter::~DataWriter(){
    scenFile.close();
}

std::string BoE::DataWriter::GetErrorMessage() const{
    switch(status){
        case WriterStatus::CantOpenFile:
            return std::string{"DATA WRITER: Can't open specified file."};
        case WriterStatus::DontOverwriteFile:
            return std::string{"DATA WRITER: Don't overwrite file already present."};
        case WriterStatus::Ok:
            return std::string{"No error."};
        default:
            return std::string{"DATA WRITER: Unspecified error."};
    }
}

void BoE::DataWriter::WriteScenHeader(){
    //scenario header data
    scenFile.write(reinterpret_cast<const char*>(&data.header),sizeof(data.header));

    //scenario general data (not stored in the game order)
    scenFile.write(reinterpret_cast<const char*>(&data.general.townsSize[0]),200*sizeof(uint8_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.townsHidden[0]),200*sizeof(uint8_t));
    scenFile.write("\0",1); //write the unused 'a' variable

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[0]),sizeof(int16_t));//flag_a

    scenFile.write(reinterpret_cast<const char*>(&data.general.introMessagePicture), sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.introMessageLength), sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.startingTownSpawnLoc),3*sizeof(Location)); //startingTownSpawnLoc + startingOutdoorSector + startingOutdoorSpawnLoc
    scenFile.write(reinterpret_cast<const char*>(&data.general.startingTownNumber), sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[1]), sizeof(int16_t)); //flag_b

    scenFile.write(reinterpret_cast<const char*>(&data.general.townsDataSize), 200*5*sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.townsToAddTo), 10*sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.townsFlagToAddTo), 20*sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[2]), sizeof(int16_t)); //flag_c

    scenFile.write(reinterpret_cast<const char*>(&data.general.outdoorsDataSize), 100*2*sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.storeItemRects), 3*sizeof(Rect16));
    scenFile.write(reinterpret_cast<const char*>(&data.general.storeItemsTowns), 3*sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[4]), sizeof(int16_t)); //flag_e (flag_d is at the bottom of the data)

    scenFile.write(reinterpret_cast<const char*>(&data.general.specialItems), 50*sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.specialItemsSpecial), 50*sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.rating), sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.usesCustomGraphics), sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[5]), sizeof(int16_t)); //flag_f

    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioMonsters[0]),256*sizeof(MonsterRecord));
    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioBoats[0]),30*sizeof(TransportRecord));
    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioHorses[0]),30*sizeof(TransportRecord));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[6]), sizeof(int16_t)); //flag_g

    scenFile.write(reinterpret_cast<const char*>(&data.general.terrainTypes[0]), 256*sizeof(TerrainRecord));

    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioTimerTimes), 20*sizeof(int16_t));
    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioTimerSpecials), 20*sizeof(int16_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[7]), sizeof(int16_t)); //flag_h

    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioSpecials[0]),256*sizeof(SpecialNode));
    scenFile.write(reinterpret_cast<const char*>(&data.general.storageShortcuts[0]),10*sizeof(ItemStorageShortcut));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[3]), sizeof(int16_t)); //flag_d

    scenFile.write(reinterpret_cast<const char*>(&data.general.scenarioStringsLengths[0]), 300*sizeof(int8_t));

    scenFile.write(reinterpret_cast<const char*>(&data.general.flags[8]), sizeof(int16_t)); //flag_i

    scenFile.write(reinterpret_cast<const char*>(&data.general.lastOutdoorEdited), sizeof(Location));
    scenFile.write(reinterpret_cast<const char*>(&data.general.lastTownEdited), sizeof(int16_t));

}

void BoE::DataWriter::WriteScenItemsData(){
    scenFile.write(reinterpret_cast<const char*>(&data.scenarioItems),400*sizeof(ItemRecord));
    scenFile.write(reinterpret_cast<const char*>(&data.monstersNames),256*20*sizeof(int8_t));
    scenFile.write(reinterpret_cast<const char*>(&data.terrainsNames),256*30*sizeof(int8_t));
}

void BoE::DataWriter::WriteScenStrings(){
    for(int i = 0 ; i  < 270 ; i++){
        if(data.general.scenarioStringsLengths[i] > 0){
            scenFile.write(reinterpret_cast<const char*>(data.scenarioStrings[i].c_str()),data.general.scenarioStringsLengths[i]);
        }
    }
}

void BoE::DataWriter::WriteScenOutdoors(){
    for(int i = 0 ; i  < data.header.outdoorsDims[0]*data.header.outdoorsDims[1] ; i++){
        scenFile.write(reinterpret_cast<const char *>(&data.outdoorsData[i].outdoor),sizeof(OutdoorRecord));

        for(int j = 0 ; j < NumberOfStringsInOutdoorChunk ; j++){
            if(data.outdoorsData[i].outdoor.outdoorsStringsLengths[j] > 0){
                scenFile.write(reinterpret_cast<const char*>(data.outdoorsData[i].outdoor_strings[j].c_str()), data.outdoorsData[i].outdoor.outdoorsStringsLengths[j]);
            }
        }
    }
}

void BoE::DataWriter::WriteScenTowns(){
    for(int i = 0 ; i  < data.header.numberOfTowns ; i++){
        scenFile.write(reinterpret_cast<const char*>(&data.townsData[i].town), sizeof(TownRecord));

        int townSize = data.general.townsSize[i];
        for(int j = 0 ; j < townDataSizesFromType[townSize][0] ; j++){//cope for the weird terrain[x][y] format (y varying first, then x)
            scenFile.write(reinterpret_cast<const char*>(&data.townsData[i].terrain.terrain[j]), townDataSizesFromType[townSize][0]);
        }
        scenFile.write(reinterpret_cast<const char*>(&data.townsData[i].terrain.roomRects[0]), 16*sizeof(Rect16));
        scenFile.write(reinterpret_cast<const char*>(&data.townsData[i].terrain.creatures[0]), townDataSizesFromType[townSize][1]*sizeof(CreatureStart));
        scenFile.write(reinterpret_cast<const char*>(&data.townsData[i].terrain.lighting[0]), townDataSizesFromType[townSize][2]*townDataSizesFromType[townSize][0]*sizeof(uint8_t));

        for (int j = 0 ; j < NumberOfStringsInTown ; j++){
            if(data.townsData[i].town.townStringsLengths[j] > 0){
                scenFile.write(reinterpret_cast<const char*>(data.townsData[i].townStrings[j].c_str()), data.townsData[i].town.townStringsLengths[j]);
            }
        }

        scenFile.write(reinterpret_cast<const char*>(&data.townsData[i].talking), sizeof(TalkingRecord));

        for (int j = 0 ; j < NumberOfTalkingStringsInTown ; j++){
            if(data.townsData[i].talking.talkingStringsLengths[j] > 0){
                scenFile.write(reinterpret_cast<const char*>(data.townsData[i].talkingStrings[j].c_str()), data.townsData[i].talking.talkingStringsLengths[j]);
            }
        }
    }
}


void BoE::DataWriter::WriteScenario(std::string filename){
    scenFile.open(filename,std::ofstream::binary | std::ofstream::out);

    if(!scenFile){
        status = WriterStatus::CantOpenFile;
        return;
    }

    status = WriterStatus::Ok;

    WriteScenHeader();
    WriteScenItemsData();
    WriteScenStrings();
    WriteScenOutdoors();
    WriteScenTowns();
}
