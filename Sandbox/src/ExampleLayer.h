#pragma once
#include "King/Layer.h"


class ExampleLayer : public King::Layer {
public:
  ExampleLayer()
    : Layer("Example")
  {
  }

  void onUpdate() override;
  void onAttach() override;
  //void onEvent(King::Event& e) override { KING_TRACE(e); };
};
