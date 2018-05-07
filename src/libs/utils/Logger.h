//
// Created by don on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LOGGER_H
#define PRODUCTION_LINE_CONTROL_LOGGER_H

#include <patterns/singleton/Singleton.h>

#include <iostream>
#include <mutex>

class Logger : public Patterns::Singleton::Singleton<Logger> {
public:
	Logger() = default;
	virtual ~Logger() = default;

	/**
	 * Log a message
	 * @param message : string to log
	 */
    void log(const std::string& message);

private:

	std::mutex lock;
};


#endif //PRODUCTION_LINE_CONTROL_LOGGER_H
