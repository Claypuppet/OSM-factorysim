//
// Created by hqnders on 20/04/18.
//

#include "Controller.h"

namespace MachineCore {

    Controller::Controller(const Models::Machine& aMachineInfo)
            : application(aMachineInfo){

    }

    Application &Controller::getApplication() {
        return application;
    }
}