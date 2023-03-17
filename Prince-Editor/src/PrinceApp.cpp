#include <King.h>
#include "EditorLayer.h"

class Prince : public King::Application {
public:
  Prince() : Application("Prince") {
      pushLayer(new EditorLayer());
	
  }

  ~Prince() {

  }
};

King::Application* King::createApplication() {
  return new Prince;
};