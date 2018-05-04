//
// Created by don on 23-4-18.
//

#include "Logger.h"

void Logger::log(const std::string& message)
{
    lock.lock();
    std::cout << message << std::endl;
    lock.unlock();
}