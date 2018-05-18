//
// Created by klei on 5/16/18.
//

#ifndef PRODUCTION_LINE_CONTROL_BUFFER_H
#define PRODUCTION_LINE_CONTROL_BUFFER_H

#include <cstdint>

#include <patterns/producerconsumer/Queue.h>

#include "Product.h"

namespace core {

class Machine;
typedef std::weak_ptr<Machine> MachinePtrW;

/**
 * Buffer class, uses a queue for storing the products. The buffer class can be infinite, then it will just be a product
 * generator / dump place.
 */
class Buffer : private patterns::producerconsumer::Queue<ProductPtr> {
 public:
  /**
   * Create an infinite buffer, default constructor
   */
  Buffer(const MachinePtrW &fromMachine);

  /**
   * Create a finite buffer
   * @param size : size of the buffer
   */
  explicit Buffer(const MachinePtrW &fromMachine, uint16_t size);

  /**
   * destruct
   */
  virtual ~Buffer() = default;

  /**
   * checks if given amount is available in buffer
   * @param amount : amount to check
   * @return : true if its available
   */
  bool checkAmountInBuffer(uint16_t amount);

  /**
   * checks if given amount can be placed in buffer
   * @param amount : amount to check
   * @return : true if its possible
   */
  bool checkFreeSpaceInBuffer(uint16_t amount);

  /**
   * Take 1 from buffer
   * @throw : throws exception if it's not possible
   * @return : product
   */
  ProductPtr takeFromBuffer();

  /**
   * Take multiple from buffer
   * @throw : throws exception if it's not possible
   * @param amount : amount to take
   * @return : product
   */
  std::vector<ProductPtr> takeFromBuffer(uint16_t amount);

  /**
   * Put an item in the buffer
   * @throw : throws exception if it's not possible
   * @param item : item to put in the buffer
   */
  void putInBuffer(const ProductPtr &item);

  /**
   * Put multiple items in the buffer
   * @throw : throws exception if it's not possible
   * @param list
   */
  void putInBuffer(const std::vector<ProductPtr> &list);

  /**
   * get machine id from the owner of this buffer
   * @return : machine id
   */
  uint16_t getFromMachineId() const;

 private:
  bool infinite;
  uint16_t maxSize;
  MachinePtrW fromMachine;

};

typedef std::shared_ptr<Buffer> BufferPtr;
typedef std::vector<BufferPtr> BufferList;

}

#endif //PRODUCTION_LINE_CONTROL_BUFFER_H
