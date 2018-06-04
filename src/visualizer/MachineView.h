//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINEVIEW_H
#define PRODUCTION_LINE_CONTROL_MACHINEVIEW_H

#include <memory>
#include "Machine.h"
namespace ui {

/**
 * View that visualizes a machine
 */
class MachineView {
 public:
  MachineView() = delete;
  MachineView(std::shared_ptr<visualisercore::Machine> machinePtr);
  MachineView(const MachineView& aMachineView);
  MachineView&operator=(const MachineView& rhs);
  /**
   * Sets the postion of the machine view
   * @param xPos : X position on screen
   * @param yPos : Y position on screen
   */
  void setPos(uint16_t xPos, uint16_t yPos);
 private:
  std::shared_ptr<visualisercore::Machine> machine;
  uint16_t x;
  uint16_t y;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINEVIEW_H
