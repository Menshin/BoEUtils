#include "Misc.hpp"
#include <iostream>

void OutputTransportInfo(TransportRecord &record){
    std::cout << "Town location x: " << static_cast<int>(record.townLocation.x) << " Town location y: " << static_cast<int>(record.townLocation.y) << std::endl;
    std::cout << "Outdoor location x: " << static_cast<int>(record.outdoorLocation.x) << " Outdoor location y: " << static_cast<int>(record.outdoorLocation.y) << std::endl;
    std::cout << "Sector x: " << static_cast<int>(record.sector.x) << " Sector y: " << static_cast<int>(record.sector.y) << std::endl;
    std::cout << "Current town number: " << static_cast<int>(record.currentTownNumber) << std::endl;
    std::cout << "Exists: " << static_cast<int>(record.exists) << " Property: " << static_cast<int>(record.property) << std::endl;
    std::cout << std::endl;

}

void OutputSpecialNodeInfo(SpecialNode &node){
    std::cout << "Type: " << static_cast<short>(node.type) << " Sd1: " << static_cast<short>(node.sd1) << " Sd2: " << static_cast<short>(node.sd2) <<std::endl;
    std::cout << "Pic: " << static_cast<short>(node.pic) << " M1: " << static_cast<short>(node.m1) << " M2: " << static_cast<short>(node.m2) <<std::endl;
    std::cout << "Ex1a: " << static_cast<short>(node.ex1a) << " Ex1b: " << static_cast<short>(node.ex1b) << std::endl;
    std::cout << "Ex2a: " << static_cast<short>(node.ex2a) << " Ex2b: " << static_cast<short>(node.ex2b) << std::endl;
    std::cout << "Jump to: " << static_cast<short>(node.jumpto) << std::endl;
    std::cout << std::endl;
}

void OutputOutdoorWanderingInfo(OutdoorWandering &record){
    std::cout << "Monsters:" << std::endl;
    for (int i = 0 ; i < 7 ; i++){
        std::cout << "\t" << static_cast<int>(record.monst[i]) << std::endl;
    }

     std::cout << "Friendlies:" << std::endl;
    for (int i = 0 ; i < 3 ; i++){
        std::cout << "\t" << static_cast<int>(record.friendly[i]) << std::endl;
    }

    std::cout << "Special on meet: " << static_cast<int>(record.spec_on_meet) << std::endl;
    std::cout << "Special on win: " << static_cast<int>(record.spec_on_win) << std::endl;
    std::cout << "Special on flee: " << static_cast<int>(record.spec_on_flee) << std::endl;
    std::cout << "Can't flee: " << static_cast<int>(record.cantflee) << std::endl;
    std::cout << "End special 1: " << static_cast<int>(record.end_spec1) << std::endl;
    std::cout << "End special 2: " << static_cast<int>(record.end_spec2) << std::endl;
}

void OutputPresetFieldInfo(PresetField &presetField){
    std::cout << "Field type " << static_cast<short>(presetField.fieldType) << " at (" << static_cast<short>(presetField.fieldLoc.x) \
              << "," << static_cast<short>(presetField.fieldLoc.y) << ")" << std::endl;
}
