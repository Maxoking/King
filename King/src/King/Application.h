#pragma once
#include "Core.h"
#include "King/Window.h"
#include "King/Events/Event.h"
#include "King/Events/ApplicationEvent.h"
#include "King/Events/MouseEvent.h"
#include "LayerStack.h"

namespace King {

  class KING_API Application
  {
  protected:
    LayerStack m_stack;

  private:
    static Application* s_instance;
    std::unique_ptr<Window> m_window;
    bool m_running = true;
  public:
    inline static Application& get() { return *s_instance; }

    Application();
    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);
    void onEvent(Event& e);
    bool onMouseMoved(MouseMoved & e);
    bool onWindowClose(WindowCloseEvent& e);
    bool onWindowRezise(WindowResizeEvent& e);
    virtual ~Application();

    inline Window& getWindow() { return *m_window; };
    void run();


  };

  //To be defined in CLIENTapplication
  Application* createApplication();
}


