//
// Created by hqnders on 09/05/18.
//

#include "WaitForProductControlState.h"
namespace simulationstates {

void WaitForProductControlState::entryAction() {

}
void WaitForProductControlState::doActivity() {

}
void WaitForProductControlState::exitAction() {

}
bool WaitForProductControlState::handleEvent(const EventPtr &event) {
  return SimulationState::handleEvent(event);
}

} // namespace simulationstates