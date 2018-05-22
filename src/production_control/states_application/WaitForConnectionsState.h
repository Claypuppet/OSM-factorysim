
#ifndef PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H

#include "ApplicationState.h"

namespace ApplicationStates {

/**
 * State that waits for all fysical machines to connect
 */
class WaitForConnectionsState : public ApplicationState {
 public:
  WaitForConnectionsState(core::Application &context);
  virtual ~WaitForConnectionsState() = default;

  bool handleEvent(const ApplicationStates::EventPtr &event) override;

  /**
   * Waits untill all configured machines are connected to the Application
   * Sends the relevant config to the machines
   */
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;

 private:

  /**
   * Executes everytime the handlEvent receives a machineReady message
   * @param event a pointer to the current event
   */
  void onMachineRegistered(const ApplicationStates::EventPtr &event);

  /**
   * Executes everytime the handleEvent method receives a message allMachinesReady
   */
  void onAllMachinesConnected();
};
}

#endif //PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
