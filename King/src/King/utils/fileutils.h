#pragma once
#include "kngpch.h"
#include "King/Log.h"


static std::string read_file(const char* filepath)
{
  std::string string;
  std::ifstream file(filepath);
  if (file.is_open()) {
    std::stringstream sstr;
    sstr << file.rdbuf();
    string = sstr.str();
  }
  else {
    KING_CORE_ERROR("Could not find file {0}",filepath);
  }

  return string;
}
