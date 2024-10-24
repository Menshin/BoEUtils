#include "Towns.hpp"
#include <iostream>
#include <iomanip>

using namespace BoE;

void BoE::OutputTownTerrainInfo(TownTerrain &townTerrain, int townType){

      for (int i = 0 ; i < townDataSizesFromType[townType][0] ; i++){
        for( int j = 0 ; j < townDataSizesFromType[townType][0] ; j++){
            std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(townTerrain.terrain[j][i]);//terrains in BoE are stored as [x][y] instead of [y][x]
        }
        std::cout << std::endl;
      }

      std::cout << std::dec << std::endl;

      for (int i = 0 ; i < 16 ; i++){
        std::cout << "Town rect " << i << " coordinates (" \
                  << static_cast<short>(townTerrain.roomRects[i].bottom) << "," \
                  << static_cast<short>(townTerrain.roomRects[i].left) << ")" \
                  << ", (" << static_cast<short>(townTerrain.roomRects[i].top) << "," \
                  << static_cast<short>(townTerrain.roomRects[i].right) << ")" << std::endl;
      }

      for(int i = 0 ; i < townDataSizesFromType[townType][1] ; i++){
        OutputCreatureStartInfo(townTerrain.creatures[i]);
        std::cout << std::endl;
      }

      std::cout << std::endl;

      for (int i = 0 ; i < townDataSizesFromType[townType][2] ; i++){
        for( int j = 0 ; j < townDataSizesFromType[townType][0] ; j++){
            std::cout << static_cast<int>(townTerrain.lighting[i][j]);//terrains in BoE are stored as [x][y] instead of [y][x]
        }
        std::cout << std::endl;
      }

      std::cout << std::endl;
}

void BoE::OutputTownInfo(TownData &townData){

    std::cout << "Town chop time: " << townData.town.townChopTime << "\tTown chop key: " << townData.town.townChopKey <<  std::endl;

    std::cout << std::endl;

    for (int i = 0 ; i < 4 ; i++){
        std::cout << "Wandering " << i << ": ";
        for(int j = 0 ; j < 4 ; j++){
            std::cout << static_cast<int>(townData.town.wandering[i].monst[j]) << " ";
        }
        std::cout << "at (" << static_cast<int>(townData.town.wanderingLocs[i].x) << "," << static_cast<int>(townData.town.wanderingLocs[i].y) << ")" << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0 ; i < 50 ; i++){
        std::cout << "Special " << i << " with id " << static_cast<int>(townData.town.specialsId[i]) \
                  << " at (" << static_cast<int>(townData.town.specialsLocations[i].x) << ","\
                  << static_cast<int>(townData.town.specialsLocations[i].y) << ")" << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0 ; i < 15 ; i++){
        std::cout << "Sign " << i << " location: (" << static_cast<int>(townData.town.signLocs[i].x) << "," << static_cast<int>(townData.town.signLocs[i].y) << ")" << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Lighting " << static_cast<int>(townData.town.lighting) << std::endl;

    std::cout << std::endl;

    for (int i = 0 ; i < 4 ; i++){
        std::cout << "Start " << i << " location: (" << static_cast<int>(townData.town.startLocs[i].x) << "," << static_cast<int>(townData.town.startLocs[i].y) << ")" << std::endl;
    }

    for (int i = 0 ; i < 4 ; i++){
        std::cout << "Exit " << i << " location: (" << static_cast<int>(townData.town.exitLocs[i].x) << "," << static_cast<int>(townData.town.exitLocs[i].y) << ")"  \
                  << " with special " << static_cast<short>(townData.town.exitSpecs[i])  << std::endl;
    }

    for (int i = 0 ; i < 64 ; i++){
        std::cout  << "Preset item " << i << std::endl;
        OutputPresetItemInfo(townData.town.presetItems[i]);
        std::cout << std::endl;
    }

    std::cout << "Max number of monsters: " << static_cast<short>(townData.town.maxNumbersOfMonsters) << std::endl;
    std::cout << std::endl;

    for (int i = 0 ; i < 50 ; i++){
        std::cout  << "Preset field " << i << std::endl;
        OutputPresetFieldInfo(townData.town.presetFields[i]);
        std::cout << std::endl;
    }

    std::cout << "Special on entry: " << static_cast<short>(townData.town.specOnEntry) << std::endl;
    std::cout << "Special on entry if town dead: " << static_cast<short>(townData.town.specOnEntryIfDead) << std::endl;

    std::cout << std::endl;

    for (int i = 0 ; i < 8 ; i++){
        std::cout << "Timer special " << static_cast<int>(townData.town.timerSpecs[i]) << " at time " << static_cast<int>(townData.town.timerSpecTimes[i]) << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0 ; i < 180 ; i++){
        std::cout << "Town string " << i << " length is " << static_cast<unsigned int>(townData.town.townStringsLengths[i]) << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0 ; i < 100 ; i++){
        std::cout << "Town special " << i << std::endl;
        OutputSpecialNodeInfo(townData.town.townSpecials[i]);
    }

    std::cout << std::endl;

    std::cout << "Special 1: " << static_cast<unsigned int>(townData.town.specials[0]) << " Special 2: " << static_cast<unsigned int>(townData.town.specials[1]) << std::endl;
    std::cout << "Reserved 1: " << static_cast<unsigned int>(townData.town.reserved[0]) << " Reserved 2: " << static_cast<unsigned int>(townData.town.reserved[1]) << std::endl;
    std::cout << "Difficulty: " << static_cast<short>(townData.town.difficulty) << std::endl;
}

void BoE::OutputTownStrings(TownData &townData){
    std::cout << "Town strings: " << std::endl;
    int i = 0;
    for(auto s : townData.townStrings){
        std::cout << i++ << ". " <<  s << std::endl;
    }
}
