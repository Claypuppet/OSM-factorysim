//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTSTATE_H

#include "LiveState.h"
namespace livefeedstates {

/**
 * State where the visualizer connects to production control
 */
class ConnectState : public LiveState {
 public:
  ConnectState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
