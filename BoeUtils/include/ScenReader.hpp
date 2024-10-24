#pragma once

#include <fstream>
#include "Scenario.hpp"
#include "Monsters.hpp"
#include "Misc.hpp"
#include "BitUtils.hpp"
#include "Towns.hpp"

namespace BoE{

 enum class ReaderStatus{Ok, FileNotFound, InvalidFile};

 /*
 * Generic BoE scenarios data reader, handles platform/scenario endianness conflicts
 */

 class DataReader{
        public:
            //DataReader(){};
            DataReader(std::string filename, ScenData &_data);
            ~DataReader();

            bool IsOk() const {return status == ReaderStatus::Ok;}
            ReaderStatus GetStatus() const {return status;}
            std::string GetErrorMessage() const;
            void LoadScenario(std::string filename);


        private:
            std::ifstream scenFile;
            ScenData& data;

            bool differentEndianness{false}; //does scenario endianness differs from platform endianness?
            ReaderStatus status;

            bool ValidateScenario();
            void ReadHeader();
            void ReadGeneralData();
            void ReadScenItemsData();
            void ReadScenStrings();
            void ReadScenOutdoors();
            void ReadScenTowns();

            void ReadMonsterRecord(MonsterRecord &record);
            void ReadItemRecord(ItemRecord &record);
            void ReadTransportRecord(TransportRecord &record);
            void ReadTerrainRecord(TerrainRecord &record);
            void ReadSpecialNode(SpecialNode &node);//endianness flipping handled here
            void ReadItemStorageShortcut(ItemStorageShortcut &shortcut);//endianness flipping handled here
            void ReadTerrainType(TownTerrain &townTerrain, int terrainSize);

            void FlipTownTerrainEndianness(TownTerrain &terrain, int terrainType);
            void FlipTownDataEndianness(TownData &townData);
            void FlipOutdoorChunkEndianness(OutdoorChunk &outdoorChunk);
            void FlipItemRecord(ItemRecord &record);
            void FlipMonsterRecord(MonsterRecord &record);
    };
}

