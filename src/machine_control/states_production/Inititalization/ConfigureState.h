//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H
#define PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H


#include "../ProductionState.h"

namespace ProductionStates::Initialization {
    class ConfigureState : public ProductionState {
    public:
        ConfigureState(Communication::NetworkComponent &aContext) : ProductionState(aContext) {};

        virtual ~ConfigureState() = default;

        virtual void entryAction();


        virtual void doActivity();

        virtual void exitAction();
    };
}


#endif //PRODUCTION_LINE_CONTROL_CONFIGURESTATE_H
