//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <cstdint>
#include "patterns/notifyobserver/Notifier.hpp"
#include "patterns/statemachine/Context.h"
#include <models/Machine.h>

namespace machinecore {

/**
 * A pure virtual machine that is controlled by Application,
 */
class Machine
    : public patterns::notifyobserver::Notifier, public patterns::statemachine::Context, public models::Machine {
 public:
  Machine() = default;
  virtual ~Machine() = default;

  /**
   * Executed while the machine is configuring
   * @return If outcome was successful or not
   */
  virtual bool configure() = 0;

  /**
   * Executed while the machine is selftesting
   */
  virtual void selfTest() = 0;

  /**
   * Executed while the machine is taking in a product
   */
  virtual void takeInProduct() = 0;

  /**
   * Executed while the machine is processing a product
   */
  virtual void processProduct() = 0;

  /**
   * Executed while the machine is taking out a product
   */
  virtual void takeOutProduct() = 0;

  /**
   * Executed to set the start state of the statemachine in a configuration cycle
   */
  virtual void setConfigureStartState() = 0;

  /**
   * Executed to set the start state of the statemachine in a production cycle
   */
  virtual void setInOperationStartState() = 0;

  void setConfigurations(const std::vector<models::MachineConfigurationPtr> &aConfigurations) {
    configurations = aConfigurations;
  }

  void setCurrentConfiguration(const models::MachineConfigurationPtr &aCurrentConfiguration) {
    currentConfiguration = aCurrentConfiguration;
  }

 protected:
  models::MachineConfigurationPtr currentConfiguration;
};

typedef std::shared_ptr<Machine> MachinePtr;
} // namespace machinecore

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
