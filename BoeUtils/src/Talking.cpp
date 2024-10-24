#include "Talking.hpp"
#include <iostream>

using namespace BoE;

void BoE::OutputTalkingRecords(TalkingRecord &record){
    std::cout << "TALKING RECORDS: " << std::endl;
    for (int i = 0 ; i < 200 ; i++){
        std::cout << static_cast<int>(record.talkingStringsLengths[i]) << " ";
    }

    for(int i = 0 ; i < 60 ; i++){
        OutputTalkingNodeInfo(record.talkingNodes[i]);
        std::cout << std::endl;
    }
}

void BoE::OutputTalkingNodeInfo(TalkingNode &talkingNode){
    std::cout << "Personality: " << static_cast<short>(talkingNode.personality) << " Type: " << static_cast<short>(talkingNode.type) << std::endl;

    std::cout << "Link 1: ";
    for(int i = 0 ; i < 4 ; i++){
        std::cout << static_cast<char>(talkingNode.link1[i]);
    }
    std::cout << std::endl;

    std::cout << "Link 2: ";
    for(int i = 0 ; i < 4 ; i++){
        std::cout << static_cast<char>(talkingNode.link2[i]);
    }
    std::cout << std::endl;

    std::cout << "Extras: ";
    for(int i = 0 ; i < 4 ; i++){
        std::cout << static_cast<short>(talkingNode.extras[i]) << " ";
    }
    std::cout << std::endl;
}
