//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <models/Machine.h>
#include <patterns/notifyobserver/Notifier.hpp>

namespace visualisercore {

/**
 * A class that holds information about a machine
 */
class Machine : public models::Machine, patterns::notifyobserver::Notifier {
 public:
  Machine() = delete;
  explicit Machine(const models::Machine &aConfig);
  explicit Machine(uint16_t anId);
  Machine(const Machine &aMachine);
  Machine &operator=(const Machine &rhs);
 private:

};

typedef std::shared_ptr<Machine> MachinePtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
