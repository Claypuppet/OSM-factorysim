
#ifndef PRODUCTION_LINE_CONTROL_APPLICATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_APPLICATIONSTATE_H

#include <patterns/statemachine/Event.h>
#include <patterns/statemachine/State.h>
#include "../Application.h"

namespace ApplicationStates {

enum EventType {
  kEventTypeMachineRegistered,
  kEventTypeAllMachinesRegistered,
  kEventTypeMachineStatusUpdate
};

typedef patterns::statemachine::Event Event;
typedef patterns::statemachine::EventPtr EventPtr;

class ApplicationState : public patterns::statemachine::State {

 public:
  virtual ~ApplicationState() = default;
  virtual bool handleEvent(const EventPtr &e) override;
  virtual void entryAction() = 0;
  virtual void doActivity() = 0;
  virtual void exitAction() = 0;

 protected:
  ApplicationState(core::Application &application);
  core::Application &context;

};

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATIONSTATE_H
