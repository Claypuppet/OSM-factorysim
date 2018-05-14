//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <cstdint>

namespace machinecore {

/**
 * A machine that is controlled by Application
 */
class Machine {
 public:
  Machine() = default;

  virtual ~Machine() = default;

};
} // namespace machinecore

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
