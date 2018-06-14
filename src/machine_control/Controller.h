//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLER_H
#define PRODUCTION_LINE_CONTROL_CONTROLLER_H

#include "Application.h"

namespace machinecore {

/**
 * Class that controls an application
 */
class Controller {
 public:
  /**
   * Constructor
   * @param aMachineInfo : The machineInfo for application
   */
  explicit Controller(uint16_t aMachineId);
  
  Controller(const Controller&) = delete;

  /**
   * The destructor
   */
  virtual ~Controller() = default;

  /**
   * Getter for application
   * @return application
   */
  ApplicationPtr &getApplication();

  /**
   * Execute method, should be implemented in in the implementation class
   */
  virtual void execute() = 0;

  virtual void stop();

 protected:
  // True or false depending on whether Controller is running
  bool executing;

  // pointer to application
  ApplicationPtr application;
};
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLER_H
