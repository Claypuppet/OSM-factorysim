//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LIVECONFIGURESTATE_H
#define PRODUCTION_LINE_CONTROL_LIVECONFIGURESTATE_H

#include "LiveState.h"

namespace livefeedstates {

/**
 * State where configurations are set
 */
class LiveConfigureState : public LiveState{
 public:
  LiveConfigureState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &event) override;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
};

}

#endif //PRODUCTION_LINE_CONTROL_LIVECONFIGURESTATE_H
