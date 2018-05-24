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

  virtual bool configure() = 0;
  virtual void selfTest() = 0;
  virtual void takeInProduct() = 0;
  virtual void processProduct() = 0;
  virtual void takeOutProduct() = 0;

  virtual void setConfigureStartState() = 0;
  virtual void setInOperationStartState() = 0;

  void setCurrentConfiguration(const models::MachineConfiguration &aCurrentConfiguration) {
    currentConfiguration = std::make_shared<models::MachineConfiguration>(aCurrentConfiguration);
  }

 protected:
  models::MachineConfigurationPtr currentConfiguration;
};

typedef std::shared_ptr<Machine> MachinePtr;
} // namespace machinecore

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
