//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include <patterns/statemachine/Context.h>
#include <patterns/notifyobserver/Observer.hpp>
#include "Event.h"
#include "Machine.h"
#include "FileReader.h"

namespace visualizercore {

/**
 * Abstract core class that schedules and handles events
 */
class Application : public patterns::statemachine::Context, patterns::notifyobserver::Notifier {
 public:
  Application() = default;

  /**
   * Schedules an event
   * @param anEvent : The event to schedule
   */
  void scheduleEvent(const Event& anEvent);

  /**
   * Adds a machine to machines
   * @param aMachine : The machine to add
   */
  void addMachine(const Machine& aMachine);
 private:
  file::FileReader fileReader;
  std::vector<Event> events;
  std::vector<Machine> machines;
};

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
