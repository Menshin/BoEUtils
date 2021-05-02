#include "ScenUtils.h"

//a valid BoE scenario begins by 4 magic bytes :
//10, 20, 30 and 40 for a Mac scenario (scen is assumed in BigEndian then)
//20, 40, 60 and 80 for a PC scenario (scen is assumed in LittleEndian then)
int CheckScenarioHeader(){
    uint32_t scenFormatFlags;

    fread(&scenFormatFlags,4,1,scenFile);

    switch(scenFormatFlags){
        case 0x281e140a: //Scen is BigEndian, platform is LittleEndian
            EndianessNeedFlipping = 1;
            break;

        case 0x14283c50: //Scen is LittleEndian, platform is BigEndian
            EndianessNeedFlipping = 1;
            break;

        case 0x503c2814: //Scen is BigEndian, platform is BigEndian
            EndianessNeedFlipping = 0;
            break;

        case 0x0a141e28: //Scen is LittleEndian, platform is LittleEndian
            EndianessNeedFlipping = 0;
            break;

        default: //error file is not a valid scenario
            return 0;
            break;
    }

    return 1;
}

uint16_t ComputeFlagB(uint16_t i){
    int32_t k = (int32_t) i;
    uint8_t numTowns;

    fseek(scenFile,0xB,SEEK_SET);
    fread(&numTowns,1,1,scenFile);

	k = k * k * k;
	k = k + 51;
	k = k % 3000;
	k = k * numTowns;
	k = k % 10000;
	k = k + 10000;

	return (uint16_t) k;
}


uint16_t ComputeFlagC(uint16_t i){
	int32_t k = (int32_t) i;
	uint16_t OutDataSize;

    fseek(scenFile,0x9C2,SEEK_SET);
    fread(&OutDataSize,2,1,scenFile);
    if(EndianessNeedFlipping){
        OutDataSize = Flip16BytesValue(OutDataSize);
    }

	k = k * k * k;
	k = k + OutDataSize;
	k = k % 3000;
	k = k * 4;
	k = k % 10000;
	k = k + 4;

	return (uint16_t) k;
}

uint16_t ComputeFlagD(uint16_t i){
    int32_t k = (int32_t) i;

    k = k * k;
	k = k + 51;
    k = k % 3000;
	k = k * 82;
	k = k % 10000;
	k = k + 10000;

	return (uint16_t) k;
}

uint16_t ComputeFlagE(uint16_t i){
    int32_t k = (int32_t) i;
    uint8_t scenStrLen[3];

    fseek(scenFile,0xA2A4,SEEK_SET);
    fread(&scenStrLen[0],3,1,scenFile);

	k = k * k;
	k = k + scenStrLen[0] + scenStrLen[1] + scenStrLen[2];
	k = k % 3000;
	k = k * 4;
	k = k % 5000;
	k = k - 9099;

	return (uint16_t) k;
}
uint16_t ComputeFlagF(uint16_t i){
    int32_t k = (int32_t) i;
    uint8_t scenOutdoorsDimensions[2];

    fseek(scenFile,0xC,SEEK_SET);
    fread(&scenOutdoorsDimensions[0],2,1,scenFile);

	k = k * k * k * k;
	k = k + 80;
	k = k % 3000;
	k = k * scenOutdoorsDimensions[0] * scenOutdoorsDimensions[1];
	k = k % 3124;
	k = k - 5426;

	return (uint16_t) k;
}
uint16_t ComputeFlagH(uint16_t i){
    int32_t k = (int32_t) i;
    uint16_t TownDataSize[4];

    fseek(scenFile,0xC,SEEK_SET);
    for(int i = 0 ; i < 4 ; ++i){
        fread(&TownDataSize[i],2,1,scenFile);
        if(EndianessNeedFlipping){
            TownDataSize[i] = Flip16BytesValue(TownDataSize[i]);
        }
    }

	k = k * (TownDataSize[0] +  TownDataSize[1] +  TownDataSize[2] +  TownDataSize[3]);
	k = k + 80;
	k = k % 3000;
	k = k * 45;
	k = k % 887;
	k = k + 9452;

	return (uint16_t) k;
}

void ComputeNewFlags(int key){
    NewFlags[0] = ComputeFlagB(key);
    NewFlags[1] = ComputeFlagC(key);
    NewFlags[2] = ComputeFlagD(key);
    NewFlags[3] = ComputeFlagE(key);
    NewFlags[4] = ComputeFlagF(key);
    NewFlags[5] = ComputeFlagH(key);

    if(EndianessNeedFlipping){
        for(int i = 0 ; i < 6 ; ++i)
            NewFlags[i] = Flip16BytesValue(NewFlags[i]);
    }
}
