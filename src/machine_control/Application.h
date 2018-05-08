//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include <models/Machine.h>
#include "patterns/statemachine/Context.h"
#include "patterns/notifyobserver/Observer.hpp"
#include "network/Manager.h"
#include "NetworkComponent.h"

//TODO: Implement Observer
namespace MachineCore {
    class Application
            : public Patterns::Statemachine::Context,
              public Patterns::NotifyObserver::Observer{
    public:
        void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

        /**
         * Constructor
         * @param aMachineInfo : The value for machineInfo
         */
        explicit Application(const models::Machine& aMachineInfo);

        /**
         * The destructor
         */
        ~Application() override = default;

        /**
         * Getter for machineInfo
         * @return machineInfo
         */
        const models::Machine &getMachineInfo() const;

        /**
         * Setter for machineInfo
         * @param machineInfo : New value for machineInfo
         */
        void setMachineInfo(const models::Machine &machineInfo);
      void setStartState();
    private:
        Network::Manager manager;
        Network::ClientPtr client;
        ThreadPtr clientThread;

        models::Machine machineInfo;
    };
}


#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
