#pragma once
#include <pqxx/pqxx>

class Client
{
public:

	// 1.ћетод, создающий структуру Ѕƒ (таблицы)
	void CreateTable(pqxx::work& tx) {

		tx.exec("create table if not exists Clients (id_client serial primary key, "
			"name_client varchar(50) not null, "
			"last_name varchar(50) not null, "
			"email varchar(50) not null)");

		tx.exec("create table if not exists Phones (id_phone serial primary key, "
			"phone varchar(20), "
			"id_client integer references Clients(id_client))");
	}

	// 2.ћетод, позвол€ющий добавить нового клиента
	void AddClients(pqxx::work& tx, const std::string& name, const std::string& last_name, const std::string& email) {
		tx.exec_prepared("insert_clients", name, last_name, email);

	}

	// 3.ћетод, позвол€ющий добавить телефон дл€ существующего клиента
	void AddPhones(pqxx::work& tx, const std::string& phone, int id_client) {
		tx.exec_prepared("insert_phones", phone, id_client);
	}

	// 4.ћетод, позвол€ющий изменить данные о клиенте
	void UpdateInfoClients(pqxx::work& tx) {
		tx.exec_prepared("UpInfoClients");
	}

	// 5.ћетод, позвол€ющий удалить телефон дл€ существующего клиента
	void DeletePhoneClients(pqxx::work& tx) {
		tx.exec_prepared("DeletePhoneClients");
	}

	// 6.ћетод, позвол€ющий удалить существующего клиента
	void DeleteClients(pqxx::work& tx) {
		tx.exec_prepared("DeleteClients");
	}

	// 7.ћетод, позвол€ющий найти клиента по его данным(имени, фамилии, email - у или телефону)
	void FindClients(pqxx::work& tx) {
		tx.exec_prepared("FindClients");
	}
};