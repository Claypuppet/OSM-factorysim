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

uint16_t PreviousMachine::getMachineId() const {
  return machineId;
}

uint16_t PreviousMachine::getNeededProducts() const {
  return neededProducts;
}

}