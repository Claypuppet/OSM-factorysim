//
// Created by klei on 5/16/18.
//

#include "Buffer.h"
#include "Machine.h"

namespace core {

Buffer::Buffer() : fromMachine(), maxSize(0), totalProcessed(0) {

}

Buffer::Buffer(const MachinePtrW &aFromMachine, uint32_t size) : fromMachine(aFromMachine), maxSize(size), totalProcessed(0) {

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
  std::cout << "Placed item in buffer, currently " << size() << " products in buffer (max: " << maxSize << ")" << std::endl;
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

}
