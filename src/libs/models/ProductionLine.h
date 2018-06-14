#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

#include "Product.h"
#include "Machine.h"

namespace models {

/**
 * Class that holds information about a production line
 * The name of the production line, the products that are produced and what machines are in it
 */
class ProductionLine;
typedef std::shared_ptr<ProductionLine> ProductionLinePtr;

class ProductionLine {
 public:
  ProductionLine() = default;
  virtual ~ProductionLine() = default;

  /**
   * ...
   * @param name
   * @param products
   * @param machines
   */
  ProductionLine(const std::string &name,
                 const std::vector<ProductPtr> &products,
                 const std::vector<MachinePtr> &machines);

  /**
   * Copy constructor
   * @param other : The object to copy
   */
  ProductionLine(const ProductionLine &other);

  /**
   * Assignment operator
   * @param other : The object to assign
   * @return The new object
   */
  ProductionLine &operator=(const ProductionLine &other);

  /**
   * Getter for name
   * @return name
   */
  const std::string &getName() const;

  /**
   * Getter for products
   * @return products
   */
  const std::vector<ProductPtr> &getProducts() const;

  /**
   * Getter for products
   * @return products
   */
  const ProductPtr getProductById(uint16_t productId) const;

  /**
   * Getter for machines
   * @return machines
   */
  const std::vector<MachinePtr> &getMachines() const;

 private:
  std::string name;
  std::vector<ProductPtr> products;
  std::vector<MachinePtr> machines;


  /**
   * A function to serialize a ProductionLine object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void serialize(Archive &ar) {
	ar(name,
       products,
       machines);
  }

  friend class cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
