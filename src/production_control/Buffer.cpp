//
// Created by klei on 5/16/18.
//

#include "Buffer.h"
#include "Machine.h"
#include "ResultLogger.h"

namespace core {

Buffer::Buffer(uint16_t aProductId) : fromMachine(), maxSize(0), totalProcessed(0), productId(aProductId) {
}

Buffer::Buffer(const MachinePtrW &aFromMachine, uint16_t aProductId) : fromMachine(aFromMachine), maxSize(0), totalProcessed(0), productId(aProductId) {
}

Buffer::Buffer(const MachinePtrW &aFromMachine, uint16_t aProductId, uint32_t size)
    : fromMachine(aFromMachine), maxSize(size), totalProcessed(0), productId(aProductId) {
}

bool Buffer::checkAmountInBuffer(uint32_t amount) {
  return size() >= amount;
}

bool Buffer::checkFreeSpaceInBuffer(uint32_t amount) {
  return (maxSize - size()) >= amount;
}

ProductPtr Buffer::takeFromBuffer() {
  if (!size()) {
    throw std::runtime_error("Unable to take from buffer: buffer empty");
  }
  return dequeue();
}

std::vector<ProductPtr> Buffer::takeFromBuffer(uint32_t amount) {
  if (size() < amount) {
    throw std::runtime_error("Unable to take from buffer: insufficient items in buffer");
  }

  std::vector<ProductPtr> list;
  while (list.size() < amount) {
    list.emplace_back(takeFromBuffer());
  }
  return list;
}

void Buffer::putInBuffer(const ProductPtr &item) {
  if (size() + 1 > maxSize) {
    throw std::runtime_error("Unable to place buffer: no space in buffer");
  }
  enqueue(item);
  ++totalProcessed;
}

void Buffer::putInBuffer(const std::vector<ProductPtr> &list) {
  for (const auto &item : list) {
    putInBuffer(item);
  }
}

uint16_t Buffer::getFromMachineId() const {
  auto machine = fromMachine.lock();
  if (machine) {
    return machine->getId();
  }
}

uint64_t Buffer::getTotalProcessed() const {
  return totalProcessed;
}

uint64_t Buffer::getAmountInBuffer() const {
  return size();
}

bool Buffer::isLastInLine() const {
  return toMachines.empty();
}

void Buffer::addToMachine(const MachinePtrW machine) {
  toMachines.emplace_back(machine);
}

void Buffer::debugPrintBuffersChain() {
  if (auto machine = fromMachine.lock()) {
    std::cout << machine->getName() << " (id " << machine->getId() << ") -> ";
  }
  else {
    std::cout << "Input -> ";
  }
  if(toMachines.empty()){
    std::cout << "End product" << std::endl;
  }
  for (const auto &machinew : toMachines){
    if (auto machine = machinew.lock()) {
      machine->getOutputBuffer(productId)->debugPrintBuffersChain();
    }
  }
}

}
