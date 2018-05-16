//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H

#include "Application.h"
#include "Machine.h"

namespace machinecore {
class Controller {
 public:
  /**
   * Constructor
   * @param aMachineInfo : The machineInfo for application
   */
  explicit Controller(uint16_t aMachineId);

  /**
   * The destructor
   */
  virtual ~Controller() = default;

  /**
   * Getter for application
   * @return application
   */
  Application &getApplication();

 protected:
  Application application;
};
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
