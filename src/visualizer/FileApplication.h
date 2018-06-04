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
  explicit FileApplication(const std::string &pathToAFile);

  /**
   * Sets events, machines and configuration from a resultfile
   * @param filePath : Path to the file
   * @return : True if successful
   */
  bool loadResults(const std::string &filePath);

  const std::string &getPathToFile() const;
  void setPathToFile(const std::string &pathToAFile);

  /**
   * Sets the state to filestates::ReadState
   */
  void setStartState() override;
 private:
  file::FileReader fileReader;
  std::string pathToFile;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILEAPPLICATION_H
