//
// Created by don on 23-4-18.
//

#include <thread>

#include "Logger.h"

namespace utils {

Logger::Logger() : enabled(true) {

}

Logger::~Logger() {
}

void Logger::log(const std::string &message) {
  getInstance().logMessage(message);
}

void Logger::logMessage(const std::string &message) {
  if (enabled) {
	lock.lock();
	std::cout << message << std::endl;
	lock.unlock();
  }

}
void Logger::setEnabled(bool enabled) {
  getInstance().enabled = enabled;
}

}
