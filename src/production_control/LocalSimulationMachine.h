//
// Created by klei on 6/6/18.
//

#ifndef PRODUCTION_LINE_CONTROL_LOCALSIMULATIONMACHINE_H
#define PRODUCTION_LINE_CONTROL_LOCALSIMULATIONMACHINE_H

#include <patterns/notifyobserver/Notifier.hpp>
#include <patterns/notifyobserver/Observer.hpp>

#include "SimulationMachine.h"

namespace simulation {

class LocalSimulationMachine : public SimulationMachine, public patterns::notifyobserver::Notifier, public patterns::notifyobserver::Observer {
 public:
  explicit LocalSimulationMachine(const models::Machine &aMachine);
  ~LocalSimulationMachine() = default;

  bool isConnected() const override;
  void setConnection(const network::ConnectionPtr &aConnection) override;
  bool isSimulationConnected() const override;
  bool isReadyForSimulation() const override;
 protected:
  void sendMessage(network::Message &message) override;

 private:
//  remoteMachine

  class RemoteMachine : models::Machine {
    SimulationMachine(const models::Machine &machine) : models::Machine(machine), timeSinceBrokenCheck(0), checkCycle(oneMinuteInMillis) {

    }

    bool configure() {
      generator = std::mt19937(static_cast<uint64_t >(std::clock()));
      distribution = std::uniform_int_distribution<uint64_t>(magicNumber,
                                                             (magicNumber
                                                                 + currentConfiguration->getMeanTimeBetweenFailureInHours())
                                                                 * oneHourInMillis / checkCycle);
      utils::Time::getInstance().increaseCurrentTime(currentConfiguration->getInitializationDurationInMilliseconds());
      timeSinceBrokenCheck = utils::Time::getInstance().getCurrentTime();
      auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeConfigured);
      scheduleEvent(event);
      return true;
    }

    void selfTest() {
      auto event = std::make_shared<patterns::statemachine::Event>(machinestates::kEventTypeSelfTestSuccess);
      scheduleEvent(event);
    }

    void takeInProduct() {
      auto notification = makeNotifcation(machinecore::NotifyEventType::kNotifyEventTypeProductTakenFromBuffer);
      notifyObservers(notification);
      auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeProductTakenIn);
      scheduleEvent(event);
    }

    void processProduct() {
      uint32_t processTime = currentConfiguration ? currentConfiguration->getProcessTime() : 0;
      utils::Time::getInstance().increaseCurrentTime(processTime);
      // TODO: NOTIFY! done
    }

    void takeOutProduct() {
      // TODO: NOTIFY! took product
    }

    void setConfigureStartState() {
      // TODO: NOTIFY! configuring
    }

    void setInOperationStartState() {
      // TODO: NOTIFY! started
    }

    bool checkBroken() {
      if (canBreak) {
        auto currentTime = utils::Time::getInstance().getCurrentTime();
        if (currentTime < timeSinceBrokenCheck + checkCycle) {
          return false;
        }

        while(currentTime > timeSinceBrokenCheck){
          // Catch up with history
          timeSinceBrokenCheck += checkCycle;

          uint64_t generated = distribution(generator);

          if (generated == magicNumber) {
            // It broke, set time since last check to now
            timeSinceBrokenCheck = currentTime;
            // TODO: NOTIFY!
            return true;
          }
        }
      }
      return false;
    }


    models::MachineConfigurationPtr currentConfiguration;
    std::mt19937 generator;
    std::uniform_int_distribution<uint64_t> distribution;
    uint16_t magicNumber = 0;
    uint64_t timeSinceBrokenCheck;
    uint64_t checkCycle;
  };
};




}

#endif //PRODUCTION_LINE_CONTROL_LOCALSIMULATIONMACHINE_H
