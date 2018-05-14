//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H

#include <patterns/statemachine/State.h>
#include "../NetworkComponent.h"
#include "../Application.h"

namespace ProductionStates {
enum EventType {
  kMachineBrokeDown,
  kEventTypeConnected,
  kEventTypeConnectionFailed,
  kEventTypeReceivedConfig,
  kEventTypeConfigured,
  kEventTypeSelfTestSuccess,
  kEventTypeSelfTestFailed,
  kEventTypeTakeProduct,
  kEventTypeProcessProduct,
  kEventTypeFinishedProduct
};

typedef Patterns::Statemachine::Event Event;
typedef Patterns::Statemachine::EventPtr EventPtr;

class ProductionState : public Patterns::Statemachine::State {
 public:
  virtual ~ProductionState() = default;

  virtual void entryAction() = 0;

  virtual void doActivity() = 0;

  virtual void exitAction() = 0;

  virtual bool handleEvent(const Patterns::Statemachine::EventPtr &e) = 0;

 protected:
  ProductionState(MachineCore::Application &aContext);

  MachineCore::Application &context;
};

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
