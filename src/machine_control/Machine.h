//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <cstdint>

namespace machinecore {

/**
 * A pure virtual machine that is controlled by Application,
 */
class Machine {
 public:
  Machine() = default;

  virtual ~Machine() = default;

  virtual void configure() = 0;
  virtual void selfTest() = 0;
  virtual void takeInProduct() = 0;
  virtual void processProduct() = 0;
  virtual void takeOutProduct() = 0;

};

typedef std::shared_ptr<Machine> MachinePtr;

} // namespace machinecore

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
