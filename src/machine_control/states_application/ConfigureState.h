//
// Created by hqnders on 23/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONFIGURE_H
#define PRODUCTION_LINE_CONTROL_CONFIGURE_H
#include "ApplicationState.h"

/**
 * State used by application to control the configuration cycle of it's machine
 */
namespace applicationstates {
class ConfigureState : public ApplicationState {
 public:
  ConfigureState(machinecore::Application &aContext);
  virtual ~ConfigureState() = default;
  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Called when the configuration succeeded
   */
  void onConfigured();

  /**
   * Called when the configuration failed
   */
  void onFailedToConfigure();
};
} // appicationstates

#endif //PRODUCTION_LINE_CONTROL_CONFIGURE_H
