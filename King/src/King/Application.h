#pragma once
#include "Core.h"

namespace King {

  class KING_API Application
  {
  public:
    Application();
    virtual ~Application();

    void run();


  };

  //To be defined in CLIENTapplication
  Application* createApplication();
}


