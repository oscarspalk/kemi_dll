#pragma once

#ifdef KEMILIBRARY_EXPORTS
#define KEMILIBRARY_API __declspec(dllexport)
#else
#define KEMILIBRARY_API __declspec(dllimport)
#endif

extern "C" KEMILIBRARY_API char* M(char* input);