//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include "patterns/statemachine/Context.h"
#include "network/Manager.h"
#include "NetworkComponent.h"

//TODO: Implement Observer
namespace Core {
    class Application : public Patterns::Statemachine::Context {
    public:
        Application(const Network::ClientPtr &client);

        Application();
        virtual ~Application();

    private:
        Network::ClientPtr client;
    };
}


#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
