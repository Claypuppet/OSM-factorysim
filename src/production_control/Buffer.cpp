//
// Created by klei on 5/16/18.
//

#include "Buffer.h"
#include "Machine.h"
#include "ResultLogger.h"

namespace core {

Buffer::Buffer(uint16_t aProductId) : taker(), maxSize(0), totalProcessed(0), productId(aProductId) {
}

Buffer::Buffer(const MachinePtrW &taker, uint16_t aProductId)
    : taker(taker), maxSize(0), totalProcessed(0), productId(aProductId) {
}

Buffer::Buffer(const MachinePtrW &taker, uint16_t aProductId, uint32_t size)
    : taker(taker), maxSize(size), totalProcessed(0), productId(aProductId) {
}

bool Buffer::checkAmountInBuffer(uint32_t amount) {
  return size() >= amount;
}

bool Buffer::checkFreeSpaceInBuffer(uint32_t amount) {
  if (auto nextMachine = taker.lock()) {
    return nextMachine->getCurrentConfigId() == productId && (maxSize - size()) >= amount;
  }
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

uint16_t Buffer::getMachineIdOfTaker() const {
  if (auto lockedTaker = taker.lock()) {
    return lockedTaker->getId();
  }
  return 0;
}

uint16_t Buffer::getMachineIdOfPutter() const {
  if (auto lockedPutter = putter.lock()) {
    return lockedPutter->getId();
  }
  return 0;
}

MachinePtrW Buffer::getPutter() const {
  return putter;
}

uint64_t Buffer::getTotalProcessed() const {
  return totalProcessed;
}

uint64_t Buffer::getAmountInBuffer() const {
  return size();
}

bool Buffer::isLastInLine() const {
  auto lockedTaker = taker.lock();
  return (lockedTaker == nullptr);
}

void Buffer::setPutterMachine(const MachinePtrW &machine) {
  putter = machine;
}

void Buffer::debugPrintBuffersChain(std::stringstream &stream) {
  if (!putter.lock()) {
    stream << "(Input) ";
  }
  stream << "Buffer (" << (maxSize ? std::to_string(maxSize) : "infinite") << ")";
  if (auto machine = taker.lock()) {
    stream << " -> " << machine->getName() << " (id " << machine->getId() << ") -> ";
    machine->getOutputBuffer(productId)->debugPrintBuffersChain(stream);
  }
  else {
    stream << " (End product)" << std::endl;
  }
}

}
