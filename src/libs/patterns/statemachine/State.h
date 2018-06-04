/*
 * State.h
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */

#ifndef STATE_H_
#define STATE_H_

#include "Event.h"

namespace patterns {
namespace statemachine {
class Context;
class State;

typedef std::shared_ptr<State> StatePtr;

class State {
 public:
  /**
   * Function that handles events
   * @param e : Event to handle
   * @return bool : True when the event is handled
   */
  virtual bool handleEvent(const EventPtr &e) = 0;

  /**
   * Function to loop through while the state is active
   */
  virtual void doActivity() = 0;

  /**
   * Function that is called when the state is entered
   */
  virtual void entryAction() = 0;

  /**
   * Function that is called when leaving a state
   */
  virtual void exitAction() = 0;

 protected:
  State() {};

  virtual ~State() {};

};
}
}

#endif /* STATE_H_ */
