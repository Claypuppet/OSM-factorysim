#ifndef PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H

#include <string>
#include <cstdint>
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

namespace models {

class Product;
typedef std::shared_ptr<Product> ProductPtr;

class Product {
 public:
  virtual ~Product() = default;

  /**
   * ...
   * @param id
   * @param name
   * @param proportion
   */
  Product(uint16_t id, const std::string &name, uint16_t proportion);

  /**
   * Copy constructor
   * @param other : The object to copy
   */
  Product(const Product &other);

  /**
   * Assignment operator
   * @param other : The object to assign
   * @return The new object
   */
  Product &operator=(const Product &other);

  /**
   * A function to deserialize a product node
   * @param productNode : The node to deserialize
   */
  void deserialize(YAML::Node &productNode);

  /**
   * Getter for id
   * @return id
   */
  uint16_t getId() const;

  /**
   * Getter for name
   * @return name
   */
  const std::string &getName() const;

  /**
   * Getter for proportion
   * @return proportion
   */
  uint16_t getProportion() const;

 private:
  uint16_t id;
  std::string name;
  uint16_t proportion;

  /**
   * A function to save a Product object in an archive
   * @tparam Archive
   * @param ar : The archive to save the objct in
   */
  template<class Archive>
  void save(Archive &ar) const {
	ar(id, name, proportion);
  }

  /**
   * A function to load a Product object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
	ar(id, name, proportion);
  }

  friend class cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
