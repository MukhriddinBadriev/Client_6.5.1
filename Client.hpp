#pragma once
#include <pqxx/pqxx>

class Client
{
public:

	// 1.Method that creates the structure of the database (tables)
	void CreateTable(pqxx::work& tx) {

		tx.exec("create table if not exists Clients (id_client serial primary key, "
			"name_client varchar(50) not null, "
			"last_name varchar(50) not null, "
			"email varchar(50) not null)");

		tx.exec("create table if not exists Phones (id_phone serial primary key, "
			"phone varchar(20), "
			"id_client integer references Clients(id_client))");
	}

	// 2.Method for adding a new client
	void AddClients(pqxx::work& tx, const std::string& name, const std::string& last_name, const std::string& email) {
		tx.exec_prepared("insert_clients", name, last_name, email);

	}

	// 3.Method to add a phone for an existing customer
	void AddPhones(pqxx::work& tx, const std::string& phone, int id_client) {
		tx.exec_prepared("insert_phones", phone, id_client);
	}

	// 4.A method that allows you to change customer data
	void UpdateInfoClients(pqxx::work& tx) {
		tx.exec_prepared("UpInfoClients");
	}

	// 5.Method to remove a phone for an existing customer
	void DeletePhoneClients(pqxx::work& tx) {
		tx.exec_prepared("DeletePhoneClients");
	}

	// 6.Method to remove an existing client
	void DeleteClients(pqxx::work& tx) {
		tx.exec_prepared("DeleteClients");
	}

	// 7.1.A method that allows you to find a client by his data (name, last name, email - at or phone)
	void FindClientsByName(pqxx::work& tx) {
		tx.exec_prepared("FindClientsByName");
	}

	// 7.2
	void FindClientsByLastName(pqxx::work& tx) {
		tx.exec_prepared("FindClientsByLastName");
	}

	// 7.3
	void FindClientsByEmail(pqxx::work& tx) {
		tx.exec_prepared("FindClientsByEmail");
	}

	// 7.4
	void FindClientsByPhone(pqxx::work& tx) {
		tx.exec_prepared("FindClientsByPhone");
	}
};