//
// Created by hqnders on 20/04/18.
//

#include "Application.h"
#include "states_production/ConnectState.h"

namespace MachineCore {
    Application::Application(const models::Machine& aMachineInfo)
            : Patterns::Statemachine::Context(), machineInfo(aMachineInfo)
    {
        clientThread = manager.runServiceThread();

        Communication::NetworkComponent connectionHandler;
        handleNotificationsFor(connectionHandler);

        client = manager.createClient(std::make_shared<Communication::NetworkComponent>(connectionHandler));

        setCurrentState(std::make_shared<ProductionStates::ConnectState>(*this));
    }

    void Application::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
    }

    const models::Machine &Application::getMachineInfo() const {
        return machineInfo;
    }

    void Application::setMachineInfo(const models::Machine &machineInfo) {
        Application::machineInfo = machineInfo;
    }
void Application::setStartState() {
  setCurrentState(std::make_shared<ProductionStates::ConnectState>(*this));
}
}
