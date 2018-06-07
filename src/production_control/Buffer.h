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
 * Buffer class, uses a queue for storing the products.
 */
class Buffer : private patterns::producerconsumer::Queue<ProductPtr> {
 public:

  /**
   * Create a finite buffer
   * @param size : size of the buffer
   */
  explicit Buffer(const MachinePtrW &taker, uint16_t productId, uint32_t size);

  /**
   * destruct
   */
  virtual ~Buffer() = default;

  /**
   * checks if given amount is available in buffer
   * @param amount : amount to check
   * @return : true if its available
   */
  virtual bool checkAmountInBuffer(uint32_t amount);

  /**
   * checks if given amount can be placed in buffer
   * @param amount : amount to check
   * @return : true if its possible
   */
  virtual bool checkFreeSpaceInBuffer(uint32_t amount);

  /**
   * Take 1 from buffer
   * @throw : throws exception if it's not possible
   * @return : product
   */
  virtual ProductPtr takeFromBuffer();

  /**
   * Take multiple from buffer
   * @throw : throws exception if it's not possible
   * @param amount : amount to take
   * @return : product
   */
  virtual std::vector<ProductPtr> takeFromBuffer(uint32_t amount);

  /**
   * Put an item in the buffer
   * @throw : throws exception if it's not possible
   * @param item : item to put in the buffer
   */
  virtual void putInBuffer(const ProductPtr &item);

  /**
   * Put multiple items in the buffer
   * @throw : throws exception if it's not possible
   * @param list
   */
  virtual void putInBuffer(const std::vector<ProductPtr> &list);

  /**
   * get machine id from the taker machine of this buffer
   * @return : machine id
   */
  uint16_t getMachineIdOfTaker() const;

  /**
   * get machine id from the putter machine of this buffer
   * @return : machine id
   */
  uint16_t getMachineIdOfPutter() const;

  /**
   * Get number of total processed items that went through the buffer
   * @return : total items
   */
  uint64_t getTotalProcessed() const;

  /**
   * get current amount in buffer
   * @return : amount of items in buffer
   */
  virtual uint64_t getAmountInBuffer() const;

  /**
   * Checks if this buffer is not used by any other machines as input buffer
   * @return : true if its last in line
   */
  bool isLastInLine() const;

  /**
   * Add a machine that uses this buffer
   * @param machine
   */
  void addToMachine(const MachinePtrW &machine);


  MachinePtrW getPutter() const;

  /**
   * Print list of buffers after this.
   */
  void debugPrintBuffersChain(std::stringstream &stream);

 protected:
  /**
   * Construct an buffer for machine, used by infinite buffer
   */
  explicit Buffer(uint16_t productId);
  explicit Buffer(const MachinePtrW &taker, uint16_t productId);

  MachinePtrW taker, putter;

  uint32_t maxSize;

  uint64_t totalProcessed;
  uint16_t productId;

};

typedef std::shared_ptr<Buffer> BufferPtr;
typedef std::vector<BufferPtr> BufferList;

}

#endif //PRODUCTION_LINE_CONTROL_BUFFER_H
