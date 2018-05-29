//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LIVEFEEDSTATE_H
#define PRODUCTION_LINE_CONTROL_LIVEFEEDSTATE_H

#include "MainWindowState.h"

namespace mainwindowstates {

/**
 * Sub state machine when the live feed option is selected
 */
class LiveFeedState : public MainWindowState {
 public:
  LiveFeedState() = default;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_LIVEFEEDSTATE_H
