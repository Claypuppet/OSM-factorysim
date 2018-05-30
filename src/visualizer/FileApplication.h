//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILEAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_FILEAPPLICATION_H

#include "Application.h"

namespace file {

/**
 * Application when a result file is selected
 */
class FileApplication : public visualisercore::Application {
 public:
  FileApplication() = default;

  /**
   * Sets events, machines and configuration from a resultfile
   * @param filePath : Path to the file
   * @return : True if successful
   */
  bool loadResults(const std::string &filePath);
 private:
  file::FileReader fileReader;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILEAPPLICATION_H
