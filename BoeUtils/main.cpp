#include <iostream>
#include <fstream>
#include "Scenario.hpp"
#include "ScenReader.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2){
        std::cout << "No filename specified." << std::endl;
        return 0;
    }

    BoE::Scenario scenario{std::string{argv[1]}};

    if(!scenario.IsOk()){
        std::cout << scenario.GetErrorMessage() << std::endl;
        return 1;
    }

  scenario.OutputGeneralInfo();

  scenario.SaveScenario("VALLNEW.EXS");

}


