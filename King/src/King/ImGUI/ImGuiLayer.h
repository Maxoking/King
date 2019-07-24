#pragma once
#include "King/Layer.h"
#include "King/Events/KeyEvent.h"
#include "King/Events/MouseEvent.h"

namespace King {
  class KING_API ImGuiLayer : public Layer {
  public:
    ImGuiLayer();
    ~ImGuiLayer() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onEvent(Event& e) override;
    bool onMousePressed(Event& e);
    virtual void onImGuiRender() override;

    void begin();
    void end();
  private:
    float m_time = 0.0f;

  };

}