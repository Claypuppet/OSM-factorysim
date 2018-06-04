//
// Created by hqnders on 09/05/18.
//

#include <utils/Logger.h>

#include "WaitForProductControlState.h"

namespace simulationstates {

void WaitForProductControlState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}
void WaitForProductControlState::doActivity() {

}
void WaitForProductControlState::exitAction() {

}
bool WaitForProductControlState::handleEvent(const EventPtr &event) {
  return SimulationState::handleEvent(event);
}

} // namespace simulationstates