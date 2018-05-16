//
// Created by klei on 5/16/18.
//

#ifndef PRODUCTION_LINE_CONTROL_PRODUCT_H
#define PRODUCTION_LINE_CONTROL_PRODUCT_H

#include <memory>

namespace core {

/**
 * Class for the product in the production line. Is just a simple class now but can hold properties like started
 * production moment, moment it's finished etc. Maybe move this to models later
 */
class Product {
 public:
  Product() = default;
  virtual ~Product() = default;

};

typedef std::shared_ptr<Product> ProductPtr;

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCT_H
