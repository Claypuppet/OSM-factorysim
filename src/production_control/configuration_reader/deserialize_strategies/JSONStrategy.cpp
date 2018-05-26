//
// Created by bas on 23-5-18.
//

#include "JSONStrategy.h"

#include <fstream>

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

JSONStrategy::JSONStrategy(const JSONStrategy &other) {
}

std::shared_ptr<models::Configuration> JSONStrategy::deserialize(const std::string &filePath) {

  try {

    std::ifstream configurationFile(filePath);

    try {

//      auto configurationModel = deserializeConfiguration();
//      return configurationModel;

    } catch (const std::exception &exception) {

      std::cerr << "Configuration file incomplete: " << exception.what() << std::endl;

    }

  } catch (const std::exception &exception) {

    std::cerr << "Invalid configuration or invalid file path: " << exception.what() << std::endl;

  }
}

//std::shared_ptr<models::Configuration> JSONStrategy::deserializeConfiguration() { // TODO : Implement function
//}