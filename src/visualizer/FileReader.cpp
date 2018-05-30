//
// Created by don on 28-5-18.
//

#include <iostream>
#include <configuration_serializer/deserialize_strategies/YAMLStrategy.h>
#include <configuration_serializer/ConfigurationReader.h>
#include "FileReader.h"
#include "Events/StatusUpdateEvent.h"
#include "Events/ConfigUpdateEvent.h"
#include "Events/BufferUpdateEvent.h"

namespace file {

bool FileReader::deserializeEvents(const std::string &filePath, std::vector<visualisercore::EventPtr> &eventList) {

  if (getFileExtension(filePath) == "yaml") {
    try {

      YAML::Node yamlFileNode = YAML::LoadFile(filePath);
      auto eventsNode = yamlFileNode["events"];
      for (uint32_t i = 0; i < eventsNode.size(); ++i) {
        auto eventNode = eventsNode[i];
        auto event = deserializeEvent(eventNode);
        if (event) {
          eventList.push_back(event);
        } else {
          return false;
        }
      }

    } catch (const YAML::Exception &exception) {

      std::cerr << "YAML Exception: " << exception.what() << std::endl;
      throw exception;

    } catch (const std::exception &exception) {

      std::cerr << exception.what() << std::endl;
      throw exception;

    }
  } else {
    std::cerr << "Given file format not supported" << std::endl;
    return false;
  }
  return true;
}

const std::string file::FileReader::getFileExtension(const std::string &filePath) const {
  return filePath.substr(filePath.find_last_of('.') + 1);
}

visualisercore::EventPtr file::FileReader::deserializeEvent(YAML::Node &eventNode) {
  std::string eventString = eventNode.as<std::string>();
  visualisercore::EventPtr event;

  std::stringstream ss(eventString);
  std::vector<std::string> eventContents;
  std::string token;

  while (std::getline(ss, token, ',')) {
    eventContents.push_back(token);
  }

  if (eventContents.size() < 3) {
    return nullptr;
  }

  auto eventId = static_cast<models::Machine::MachineLogEventIds >(std::stoul(eventContents[0]));
  auto timeStamp = static_cast<uint64_t>(std::stoull(eventContents[1]));
  auto machineId = static_cast<uint16_t>(std::stoul(eventContents[2]));

  switch (eventId) {
    case models::Machine::MachineLogEventIds::kMachineLogEventMachineStatusUpdate: {
      auto machineStatus = static_cast<models::Machine::MachineStatus>(std::stoul(eventContents[3]));
      event = std::make_shared<visualisercore::StatusUpdateEvent>(timeStamp, machineId, machineStatus);
      break;
    }
    case models::Machine::MachineLogEventIds::kMachineLogEventMachineReconfigured: {
      auto configId = static_cast<uint16_t>(std::stoul(eventContents[3]));
      event = std::make_shared<visualisercore::ConfigUpdateEvent>(timeStamp, machineId, configId);
      break;
    }
    case models::Machine::MachineLogEventIds::kMachineLogEventMachineBufferUpdate: {
      if (eventContents.size() < 4) {
        return nullptr;
      }
      auto productId = static_cast<uint16_t>(std::stoul(eventContents[3]));
      auto bufferAmount = static_cast<uint32_t>(std::stoul(eventContents[4]));
      event = std::make_shared<visualisercore::BufferUpdateEvent>(timeStamp, machineId, productId, bufferAmount);
      break;
    }
    default:
      //Do nothing
      break;
  }

  return event;
}

models::ConfigurationPtr FileReader::deserializeSimConfig(const std::string &filePath) {
  configurationserializer::ConfigurationReader reader;
  return reader.deserialize(filePath);
}

}