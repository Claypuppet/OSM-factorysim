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

class ProductionLine;
typedef std::shared_ptr<ProductionLine> ProductionLinePtr;

class ProductionLine {
 public:
  ProductionLine() = default;
  virtual ~ProductionLine() = default;

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
   * A function to deserialize a production line node
   * @param productionLineNode : The node to deserialize
   */
  void deserialize(YAML::Node &productionLineNode);

  /**
   * Getter for name
   * @return name
   */
  const std::string &getName() const;

  /**
   * Getter for products
   * @return products
   */
  const std::vector<Product> &getProducts() const;

  /**
   * Getter for machines
   * @return machines
   */
  const std::vector<Machine> &getMachines() const;

 private:
  std::string name;
  std::vector<Product> products;
  std::vector<Machine> machines;

  /**
   * A function to save a ProductionLine object in an archive
   * @tparam Archive
   * @param ar : The archive to save the object in
   */
  template<class Archive>
  void save(Archive &ar) const {
	ar(name, products, machines);
  }

  /**
   * A function to load a ProductionLine object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
	ar(name, products, machines);
  }

  friend class cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
