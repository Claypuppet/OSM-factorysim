//
// Created by don on 29-5-18.
//

#include "WindowApplication.h"
#include "MainWindow.h"

bool WindowApplication::OnInit() {
  auto *window = new ui::MainWindow();

  //Get screen size of device
  auto screenX = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
  auto screenY = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
  wxSize windowSize(screenX * 0.5, screenY * 0.5);

  //Set size of frame
  window->SetInitialSize(windowSize);
  window->Show();
  return true;
}
