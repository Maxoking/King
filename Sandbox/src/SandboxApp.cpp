#include <King.h>

class Sandbox : public King::Application {
public:
  Sandbox() {

  }

  ~Sandbox() {

  }
};

King::Application* King::createApplication() {
  return new Sandbox();
};