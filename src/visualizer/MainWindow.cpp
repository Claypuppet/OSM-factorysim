//
// Created by don on 28-5-18.
//

#include "MainWindow.h"
#include "application_states/file_states/FileState.h"
#include "FileApplication.h"
#include <wx/wfstream.h>

namespace ui {

MainWindow::MainWindow()
    : wxFrame(NULL, wxID_ANY, "Visualizer") {
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(wxID_FILE, "Select file");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);
  CreateStatusBar();
  //SetStatusText("Welcome to wxWidgets!");

  Bind(wxEVT_MENU, &MainWindow::onOpenFile, this, wxID_FILE);
  Bind(wxEVT_MENU, &MainWindow::onAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainWindow::onExit, this, wxID_EXIT);
}

void MainWindow::onExit(wxCommandEvent &event) {
  if(application){
    application->stop();
  }
  Close(true);
}
void MainWindow::onAbout(wxCommandEvent &event) {
  wxMessageBox("This is a wxWidgets Hello World example",
               "About Hello World", wxOK | wxICON_INFORMATION);
}
void MainWindow::onOpenFile(wxCommandEvent &event) {
  wxFileDialog
      openFileDialog(this, _("Open yaml file"), "", "",
                     "YAML files (*.yaml)|*.yaml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL)
    return;     // the user changed idea...

  // proceed loading the file chosen by the user;
  // this can be done with e.g. wxWidgets input streams:
  std::string pathToFile = std::string(openFileDialog.GetPath());
  wxFileInputStream input_stream(pathToFile);
  if (!input_stream.IsOk()) {
    wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
    return;
  } else {
    std::cout << "Selected file: " << pathToFile << std::endl;
    application = std::make_shared<file::FileApplication>(pathToFile);
    application->setStartState();
    application->start();
  }
}

}