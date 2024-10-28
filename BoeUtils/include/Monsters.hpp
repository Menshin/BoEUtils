#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include <inttypes.h>
#include "Misc.hpp"
namespace BoE{
    struct MonsterRecord{
        uint8_t monsterNumber, level, monsterName[26]; //monsterName is zeroed in the scenario file and fetched from the scenario monster name list
        int16_t health, maxHealth, magicPoints, maxMagicPoints;

        uint8_t armor, skill;
        int16_t attacks[3];
        uint8_t attackMainType, attackOthersType, monsterType, speed, actionPoints, magicUserLevel, clericLevel;
        uint8_t breath, breathType, treasure, specialSkill, poison;

        int16_t morale, maxMorale, loot, lootChance;
        int16_t status[15];

        uint8_t direction, immunities, xWidth, yWidth, radiate1, radiate2, defaultAttitude, summonType;
        uint8_t defaultFacialPic, reserved[3];
        int16_t pictureNumber;
    };

    struct CreatureStart{
        uint8_t number;

        uint8_t startAttitude;
        Location startLoc;

        uint8_t mobile;

        uint8_t timeFlag;

        uint8_t extra[2];

        int16_t special[2];
        int8_t specialEncounterCode;

        int8_t timeCode;
        int16_t monsterTime;
        int16_t personality;
        int16_t specialOnKill;
        int16_t facialPicture;

    };

    void OutputMonsterInfo(MonsterRecord &record);
    void OutputCreatureStartInfo(CreatureStart &creatureStart);

}
#endif // MONSTERS_HPP
