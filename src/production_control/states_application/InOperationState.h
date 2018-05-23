//
// Created by bas on 15-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "ApplicationState.h"

namespace applicationstates {

class InOperationState : public ApplicationState {
 public:
  InOperationState(core::Application &context);
  virtual ~InOperationState() = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;

  bool handleEvent(const applicationstates::EventPtr &event) override;

};

}

#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
