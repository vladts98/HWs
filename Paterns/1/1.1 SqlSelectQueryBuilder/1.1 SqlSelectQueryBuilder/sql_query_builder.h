#pragma once
#include "sql_query.h"
#include <map>
#include <vector>

class SqlSelectQueryBuilder
{
public:
	//SqlSelectQueryBuilder() = delete;
	SqlSelectQueryBuilder& AddColumn(const std::string& s);
	SqlSelectQueryBuilder& AddFrom(const std::string& s);
	SqlSelectQueryBuilder& AddWhere(const std::string& f, const std::string& s);
	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;

	std::string BuildQuery();
private:
	sql_query query;
};

