//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LISTENSTATE_H
#define PRODUCTION_LINE_CONTROL_LISTENSTATE_H

#include "LiveState.h"
namespace livefeedstates {

/**
 * State in which the visualizer listens to production control and visualizes te received events.
 */
class ListenState : LiveState{
 public:
  ListenState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
};

}

#endif //PRODUCTION_LINE_CONTROL_LISTENSTATE_H
