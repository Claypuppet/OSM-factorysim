//
// Created by bas on 23-5-18.
//

#include "PreviousMachine.h"

namespace models {

PreviousMachine::PreviousMachine(uint16_t machineId,
                                 uint16_t neededProducts)
    : machineId(machineId),
      neededProducts(neededProducts) {
}

PreviousMachine::PreviousMachine(const models::PreviousMachine &other)
    : machineId(other.machineId),
      neededProducts(other.neededProducts) {
}


PreviousMachine &PreviousMachine::operator=(const PreviousMachine &other) {
  if(&other != this) {
    machineId = other.machineId;
    neededProducts = other.neededProducts;
  }
  return *this;
}

uint16_t PreviousMachine::getMachineId() const {
  return machineId;
}

uint16_t PreviousMachine::getNeededProducts() const {
  return neededProducts;
}

}