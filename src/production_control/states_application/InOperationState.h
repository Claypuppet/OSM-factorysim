//
// Created by bas on 15-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "../Application.h"
#include "ApplicationState.h"

namespace ApplicationStates {

class InOperationState : public ApplicationState {
 public:
  InOperationState(core::Application &context);
  virtual ~InOperationState() = default;

  bool handleEvent(const ApplicationStates::EventPtr &event) override;

  /**
   *
   */
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;

};

}

#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
