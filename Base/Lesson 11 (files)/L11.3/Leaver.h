#pragma once
#include <iostream> 

#ifdef Leaver_EXPORTS
#define LEAVERLIBRARYAPI __declspec(dllexport)
#else
#define LEAVERLIBRARYAPI __declspec(dllimport)
#endif

class Leaver {
public:
	LEAVERLIBRARYAPI void leave(std::string name);
};