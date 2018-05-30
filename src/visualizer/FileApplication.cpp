//
// Created by don on 28-5-18.
//

#include "FileApplication.h"

namespace file {

bool FileApplication::loadResults(const std::string &filePath) {

  if(!fileReader.deserializeEvents(filePath, events)){
    return false;
  }

  configuration = fileReader.deserializeSimConfig(filePath);

  for(auto &machine : configuration->getProductionLine()->getMachines())
  {
    machines.push_back(std::make_shared<visualisercore::Machine>(*machine.get()));
  }

  return true;
}

}
