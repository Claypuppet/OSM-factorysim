//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include <patterns/statemachine/Context.h>
#include <patterns/notifyobserver/Observer.hpp>
#include <models/ProductionLine.h>
#include <thread>
#include "Events/Event.h"
#include "Machine.h"
#include "FileReader.h"

namespace visualisercore {

/**
 * Abstract core class that schedules and handles events
 */
class Application : public patterns::statemachine::Context, patterns::notifyobserver::Notifier {
 public:
  Application();

  /**
   * Destructs the object and runs the stop function
   */
  ~Application() override;

  /**
   * Adds a machine to machines
   * @param aMachine : The machine to add
   */
  void addMachine(const MachinePtr& aMachine);

  /**
   * Sets the start state
   */
  virtual void setStartState() = 0;

  /**
   * Sets start state and,
   * Starts a thread where the state machine runs
   */
  void start();

  /**
   * Stops the thread the state machine is running on
   */
  void stop();

 protected:
  std::vector<EventPtr> productionEvents;
  std::vector<MachinePtr> machines;
  models::ConfigurationPtr configuration;
  std::shared_ptr<std::thread> contextThread;
  bool running;
};

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
