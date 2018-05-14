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

namespace patterns {
namespace statemachine {
        class Context {
        public:
			virtual ~Context() = default;

			/**
			 * Run context once. Will handle events in the event queue and apply doAction in currentState.
			 */
			virtual void run();

          /**
           * Add event to the event queue.
           * @param event : Event to add
           */
          void scheduleEvent(EventPtr event);

            /**
             * Set a new state
             * @param currentState : State to set
             */
            void setCurrentState(StatePtr currentState);

          /**
           * Get the current state
           */
          const StatePtr &getCurrentState() const;

        protected:
            Context() = default;

            StatePtr currentState;
          std::queue<EventPtr> events;
        };
    }
}

#endif /* CONTEXT_H_ */
