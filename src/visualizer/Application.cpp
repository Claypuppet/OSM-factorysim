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
  threadRunning = true;
  contextThread = std::make_shared<std::thread>([this]() {
    while (threadRunning) {
      run();
    }
  });
}

void Application::stop() {
  if (contextThread) {
    threadRunning = false;
    if(contextThread->joinable()) {
      contextThread->join();
    }
  }
}

Application::Application()
    : threadRunning(false) {

}

Application::~Application() {
  stop();
}

}
