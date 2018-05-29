//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILECONFIGURESTATE_H
#define PRODUCTION_LINE_CONTROL_FILECONFIGURESTATE_H

#include "FileState.h"

namespace filestates {

/**
 * State in which the configurations are set
 */
class FileConfigureState : public FileState {
 public:
  FileConfigureState() = default;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILECONFIGURESTATE_H
