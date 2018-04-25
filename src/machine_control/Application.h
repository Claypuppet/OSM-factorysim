//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include "patterns/statemachine/Context.h"
#include "patterns/notifyobserver/Observer.hpp"
#include "network/Manager.h"
#include "NetworkComponent.h"

//TODO: Implement Observer
namespace MachineCore {
    class Application
            : public Patterns::Statemachine::Context, public Patterns::NotifyObserver::Observer{
    public:
        virtual void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification);

        Application();
        virtual ~Application() = default;

    private:
        Network::Manager manager;
        Network::ClientPtr client;
        ThreadPtr clientThread;
    };
}


#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
