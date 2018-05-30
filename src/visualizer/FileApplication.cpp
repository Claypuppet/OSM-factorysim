//
// Created by don on 28-5-18.
//

#include "FileApplication.h"

namespace file {

bool FileApplication::loadResults(const std::string &filePath) {

  if(!fileReader.deserializeEvents(filePath, events)){
    return false;
  }

  if(!fileReader.deserializeMachines(filePath, machines)){
    return false;
  }

  configuration = fileReader.deserializeSimConfig(filePath);

  return false;
}

}
