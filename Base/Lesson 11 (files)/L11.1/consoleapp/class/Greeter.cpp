#include "Greeter.h"


namespace greet {
	void Greeter::greet(std::string name)
	{
		std::cout << "Здравствуйте, " << name << "!";
	}
}