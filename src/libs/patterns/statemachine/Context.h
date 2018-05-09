/*
 * Context.h
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <memory>
#include <queue>

#include "State.h"

namespace Patterns {
namespace Statemachine {
class Context {
 public:
  virtual ~Context() = default;

  /**
   * Run context once. Will handle events in the event queue and apply doAction in currentState.
   */
  virtual void run();

  /**
   * Add event to the event queue.
   * @param e : Event to add
   */
  void scheduleEvent(EventPtr e);

  /**
   * Set a new state
   * @param currentState : State to set
   */
  void setCurrentState(StatePtr currentState);

  const StatePtr &getCurrentState() const {
    return currentState;
  }

 protected:
  Context() = default;

  StatePtr currentState;
  std::queue<EventPtr> events;
};
}
}

#endif /* CONTEXT_H_ */
