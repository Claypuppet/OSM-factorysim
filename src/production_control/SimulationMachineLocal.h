//
// Created by klei on 6/11/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINELOCAL_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINELOCAL_H

#include <utils/RandomHelper.h>

#include "SimulationMachine.h"

namespace simulation {

/**
 * A simulation machine that also simulates the network connection to the remote "simulation" machine control.
 */
class SimulationMachineLocal : public SimulationMachine, public patterns::notifyobserver::Notifier{
 public:
  explicit SimulationMachineLocal(const models::Machine &aMachine);
  SimulationMachineLocal(const SimulationMachineLocal &other) = delete;
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

  /**
   * Checks if the machine broke between last time and given time.
   * @param time : time to check broken on
   */
  bool checkBroken(uint64_t time);

  /**
   * calculate a new repair time
   * @return : time it takes to repair machine
   */
  uint64_t calculateRepairTime();

  // To keep track if its  "connected"  or not
  bool connected;

  // To simulate a machine
  utils::UnsignedUniformDistribution breakDistribution;
  utils::NormalDistribution repairDistribution;
  uint64_t timeSinceBrokenCheck;
  uint64_t momentOfLastItemProcessed;
  models::MachineConfigurationPtr currentConfig;
};

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINELOCAL_H
