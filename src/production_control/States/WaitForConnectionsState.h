//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H


#include <patterns/statemachine/State.h>

class WaitForConnectionsState : public Patterns::Statemachine::State {
public:
    bool handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) override;

    void doActivity() override;

    void entryAction() override;

    void exitAction() override;
};


#endif //PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
