
#include "JSONStrategy.h"

#include <fstream>

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>


namespace configurationserializer {

JSONStrategy::JSONStrategy(const JSONStrategy &other) {
}

std::shared_ptr<models::Configuration> JSONStrategy::deserialize(const std::string &filePath) {
  YAMLStrategy::deserialize(filePath);
}

}