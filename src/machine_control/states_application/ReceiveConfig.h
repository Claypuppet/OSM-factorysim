//
// Created by sven on 9-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_RECEIVECONFIG_H
#define PRODUCTION_LINE_CONTROL_RECEIVECONFIG_H

#include "ProductionState.h"

namespace productionstates {
/**
 * Sends machine number and receives initial config
 */
class ReceiveConfig : public ProductionState {
 public:
  ReceiveConfig(machinecore::Application &aContext)
	  : ProductionState(aContext) {};

  virtual ~ReceiveConfig() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
/**
 * This function handles incoming state events
 * @param e: incomming event as eventPointer
 * @return
 */
  virtual bool handleEvent(const patterns::statemachine::EventPtr &e);
/**
 * This function checks if received config exists and fires event if it can switch
 * @param e: incomming event as eventPointer
 * @return
 */
  void onConfigReceived(const EventPtr &event);
};
}
#endif //PRODUCTION_LINE_CONTROL_RECEIVECONFIG_H
