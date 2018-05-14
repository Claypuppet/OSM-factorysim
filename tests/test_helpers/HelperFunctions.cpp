//
// Created by klei on 5/10/18.
//

#include <ctime>

#include "HelperFunctions.h"

namespace testutils {

/* static */ void HelperFunctions::waitForPredicate(Predicate predicate, uint32_t timeout) {
  auto startTime = std::clock();
  while(!predicate() && std::difftime(std::clock(), startTime) < timeout){
	// Wait
  }
}
}