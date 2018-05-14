//
// Created by klei on 5/10/18.
//

#include <chrono>
#include <iostream>

#include "HelperFunctions.h"

namespace testutils {

/* static */ void HelperFunctions::waitForPredicate(Predicate predicate, uint32_t timeout) {
  auto getTime = std::chrono::system_clock::now;
  auto startTime = getTime();
  auto timeoutMillis = std::chrono::milliseconds(timeout);
  while(!predicate() && std::chrono::duration_cast<std::chrono::milliseconds>(getTime() - startTime) < timeoutMillis){

	// Wait
  }
}
}