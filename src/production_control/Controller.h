
#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H

#include "Application.h"
#include "patterns/statemachine/Context.h"

namespace core {

class Controller {
 public:
  Controller();
  virtual ~Controller() = default;

  /**
   * Execute main loop
   */
  virtual void execute();

  /**
   * Stop the execution.
   */
  virtual void stop();

  /**
   * Get controllers application instance
   * @return controllers application instance
   */
  ApplicationPtr &getApplication();

 protected:
  ApplicationPtr application;
  std::vector<MachinePtr> machines;

  bool executing;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
