#pragma once
#include <pqxx/pqxx>

class Client
{
public:

	// 1.�����, ��������� ��������� �� (�������)
	void CreateTable(pqxx::work& tx) {

		tx.exec("create table if not exists Clients (id_client serial primary key, "
			"name_client varchar(50) not null, "
			"last_name varchar(50) not null, "
			"email varchar(50) not null)");

		tx.exec("create table if not exists Phones (id_phone serial primary key, "
			"phone varchar(20), "
			"id_client integer references Clients(id_client))");
	}

	// 2.�����, ����������� �������� ������ �������
	void AddClients(pqxx::work& tx, const std::string& name, const std::string& last_name, const std::string& email) {
		tx.exec_prepared("insert_clients", name, last_name, email);

	}

	// 3.�����, ����������� �������� ������� ��� ������������� �������
	void AddPhones(pqxx::work& tx, const std::string& phone, int id_client) {
		tx.exec_prepared("insert_phones", phone, id_client);
	}

	// 4.�����, ����������� �������� ������ � �������
	void UpdateInfoClients(pqxx::work& tx) {
		tx.exec_prepared("UpInfoClients");
	}

	// 5.�����, ����������� ������� ������� ��� ������������� �������
	void DeletePhoneClients(pqxx::work& tx) {
		tx.exec_prepared("DeletePhoneClients");
	}

	// 6.�����, ����������� ������� ������������� �������
	void DeleteClients(pqxx::work& tx) {
		tx.exec_prepared("DeleteClients");
	}

	// 7.�����, ����������� ����� ������� �� ��� ������(�����, �������, email - � ��� ��������)
	void FindClients(pqxx::work& tx) {
		tx.exec_prepared("FindClients");
	}
};