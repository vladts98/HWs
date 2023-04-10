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

		Wt::Dbo::hasMany(a, sale, Wt::Dbo::ManyToOne, "id_stock");
	}
};

class sale {
public:
	int price = 0;
	int date_sale = 0;  //что за формат для даты

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
			" dbname=test"
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
		//session.createTables();

		Wt::Dbo::Transaction transaction(session);

		//std::unique_ptr<publisher> publisher_{ new publisher };
		//std::unique_ptr<publisher> publisher_1{ new publisher };
		//std::unique_ptr<publisher> publisher_2{ new publisher };
		//publisher_->name = "ppp";
		//publisher_1->name = "Grisha";
		//publisher_2->name = "Lev";
		//Wt::Dbo::ptr<publisher> p_ = session.add(std::move(publisher_));
		//Wt::Dbo::ptr<publisher> p_1 = session.add(std::move(publisher_1));
		//Wt::Dbo::ptr<publisher> p_2 = session.add(std::move(publisher_2));

		//std::unique_ptr<shop> shop_{ new shop };
		//std::unique_ptr<shop> shop_1{ new shop };
		//std::unique_ptr<shop> shop_2{ new shop };
		//shop_->name = "knigi";
		//shop_1->name = "bookShop";
		//shop_2->name = "0";
		//Wt::Dbo::ptr<shop> s_ = session.add(std::move(shop_));
		//Wt::Dbo::ptr<shop> s_1 = session.add(std::move(shop_1));
		//Wt::Dbo::ptr<shop> s_2 = session.add(std::move(shop_2));

		//std::unique_ptr<book> book_{ new book };
		//std::unique_ptr<book> book_1{ new book };
		//std::unique_ptr<book> book_2{ new book };
		//std::unique_ptr<book> book_3{ new book };
		//std::unique_ptr<book> book_4{ new book };
		//book_->title = "King";
		//book_1->title = "sldkf";
		//book_2->title = "qwerty";
		//book_3->title = "poiuy";
		//book_4->title = "zxcvb";
		//Wt::Dbo::ptr<book> b_ = session.add(std::move(book_));
		//Wt::Dbo::ptr<book> b_1 = session.add(std::move(book_1));
		//Wt::Dbo::ptr<book> b_2 = session.add(std::move(book_2));
		//Wt::Dbo::ptr<book> b_3 = session.add(std::move(book_3));
		//Wt::Dbo::ptr<book> b_4 = session.add(std::move(book_4));

		//p_.modify()->book.insert(b_);
		//p_.modify()->book.insert(b_1);
		//p_.modify()->book.insert(b_2);
		//p_1.modify()->book.insert(b_3);
		//p_2.modify()->book.insert(b_4);

		//std::unique_ptr<stock> stock_{ new stock };
		//std::unique_ptr<stock> stock_1{ new stock };
		//std::unique_ptr<stock> stock_2{ new stock };
		//std::unique_ptr<stock> stock_3{ new stock };
		//std::unique_ptr<stock> stock_4{ new stock };
		//std::unique_ptr<stock> stock_5{ new stock };
		//std::unique_ptr<stock> stock_6{ new stock };
		//std::unique_ptr<stock> stock_7{ new stock };
		//stock_->count = 2;
		//stock_1->count = 1;
		//stock_2->count = 4;
		//stock_3->count = 1;
		//stock_4->count = 2;
		//stock_5->count = 3;
		//stock_6->count = 1;
		//stock_7->count = 10;
		//Wt::Dbo::ptr<stock> st_ = session.add(std::move(stock_));
		//Wt::Dbo::ptr<stock> st_1 = session.add(std::move(stock_1));
		//Wt::Dbo::ptr<stock> st_2 = session.add(std::move(stock_2));
		//Wt::Dbo::ptr<stock> st_3 = session.add(std::move(stock_3));
		//Wt::Dbo::ptr<stock> st_4 = session.add(std::move(stock_4));
		//Wt::Dbo::ptr<stock> st_5 = session.add(std::move(stock_5));
		//Wt::Dbo::ptr<stock> st_6 = session.add(std::move(stock_6));
		//Wt::Dbo::ptr<stock> st_7 = session.add(std::move(stock_7));

		//b_4.modify()->stock.insert(st_);
		//b_3.modify()->stock.insert(st_1);
		//b_2.modify()->stock.insert(st_2);
		//b_1.modify()->stock.insert(st_3);
		//b_.modify()->stock.insert(st_4);
		//b_4.modify()->stock.insert(st_5);
		//b_4.modify()->stock.insert(st_6);
		//b_1.modify()->stock.insert(st_7);

		//s_1.modify()->stock.insert(st_);
		//s_2.modify()->stock.insert(st_1);
		//s_.modify()->stock.insert(st_2);
		//s_2.modify()->stock.insert(st_3);
		//s_2.modify()->stock.insert(st_4);
		//s_2.modify()->stock.insert(st_5);
		//s_3.modify()->stock.insert(st_6);
		//s_1.modify()->stock.insert(st_7);

		//std::unique_ptr<sale> sale_{ new sale };
		//std::unique_ptr<sale> sale_1{ new sale };
		//std::unique_ptr<sale> sale_2{ new sale };
		//std::unique_ptr<sale> sale_3{ new sale };
		//std::unique_ptr<sale> sale_4{ new sale };
		//sale_->count = 1;
		//sale_1->count = 2;
		//sale_2->count = 1;
		//sale_3->count = 4;
		//sale_4->count = 2;
		//sale_->price = 550;
		//sale_1->price = 950;
		//sale_2->price = 200;
		//sale_3->price = 350;
		//sale_4->price = 450;
		//sale_->date_sale = 5;				// как вставить дату
		//sale_1->date_sale = 55;
		//sale_2->date_sale = 10;
		//sale_3->date_sale = 4;
		//sale_4->date_sale = 1;

		//Wt::Dbo::ptr<sale> sa_ = session.add(std::move(sale_));
		//Wt::Dbo::ptr<sale> sa_1 = session.add(std::move(sale_1));
		//Wt::Dbo::ptr<sale> sa_2 = session.add(std::move(sale_2));
		//Wt::Dbo::ptr<sale> sa_3 = session.add(std::move(sale_3));
		//Wt::Dbo::ptr<sale> sa_4 = session.add(std::move(sale_4));

		//st_.modify()->sale.insert(sa_);
		//st_3.modify()->sale.insert(sa_1);
		//st_6.modify()->sale.insert(sa_2);
		//st_4.modify()->sale.insert(sa_3);
		//st_3.modify()->sale.insert(sa_4);

		std::string name = "";
		std::cin >> name;
		Wt::Dbo::ptr<publisher> p = session.find<publisher>().where("name = ?").bind(name);
		if (!p) {
			p = session.find<publisher>().where("id = ?").bind(name);
		}


		typedef Wt::Dbo::collection<Wt::Dbo::ptr<book>> Books;
		Books books = session.find<book>();

		std::set<Wt::Dbo::dbo_default_traits::IdType> shops_p;
		for (auto bo : books) {
			if ((bo->id_publisher.id() == p.id())) {
				typedef Wt::Dbo::collection<Wt::Dbo::ptr<stock>> Stocks;
				Stocks stocks = session.find<stock>();
				for(auto st:stocks) {
					if (bo.id() == st->id_book.id()) {
						shops_p.insert(st->id_shop.id());
					}
				}
			}
		}
		for (auto sh : shops_p) {
			Wt::Dbo::ptr<shop> s = session.find<shop>().where("id = ?").bind(sh);
			std::cout << s.id() << " " << s->name << "\n";
		}

		transaction.commit();
	}
	catch (const Wt::Dbo::Exception& e) {
		std::cout << e.what() << "\n";
	}
}