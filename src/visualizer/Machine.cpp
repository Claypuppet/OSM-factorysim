//
// Created by don on 28-5-18.
//

#include "Machine.h"

namespace visualizercore {

Machine::Machine(const models::Machine &aConfig) : models::Machine(aConfig) {
}
Machine::Machine(const Machine &aMachine)
    : models::Machine(aMachine) {

}

Machine &visualizercore::Machine::operator=(const Machine &rhs) {
  if (this != &rhs) {
    this->name = rhs.name;
    this->id = rhs.id;
    this->configurations = rhs.configurations;
  }
  return *this;
}

Machine::Machine(uint16_t anId) : id(anId) {
}

}
