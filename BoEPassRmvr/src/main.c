#include <stdio.h>
#include "BitUtils.h"
#include "ScenUtils.h"

FILE* scenFile;
int EndianessNeedFlipping;

size_t passwordFlagsOffsets[6] = {//0x1A2, //flag_a, unused
                                 0x1B0, //flag_b
                                 0x9BE, //flag_c
                                 0xA2A2, //flag_d
                                 0xB6E, //flag_e
                                 0xC3C, //flag_f
                                 //0x7A96, //flag_g, unused
                                 0x8AE8, //flag_h
                                 //0xA3D0, //flag_i, unused
                                };

uint16_t NewFlags[6];

int main(int argc, char* argv[])
{
    if(argc < 2){
        printf("Usage : BoEPassRmv filename.exs\n");
        return 0;
    }

    scenFile = fopen(argv[1], "rb+");
    if(scenFile == NULL){
        printf("Error: can't open file: %s\n",  argv[1]);
        fclose(scenFile);
        return 1;
    }

    if(!CheckScenarioHeader()){
        printf("Error: invalid scenario file\n");
        fclose(scenFile);
        return 2;
    }

    ComputeNewFlags(0); //0 is the key for "no password"

    for(unsigned int i = 0 ; i < 6 ; ++i){
        fseek(scenFile,passwordFlagsOffsets[i], SEEK_SET);
        fwrite(&NewFlags[i],2,1,scenFile);
    }

    printf("Password succesfully removed\n");
    fclose(scenFile);

    return 0;
}
