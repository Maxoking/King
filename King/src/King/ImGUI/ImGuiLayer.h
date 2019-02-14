#pragma once
#include "King/Layer.h"
#include "King/Events/KeyEvent.h"
#include "King/Events/MouseEvent.h"

namespace King {
  class KING_API ImGuiLayer : public Layer {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void onAttach() override;
    void onDetach() override;
    void onEvent(Event& e) override;
    void onUpdate() override;


  private:
    float m_time;

    bool onMousePressed(MouseButtonPressed& e);
    bool onMouseReleased(MouseButtonReleased& e);
    bool onMouseMoved(MouseMoved& e);
    bool onKeyPressed(KeyPressedEvent& e);
    bool onKeyReleased(KeyReleasedEvent& e);

  };

}