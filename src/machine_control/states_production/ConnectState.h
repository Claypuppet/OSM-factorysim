//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTSTATE_H

#include "ProductionState.h"

namespace ProductionStates {
class ConnectState : public ProductionState {
 public:
  ConnectState(MachineCore::Application &aContext)
      : ProductionState(aContext) {};

  virtual ~ConnectState() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
/**
 * This function handles incoming state events
 * for example: conection is ready makes does mean that it switches to another state
 * @param e: incomming event as eventPointer
 * @return
 */
  virtual bool handleEvent(const Patterns::Statemachine::EventPtr &e);
};
}

#endif //PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
