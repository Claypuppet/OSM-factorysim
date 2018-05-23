//
// Created by bas on 23-5-18.
//

#include "JSONStrategy.h"

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>

models::Configuration JSONStrategy::deserializeConfigurationFile(const std::string &filePath) {
  try {

    std::ofstream file( "configurationFile.json" );
    cereal::JSONOutputArchive archive( file );

    std::stringstream binaryStream((std::ios::in | std::ios::binary));
    binaryStream.str(json);
    Protocol::InputArchive archive(binaryStream);
    archive(object);

  } catch (const std::exception &exception) {
    std::cerr << "Invalid configuration file path: " << exception.what() << std::endl;
  }
}
