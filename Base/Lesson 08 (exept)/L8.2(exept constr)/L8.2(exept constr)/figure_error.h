#pragma once
#include <iostream>
#include <string>

class figure_error : public std::domain_error
{
public:
	figure_error(const char* msg);

	//const char* what() const override {
		//return "how did u do this? ";
	//}
};