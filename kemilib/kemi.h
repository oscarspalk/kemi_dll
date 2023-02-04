#include <string>
#include <vector>
#include "Element.h"

#pragma once

#ifdef KEMILIBRARY_EXPORTS
#define KEMILIBRARY_API __declspec(dllexport)
#else
#define KEMILIBRARY_API __declspec(dllimport)
#endif

extern "C" KEMILIBRARY_API char* M(char* input);

extern "C" KEMILIBRARY_API void initlib();

extern "C" KEMILIBRARY_API const char* G(int num);