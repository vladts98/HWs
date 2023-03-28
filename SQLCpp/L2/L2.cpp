#include <iostream>
#include <Windows.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

class publisher;
class book;
class shop;
class stock;
class sale;

class publisher {
public:
	std::string name = "";

	Wt::Dbo::collection< Wt::Dbo::ptr<book> > book;

	template <class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, name, "name");

		Wt::Dbo::hasMany(a, book, Wt::Dbo::ManyToOne, "id_publisher");
	}
};

class book {
public:
	std::string title = "";
	Wt::Dbo::ptr<publisher> id_publisher;

	Wt::Dbo::collection< Wt::Dbo::ptr<stock> > stock;

	template <class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, id_publisher, "id_publisher");

		Wt::Dbo::hasMany(a, stock, Wt::Dbo::ManyToOne, "id_book");
	}
};

class shop {
public:
	std::string name = "";

	Wt::Dbo::collection< Wt::Dbo::ptr<stock> > stock;

	template <class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, name, "name");

		Wt::Dbo::hasMany(a, stock, Wt::Dbo::ManyToOne, "id_shop");
	}
};

class stock {
public:
	Wt::Dbo::ptr<book> id_book;
	Wt::Dbo::ptr<shop> id_shop;
	int count = 0;

	Wt::Dbo::collection< Wt::Dbo::ptr<sale> > sale;

	template <class Action>
	void persist(Action& a) {
		Wt::Dbo::belongsTo(a, id_book, "id_book");
		Wt::Dbo::belongsTo(a, id_shop, "id_shop");
		Wt::Dbo::field(a, count, "count");
	}
};

class sale {
public:
	int price = 0;
	std::time_t date_sale;  //что за формат для даты

	Wt::Dbo::ptr<stock> id_stock;

	int count = 0;

	template <class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, date_sale, "data_sale");

		Wt::Dbo::belongsTo(a, id_stock, "id_stock");

		Wt::Dbo::field(a, count, "count");
	}

};

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	try {
		std::string connectionString =
			"host=localhost"
			" port=5432"
			" dbname=postgres"
			" user=postgres"
			" password=1307";

		auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
		Wt::Dbo::Session session;
		session.setConnection(std::move(postgres));

		session.mapClass<publisher>("publisher");
		session.mapClass<book>("book");
		session.mapClass<shop>("shop");
		session.mapClass<stock>("stock");
		session.mapClass<sale>("sale");
		session.createTables();
	}
	catch (const Wt::Dbo::Exception& e) {
		std::cout << e.what() << "\n";
	}
}