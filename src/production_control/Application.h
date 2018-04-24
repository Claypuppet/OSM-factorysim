//
// Created by sven on 22-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H


#include <patterns/statemachine/Context.h>
#include "network/Manager.h"



//TODO: Implement Observer
namespace Core {
    class Application : public Patterns::Statemachine::Context  /*, public Patterns::Observer::Observer*/{
    public:
        Application();

        virtual ~Application();

    private:
        Network::ServerPtr appConnectionHandlet;
    };
}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
