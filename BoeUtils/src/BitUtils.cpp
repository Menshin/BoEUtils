#include "BitUtils.hpp"

namespace BoE{

    void Flip16BytesValue(int16_t &i){
        i = (i&0xFF00) >> 8 | (i&0x00FF) << 8;
    }

    void Flip32BytesValue(int32_t &i){
        i = (i&0xFF000000) >> 24 | (i&0x00FF0000) >> 8 | (i&0x0000FF00) << 8 | (i&0x000000FF) << 24;
    }

    void FlipUnsigned16BytesValue(uint16_t &i){
        i = (i&0xFF00) >> 8 | (i&0x00FF) << 8;
    }

    void FlipUnsigned32BytesValue(uint32_t &i){
        i = (i&0xFF000000) >> 24 | (i&0x00FF0000) >> 8 | (i&0x0000FF00) << 8 | (i&0x000000FF) << 24;
    }

    std::istream& Read16bits(std::istream& stream, char* target, const size_t howMany, const bool needEndiannessFlipping){

        std::istream& is = stream.read(target,sizeof(int16_t)*howMany);

        if(needEndiannessFlipping){
            int16_t* iter = reinterpret_cast<int16_t*>(target);
            for(size_t i = 0 ; i < howMany ; i++){
                Flip16BytesValue(*(iter+i));
            }
        }

        return is;
    }

}
