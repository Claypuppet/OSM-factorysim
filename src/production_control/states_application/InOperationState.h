
#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "ApplicationState.h"

namespace applicationstates {

/**
 * the operation state, where products are produced!
 */
class InOperationState : public ApplicationState {
 public:
  virtual ~InOperationState() = default;
  void doActivity() override;
  bool handleEvent(const applicationstates::EventPtr &event) override;

 protected:
  InOperationState(core::Application &context);

  /**
   * Function to execute when a machineStatusUpdate event is received.
   * @param event the current event
   */
  void onMachineStatusUpdateEvent(const EventPtr &event);

  /**
   * Function to execute when a machineProductTaken event is received
   * @param event : The received event
   */
  void onMachineProductTaken(const EventPtr &event);

  /**
   * Function to execute when a machineProductAdded event is received
   * @param event
   */
  void onMachineProductAdded(const EventPtr &event);

  /**
   * Function to execute when a machineDisconnected event is received
   * @param event
   */
  void onMachineDisconnected(const EventPtr &event);

  /**
   * Function to execute when a work day over event is received
   * @param event
   */
  void onWorkDayOver();
};

}

#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
