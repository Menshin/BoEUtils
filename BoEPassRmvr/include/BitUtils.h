/*
 * Misc. endianness handling functions
 */

#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>

enum Endianness{LittleEndian, BigEndian};

enum Endianness CheckPlatformEndianness();

uint16_t Flip16BytesValue(uint16_t i);
uint32_t Flip32BytesValue(uint32_t i);

#endif // BIT_UTILS_H
