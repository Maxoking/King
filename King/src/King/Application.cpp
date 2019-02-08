//Always include precompiled header first
#include "kngpch.h"

#include "Application.h"
#include "Events/KeyEvent.h"
#include "Log.h"

namespace King {

  Application::Application()
  {
  }


  Application::~Application()
  {
  }

  void Application::run() {
    KeyPressedEvent e(0, 0);
    KING_CORE_INFO(e);

    if (e.isInCategory(EventCategoryInput)) {
      KING_CORE_TRACE("CATEGORY INPUT");
    }

    if (e.isInCategory(EventCategoryKeyboard)) {
      KING_CORE_TRACE("CATEGORY KEYBOARD");
    }

    if (e.isInCategory(EventCategoryApplication)) {
      KING_CORE_TRACE("FALSCH");
    }

    
    while (true) {
    };
  }
}
