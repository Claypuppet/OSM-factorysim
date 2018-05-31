//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILESTATE_H
#define PRODUCTION_LINE_CONTROL_FILESTATE_H

#include "../../../visualizer/application_states/ApplicationState.h"
#include "../../FileApplication.h"

namespace filestates {

enum StateEventTypes{
  eDoneReading,
  eDoneConfiguring
};

/**
 * Abstract state for file states
 */
class FileState : public patterns::statemachine::State {
 public:
  bool handleEvent(const patterns::statemachine::EventPtr &event) override;
 protected:
  explicit FileState(file::FileApplication &application);
  file::FileApplication &context;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILESTATE_H
