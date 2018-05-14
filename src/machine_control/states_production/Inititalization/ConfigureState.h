//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H
#define PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H

#include "../ProductionState.h"

namespace productionstates {
class ConfigureState : public ProductionState {
 public:
  ConfigureState(machinecore::Application &aContext) : ProductionState(aContext) {};

  virtual ~ConfigureState() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
  virtual bool handleEvent(const patterns::statemachine::EventPtr &e);
};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H
