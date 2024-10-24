#include "Outdoors.hpp"
#include <iostream>

using namespace BoE;

void BoE::OutputOutdoorInfo(OutdoorChunk &outdoorChunk){

    std::cout << "Terrains :" << std::endl;

    for(int i = 0 ; i < 48 ; i++){
        for(int j = 0 ; j < 48 ; j++){
            std::cout << static_cast<int>(outdoorChunk.outdoor.terrain[i][j]);
        }
        std::cout << std::endl;
    }

    for(int i = 0 ; i < 18 ; i++){
        std::cout << "Special " << i << " id: " << static_cast<int>(outdoorChunk.outdoor.specialIds[i]) << " ";
        std::cout << "location: (" << static_cast<int>(outdoorChunk.outdoor.specialLocs[i].x) << ", " << static_cast<int>(outdoorChunk.outdoor.specialLocs[i].y) << ")" << std::endl;
    }

    for(int i = 0 ; i < 8 ; i++){
        std::cout << "Exit " << i << " dest: " << static_cast<int>(outdoorChunk.outdoor.exitDest[i]) << " ";
        std::cout << "location: (" << static_cast<int>(outdoorChunk.outdoor.exitLocs[i].x) << ", " << static_cast<int>(outdoorChunk.outdoor.exitLocs[i].y) << ")" << std::endl;
    }

    for(int i = 0 ; i < 8 ; i++){
        std::cout << "Sign " << i << " location: (" << static_cast<int>(outdoorChunk.outdoor.signLocs[i].x) << ", " << static_cast<int>(outdoorChunk.outdoor.signLocs[i].y) << ")" << std::endl;
    }

    for(int i = 0; i < 4 ; i++){
        std::cout << "Outdoor wandering " << i << std::endl;
        OutputOutdoorWanderingInfo(outdoorChunk.outdoor.wandering[i]);
        std::cout << std::endl;
    }

    for(int i = 0; i < 4 ; i++){
        std::cout << "Special encounters " << i << std::endl;
        OutputOutdoorWanderingInfo(outdoorChunk.outdoor.specialEnc[i]);
        std::cout << std::endl;
    }

    for(int i = 0 ; i < 4 ; i++){
        std::cout << "Wandering " << i << " location: (" << static_cast<int>(outdoorChunk.outdoor.wanderingLocs[i].x) << ", " << static_cast<int>(outdoorChunk.outdoor.wanderingLocs[i].y) << ")" << std::endl;
    }

    for(int i = 0 ; i < 8 ; i++){
        std::cout << "Info Rect " << i << " left/top/right/bottom: " << static_cast<int>(outdoorChunk.outdoor.infoRect[i].left) << "/" << static_cast<int>(outdoorChunk.outdoor.infoRect[i].top) << "/" << static_cast<int>(outdoorChunk.outdoor.infoRect[i].right) << "/" << static_cast<int>(outdoorChunk.outdoor.infoRect[i].bottom) << std::endl;
    }

    for(int i = 0 ; i < 180 ; i++){
        std::cout << "String " << i << " length: " << static_cast<int>(outdoorChunk.outdoor.outdoorsStringsLengths[i]) << std::endl;
    }

    for(int i = 0 ; i < 60 ; i++)
    {
        std::cout << "Outdoor special node " << i << ": " << std::endl;
        OutputSpecialNodeInfo(outdoorChunk.outdoor.outdoorSpecials[i]);
    }

    std::cout << "Outdoor strings: " << std::endl;
    int i = 0;
    for(auto s : outdoorChunk.outdoor_strings){
        std::cout << i++ << ". " <<  s << std::endl;
    }
}
