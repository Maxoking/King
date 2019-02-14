#pragma once

#ifdef KING_BUILD_DLL
  #define KING_API __declspec(dllexport)
#else
  #define KING_API __declspec(dllimport)
#endif

#define BIT(x) (1<<x)

#define KING_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)