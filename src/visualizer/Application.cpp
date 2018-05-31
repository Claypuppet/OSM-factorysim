//
// Created by don on 28-5-18.
//

#include "Application.h"

namespace visualisercore {

void Application::scheduleProductionEvent(const EventPtr &anEvent) {
  //Check if time is not before the last event
  if (anEvent->getTime() >= productionEvents.back()->getTime()) {
    productionEvents.push_back(anEvent);
  } else {
    throw std::runtime_error("Can't schedule event!");
  }
}

void Application::addMachine(const MachinePtr &aMachine) {
  machines.push_back(aMachine);
}

void Application::start() {
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
    contextThread->join();
  }
}

Application::Application()
    : threadRunning(false) {

}

Application::~Application() {
  stop();
}

}
