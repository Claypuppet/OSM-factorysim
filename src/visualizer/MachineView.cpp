//
// Created by don on 28-5-18.
//

#include "MachineView.h"
ui::MachineView::MachineView(std::shared_ptr<visualizercore::Machine> machinePtr) : machine(machinePtr) {

}
ui::MachineView::MachineView(const ui::MachineView &aMachineView)
    : machine(aMachineView.machine), x(aMachineView.x), y(aMachineView.y) {
}
ui::MachineView &ui::MachineView::operator=(const ui::MachineView &rhs) {
  if(this != &rhs){
    machine = rhs.machine;
    x = rhs.x;
    y = rhs.y;
  }
  return *this;
}
void ui::MachineView::setPos(uint16_t xPos, uint16_t yPos) {
  x = xPos;
  y = yPos;
}
