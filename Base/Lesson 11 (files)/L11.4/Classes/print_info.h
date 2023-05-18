#pragma once
#include "Figures.h"

#ifdef Classes_EXPORTS
#define Classes_API __declspec(dllexport)
#else
#define Classes_API __declspec(dllimport)
#endif

Classes_API void print_info(Figure* figure);