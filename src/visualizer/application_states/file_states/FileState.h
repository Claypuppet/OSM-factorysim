//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILESTATE_H
#define PRODUCTION_LINE_CONTROL_FILESTATE_H

#include "../../../visualizer/application_states/ApplicationState.h"
#include "../../FileApplication.h"

namespace filestates {

/**
 * Enum for filestate event types
 */
enum StateEventTypes{
  eDoneReading,
  eFailedReading,
  eDoneConfiguring
};

/**
 * Abstract state for file states
 */
class FileState : public patterns::statemachine::State {
 protected:
  explicit FileState(file::FileApplication &application);
  file::FileApplication &context;
 public:
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILESTATE_H
