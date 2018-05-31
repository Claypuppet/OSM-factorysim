//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LIVEAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_LIVEAPPLICATION_H

#include "Application.h"
namespace live {

/**
 * Application class when the live feed option was selected
 */
class LiveApplication : public visualisercore::Application, patterns::notifyobserver::Observer{
 public:
  LiveApplication() = default;

  /**
   * Schedules an event
   * @param anEvent : The event to schedule
   */
  void scheduleProductionEvent(const visualisercore::EventPtr &anEvent);
};

}

#endif //PRODUCTION_LINE_CONTROL_LIVEAPPLICATION_H
