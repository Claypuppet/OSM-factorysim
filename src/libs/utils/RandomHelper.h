//
// Created by klei on 6/11/18.
//

#ifndef PRODUCTION_LINE_CONTROL_RANDOMHELPER_H
#define PRODUCTION_LINE_CONTROL_RANDOMHELPER_H

#include <patterns/singleton/Singleton.h>
#include <random>

namespace utils {

typedef std::uniform_int_distribution<uint64_t> UnsignedUniformDistribution;
typedef std::uniform_int_distribution<int32_t> SignedUniformDistribution;
typedef std::normal_distribution<> NormalDistribution;

class RandomHelper : public patterns::singleton::Singleton<RandomHelper> {
 public:
  void setSeed(uint64_t seed);
  static uint32_t getRandom(NormalDistribution &distribution);
  static uint64_t getRandom(UnsignedUniformDistribution &distribution);
  static int32_t getRandom(SignedUniformDistribution &distribution);

 private:
  friend patterns::singleton::Singleton<RandomHelper>;
  RandomHelper();
  virtual ~RandomHelper() = default;

  std::mt19937 generator;
};

}

#endif //PRODUCTION_LINE_CONTROL_RANDOMHELPER_H
