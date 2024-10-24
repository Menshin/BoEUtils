#pragma once

#include <fstream>
#include <filesystem>
#include "Scenario.hpp"
#include "Towns.hpp"

namespace BoE{

    enum class WriterStatus{Ok, CantOpenFile, DontOverwriteFile};

/*
 * Generic BoE scenarios data writer, uses the current platform endianness
 */

    class DataWriter{
            public:
                DataWriter(std::string filename, const ScenData &_data);
                ~DataWriter();

                bool IsOk() const {return status == WriterStatus::Ok;}
                WriterStatus GetStatus() const {return status;}
                std::string GetErrorMessage() const;
                void WriteScenario(std::string filename);


            private:
                std::ofstream scenFile;
                const ScenData &data;

                WriterStatus status;

                void WriteScenHeader();
                void WriteScenItemsData();
                void WriteScenStrings();
                void WriteScenOutdoors();
                void WriteScenTowns();
    };
}
