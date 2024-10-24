#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <inttypes.h>
#include "Misc.hpp"

namespace BoE{

    struct ItemRecord{
        int16_t variety;
        int16_t itemLevel;
        int8_t awkward;
        int8_t bonus;
        int8_t protection;
        int8_t charges;
        int8_t type;
        int8_t magicUseType;
        uint8_t graphicNumber;
        uint8_t ability;
        uint8_t abilityStrength;
        uint8_t typeFlag;
        uint8_t isSpecial;
        uint8_t a;
        int16_t value;
        uint8_t weight;
        uint8_t specialClass;
        Location itemLoc;
        int8_t fullname[25];
        int8_t name[15];
        uint8_t treasureClass;
        uint8_t itemProperties;
        uint8_t reserved[2];
    };



    struct PresetItem{
        Location itemLoc;
        int16_t itemCode;
        int16_t ability;
        uint8_t charges;
        uint8_t alwaysThere;
        uint8_t property;
        uint8_t contained;
    };

    void OutputItemInfo(ItemRecord &record);
    void OutputPresetItemInfo(PresetItem &record);
}

#endif // ITEMS_HPP
