//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H
#define PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H

#include "../MachineState.h"

namespace machinestates {

/**
 * State in which the machine configures itself by running the machine.configure() function
 */
class ConfiguringState : public MachineState {
 public:
  ConfiguringState(machinecore::Machine &aContext) : MachineState(aContext) {};
  virtual ~ConfiguringState() = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;

 private:
  /**
   * Called when configuring is completed
   */
   void onConfigured();
};
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H
