
#include "Controller.h"

core::Controller::Controller() : executing(false) {

}

void core::Controller::execute() {
  executing = true;
  while (executing) {
    application.run();
  }
}

void core::Controller::stop() {
  executing = false;
}

core::Application &core::Controller::getApplication() {
  return application;
}
