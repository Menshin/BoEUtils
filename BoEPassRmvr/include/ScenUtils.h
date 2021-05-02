/*
 * Contains functions that validates the scenario file and
 * computes the password flags exactly as the original game
 * did, fetching the needed scenario data on the fly
 */

#ifndef SCEN_UTILS_H
#define SCEN_UTILS_H

#include <stdio.h>
#include <stdint.h>
#include "BitUtils.h"

extern FILE* scenFile;
extern int EndianessNeedFlipping;
extern uint16_t NewFlags[6];

int CheckScenarioHeader();

//Flags A, G and I are not used in the password calculation
uint16_t ComputeFlagB(uint16_t i);
uint16_t ComputeFlagC(uint16_t i);
uint16_t ComputeFlagD(uint16_t i);
uint16_t ComputeFlagE(uint16_t i);
uint16_t ComputeFlagF(uint16_t i);
uint16_t ComputeFlagH(uint16_t i);
void ComputeNewFlags(int i);

#endif // SCEN_UTILS_H
