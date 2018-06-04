//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILEREADER_H
#define PRODUCTION_LINE_CONTROL_FILEREADER_H

#include <memory>
#include <vector>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include <models/Configuration.h>
#include "Events/Event.h"
#include "Machine.h"

namespace file {

/**
 * A class that reads a result file and creates events
 */
class FileReader {
 public:
  FileReader() = default;

  /**
   * Function that fills a vector of events with events from a yaml file
   * @param filePath : Path to the yaml file
   * @param eventList : The vector of events to fill
   * @return : True if successful
   */
  bool deserializeEvents(const std::string &filePath, std::vector<visualisercore::EventPtr> &eventList);

  /**
   * A function that deserializes configurations from a yaml result file
   * @param filePath : Path to the yaml file
   * @return : The deserialized configurations
   */
  models::ConfigurationPtr deserializeSimConfig(const std::string &filePath);

 private:
  const std::string getFileExtension(const std::string &filePath) const;

  /**
   * Deserializes a single event
   * @param eventNode : Yaml node of a single event
   * @return : Pointer to the event
   */
  visualisercore::EventPtr deserializeEvent(YAML::Node &eventNode);
};

}

#endif //PRODUCTION_LINE_CONTROL_FILEREADER_H
