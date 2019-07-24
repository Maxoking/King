#pragma once
#include "Log.h"

//implement this in client
extern King::Application* King::createApplication();

int main(int argc, char** argv) {

  King::Log::init();
  auto app = King::createApplication();
  app->run();

  delete app;
}