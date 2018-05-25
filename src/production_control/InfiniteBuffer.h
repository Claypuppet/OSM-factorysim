//
// Created by klei on 5/24/18.
//

#ifndef PRODUCTION_LINE_CONTROL_INFINITEBUFFER_H
#define PRODUCTION_LINE_CONTROL_INFINITEBUFFER_H

#include "Buffer.h"

namespace core{

/**
 * Infinite buffer class, a product generator / dump place. Also known as the INFINITY BUFFER
 */
class InfiniteBuffer : public Buffer {
 public:
  /**
   * Construct infinite buffer
   * @param fromMachine
   * @param productId
   */
  InfiniteBuffer(uint16_t productId);

  ~InfiniteBuffer() override = default;

  /**
   * checks if given amount is available in buffer, which is always true in the INFINITY BUFFER
   * @param amount : amount to check
   * @return : true if its available
   */
  bool checkAmountInBuffer(uint32_t amount) override;

  /**
   * checks if given amount can be placed in buffer, which is always true in the INFINITY BUFFER
   * @param amount : amount to check
   * @return : true if its possible
   */
  bool checkFreeSpaceInBuffer(uint32_t amount) override;

  /**
   * Take 1 from buffer, the INFINITY BUFFER will create the product
   * @throw : throws exception if it's not possible
   * @return : product
   */
  ProductPtr takeFromBuffer() override;

  /**
   * Take multiple from buffer
   * @throw : throws exception if it's not possible
   * @param amount : amount to take
   * @return : product
   */
  std::vector<ProductPtr> takeFromBuffer(uint32_t amount) override;

  /**
   * Put an item in the buffer, the INFINITY BUFFER will "destroy" the product and just keep track of the total produced
   * @throw : throws exception if it's not possible
   * @param item : item to put in the buffer
   */
  void putInBuffer(const ProductPtr &item) override;

  /**
   * Put multiple items in the buffer
   * @throw : throws exception if it's not possible
   * @param list
   */
  void putInBuffer(const std::vector<ProductPtr> &list) override;

  uint16_t productId;

};

typedef std::shared_ptr<InfiniteBuffer> InfiniteBufferPtr;

}

#endif //PRODUCTION_LINE_CONTROL_INFINITEBUFFER_H
