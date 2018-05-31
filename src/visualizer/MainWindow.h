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
class MainWindow : public wxFrame, patterns::statemachine::Context {
 public:
  MainWindow();
 private:

  /**
   * Closes the application and stops running threads
   * @param event
   */
  void onExit(wxCommandEvent &event);

  /**
   * placeholder
   * @param event
   */
  void onAbout(wxCommandEvent &event);

  /**
   * Function that is called when the select file option in the menu bar is clicked
   * Than you can select a file
   * When a file is selected a FileApplication is made and its state machine starts running
   * @param event
   */
  void onOpenFile(wxCommandEvent &event);

  std::shared_ptr<visualisercore::Application> application;
  Canvas canvas;
};

}

#endif //PRODUCTION_LINE_CONTROL_MAINWINDOW_H
