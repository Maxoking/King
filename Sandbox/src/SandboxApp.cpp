#include <King.h>
#include "ExampleLayer.h"
#include "BackgoundLayer.h"
#include "TestGameLayer.h"


class Sandbox : public King::Application {
public:
  Sandbox() {
	//ExampleLayer* layer = new ExampleLayer();
 // pushLayer(layer);
	//pushLayer(new BackgroundLayer());
    pushLayer(new TestGameLayer());
    pushOverlay(new King::ImGuiLayer());
	
  }

  ~Sandbox() {

  }
};

King::Application* King::createApplication() {
  return new Sandbox();
};