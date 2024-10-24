#ifndef TERRAINS_HPP
#define TERRAINS_HPP

#include <inttypes.h>
namespace BoE{
    struct TerrainRecord{
        int16_t picture;
        uint8_t blockage;
        uint8_t flags[2];
        uint8_t special;
        uint8_t transToWhat;
        uint8_t flyOver;
        uint8_t boatOver;
        uint8_t blockHorse;
        uint8_t lightRadius;
        uint8_t stepSound;
        uint8_t shortcutKey;
        uint8_t res[3];
    };

    void OutputTerrainInfo(TerrainRecord &record);
}
#endif // TERRAINS_HPP
