/*
 * State.h
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */

#ifndef STATE_H_
#define STATE_H_

#include "Event.h"

namespace Patterns {
    namespace Statemachine {
        class Context;
        class State;

        typedef std::shared_ptr<State> StatePtr;

        class State {
        public:
            /**
             *
             * @param e : Event to handle
             * @return bool : handled the event
             */
            virtual bool handleEvent(const EventPtr &e) = 0;

            virtual void doActivity() = 0;

            virtual void entryAction() = 0;

            virtual void exitAction() = 0;

        protected:
            State() {};

            virtual ~State() {};

        };
    }
}

#endif /* STATE_H_ */
