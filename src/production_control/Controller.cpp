
#include "Controller.h"

core::Controller::Controller() : application(std::make_shared<Application>()), executing(false) {
}

void core::Controller::execute() {
  executing = true;
  while (executing) {
	application->run();
  }
}

void core::Controller::stop() {
  executing = false;
}

core::ApplicationPtr &core::Controller::getApplication() {
  return application;
}
