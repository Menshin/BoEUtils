/*
 * Various data structures used through the BoE code
 */

#ifndef MISC_HPP
#define MISC_HPP

#include <inttypes.h>

struct Location{
    int8_t x, y;
};

struct Rect16{
    int16_t left, top, right, bottom;
};

struct OutdoorWandering{
    unsigned char monst[7];
    unsigned char friendly[3];
    int16_t spec_on_meet, spec_on_win, spec_on_flee;
    int16_t cantflee;
    int16_t end_spec1, end_spec2;
};

struct Wandering{
    uint8_t monst[4];
};

struct SpecialNode{
    int16_t type;
    int16_t sd1, sd2;
    int16_t pic, m1, m2;
    int16_t ex1a, ex1b, ex2a, ex2b;
    int16_t jumpto;
};

struct TransportRecord{ //horse or boat
    Location townLocation, outdoorLocation, sector;
    int16_t currentTownNumber;
    int8_t exists, property;
};

struct ItemStorageShortcut{
    int16_t terrainType;
    int16_t itemNumber[10];
    int16_t itemOdds[10];
    int16_t property;
};

struct PresetField{
    Location fieldLoc;
    int16_t fieldType;
};

void OutputTransportInfo(TransportRecord &record);
void OutputSpecialNodeInfo(SpecialNode &node);
void OutputOutdoorWanderingInfo(OutdoorWandering &record);
void OutputPresetFieldInfo(PresetField &presetField);

#endif // MISC_HPP
