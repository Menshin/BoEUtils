#include "BitUtils.hpp"

uint16_t Flip16BytesValue(uint16_t i){
    return (i&0xFF00) >> 8 | (i&0x00FF) << 8;
}

uint32_t Flip32BytesValue(uint32_t i){
    return (i&0xFF000000) >> 24 | (i&0x00FF0000) >> 8 | (i&0x0000FF00) << 8 | (i&0x000000FF) << 24;
}
