//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_READSTATE_H
#define PRODUCTION_LINE_CONTROL_READSTATE_H

#include "FileState.h"

namespace filestates {

/**
 * State in which the result file is read and events are scheduled
 */
class ReadState : public FileState{
 public:
  ReadState() = default;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_READSTATE_H
