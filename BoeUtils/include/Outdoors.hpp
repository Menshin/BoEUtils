#ifndef OUTDOORS_HPP
#define OUTDOORS_HPP

#include <string>
#include <vector>
#include "Misc.hpp"

namespace BoE{

    struct OutdoorRecord{
        uint8_t terrain[48][48];

        Location specialLocs[18];
        uint8_t specialIds[18];

        Location exitLocs[8];
        int8_t exitDest[8];

        Location signLocs[8];

        OutdoorWandering wandering[4];
        OutdoorWandering specialEnc[4];

        Location wanderingLocs[4];

        Rect16 infoRect[8];

        uint8_t outdoorsStringsLengths[180];

        SpecialNode outdoorSpecials[60];
    };

    struct OutdoorChunk{
        OutdoorRecord outdoor;
        std::vector<std::string> outdoor_strings;
    };

    void OutputOutdoorInfo(OutdoorChunk &outdoorChunk);

}

#endif // OUTDOORS_HPP
