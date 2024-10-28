#include "Monsters.hpp"
#include <iostream>

using namespace BoE;

void BoE::OutputMonsterInfo(MonsterRecord &record){

    std::cout << "Number: " << static_cast<int>(record.monsterNumber) << " Level: " << static_cast<int>(record.level) << " Name: " << record.monsterName << std::endl;
    std::cout << "Health: " << static_cast<int>(record.health) << " Max Health: " << static_cast<int>(record.maxHealth) \
              << " MP: " << static_cast<int>(record.magicPoints) << " Max MP: " << static_cast<int>(record.maxMagicPoints) << std::endl;

    std::cout << "Armor: " << static_cast<int>(record.armor) << " Skill: "  << static_cast<int>(record.skill) << std::endl;
    std::cout << "Attack 1: " << static_cast<int>(record.attacks[0]) << " Attack 2: "  << static_cast<int>(record.attacks[1]) << " Attack 3: "  << static_cast<int>(record.attacks[2]) << std::endl;

    std::cout << "Main attack type: " << static_cast<int>(record.attackMainType) << " Other attack Type: "  << static_cast<int>(record.attackOthersType) << std::endl;

    std::cout << "monsterType: " << static_cast<int>(record.monsterType) << " Speed: "  << static_cast<int>(record.speed) << " Action points: "  << static_cast<int>(record.actionPoints) << std::endl;
    std::cout << "Magic user level: " << static_cast<int>(record.magicUserLevel) << " Cleric user level: "  << static_cast<int>(record.clericLevel) << std::endl;


    std::cout << "Breath: " << static_cast<int>(record.breath) << " Breath Type: "  << static_cast<int>(record.breathType) << " Treasure: "  << static_cast<int>(record.treasure) << std::endl;
    std::cout << "Special skill: " << static_cast<int>(record.specialSkill) << " Poison: "  << static_cast<int>(record.poison) << std::endl;

    std::cout << "Morale: " << static_cast<int>(record.morale) << " Max Morale: "  << static_cast<int>(record.maxMorale) << std::endl;
    std::cout << "Loot: " << static_cast<int>(record.loot) << " Loot chance: "  << static_cast<int>(record.lootChance) << std::endl;
    std::cout << "Status: ";
    for(int i = 0 ; i < 15 ; ++i)
        std::cout << static_cast<int>(record.status[i]) << " ";
    std::cout << std::endl;

    std::cout << "Direction: " << static_cast<int>(record.direction) << " Immunities: "  << static_cast<int>(record.immunities) << std::endl;
    std::cout << "xWidth: " << static_cast<int>(record.xWidth) << " yWidth: "  << static_cast<int>(record.yWidth) << std::endl;
    std::cout << "Radiate 1: " << static_cast<int>(record.radiate1) << " Radiate 2: "  << static_cast<int>(record.radiate2) << std::endl;
    std::cout << "Default attitude: " << static_cast<int>(record.defaultAttitude) << " Summon Type: "  << static_cast<int>(record.summonType) << std::endl;

    std::cout << "Default facial pic: " << static_cast<int>(record.defaultFacialPic) << " Picture number: "  << static_cast<int>(record.pictureNumber) << std::endl;

    std::cout << std::endl;

}

void BoE::OutputCreatureStartInfo(CreatureStart &creatureStart){
    std::cout << "Number: " << static_cast<int>(creatureStart.number) << " Start attitude: " << static_cast<int>(creatureStart.startAttitude) << std::endl;
    std::cout << "Location: (" << static_cast<int>(creatureStart.startLoc.x) << "," << static_cast<int>(creatureStart.startLoc.y) << ")" << std::endl;
    std::cout << "Mobile: " << static_cast<int>(creatureStart.mobile) << " Time flag: " << static_cast<int>(creatureStart.timeFlag) << std::endl;
    std::cout << "Extra 1: " << static_cast<int>(creatureStart.extra[0]) << " Extra 2: " << static_cast<int>(creatureStart.extra[1]) << std::endl;

    std::cout << "Special 1: " << static_cast<short>(creatureStart.special[0]) << " Special 2: " << static_cast<short>(creatureStart.special[1]) << std::endl;
    std::cout << "Special encounter code: " << static_cast<int>(creatureStart.specialEncounterCode) << " Time code: " << static_cast<int>(creatureStart.timeCode) << std::endl;
    std::cout << "Monster time: " << static_cast<short>(creatureStart.monsterTime) << " Personality: " << static_cast<short>(creatureStart.personality) << std::endl;
    std::cout << "Special on kill: " << static_cast<short>(creatureStart.specialOnKill) << " Facial picture: " << static_cast<short>(creatureStart.facialPicture) << std::endl;


}

