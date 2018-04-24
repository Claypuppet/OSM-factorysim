//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H


#include <patterns/statemachine/State.h>
#include <patterns/statemachine/Context.h>

class ConnectMachinesContext : public Patterns::Statemachine::Context
{
public:
    ConnectMachinesContext() = default;
    ~ConnectMachinesContext() = default;
};

class ConnectMachinesState : public Patterns::Statemachine::State{
public:
    ConnectMachinesState();

    bool handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) override;

    void doActivity() override;

    void entryAction() override;

    void exitAction() override;
private:
    ConnectMachinesContext context;
};


#endif //PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H
