//
// Created by hqnders on 24/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_READYINGCONFIGSTATE_H
#define PRODUCTION_LINE_CONTROL_READYINGCONFIGSTATE_H

#include "../MachineState.h"

namespace machinestates {

/**
 * State in which the machine waits for an event containing the configuration to load
 */
class PrepareConfiguration : public MachineState {
 public:
  PrepareConfiguration(machinecore::Machine &aContext);
  ~PrepareConfiguration() = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Called when configurion is loaded
   * @param event Event containing the next configuration
   */
  void onReconfigure(const EventPtr &event);
};
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_READYINGCONFIGSTATE_H
