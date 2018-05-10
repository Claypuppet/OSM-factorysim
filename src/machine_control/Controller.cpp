//
// Created by hqnders on 20/04/18.
//

#include "Controller.h"

namespace machinecore {

Controller::Controller(uint16_t aMachineId)
    : application(aMachineId) {

}

Application &Controller::getApplication() {
  return application;
}
}