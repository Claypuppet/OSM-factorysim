//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_NEUTRALSTATE_H
#define PRODUCTION_LINE_CONTROL_NEUTRALSTATE_H

#include "MainWindowState.h"

namespace mainwindowstates {

/**
 * State that waits until a visualization option is selected
 */
class NeutralState : public MainWindowState {
 public:
  NeutralState() = default;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_NEUTRALSTATE_H
