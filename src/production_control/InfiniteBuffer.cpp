//
// Created by klei on 5/24/18.
//

#include "InfiniteBuffer.h"

namespace core {

InfiniteBuffer::InfiniteBuffer(uint16_t aProductId)
    : Buffer(aProductId) {

}

InfiniteBuffer::InfiniteBuffer(const MachinePtrW &aFromMachine, uint16_t aProductId)
    : Buffer(aFromMachine, aProductId) {

}

InfiniteBuffer::InfiniteBuffer(const InfiniteBuffer &other) : Buffer(other) {}

bool InfiniteBuffer::checkAmountInBuffer(uint32_t amount) {
  return true;
}

bool InfiniteBuffer::checkFreeSpaceInBuffer(uint32_t amount) {
  return true;
}

ProductPtr InfiniteBuffer::takeFromBuffer() {
  return std::make_shared<Product>(productId);
}

std::vector<ProductPtr> InfiniteBuffer::takeFromBuffer(uint32_t amount) {
  std::vector<ProductPtr> list;
  while (list.size() < amount) {
    list.emplace_back(takeFromBuffer());
  }
  return list;
}

void InfiniteBuffer::putInBuffer(const ProductPtr &item) {
  ++totalProcessed;
}

void InfiniteBuffer::putInBuffer(const std::vector<ProductPtr> &list) {
  totalProcessed += list.size();
}
uint64_t InfiniteBuffer::getAmountInBuffer() const {
  return totalProcessed;
}

}
