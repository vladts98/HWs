#pragma once
#include "Figures.h"

#ifdef Class_EXPORTS
#define Class_API __declspec(dllexport)
#else
#define Class_API __declspec(dllimport)
#endif

Class_API void print_info(Figure* figure);