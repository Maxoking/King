#include <King.h>
#include "TestGameLayer.h"
//#include "TestShadowLayer.h"

class Sandbox : public King::Application {
public:
  Sandbox() {
	pushLayer(new TestGameLayer());
   // pushLayer(new TestShadowLayer());
	
  }

  ~Sandbox() {

  }
};

King::Application* King::createApplication() {
  return new Sandbox();
};