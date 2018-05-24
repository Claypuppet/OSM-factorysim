//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PREVIOUSMACHINE_H
#define PRODUCTION_LINE_CONTROL_PREVIOUSMACHINE_H

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

/**
 * Class used by configuration to link previous machines.
 */
class PreviousMachine {
 public:
  PreviousMachine() = default;
  virtual ~PreviousMachine() = default;

  uint16_t getMachineId() const;
  uint16_t getNeededProducts() const;

 private:
  uint16_t machineId;
  uint16_t neededProducts;

  /**
   * A function to save a MachineConfiguration object in an archive
   * @tparam Archive
   * @param ar : The archive to save the object in
   */
  template<class Archive>
  void save(Archive &ar) const {
    ar(machineId, neededProducts);
  }

  /**
   * A function to load a MachineConfiguration object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
    ar(machineId, neededProducts);
  }

  friend class ::cereal::access;
};

#endif //PRODUCTION_LINE_CONTROL_PREVIOUSMACHINE_H
