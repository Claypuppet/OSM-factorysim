//
// Created by sven on 9-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_RECEIVECONFIG_H
#define PRODUCTION_LINE_CONTROL_RECEIVECONFIG_H

#include "ApplicationState.h"

namespace applicationstates {

/**
 * Sends machine number and receives initial config
 */
class Initialize : public ApplicationState {
 public:
  Initialize(machinecore::Application &aContext);
  ~Initialize() override = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;

 private:
/**
 * This function checks if received config exists and fires event if it can switch
 * @param e: incomming event as eventPointer
 * @return
 */
  void onReceivedConfig(const EventPtr &event);
};
} // applicationstates

#endif //PRODUCTION_LINE_CONTROL_RECEIVECONFIG_H
