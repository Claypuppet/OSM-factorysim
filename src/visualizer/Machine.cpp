//
// Created by don on 28-5-18.
//

#include "Machine.h"
visualizercore::Machine::Machine(const models::Machine &aConfig) : models::Machine(aConfig) {
}
visualizercore::Machine::Machine(const visualizercore::Machine &aMachine)
    : models::Machine(aMachine) {

}

visualizercore::Machine &visualizercore::Machine::operator=(const visualizercore::Machine &rhs) {
  if(this != &rhs)
  {
    this->name = rhs.name;
    this->id = rhs.id;
    this->configurations = rhs.configurations;
  }
  return *this;
}
visualizercore::Machine::Machine(uint16_t anId) :id(anId){
}
