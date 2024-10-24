#include "Items.hpp"
#include <iostream>

using namespace BoE;

void BoE::OutputItemInfo(ItemRecord &record){

    std::cout << "Variety: " << static_cast<int>(record.variety) << " Level: " << static_cast<int>(record.itemLevel) << " Awkward: " << static_cast<int>(record.awkward) << std::endl;
    std::cout << "Bonus: " << static_cast<int>(record.bonus) << " Protection: " << static_cast<int>(record.protection) \
              << " Charges: " << static_cast<int>(record.charges) << " Type " << static_cast<int>(record.type) << std::endl;

    std::cout << "Ability: " << static_cast<int>(record.ability) << " Ability Strength: "  << static_cast<int>(record.abilityStrength) << std::endl;
    std::cout << "Type Flag: " << static_cast<int>(record.typeFlag) << " Is Special?: "  << static_cast<int>(record.isSpecial) << std::endl;

    std::cout << "a: " << static_cast<int>(record.a) << " Value: "  << static_cast<int>(record.value) << std::endl;

    std::cout << "Weight: " << static_cast<int>(record.weight) << " Special Class: "  << static_cast<int>(record.specialClass) << std::endl;
    std::cout << "Location : (" << static_cast<int>(record.itemLoc.x) << "," << static_cast<int>(record.itemLoc.y) << ")" << std::endl;

    std::cout << "Full name: " << &record.fullname[0] << " Name: "  << &record.name[0] << std::endl;

    std::cout << "Treasure Class: " << static_cast<int>(record.treasureClass) << " Item Properties: "  << static_cast<int>(record.itemProperties) << std::endl;

    std::cout << "Reserved 1: " << static_cast<int>(record.reserved[0]) << " Reserved 2: "  << static_cast<int>(record.reserved[1]) << std::endl;

    std::cout << std::endl;
}

void BoE::OutputPresetItemInfo(PresetItem &presetItem){

    std::cout << "Item location: (" << static_cast<int>(presetItem.itemLoc.x) << "," << static_cast<int>(presetItem.itemLoc.y) << ")" << std::endl;
    std::cout << "Item code: " << static_cast<short>(presetItem.itemCode) << std::endl;
    std::cout << "Ability: " << static_cast<short>(presetItem.ability) << std::endl;
    std::cout << "Charges: " << static_cast<int>(presetItem.charges) << std::endl;
    std::cout << "Always there? " << static_cast<int>(presetItem.alwaysThere) << std::endl;
    std::cout << "Property? " << static_cast<int>(presetItem.property) << std::endl;
    std::cout << "Contained? " << static_cast<int>(presetItem.contained) << std::endl;
}
