//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H

#include "Application.h"

namespace MachineCore{
    class Controller {
    public:
        Controller(const Models::Machine& aMachineInfo);
        virtual ~Controller() = default;

        Application &getApplication();

    protected:
        Application application;
    };
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
