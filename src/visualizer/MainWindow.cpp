//
// Created by don on 28-5-18.
//

#include "MainWindow.h"

ui::MainWindow::MainWindow()
    : wxFrame(NULL, wxID_ANY, "Hello world") {
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(1, "&Hello...\tCtrl-H",
                   "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);
  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");
  Bind(wxEVT_MENU, &MainWindow::onHello, this, 1);
  Bind(wxEVT_MENU, &MainWindow::onAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainWindow::onExit, this, wxID_EXIT);
}
void ui::MainWindow::onHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}
void ui::MainWindow::onExit(wxCommandEvent &event) {
  Close(true);
}
void ui::MainWindow::onAbout(wxCommandEvent &event) {
  wxMessageBox("This is a wxWidgets Hello World example",
               "About Hello World", wxOK | wxICON_INFORMATION);
}
