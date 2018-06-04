//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTSTATE_H

#include "ApplicationState.h"

namespace applicationstates {

/**
 * State in which application sets up it's network with Production Control
 */
class ConnectState : public ApplicationState {
 public:
  ConnectState(machinecore::Application &aContext);
  virtual ~ConnectState() = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &event) override;

 private:
  /**
   * Called on successfull connection
   */
  void onConnected();
};
} // applicationstate

#endif //PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
