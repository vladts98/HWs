#include <iostream>
#include <vector>
#include <variant>
#include <string>

std::variant<int, std::string, std::vector<int>> get_variant() {
	std::srand(std::time(nullptr));
	int random_variable = std::rand() % 3;

	std::variant<int, std::string, std::vector<int>> result;
	switch (random_variable)
	{
	case 0:
		result = 5;
		break;
	case 1:
		result = "string";
		break;
	case 2:
		result = std::vector<int>{ 1, 2, 3, 4, 5 };
		break;
	default:
		break;
	}
	return result;
}

int main()
{
	auto a = get_variant();
	if (std::holds_alternative<int>(a)) {
		std::cout << std::get<int>(a) * 2;
	}
	else if (std::holds_alternative<std::string>(a)) {
		std::cout << std::get<std::string>(a);
	}
	else if (std::holds_alternative<std::vector<int>>(a))
		for (auto i : std::get<std::vector<int>>(a)) {
			std::cout << i << " ";
		}
	else {
		std::cout << " aaaaaaa";
	}
}