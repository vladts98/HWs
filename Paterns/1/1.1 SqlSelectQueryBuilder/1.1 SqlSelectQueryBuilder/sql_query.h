#pragma once
#include <iostream>
#include <list>


class sql_query
{
public:
	std::list<std::string> select;
	std::string from;
	std::list<std::pair<std::string, std::string>> where;
};

