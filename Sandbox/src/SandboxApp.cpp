#include <King.h>
#include "ExampleLayer.h"
#include "BackgoundLayer.h"
#include "TestGameLayer.h"


class Sandbox : public King::Application {
public:
  Sandbox() {
    pushLayer(new TestGameLayer());
	
  }

  ~Sandbox() {

  }
};

King::Application* King::createApplication() {
  return new Sandbox();
};