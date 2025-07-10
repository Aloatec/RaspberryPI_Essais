#pragma once

#include <iostream>

#if WIN32
#  if defined(FMT_LIB_EXPORT)
#    define FMT_API __declspec(dllexport)
#  elif defined(FMT_SHARED)
#    define FMT_API __declspec(dllimport)
#  endif
#endif

void printSomething();