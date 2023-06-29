#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& s)
{
	query.select.push_back(s);
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& s)
{
	query.from = s;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& f, const std::string& s)
{
	query.where.push_back(make_pair(f, s));
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept
{
	for (auto a : kv) {
		query.where.push_back(a);
	}
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept
{
	for (auto c : columns) {
		query.select.push_back(c);
	}
	return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery()
{
	std::string q = "SELECT ";
	if (query.select.size() == 0) {
		q += "*";
	}
	else {
		bool flag = false;
		for (auto s : query.select) {
			if (flag)
				q += ", " + s;
			else {
				q += s;
				flag = true;
			}
		}
	}
	q += " FROM " + query.from;

	if (query.where.size()) {
		q += " WHERE ";
		bool flag = false;
		for (auto w : query.where) {
			if (flag)
				q += " AND " + w.first + "=" + w.second;
			else {
				q += w.first + "=" + w.second;
				flag = true;
			}
		}
	}
	q += ";";
	return q;
}
