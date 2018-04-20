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

        class State {
        public:
            virtual bool handleEvent(const Event &e, Context &c) = 0;

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
