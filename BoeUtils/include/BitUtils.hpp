/*
 * Misc. endianness handling functions
 */

#ifndef BIT_UTILS_HPP
#define BIT_UTILS_HPP

#include <fstream>
#include <inttypes.h>

namespace BoE{

    void FlipUnsigned16BytesValue(uint16_t &i);
    void FlipUnsigned32BytesValue(uint32_t &i);
    void Flip16BytesValue(int16_t &i);
    void Flip32BytesValue(int32_t &i);

    std::istream& Read16bits(std::istream& stream, char* target, const size_t howMany, const bool needEndiannessFlipping);

}
#endif // BIT_UTILS_HPP
