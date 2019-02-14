#include <King.h>
#include "ExampleLayer.h"


class Sandbox : public King::Application {
public:
  Sandbox() {

    pushLayer(new ExampleLayer());
    pushOverlay(new King::ImGuiLayer());
  }

  ~Sandbox() {

  }
};

King::Application* King::createApplication() {
  return new Sandbox();
};