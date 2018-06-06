//
// Created by klei on 5/16/18.
//

#include "Buffer.h"
#include "Machine.h"
#include "ResultLogger.h"

namespace core {

Buffer::Buffer(uint16_t aProductId) : inputFor(), maxSize(0), totalProcessed(0), productId(aProductId) {
}

Buffer::Buffer(const MachinePtrW &aFromMachine, uint16_t aProductId) : inputFor(aFromMachine), maxSize(0), totalProcessed(0), productId(aProductId) {
}

Buffer::Buffer(const MachinePtrW &inputFor, uint16_t aProductId, uint32_t size)
    : inputFor(inputFor), maxSize(size), totalProcessed(0), productId(aProductId) {
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

uint16_t Buffer::getMachineIdOfInputFor() const {
  return inputFor.lock()->getId();
}

MachinePtrW Buffer::getOutputFor() const {
  return outputFor;
}

uint64_t Buffer::getTotalProcessed() const {
  return totalProcessed;
}

uint64_t Buffer::getAmountInBuffer() const {
  return size();
}

bool Buffer::isLastInLine() const {
  return (inputFor.lock() == nullptr);
}

void Buffer::addToMachine(const MachinePtrW &machine) {
  outputFor = machine;
}

void Buffer::debugPrintBuffersChain(std::stringstream &stream) {
  if (auto machine = inputFor.lock()) {
    stream << machine->getName() << " (id " << machine->getId() << ") -> ";
  }
  else {
    stream << "Input -> ";
  }

  if(outputFor.lock() == nullptr){
    stream << "End product" << std::endl;
  }

  if (auto machine = outputFor.lock()) {
    machine->getOutputBuffer(productId)->debugPrintBuffersChain(stream);
  }
}

}
