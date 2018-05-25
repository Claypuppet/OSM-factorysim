
#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H

#include <patterns/statemachine/State.h>

#include "../NetworkComponent.h"
#include "../Application.h"

namespace applicationstates {

enum EventType {
  kEventTypeConnected,
  kEventTypeConnectionFailed,
  kEventTypeReceivedConfig,
  kEventTypeConfigured,
  kEventTypeFailedToConfigure,
  kEventTypeRepairStarted,
  kEventTypeStartProcessing,
  kEventTypeFinishedProcessing,
  kEventTypeMachineBroke
};

typedef patterns::statemachine::Event Event;
typedef patterns::statemachine::EventPtr EventPtr;

/**
 * Superstate of any state that can be executed by Application
 */
class ApplicationState : public patterns::statemachine::State {
 public:
  virtual ~ApplicationState() = default;

  void entryAction() override = 0;
  void doActivity() override = 0;
  void exitAction() override = 0;
  bool handleEvent(const EventPtr &event) override;

 protected:
  ApplicationState(machinecore::Application &aContext);

  machinecore::Application &context;
};
} // applicationstates

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
