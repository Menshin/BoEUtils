#include <fstream>
#include "Scenario.hpp"
#include "BitUtils.hpp"
#include "ScenReader.hpp"
#include "ScenWriter.hpp"

using namespace BoE;

BoE::Scenario::Scenario(std::string filename){
    DataReader reader{filename, GetScenData()};
    if(!reader.IsOk()){
        std::cout << reader.GetErrorMessage() << std::endl;
        status = ScenarioStatus::ReaderError;
        return;
    }

    status = ScenarioStatus::Ok;
}

BoE::Scenario::~Scenario(){
}

void BoE::Scenario::SaveScenario(std::string filename){
    DataWriter writer{filename, GetScenData()};
}

void BoE::Scenario::OutputGeneralInfo(){
    std::cout << "Scenario version: " << static_cast<int>(data.header.version[0]) << "." <<  static_cast<int>(data.header.version[1]) << "."  <<  static_cast<int>(data.header.version[2]) << std::endl;
    std::cout << "Scenario minimum version: " <<  static_cast<int>(data.header.minRunVersion) << std::endl;
    std::cout << "Scenario program make version: " <<  static_cast<int>(data.header.progMakeVersion[0]) << "." <<  static_cast<int>(data.header.progMakeVersion[1]) << "."  <<  static_cast<int>(data.header.progMakeVersion[2]) << std::endl;
    std::cout << "Scenario number of towns: " <<  static_cast<int>(data.header.numberOfTowns) << std::endl;
    std::cout << "Scenario difficulty: " << static_cast<int>(data.header.difficulty) << std::endl;
    std::cout << "Scenario intro pic: " << static_cast<int>(data.header.introPic) << std::endl;
    std::cout << "Scenario default ground: " << static_cast<int>(data.header.defaultGround) << std::endl;
    //std::cout << "Scenario endianness is different: " << (DifferentEndianness ? "True" : "False") << std::endl;
    std::cout << "Scenario starting town number: " << static_cast<int>(data.general.startingTownNumber) << std::endl;

    std::cout << "Flag E : " << std::hex <<  static_cast<int16_t>(data.general.flags[4]) << std::dec << std::endl;

    std::cout << std::endl;

    /*std::cout << "Scenario outdoor start chunk: " << static_cast<int>(data.general.startingOutdoorSpawnLoc.x) << "x" << static_cast<int>(data.general.startingOutdoorSpawnLoc.y) << std::endl;
    for(int i = 0 ; i < 200 ; ++i){
        std::cout << "Town size : " << static_cast<unsigned int>(data.general.townsSize[i]) << std::endl;
        std::cout << "Town data size: " << static_cast<int>(data.general.townsDataSize[i][0]) << " " << static_cast<int>(data.general.townsDataSize[i][1]) << " " << static_cast<int>(data.general.townsDataSize[i][2]) << " " << static_cast<int>(data.general.townsDataSize[i][3]) << " " << static_cast<int>(data.general.townsDataSize[i][4]) << std::endl;
    }*/

    /*for(int i = 0 ; i < 10 ; ++i)
        std::cout << "Scenario town to add to " << static_cast<int>(data.general.townsToAddTo[i]) << std::endl;
    for(int i = 0 ; i < 20 ; ++i)
        std::cout << "Scenario town flag to add to " << static_cast<int>(data.general.townsFlagToAddTo[i][0]) << " " << static_cast<int>(data.general.townsFlagToAddTo[i][1]) << std::endl;
    */
    /*std::cout << "Flag C : " <<  static_cast<int>(data.general.flags[2]) << std::endl;*/
    /*for(int i = 0 ; i < 100 ; ++i)
        std::cout << "Outdoor data size: " << static_cast<int>(data.general.outdoorsDataSize[i][0]) << " " << static_cast<int>(data.general.outdoorsDataSize[i][1]) << " " << std::endl;
    for(int i = 1 ; i < 10 ; ++i)
        std::cout << "TEST :" << static_cast<int>(*(&data.general.outdoorsDataSize[99][1]+i)) << std::endl;*/
    /*for(int i = 0 ; i < 3 ; ++i)
        std::cout << "Stored Item Rects : " << static_cast<int>(data.general.storeItemRects[i].left) << " " << static_cast<int>(data.general.storeItemRects[i].top) << " " << static_cast<int>(data.general.storeItemRects[i].right) << " " << static_cast<int>(data.general.storeItemRects[i].bottom) << " " <<std::endl;*/
    /*for(int i = 0 ; i < 3 ; ++i)
        std::cout << "Stored Item Towns : " << static_cast<int>(data.general.storeItemsTowns[i]) << std::endl;
    std::cout << "Flag E : " << static_cast<int>(data.general.flags[4]) << std::endl;*/
    /*for(int i=0 ; i < 50 ; ++i)
        std::cout << "specialItems: " << static_cast<int>(data.general.specialItems[i]) << std::endl;
    for(int i=0 ; i < 50 ; ++i)
        std::cout << "specialItemsSpecial: " << static_cast<int>(data.general.specialItemsSpecial[i]) << std::endl;*/

    /*
    std::cout << "Rating : " << static_cast<int>(data.general.rating) << std::endl;
    std::cout << "Use custom graphics : " << static_cast<int>(data.general.usesCustomGraphics) << std::endl;
    std::cout << "Flag F : " <<  static_cast<int>(data.general.flags[5]) << std::endl;

    //OutputMonsterInfo(data.general.scenarioMonsters[25]);
    //OutputTransportInfo(data.general.scenarioBoats[0]);
    //OutputTransportInfo(data.general.scenarioBoats[1]);
    //OutputTransportInfo(data.general.scenarioBoats[2]);

    std::cout << "Flag G : " <<  static_cast<int>(data.general.flags[6]) << std::endl << std::endl;

    //OutputTerrainInfo(data.general.terrainTypes[77]);

    //for(int i = 0 ; i < 20 ; ++i)
        //std::cout << "Timer time: " << static_cast<int>(data.general.scenarioTimerTimes[i]) << " Timer special: " << static_cast<int>(data.general.scenarioTimerSpecials[i]) << std::endl;

    std::cout << "Flag H : " <<  static_cast<int>(data.general.flags[7]) << std::endl << std::endl;

    for(int i = 0 ; i < 5 ; ++i)
        OutputSpecialNodeInfo(data.general.scenarioSpecials[i]);

    std::cout << "Flag D : " <<  static_cast<int>(data.general.flags[3]) << std::endl << std::endl;

    for(int i = 0 ; i < 5 ; ++i){
        std::cout << "Scenario strings length " << i << ": ";
        std::cout <<  static_cast<int>(data.general.scenarioStringsLengths[i]) << std::endl;
    }

    std::cout << "Flag I : " <<  static_cast<int>(data.general.flags[8]) << std::endl << std::endl;
    */

    /*for(int i = 0 ; i < 3 ; i++){
        OutputItemInfo(data.scenarioItems[i]);
    }

    for(int i = 0 ; i < 256 ; i++){
        std::cout << (data.monstersNames[i]) << std::endl;
    }

    for(int i = 0 ; i < 256 ; i++){
        std::cout << (data.terrainsNames[i]) << std::endl;
    }

    for(auto s : data.scenarioStrings){
        std::cout << s << std::endl;
    }*/

    /*for(auto o : data.outdoorsData){
        OutputOutdoorInfo(o);
    }*/


    /*for(int i = 0 ; i < 1 ; i++){
        OutputTownInfo(data.townsData[i]);
        std::cout << std::endl << "Town terrain (size is " << static_cast<int>(data.general.townsSize[i]) << ")" << std::endl;
        OutputTownTerrainInfo(data.townsData[i].terrain, data.general.townsSize[i]);
        OutputTownStrings(data.townsData[i]);
        OutputTalkingRecords(data.townsData[i].talking);

        std::cout << "Talking strings: " << std::endl;
        int j = 0;
        for(auto s : data.townsData[i].talkingStrings){
            std::cout << j++ << ". " <<  s << std::endl;
        }
    }*/
}

std::string BoE::Scenario::GetErrorMessage() const{
    switch(status){
        case ScenarioStatus::Ok:
            return std::string{"No error."};
        case ScenarioStatus::ReaderError:
            return std::string{"Error during file reading."};
        default:
            return std::string{"Unspecified error."};
    }
}

