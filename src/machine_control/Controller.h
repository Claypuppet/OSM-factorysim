//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H

#include "Application.h"

namespace Core{
    class Controller {
    public:
        Controller();
        virtual ~Controller() = default;

    private:
        Application application;
    };
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
