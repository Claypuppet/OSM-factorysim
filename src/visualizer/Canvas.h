//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CANVAS_H
#define PRODUCTION_LINE_CONTROL_CANVAS_H

#include <patterns/notifyobserver/Observer.hpp>
#include <cereal/types/vector.hpp>
#include <wx/wx.h>
#include "MachineView.h"
namespace ui {

/**
 * Class that displays machines and their status
 */
class Canvas : public wxScrolledCanvas, public patterns::notifyobserver::Observer{
 public:
  Canvas() = default;
  void handleNotification(const patterns::notifyobserver::NotifyEvent &notification) override;
 private:
  std::vector<MachineView> machineViews;
};

}

#endif //PRODUCTION_LINE_CONTROL_CANVAS_H
