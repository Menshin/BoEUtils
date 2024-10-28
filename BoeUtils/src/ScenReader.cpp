#include "ScenReader.hpp"

using namespace BoE;

DataOffsets dataOffsets;

DataReader::DataReader(std::string filename, ScenData &_data): data{_data}{
    LoadScenario(filename);
}

BoE::DataReader::~DataReader(){
    scenFile.close();
}

bool BoE::DataReader::ValidateScenario(){
    uint32_t scenFormatFlags;

    scenFile.seekg(0,std::fstream::beg);
    scenFile.read(reinterpret_cast<char*>(&scenFormatFlags),4);

    switch(scenFormatFlags){
        case 0x281e140a: //Scen is BigEndian, platform is LittleEndian
            differentEndianness = true;
            break;

        case 0x14283c50: //Scen is LittleEndian, platform is BigEndian
            differentEndianness = true;
            break;

        case 0x503c2814: //Scen is LittleEndian, platform is LittleEndian
            differentEndianness = false;
            break;

        case 0x0a141e28: //Scen is BigEndian, platform is BigEndian
            differentEndianness = false;
            break;

        default: //error file is not a valid scenario
            return false;
            break;
    }
    return true;
}

std::string BoE::DataReader::GetErrorMessage() const{
    switch(status){
        case ReaderStatus::FileNotFound:
            return std::string{"DATA READER: File not found."};
        case ReaderStatus::InvalidFile:
            return std::string{"DATA READER: File isn't a valid BoE scenario."};
        case ReaderStatus::Ok:
            return std::string{"No error."};
        default:
            return std::string{"DATA READER: Unspecified error."};
    }
}

void BoE::DataReader::ReadHeader(){
    scenFile.seekg(0,std::fstream::beg);
    scenFile.read(reinterpret_cast<char*>(&data.header),sizeof(ScenHeader));

    //Update the validation flags since we're flipping endianness
    if(differentEndianness){
        FlipWinMacFlags();
    }
}

void BoE::DataReader::ReadGeneralData(){
    scenFile.seekg(dataOffsets.generalDataStart,std::fstream::beg);
    scenFile.read(reinterpret_cast<char*>(&data.general.townsSize),200);
    scenFile.read(reinterpret_cast<char*>(&data.general.townsHidden),200);
    scenFile.seekg(1,std::fstream::cur); //skip unsigned char a

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[0]), 1, differentEndianness); //flag_a
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.introMessagePicture), 2, differentEndianness); //introMessagePicture + introMessageLength
    scenFile.read(reinterpret_cast<char*>(&data.general.startingTownSpawnLoc),3*2); //startingTownSpawnLoc + startingOutdoorSector + startingOutdoorSpawnLoc
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.startingTownNumber), 1, differentEndianness);
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[1]), 1, differentEndianness); //flag_b

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.townsDataSize), 200*5, differentEndianness);
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.townsToAddTo), 10, differentEndianness);
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.townsFlagToAddTo), 20, differentEndianness);

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[2]), 1, differentEndianness); //flag_c

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.outdoorsDataSize), 100*2, differentEndianness);

    //Can't just flip Rect attributes if conversion is needed, since the structure is different between Mac and Windows
    scenFile.read(reinterpret_cast<char*>(&data.general.storeItemRects),3*sizeof(Rect16));
    if(differentEndianness){
        for(int i = 0 ; i < 4 ; i++){
            FlipRect(data.general.storeItemRects[i]);
        }
    }
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.storeItemsTowns), 3, differentEndianness);

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[4]), 1, differentEndianness); //flag_e (flag_d is at the bottom of the data)

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.specialItems), 50*2, differentEndianness); //specialItems + specialItemsSpecial

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.rating), 2*1, differentEndianness); //rating + usesCustomGraphics

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[5]), 1, differentEndianness); //flag_f

    for(int i = 0 ; i < 256 ; ++i)
        ReadMonsterRecord(data.general.scenarioMonsters[i]);

    for(int i = 0 ; i < 30 ; ++i)
        ReadTransportRecord(data.general.scenarioBoats[i]);
    for(int i = 0 ; i < 30 ; ++i)
        ReadTransportRecord(data.general.scenarioHorses[i]);

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[6]), 1, differentEndianness); //flag_g

    for(int i = 0 ; i < 256 ; ++i)
        ReadTerrainRecord(data.general.terrainTypes[i]);

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.scenarioTimerTimes), 20+20, differentEndianness); //scenarioTimerTimes + scenarioTimerSpecials

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[7]), 1, differentEndianness); //flag_h

    for(int i = 0 ; i < 256 ; ++i)
        ReadSpecialNode(data.general.scenarioSpecials[i]);

    for(int i = 0 ; i < 10 ; ++i)
        ReadItemStorageShortcut(data.general.storageShortcuts[i]);

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[3]), 1, differentEndianness); //flag_d

    scenFile.read(reinterpret_cast<char*>(&data.general.scenarioStringsLengths),300);

    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.flags[8]), 1, differentEndianness); //flag_i

    scenFile.read(reinterpret_cast<char*>(&data.general.lastOutdoorEdited),sizeof(Location));
    Read16bits(scenFile, reinterpret_cast<char*>(&data.general.lastTownEdited), 1, differentEndianness);
}

void BoE::DataReader::ReadTransportRecord(TransportRecord &record){
    scenFile.read(reinterpret_cast<char*>(&record),sizeof(TransportRecord));

    if(differentEndianness)
        Flip16BytesValue(record.currentTownNumber);
}

void BoE::DataReader::ReadTerrainRecord(TerrainRecord &record){
    scenFile.read(reinterpret_cast<char*>(&record),sizeof(TerrainRecord));

    if(differentEndianness)
        Flip16BytesValue(record.picture);
}

void BoE::DataReader::ReadMonsterRecord(MonsterRecord &record){
    scenFile.read(reinterpret_cast<char*>(&record),sizeof(MonsterRecord));

    if(differentEndianness){
        FlipMonsterRecord(record);
    }
}

void BoE::DataReader::ReadSpecialNode(SpecialNode &node){
    Read16bits(scenFile, reinterpret_cast<char*>(&node), 11, differentEndianness);
}

void BoE::DataReader::ReadItemStorageShortcut(ItemStorageShortcut &shortcut){
    Read16bits(scenFile, reinterpret_cast<char*>(&shortcut), 22, differentEndianness);
}

void BoE::DataReader::ReadItemRecord(ItemRecord &record){
    scenFile.read(reinterpret_cast<char*>(&record),sizeof(ItemRecord));

    if(differentEndianness){
        FlipItemRecord(record);
    }
}

void BoE::DataReader::ReadScenItemsData(){
    for (int i = 0 ; i < 400 ; i++){
        ReadItemRecord(data.scenarioItems[i]);
    }
    scenFile.read(reinterpret_cast<char*>(&data.monstersNames[0]),256*20);
    scenFile.read(reinterpret_cast<char*>(&data.terrainsNames[0]),256*30);
}

void BoE::DataReader::ReadScenStrings(){
    for (int i = 0 ; i < 270 ; i++){
        char buffer[256];
        scenFile.read(buffer,data.general.scenarioStringsLengths[i]);
        buffer[data.general.scenarioStringsLengths[i]] = '\0';
        data.scenarioStrings.push_back(buffer);
    }
}

void BoE::DataReader::ReadScenOutdoors(){
    char buffer[256];

    for (int i = 0 ; i < data.header.outdoorsDims[0]*data.header.outdoorsDims[1] ; i++){
        OutdoorChunk outdoorChunk;
        scenFile.read(reinterpret_cast<char*>(&outdoorChunk.outdoor),sizeof(OutdoorRecord));

        for(int stringNumber = 0; stringNumber < NumberOfStringsInOutdoorChunk ; stringNumber++){
                scenFile.read(buffer, outdoorChunk.outdoor.outdoorsStringsLengths[stringNumber]);
                buffer[outdoorChunk.outdoor.outdoorsStringsLengths[stringNumber]] = '\0';
                outdoorChunk.outdoor_strings.push_back(buffer);
        }

        if(differentEndianness){
            FlipOutdoorChunkEndianness(outdoorChunk);
        }

        data.outdoorsData.push_back(outdoorChunk);
    }
}

 void BoE::DataReader::ReadTerrainType(TownTerrain &townTerrain, int terrainType){
    //fill line by line (actually row by row in game) the terrain array (which can be larger than the actual terrain type if a medium or small town)
    for (int i = 0 ; i < townDataSizesFromType[terrainType][0] ; i++){
        scenFile.read(reinterpret_cast<char*>(&townTerrain.terrain[i]), townDataSizesFromType[terrainType][0]);
    }

    scenFile.read(reinterpret_cast<char*>(townTerrain.roomRects), 16*sizeof(Rect16));
    scenFile.read(reinterpret_cast<char*>(townTerrain.creatures), townDataSizesFromType[terrainType][1]*sizeof(CreatureStart));
    scenFile.read(reinterpret_cast<char*>(&townTerrain.lighting[0][0]), townDataSizesFromType[terrainType][2]*townDataSizesFromType[terrainType][0]*sizeof(uint8_t));

    if(differentEndianness){
        FlipTownTerrainEndianness(townTerrain, terrainType);
    }
}

 void BoE::DataReader::ReadScenTowns(){
     char buffer[256];

     for (int townNumber = 0 ; townNumber < data.header.numberOfTowns ; townNumber++){
        TownData townData;

        scenFile.read(reinterpret_cast<char*>(&townData.town),sizeof(TownRecord));
        ReadTerrainType(townData.terrain, data.general.townsSize[townNumber]);

        for (int i = 0 ; i < NumberOfStringsInTown ; i++){
            scenFile.read(buffer,townData.town.townStringsLengths[i]);
            buffer[townData.town.townStringsLengths[i]] = '\0';
            townData.townStrings.push_back(buffer);
        }

        scenFile.read(reinterpret_cast<char*>(townData.talking.talkingStringsLengths), 200*sizeof(uint8_t));
        scenFile.read(reinterpret_cast<char*>(townData.talking.talkingNodes), 60*sizeof(TalkingNode));

        for (int i = 0 ; i < NumberOfTalkingStringsInTown ; i++){
            scenFile.read(buffer, townData.talking.talkingStringsLengths[i]);
            buffer[townData.talking.talkingStringsLengths[i]] = '\0';
            townData.talkingStrings.push_back(buffer);
        }

        if(differentEndianness){
            FlipTownDataEndianness(townData);
        }

        data.townsData.push_back(townData);
     }
}

void BoE::DataReader::LoadScenario(std::string filename){
    scenFile.open(filename,std::ifstream::binary | std::ofstream::in);

    if(!scenFile){
        status = ReaderStatus::FileNotFound;
        return;
    }

    if(!ValidateScenario()){
        status = ReaderStatus::InvalidFile;
        return;
    }

    status = ReaderStatus::Ok;

    ReadHeader();
    ReadGeneralData();
    ReadScenItemsData();
    ReadScenStrings();
    ReadScenOutdoors();
    ReadScenTowns();
}

/*
 * Endianness flipping helpers
 */

void BoE::DataReader::FlipTownTerrainEndianness(TownTerrain &townTerrain, int terrainType){
    for (int i = 0 ; i < 16 ; i++){
        FlipRect(townTerrain.roomRects[i]);
    }

    for(int i = 0 ; i < townDataSizesFromType[terrainType][1] ; i++){
        Flip16BytesValue(townTerrain.creatures[i].special[0]);
        Flip16BytesValue(townTerrain.creatures[i].special[1]);
        Flip16BytesValue(townTerrain.creatures[i].monsterTime);
        Flip16BytesValue(townTerrain.creatures[i].personality);
        Flip16BytesValue(townTerrain.creatures[i].specialOnKill);
        Flip16BytesValue(townTerrain.creatures[i].facialPicture);
    }
}

void BoE::DataReader::FlipTownDataEndianness(TownData &townData){
    //town
    Flip16BytesValue(townData.town.townChopTime);
    Flip16BytesValue(townData.town.townChopKey);
    Flip16BytesValue(townData.town.lighting);

    for(int i = 0 ; i < 4 ; i++){
        Flip16BytesValue(townData.town.exitSpecs[i]);
    }

    FlipRect(townData.town.inTownRect);

    for (int i = 0 ; i < 64 ; i++){
       Flip16BytesValue(townData.town.presetItems[i].itemCode);
       Flip16BytesValue(townData.town.presetItems[i].ability);
    }

    Flip16BytesValue(townData.town.maxNumbersOfMonsters);

    for (int i = 0 ; i < 50 ; i++){
       Flip16BytesValue(townData.town.presetFields[i].fieldType);
    }

    Flip16BytesValue(townData.town.specOnEntry);
    Flip16BytesValue(townData.town.specOnEntryIfDead);

    for (int i = 0 ; i < 8 ; i++){
        Flip16BytesValue(townData.town.timerSpecTimes[i]);
        Flip16BytesValue(townData.town.timerSpecs[i]);
    }

    for (int i = 0 ; i < 100 ; i++){
        Flip16BytesValue(townData.town.townSpecials[i].ex1a);
        Flip16BytesValue(townData.town.townSpecials[i].ex1b);
        Flip16BytesValue(townData.town.townSpecials[i].ex2a);
        Flip16BytesValue(townData.town.townSpecials[i].ex2b);
        Flip16BytesValue(townData.town.townSpecials[i].jumpto);
        Flip16BytesValue(townData.town.townSpecials[i].m1);
        Flip16BytesValue(townData.town.townSpecials[i].m2);
        Flip16BytesValue(townData.town.townSpecials[i].pic);
        Flip16BytesValue(townData.town.townSpecials[i].sd1);
        Flip16BytesValue(townData.town.townSpecials[i].sd2);
        Flip16BytesValue(townData.town.townSpecials[i].type);
    }

    Flip16BytesValue(townData.town.difficulty);

    //talking nodes
    for (int i = 0 ; i < 60 ; i++){
        Flip16BytesValue(townData.talking.talkingNodes[i].personality);
        Flip16BytesValue(townData.talking.talkingNodes[i].type);
        for (int j = 0 ; j < 4 ; j++){
            Flip16BytesValue(townData.talking.talkingNodes[i].extras[j]);
        }
    }
}

void BoE::DataReader::FlipOutdoorChunkEndianness(OutdoorChunk &outdoorChunk){
    for (int i = 0 ; i < 4 ; i++){
        Flip16BytesValue(outdoorChunk.outdoor.wandering[i].spec_on_meet);
        Flip16BytesValue(outdoorChunk.outdoor.wandering[i].spec_on_win);
        Flip16BytesValue(outdoorChunk.outdoor.wandering[i].spec_on_flee);
        Flip16BytesValue(outdoorChunk.outdoor.wandering[i].cantflee);
        Flip16BytesValue(outdoorChunk.outdoor.wandering[i].end_spec1);
        Flip16BytesValue(outdoorChunk.outdoor.wandering[i].end_spec2);

        Flip16BytesValue(outdoorChunk.outdoor.specialEnc[i].spec_on_meet);
        Flip16BytesValue(outdoorChunk.outdoor.specialEnc[i].spec_on_win);
        Flip16BytesValue(outdoorChunk.outdoor.specialEnc[i].spec_on_flee);
        Flip16BytesValue(outdoorChunk.outdoor.specialEnc[i].cantflee);
        Flip16BytesValue(outdoorChunk.outdoor.specialEnc[i].end_spec1);
        Flip16BytesValue(outdoorChunk.outdoor.specialEnc[i].end_spec2);
    }

     for (int i = 0 ; i < 8 ; i++){
        FlipRect(outdoorChunk.outdoor.infoRect[i]);
    }

     for (int i = 0 ; i < 60 ; i++){
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].ex1a);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].ex1b);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].ex2a);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].ex2b);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].jumpto);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].m1);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].m2);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].pic);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].sd1);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].sd2);
        Flip16BytesValue(outdoorChunk.outdoor.outdoorSpecials[i].type);
    }
}

void BoE::DataReader::FlipItemRecord(ItemRecord &record){
    Flip16BytesValue(record.variety);
    Flip16BytesValue(record.itemLevel);
    Flip16BytesValue(record.value);
}

void BoE::DataReader::FlipMonsterRecord(MonsterRecord &record){
    Flip16BytesValue(record.health);
    Flip16BytesValue(record.maxHealth);
    Flip16BytesValue(record.magicPoints);
    Flip16BytesValue(record.maxMagicPoints);
    for(int i = 0 ; i < 3 ; ++i)
        Flip16BytesValue(record.attacks[i]);
    Flip16BytesValue(record.morale);
    Flip16BytesValue(record.maxMorale);
    Flip16BytesValue(record.loot);
    Flip16BytesValue(record.lootChance);
    for(int i = 0 ; i < 15 ; ++i)
        Flip16BytesValue(record.status[i]);
    Flip16BytesValue(record.pictureNumber);
}

void BoE::DataReader::FlipRect(Rect16 &rect){
    Flip16BytesValue(rect.bottom);
    Flip16BytesValue(rect.left);
    Flip16BytesValue(rect.right);
    Flip16BytesValue(rect.top);

    short tmp = rect.bottom;
    rect.bottom = rect.right;
    rect.right = tmp;

    tmp = rect.top;
    rect.top = rect.left;
    rect.left = tmp;
}

void BoE::DataReader::FlipWinMacFlags(){
    data.header.validationFlags[0] = 0x14;
    data.header.validationFlags[1] = 0x28;
    data.header.validationFlags[2] = 0x3c;
    data.header.validationFlags[3] = 0x50;
}
