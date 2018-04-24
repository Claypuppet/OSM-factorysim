//
// Created by sven on 22-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H


#include "Application.h"

namespace Core {
    class Controller : public Patterns::Statemachine::Context {
    public:
        Controller();

        virtual ~Controller();

    private:
        Application application;
    };
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
