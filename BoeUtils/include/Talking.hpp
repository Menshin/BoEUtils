#ifndef TALKING_HPP
#define TALKING_HPP

#include <inttypes.h>

namespace BoE{

    struct TalkingNode{
        int16_t personality;
        int16_t type;
        int8_t link1[4], link2[4];
        int16_t extras[4];
    };

    struct TalkingRecord{
        uint8_t talkingStringsLengths[200];
        TalkingNode talkingNodes[60];
    };

    void OutputTalkingRecords(TalkingRecord &record);
    void OutputTalkingNodeInfo(TalkingNode &talkingNode);
}



#endif // TALKING_HPP
