#pragma once
#include "Log.h"

//implement this in client
extern King::Application* King::createApplication();

int main(int argc, char** argv) {

  King::Log::init();

  KING_CORE_INFO("MAKRO");
  KING_ERROR("Client");
  int a = 5;
  KING_INFO(a);

  auto app = King::createApplication();
  app->run();

  delete app;
}