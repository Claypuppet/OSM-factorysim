//
// Created by don on 29-5-18.
//

#include "WindowApplication.h"
#include "MainWindow.h"

bool WindowApplication::OnInit() {
  auto *window = new ui::MainWindow();
  window->Show();
  return true;
}
