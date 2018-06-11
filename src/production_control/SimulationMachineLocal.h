//
// Created by klei on 6/11/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINELOCAL_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINELOCAL_H

#include "SimulationMachine.h"

namespace simulation {

class SimulationMachineLocal : public SimulationMachine, public patterns::notifyobserver::Notifier{
 public:
  explicit SimulationMachineLocal(const models::Machine &aMachine);
  ~SimulationMachineLocal() override = default;

  // Overrides
  bool isSimulationConnected() const override;
  bool isReadyForSimulation() const override;
  void sendTurnOnCommand() override;
  void sendTurnOffCommand() override;
  bool isConnected() const override;
  void setConnection(const network::ConnectionPtr &aConnection) override;
  void sendStartProcessMessage() override;
  void sendConfigureMessage(uint16_t configureId) override;
  void setSimulationConnection(const network::ConnectionPtr &aConnection) override;

 private:
  /**
   * Notify application of register machine event
   * @param time : time this event happens
   */
  void notifyRegisterMachine(uint64_t time);

  /**
   * Notify application of machine disconnected event
   * @param time : time this event happens
   */
  void notifyMachineDisconnected(uint64_t time);

  /**
   * Notify application of a status update event
   * @param time : time this event happens
   * @param status : the new status
   */
  void notifyOK(uint64_t time, MachineStatus status);

  /**
   * Notify application of an error event
   * @param time : time this event happens
   * @param errorCode : the error code
   */
  void notifyNOK(uint64_t time, MachineErrorCode errorCode);

  /**
   * Notify application of product placed in buffer event
   * @param time : time this event happens
   */
  void notifyProductAddedToBuffer(uint64_t time);

  /**
   * Notify application of product taken from buffer event
   * @param time : time this event happens
   */
  void notifyProductTakenFromBuffer(uint64_t time);

  // To keep track if its  "connected"  or not
  bool connected;
  models::MachineConfigurationPtr currentConfig;
};

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINELOCAL_H
