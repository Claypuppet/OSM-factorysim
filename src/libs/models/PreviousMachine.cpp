//
// Created by bas on 23-5-18.
//

#include "PreviousMachine.h"

namespace models {

PreviousMachine::PreviousMachine(uint16_t machineId,
                                 uint16_t neededProducts,
                                 uint16_t inputBufferSize)
    : machineId(machineId),
      neededProducts(neededProducts),
      inputBufferSize(inputBufferSize) {
}

PreviousMachine::PreviousMachine(const models::PreviousMachine &other)
    : machineId(other.machineId),
      neededProducts(other.neededProducts),
      inputBufferSize(other.inputBufferSize) {
}


PreviousMachine &PreviousMachine::operator=(const PreviousMachine &other) {
  if(&other != this) {
    machineId = other.machineId;
    neededProducts = other.neededProducts;
    inputBufferSize = other.inputBufferSize;
  }
  return *this;
}

uint16_t PreviousMachine::getMachineId() const {
  return machineId;
}

uint16_t PreviousMachine::getNeededProducts() const {
  return neededProducts;
}

uint16_t PreviousMachine::getInputBufferSize() const {
  return inputBufferSize;
}

}