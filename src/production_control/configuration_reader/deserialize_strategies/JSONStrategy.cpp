//
// Created by bas on 23-5-18.
//

#include "JSONStrategy.h"

#include <fstream>

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

void JSONStrategy::deserializeConfigurationFile(const std::string &filePath, models::Configuration &configuration) {
  try {

    std::ifstream configurationFile(filePath);

    try {
      cereal::JSONInputArchive archive(configurationFile);
      archive(configuration);
    } catch (const std::exception &exception) {
      std::cerr << "Configuration file incomplete: " << exception.what() << std::endl;
    }

  } catch (const std::exception &exception) {
    std::cerr << "Invalid configuration or invalid file path: " << exception.what() << std::endl;
  }
}
