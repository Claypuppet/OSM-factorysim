//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PLAYSTATE_H
#define PRODUCTION_LINE_CONTROL_PLAYSTATE_H

#include "FileState.h"

namespace filestates {

/**
 * State in which the scheduled events are visualized
 */
class PlayState : public FileState{
 public:
  PlayState() = default;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &event) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_PLAYSTATE_H
