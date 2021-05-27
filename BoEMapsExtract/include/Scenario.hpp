/*
 * Contains functions that handles everything related to the
 * scenario data (general IO, parsing, data extraction, etc).
 */

#ifndef SCENARIO_HPP
#define SCENARIO_HPP

#include <fstream>
#include <vector>
#include "BitUtils.hpp"
#include "ArgsHandler.hpp"

enum class ScenFileStatus{Ok, ErrorReadingFile, InvalidScenarioFile};

//scenario file offset values
constexpr int terTypesOffset = 0x7A98; //offset to the terrain templates in the scenario header
constexpr int scenStrLensOffset = 0xA2A4; //offset to the scenario strings lengths array in the scenario header
constexpr int scenStringsOffset = 0x13CF6; //offset to the scenario strings in the scenario file
constexpr int outdoorStrLensOffset = 0xA56-48*48; //offset relative to the Outdoor Record struct
constexpr int townStrLensOffset = 0x460; //offset relative to the Town Record struct
constexpr int townStrLensToEndOffset = 0xDB2 - 0x514; //offset to the end of the Town Record struct from townStrLens
constexpr int townTerrainToEndOffset[3] ={0x7A8,0x510,0x394};//offsets to the end of the TownTrSize struct from townTerrain depending on the town size
constexpr int talkingStrLenToEndOffset = 0x4B0;//offset to the end of the Talking Record struct from talkingStrLens

constexpr int sizeOfSpecialNodeType = 0x16;
constexpr int townTypesSizes[3]{64,48,32}; //Town terrain dimensions by town size

/*
 * TownData will contain the town terrain and infos
 * Unlike outdoor the terrain size can vary
 */
struct TownData{
    TownData(int _townNumber, int _townSize) : townNumber(_townNumber), townSize(_townSize){};

    int townNumber;
    int townSize; //0-Large, 1-Average, 2-Tiny
    std::string townName;
    std::vector<unsigned char> townTerrain;
};

/*
 * Outdoors are split in 48*48 tiles chunks
 */
struct OutdoorChunk{
    std::string chunkName;
    unsigned char outdoorChunk[48*48];
};

/*
 * Main data structure, will be served to the MapExtractor once filled
 */
struct ScenData{
    unsigned char scenVersion[3];
    unsigned char numberOfTowns;
    unsigned char outdoorsDims[2];
    int16_t terrainsPictures[256]; //terrain id <=> terrain picture correspondence
    unsigned char strLens[300]; //needed to skip over the scenario strings section
    std::string scenName;
    std::vector<unsigned char> townsSize;
    std::vector<TownData> townsData;
    std::vector<OutdoorChunk> outdoorsChunks;
};

/*
 * This class will handle the parsing of the scenario file and fill
 * the ScenData structure with extracted data
 */
class Scenario{
    public:
        Scenario(Arguments *args);
        ~Scenario();

        ScenFileStatus GetStatus() {return status;}
        bool IsOk() { return status == ScenFileStatus::Ok; } //convenience wrapper
        std::string GetError();

        ScenData scenData;

    private:
        bool ReadScenarioHeader(int extractOption);
        void ReadScenarioOutdoors(int extractOptions);
        void ReadScenarioTowns(int extractOptions);
        std::ifstream scenFile;
        ScenFileStatus status;

        //do we need to handle old Mac (Motorola 680x0 - Big Endian) to Windows (Intel - Little Endian) conversion ?
        bool isDifferentEndianness;
};

/*
 * Purely cosmetic as some c-strings have lots of trailing
 * space in the base scenarios
 */
void RemoveTrailingSpaces(char *str, int strSize);

#endif // SCENARIO_HPP
