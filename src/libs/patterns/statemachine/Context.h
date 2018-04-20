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
            void run();

            void scheduleEvent(Event e);

            void setCurrentState(const std::shared_ptr<State> currentState);

        protected:
            Context();

            virtual ~Context();

            std::shared_ptr<State> currentState;
            std::queue<Event> events;
        };
    }
}

#endif /* CONTEXT_H_ */
