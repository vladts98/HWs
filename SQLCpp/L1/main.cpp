#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <pqxx/except>

class clienst_db {
public:
	/*db(pqxx::work& tx) {
		this.tx = std::move(tx); это не работает или как в этот класс записаит данные дл€ подключени€ или данные дл€ работы с Ѕƒ
	}*/
	clienst_db() = default;
	void create_struct_db(pqxx::connection& c) {
		pqxx::work tx(c);
		tx.exec(
			"CREATE TABLE IF NOT EXISTS client ( "
			"id serial PRIMARY KEY, "
			"name varchar(60) unique NOT NULL "
			"); "
		);
		tx.exec(
			"CREATE TABLE IF NOT EXISTS phone_number ( "
			"phone_number varchar(15) unique NOT NULL, "
			"client_id integer REFERENCES client(id) "
			"); "

			"CREATE TABLE IF NOT EXISTS email ( "
			"email varchar(60) unique, "
			"client_id integer REFERENCES client(id) "
			"); "
		);
		tx.commit();
	}

	void add_new_client(pqxx::connection& c, std::string name) {
		pqxx::work tx(c);
		tx.exec(
			"INSERT INTO client (name) "
			"VALUES('" + tx.esc(name) + "') "
		);
		tx.commit();
	}

	void add_phone_number(pqxx::connection& c, int id, std::string phone) {
		pqxx::work tx(c);
		tx.exec(
			"INSERT INTO phone_number (phone_number, client_id) "
			"VALUES ('" + phone + "', '" + tx.esc(std::to_string(id)) + "'); "
		);
		tx.commit();
	}

	void add_email(pqxx::connection& c, int id, std::string email) {
		pqxx::work tx(c);
		tx.exec(
			"INSERT INTO email (email, client_id) "
			"VALUES ('" + email + "', '" + tx.esc(std::to_string(id)) + "'); "
		);
		tx.commit();
	}

	void change_client_data(pqxx::connection& c, int id, std::string name, std::string email = "", std::string ph = "") {
		pqxx::work tx(c);
		tx.exec(
			"UPDATE client "
			"SET name = '" + name + "' "
			"WHERE id = " + std::to_string(id) + "; "
		);
		tx.commit();
		if (email != "") {
			this->add_email(c, id, email);
		}
		if (ph != "") {
			this->add_phone_number(c, id, ph);
		}
	}

	void delete_phone(pqxx::connection& c, int id) {
		pqxx::work tx(c);
		tx.exec(
			"DELETE FROM phone_number "
			"WHERE client_id = " + std::to_string(id) + "; "
		);
		tx.commit();
	}

	void delete_email(pqxx::connection& c, int id) {
		pqxx::work tx(c);
		tx.exec(
			"DELETE FROM email "
			"WHERE client_id = " + std::to_string(id) + "; "
		);
		tx.commit();
	}

	void delete_client(pqxx::connection& c, int id) {
		this->delete_phone(c, id);
		this->delete_email(c, id);

		pqxx::work tx(c);
		tx.exec(
			"DELETE FROM client "
			"WHERE id = " + std::to_string(id) + "; "
		);
		tx.commit();
	}

	int find_client_by_name(pqxx::connection& c, std::string string) { // если 2 одинаковых имени он вернет -1
		pqxx::work tx(c);
		int id = -1;
		try {
			id = tx.query_value<int>(
				"SELECT id "
				"FROM client "
				"WHERE name = '" + string + "'; "
				);
		}
		catch (const pqxx::unexpected_rows& e) {
			//std::cout << e.what() << "\n";
			id = -1;
		}
		tx.commit();
		return id;
	}

	int find_client_by_email(pqxx::connection& c, std::string string) {
		pqxx::work tx(c);
		int id = -1;
		try {
			id = tx.query_value<int>(
				"SELECT client_id "
				"FROM email "
				"WHERE email = '" + string + "'; "
				);
		}
		catch (const pqxx::unexpected_rows& e) {
			id = -1;
		}
		tx.commit();
		return id;
	}

	int find_client_by_phone_number(pqxx::connection& c, std::string string) {
		pqxx::work tx(c);
		int id = -1;
		try {
			id = tx.query_value<int>(
				"SELECT client_id "
				"FROM phone_number "
				"WHERE phone_number = '" + string + "' ; "
				);
		}
		catch (const pqxx::unexpected_rows& e) {
			id = -1;
		}
		tx.commit();
		return id;
	}

	int find_client(pqxx::connection& c, std::string string) {
		int id = this->find_client_by_name(c, string);
		if (id == -1) {
			id = this->find_client_by_phone_number(c, string);
			if (id == -1) {
				id = this->find_client_by_email(c, string);
			}
		}
		return id;
	}
};

int main() {
	try {
		pqxx::connection c(
			"host=localhost "
			"port=5432 "
			"dbname=test2 "
			"user=postgres "
			"password=**** ");

		clienst_db aaa;
		std::cout << aaa.find_client(c, "654654897") << "\n";
		aaa.change_client_data(c, 7, "OLEG");
	}
	catch (pqxx::sql_error e) {
		std::cout << "SQL_ERROR: " << e.what();
	}
	catch (const std::exception e) {
		std::cout << "OTHER ERROR: ";
		std::cout << e.what();
	}
	std::cout << "Code is OK.";

}