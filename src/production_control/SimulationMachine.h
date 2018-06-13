//
// Created by don on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H

#include <network/Connection.h>
#include <models/Machine.h>
#include <patterns/notifyobserver/Notifier.hpp>
#include "Machine.h"

namespace simulation {

/**
 * Machine used in simulations, adds a simulation connection.
 * Inherits Core::Machine : Core machine is used in the application, this simualtion class adds sim connection
 */
class SimulationMachine : public core::Machine {
 public:

  /**
   * Constructs a machine with existing machine information (Models::Machine)
   * @param aMachine : A machine model
   */
  explicit SimulationMachine(const models::Machine &aMachine);
  SimulationMachine(const SimulationMachine &other);

  /**
   * Destruct
   */
  virtual ~SimulationMachine() = default;

  /**
  * A function to check if a connection is established with the machine
  * @return True if theres a connection establised with the machine
  */
  virtual bool isSimulationConnected() const;

  /**
  * A function to check if the machine is ready for configuration
  * @return True if theres a connection establised with the machine and its configured
  */
  virtual bool isReadyForSimulation() const;

  /**
  * Set the simulation connection wit this machine
  * @param aConnection : The connection with this machine
  */
  virtual void setSimulationConnection(const network::ConnectionPtr &aConnection);

  /**
   * Send the simulation configuration to this machine.
   */
  void sendSimulationConfiguration();

  /**
   * Sets the machine ready for simulation
   */
  virtual void setReady(bool aReady);

  /**
   * Send the command to turn on the machine
   */
  virtual void sendTurnOnCommand();

  /**
   * Send the command to turn on the machine
   */
  virtual void sendTurnOffCommand();

  /**
   * Get next moment for event, return 0 if no event is in queue
   */
  uint64_t getNextEventMoment();

  /**
   * Get all events from queue with given time, throws exception is time is later than first event in queue
   * @param moment : Time
   * @param list : List of events to add this machine's events to.
   */
  void getEvents(uint64_t moment, std::vector<patterns::notifyobserver::NotifyEvent> &list);

  /**
   * Add a simulation event to the queue
   * @param simulationEvent : Event to add
   */
  void addEvent(const patterns::notifyobserver::NotifyEvent &simulationEvent);
  bool isWaitingForSimulationResponse() const;
  bool isWaitingForResponse() override;
  bool isIdle(bool completelyIdle) override;

 protected:

  void handleBreak() override;

 private:
  /**
  * A function to send a message to this machine
  * @param message : The message to send to this machine
  */
  void sendSimulationMessage(network::Message &message);

  /**
   * Overrides Machine::sendMessage, sets awaitingSimulationResponse to true
   * @param message
   */
  void sendMessage(network::Message &message) override;


  std::mutex eventPusher;
  bool ready;
  network::ConnectionPtr simConnection;

  bool awaitingSimulationResponse;

  std::queue<patterns::notifyobserver::NotifyEvent> simulationStatusEvents;
  std::queue<patterns::notifyobserver::NotifyEvent> simulationBufferEvents;

};

typedef std::shared_ptr<SimulationMachine> SimulationMachinePtr;
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
