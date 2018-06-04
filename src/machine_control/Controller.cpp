//
// Created by hqnders on 20/04/18.
//

#include "Controller.h"

namespace machinecore {

Controller::Controller(uint16_t aMachineId) : executing(false), application(std::make_shared<Application>(aMachineId)) {
}

ApplicationPtr &Controller::getApplication() {
  return application;
}

void Controller::stop() {
  executing = false;
}

}