//
// Created by don on 17-5-18.
//

#include "Time.h"
#include "SystemTime.h"
#include "CustomTime.h"

namespace utils {

Time::Time() {
  timer = std::make_shared<SystemTime>();
}

uint64_t Time::getCurrentTime() {
  return timer->getCurrentTime();
}

void Time::syncTime(uint64_t newMillis) {
  timer->syncTime(newMillis);
}

void Time::increaseCurrentTime(uint64_t increaseMillis) {
  timer->increaseCurrentTime(increaseMillis);
}

void Time::reset(){
  timer->reset();
}

void Time::setType(utils::TimeType aType) {
  switch (aType) {
	case TimeType::systemTime:
	  timer = std::make_shared<SystemTime>();
	  break;
	case TimeType::customTime:
	  timer = std::make_shared<CustomTime>();
	  break;
	default:

	  break;
  }
}

const std::string Time::getCurrentTimeString(const std::string &format) {
	uint64_t millis = getCurrentTime();

	// from https://www.experts-exchange.com/questions/23481267/C-millisecond-date-and-time-into-a-string.html
	char timestamp[30] = "";
	time_t secs = millis / 1000;
	tm *ptm = gmtime(&secs);
	strftime(timestamp, 30, format.c_str(), ptm);

	return std::string(timestamp);
}

}
