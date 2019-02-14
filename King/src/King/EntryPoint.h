#pragma once
#include "Log.h"
#include "Maths/vec2.h"
#include "Maths/vec3.h"
#include "utils/glmutils.h"

//implement this in client
extern King::Application* King::createApplication();

int main(int argc, char** argv) {

  King::Log::init();
  glm::vec3 test(1.f, 2.f, 3.f);
  glm::vec3 test2(1.f);
  KING_CORE_TRACE(test + test2);
  auto app = King::createApplication();
  app->run();

  delete app;
}