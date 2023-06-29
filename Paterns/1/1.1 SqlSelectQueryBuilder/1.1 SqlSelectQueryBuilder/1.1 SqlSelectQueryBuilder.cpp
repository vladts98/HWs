﻿#include "sql_query_builder.h"

int main() {
	SqlSelectQueryBuilder query_builder;
	query_builder.AddColumn("name").AddColumn("phone");
	query_builder.AddFrom("students");
	query_builder.AddWhere("id", "42").AddWhere("name", "John");

	//static_assert(query_builder.BuildQuery(),
					//"SELECT name, phone FROM students WHERE id=42 AND name=John;");
	if ("SELECT name, phone FROM students WHERE id=42 AND name=John;" == query_builder.BuildQuery()) {
		return 0;
	}
	return 1;
}