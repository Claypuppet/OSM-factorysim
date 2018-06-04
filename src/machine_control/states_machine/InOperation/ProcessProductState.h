
#ifndef PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H

#include "../MachineState.h"

namespace machinestates {

/**
 * Machine state dureing product processing
 */
class ProcessProductState : public MachineState{
 public:
  ProcessProductState(machinecore::Machine &aContext);

  virtual ~ProcessProductState() = default;

  virtual bool handleEvent(const EventPtr &event);
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:
  /**
   * Gets executed when product processing is finished
   */
  void onProductFinishedEvent();
};
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
