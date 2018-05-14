//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H

#include <patterns/statemachine/State.h>
#include "../NetworkComponent.h"
#include "../Application.h"

namespace productionstates {
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

typedef patterns::statemachine::Event Event;
typedef patterns::statemachine::EventPtr EventPtr;

class ProductionState : public patterns::statemachine::State {
 public:
  virtual ~ProductionState() = default;

  virtual void entryAction() = 0;

  virtual void doActivity() = 0;

  virtual void exitAction() = 0;

  virtual bool handleEvent(const patterns::statemachine::EventPtr &e) = 0;

 protected:
  ProductionState(machinecore::Application &aContext);

  machinecore::Application &context;
};

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
