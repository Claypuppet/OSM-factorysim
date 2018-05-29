//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MAINWINDOWSTATE_H
#define PRODUCTION_LINE_CONTROL_MAINWINDOWSTATE_H

#include <patterns/statemachine/State.h>

namespace mainwindowstates {

/**
 * Abstract class for main window states
 */
class MainWindowState : public patterns::statemachine::State {
 public:
  MainWindowState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_MAINWINDOWSTATE_H
