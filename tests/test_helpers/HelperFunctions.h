//
// Created by klei on 5/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_HELPERFUNCTIONS_H
#define PRODUCTION_LINE_CONTROL_HELPERFUNCTIONS_H

#include <functional>
namespace testUtils{

typedef std::function<bool()> Predicate;

class HelperFunctions {
 public:
  /**
   * Wait for the predicate to be true, times out after given milliseconds
   * @param predicate : predicate to be true
   * @param timeout : timeout in milliseconds
   */
  static void waitForPredicate(Predicate predicate, uint32_t timeout);

 private:
  // Because its a "static" class which holds only helper functions, no objects can be instanced
  HelperFunctions() = default;
  virtual ~HelperFunctions() = default;
};

}

#endif //PRODUCTION_LINE_CONTROL_HELPERFUNCTIONS_H
