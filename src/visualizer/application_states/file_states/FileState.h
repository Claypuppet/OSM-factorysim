//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILESTATE_H
#define PRODUCTION_LINE_CONTROL_FILESTATE_H

#include "../../../visualizer/application_states/ApplicationState.h"

namespace filestates {

/**
 * Abstract state for file states
 */
class FileState : public patterns::statemachine::State {
 public:
  FileState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &event) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_FILESTATE_H
