//
// Created by klei on 6/11/18.
//

#include <chrono>
#include "RandomHelper.h"

namespace utils {

RandomHelper::RandomHelper()
    : generator(std::mt19937(static_cast<uint64_t >(std::chrono::system_clock::now().time_since_epoch().count()))) {
}

void RandomHelper::setSeed(uint64_t seed) {
  generator = std::mt19937(seed);
}
uint32_t RandomHelper::getRandom(NormalDistribution &distribution) {
  return static_cast<uint32_t>(std::round(distribution(getInstance().generator)));
}
uint64_t RandomHelper::getRandom(UnsignedUniformDistribution &distribution) {
  return distribution(getInstance().generator);
}
int32_t RandomHelper::getRandom(SignedUniformDistribution &distribution) {
  return distribution(getInstance().generator);
}

}