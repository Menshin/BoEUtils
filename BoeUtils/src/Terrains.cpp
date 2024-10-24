#include "Terrains.hpp"
#include <iostream>

using namespace BoE;

void BoE::OutputTerrainInfo(TerrainRecord &record){

    std::cout << "Picture: " << static_cast<int>(record.picture) << " Blockage: " << static_cast<int>(record.blockage) << std::endl;
    std::cout << "Flag 1: " << static_cast<int>(record.flags[0]) << " Flag 2: " << static_cast<int>(record.flags[1]) << std::endl;

    std::cout << "Special: " << static_cast<int>(record.special) << " Transform to: "  << static_cast<int>(record.transToWhat) << std::endl;
    std::cout << "Can fly over: " << static_cast<int>(record.flyOver) << " Can boat over: "  << static_cast<int>(record.boatOver) << " Block horses: "  << static_cast<int>(record.blockHorse) << std::endl;

    std::cout << "Light radius: " << static_cast<int>(record.lightRadius) << " Step sound: "  << static_cast<int>(record.stepSound) << " Shortcut key: "  << static_cast<int>(record.shortcutKey) << std::endl;

    std::cout << std::endl;

}
