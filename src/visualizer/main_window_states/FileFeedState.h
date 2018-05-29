//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILEFEEDSTATE_H
#define PRODUCTION_LINE_CONTROL_FILEFEEDSTATE_H

#include "MainWindowState.h"

namespace mainwindowstates {

/**
 * Sub state machine when a result file is selected
 */
class FileFeedState : public MainWindowState {
 public:
  FileFeedState() = default;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILEFEEDSTATE_H
