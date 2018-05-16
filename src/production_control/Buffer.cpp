//
// Created by klei on 5/16/18.
//

#include "Buffer.h"


namespace core {

Buffer::Buffer(): infinite(true), maxSize(0) {

}
Buffer::Buffer(uint16_t size) : infinite(false), maxSize(size) {

}
bool Buffer::checkAmountInBuffer(uint16_t amount) {
  return infinite || size() >= amount;
}

bool Buffer::canPutinInBuffer(uint16_t amount) {
  return infinite || (maxSize - size()) >= amount;
}

ProductPtr Buffer::takeFromBuffer() {
  if(infinite){
    return std::shared_ptr<Product>(new Product);
  }
  else if(!size()){
    throw std::runtime_error("Unable to take from buffer: buffer empty");
  }
  return dequeue();
}

std::vector<ProductPtr> Buffer::takeFromBuffer(uint16_t amount) {
  std::vector<ProductPtr> list;

  if(infinite){
    while (list.size() < amount){
      list.emplace_back(std::shared_ptr<Product>(new Product));
    }
  }
  else if(size() < amount){
    throw std::runtime_error("Unable to take from buffer: buffer not enough products");
  }
  else{
    while (list.size() < amount){
      list.emplace_back(dequeue());
    }
  }
  return list;
}

void Buffer::putInBuffer(const ProductPtr &item) {
  if(!infinite) {
    if(size() + 1 > maxSize){
      throw std::runtime_error("Unable to place buffer: no space in buffer");
    }
    enqueue(item);
  }
}

void Buffer::putInBuffer(const std::vector<ProductPtr> &list) {
  if(!infinite) {
    if(size() + 1 > maxSize){
      throw std::runtime_error("Unable to place buffer: no space in buffer");
    }
    for (const auto &item : list){
      enqueue(item);
    }
  }
}

}
