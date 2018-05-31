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
  explicit PlayState(file::FileApplication &application);
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
};

}

#endif //PRODUCTION_LINE_CONTROL_PLAYSTATE_H
