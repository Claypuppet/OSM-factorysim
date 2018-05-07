//
// Created by sven on 22-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H


#include "Application.h"
#include "patterns/statemachine/Context.h"

namespace Core {
    class Controller {
    public:
        Controller();

        virtual ~Controller() = default;

        /**
         * Execute main loop
         */
        virtual void execute();

        /**
         * Stop the execution.
         */
        virtual void stop();

    protected:
        Application application;
        bool executing;
    };
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
