#pragma once

#include <iostream>
#include <vector>
#include "Outdoors.hpp"
#include "Towns.hpp"
#include "Monsters.hpp"
#include "Terrains.hpp"
#include "Items.hpp"
#include "Misc.hpp"

namespace BoE{

    enum class ScenarioStatus{Ok, ReaderError};
    const int NumberOfStringsInOutdoorChunk = 120; //180 reserved with 60 unused
    const int NumberOfStringsInTown = 140; //180 reserved with 40 unused
    const int NumberOfTalkingStringsInTown = 200;

    struct DataOffsets{
        size_t generalDataStart = 0x11;
        size_t itemsDataStart = 0xA3D6;
        size_t scenariosStringsStart = 0x13CF6;
        size_t outdoorsDataStart;
        size_t townsDataStart;
        };

    /*
     * Scenario Header, contains various data size and misc. infos
     */
    struct ScenHeader{
        uint8_t validationFlags[4];
        uint8_t version[3];
        uint8_t minRunVersion;
        uint8_t progMakeVersion[3];
        uint8_t numberOfTowns;
        uint8_t outdoorsDims[2];
        uint8_t difficulty;
        uint8_t introPic;
        uint8_t defaultGround;
    };

    /*
     * Scenario general data : terrains types, monsters types, scen specials,town/items/strings related data, etc
     */
    struct ScenGeneral{
        uint8_t townsSize[200], townsHidden[200];
        int16_t flags[9];

        int16_t introMessagePicture, introMessageLength;
        Location startingTownSpawnLoc, startingOutdoorSector, startingOutdoorSpawnLoc;
        int16_t startingTownNumber;

        int16_t townsDataSize[200][5];
        int16_t outdoorsDataSize[100][2];
        int16_t townsToAddTo[10];
        int16_t townsFlagToAddTo[10][2];

        Rect16 storeItemRects[3];
        int16_t storeItemsTowns[3];

        int16_t specialItems[50], specialItemsSpecial[50];
        int16_t rating, usesCustomGraphics;

        MonsterRecord scenarioMonsters[256];
        TransportRecord scenarioBoats[30];
        TransportRecord scenarioHorses[30];

        TerrainRecord terrainTypes[256];

        int16_t scenarioTimerTimes[20];
        int16_t scenarioTimerSpecials[20];

        SpecialNode scenarioSpecials[256];

        ItemStorageShortcut storageShortcuts[10];

        uint8_t scenarioStringsLengths[300];

        Location lastOutdoorEdited;
        int16_t lastTownEdited;
    };

    /*
     * Main data structure
     */
    struct ScenData{
        ScenHeader header;
        ScenGeneral general;

        ItemRecord scenarioItems[400];
        int8_t monstersNames[256][20];
        int8_t terrainsNames[256][30];

        std::vector<std::string> scenarioStrings;

        std::vector<OutdoorChunk> outdoorsData;
        std::vector<TownData> townsData;
         //terrain id <=> terrain picture correspondence
        /*int16_t terrainsPictures[125] = {0,86,86,1,1,2,3,3,4,5,5,6,7,5,8,9,
                                          10,11,12,13,13,15,14,14,14,16,17,18,19,20,21,22,
                                          23,24,25,25,400,405,405,28,29,30,31,32,33,34,35,36,
                                          36,37,37,38,38,408,404,404,403,42,42,43,43,44,45,46,
                                          47,401,402,50,406,406,406,52,53,54,56,56,58,61,59,60,
                                          57,23,65,64,63,62,66,67,67,68,69,69,70,71,72,73,
                                          55,74,75,76,77,78,406,406,406,81,81,79,80,57,57,14,
                                          57,23,7,82,83,84,85,407,87,87,88,0,89};*/
    };

/*
 * Scenario class, parse the file and fill the various data substructures
 */

    class Scenario{
        public:

            Scenario(std::string filename);
            ~Scenario();

            bool IsOk() {return status == ScenarioStatus::Ok;}
            ScenarioStatus GetStatus() const{return status;}
            std::string GetErrorMessage() const;
            ScenData& GetScenData() {return data;}
            const ScenData& GetScenData() const{return data;}

            ScenHeader GetScenHeader() const{return data.header;}
            ScenGeneral GetScenGeneral() const{return data.general;}

            void SaveScenario(std::string filename);

            void OutputGeneralInfo();
        private:
            ScenarioStatus status;
            ScenData data;
    };

}

