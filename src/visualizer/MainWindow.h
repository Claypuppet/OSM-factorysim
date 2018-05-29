//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MAINWINDOW_H
#define PRODUCTION_LINE_CONTROL_MAINWINDOW_H

#include <patterns/statemachine/Context.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "Application.h"
#include "Canvas.h"

namespace ui {

/**
 * Class that displays the application on the screen
 */
class MainWindow : public patterns::statemachine::Context, wxFrame {
 public:
  MainWindow();
 private:
  visualizercore::Application application;
  Canvas canvas;
  void onHello(wxCommandEvent& event);
  void onExit(wxCommandEvent& event);
  void onAbout(wxCommandEvent& event);
};

}

#endif //PRODUCTION_LINE_CONTROL_MAINWINDOW_H
