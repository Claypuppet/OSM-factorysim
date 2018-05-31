//
// Created by don on 28-5-18.
//

#include "Application.h"

namespace visualisercore {

void Application::addMachine(const MachinePtr &aMachine) {
  machines.push_back(aMachine);
}

void Application::start() {
  setStartState();
  running = true;
  contextThread = std::make_shared<std::thread>([this]() {
    while (running) {
      run();
    }
  });
}

void Application::stop() {
  if (contextThread) {
    running = false;
    if(contextThread->joinable()) {
      contextThread->join();
    }
  }
}

Application::Application()
    : running(false) {

}

Application::~Application() {
  stop();
}

}
