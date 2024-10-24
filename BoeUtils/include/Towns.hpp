#ifndef TOWNS_HPP
#define TOWNS_HPP

#include <string>
#include <vector>

#include "Items.hpp"
#include "Monsters.hpp"
#include "Talking.hpp"
#include "Misc.hpp"

namespace BoE{

    //terrain size (square), number of creatures, number of lightings
    const int townDataSizesFromType[3][3] {{64,60,8},{48,40,6},{32,30,4}};

    enum TownSizes{Big = 0, Average, Tiny};

    struct TownRecord{
        int16_t townChopTime, townChopKey;

        Wandering wandering[4];
        Location wanderingLocs[4];

        Location specialsLocations[50];
        uint8_t specialsId[50];

        Location signLocs[15];

        int16_t lighting;

        Location startLocs[4], exitLocs[4];
        int16_t exitSpecs[4];

        Rect16 inTownRect;

        PresetItem presetItems[64];

        int16_t maxNumbersOfMonsters;

        PresetField presetFields[50];

        int16_t specOnEntry, specOnEntryIfDead;
        int16_t timerSpecTimes[8], timerSpecs[8];

        uint8_t townStringsLengths[180];

        SpecialNode townSpecials[100];

        uint8_t specials[2], reserved[2];

        int16_t difficulty;
    };

    struct TownTerrain{
        uint8_t terrain[64][64]; //different from the game structure, which depends on the town size
        Rect16 roomRects[16];
        CreatureStart creatures[60]; //different from the game structure, which depends on the town size
        uint8_t lighting[8][64]; //different from the game structure, which depends on the town size

        //int terrainSize; //0 - big, 1 - average, 2 - tiny
    };

    struct TownData{
        TownRecord town;
        TownTerrain terrain;
        std::vector<std::string> townStrings;
        TalkingRecord talking;
        std::vector<std::string> talkingStrings;
    };

    void OutputTownInfo(TownData &townData);
    void OutputTownTerrainInfo(TownTerrain &terrain, int terrainType);
    void OutputTownStrings(TownData &townData);
}

#endif // TOWNS_HPP
