//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MAINWINDOW_H
#define PRODUCTION_LINE_CONTROL_MAINWINDOW_H

#include <patterns/statemachine/Context.h>
#include "Application.h"
#include "Canvas.h"

namespace ui {

/**
 * Class that displays the application on the screen
 */
class MainWindow : public patterns::statemachine::Context {
 public:
  MainWindow() = default;
 private:
  visualizercore::Application application;
  Canvas canvas;
};

}

#endif //PRODUCTION_LINE_CONTROL_MAINWINDOW_H
