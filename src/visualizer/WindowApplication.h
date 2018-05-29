//
// Created by don on 29-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_WINDOWAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_WINDOWAPPLICATION_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class WindowApplication : public wxApp{
 public:
  virtual bool OnInit();
};

#endif //PRODUCTION_LINE_CONTROL_WINDOWAPPLICATION_H
