//
// Created by sven on 17-5-18.
//

#include <thread>
#include "FileLogger.h"



namespace utils {

FileLogger::FileLogger() : enabled(true) {

}

FileLogger::~FileLogger() {
}

void FileLogger::log(const std::string &message) {
  getInstance().logMessage(message);
}

void FileLogger::logMessage(const std::string &message) {
  if (enabled) {
    lock.lock();
    std::cout << message << std::endl;
    lock.unlock();
  }

}
void FileLogger::setEnabled(bool enabled) {
  getInstance().enabled = enabled;
}

}
