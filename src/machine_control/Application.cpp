//
// Created by hqnders on 20/04/18.
//

#include "Application.h"
#include "states_production/ConnectState.h"

Core::Application::Application(const Network::ClientPtr &client) : client(client) {
    setCurrentState(std::make_shared<ProductionStates::ConnectState>(*this));
}
