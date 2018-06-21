//
// Created by klei on 5/16/18.
//

#include <utils/time/Time.h>
#include "Product.h"

namespace core {

Product::Product(uint16_t aProductId)
    : startTime(utils::Time::getInstance().getCurrentTime()), finishTime(0), productId(aProductId) {

}

Product::Product(const Product &other)
    : startTime(other.startTime), finishTime(other.finishTime), productId(other.productId) {

}

uint16_t Product::getProductId() const {
  return productId;
}

}