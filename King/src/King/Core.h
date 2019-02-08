#pragma once

#ifdef KING_BUILD_DLL
  #define KING_API __declspec(dllexport)
#else
  #define KING_API __declspec(dllimport)
#endif

#define BIT(x) (1<<x)