#include <iostream>
#include <string>
#include <Windows.h>
#include <pqxx/pqxx>
#include <Client.hpp>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	try {
		pqxx::connection c(
			"host=localhost "
			"port=5432 "
			"dbname= "
			"user= "
			"password=");

		pqxx::work tx{ c };

		std::string new_name, new_last_name, new_email;

		Client C;

		C.CreateTable(tx);

		c.prepare("insert_clients", "INSERT INTO Clients(name_client,last_name,email) VALUES($1, $2, $3)");
		C.AddClients(tx, "Mukhriddin", "Badriev", "BadrievM@gmail.com");

		c.prepare("insert_phones", "INSERT INTO Phones(phone,id_client) values($1, $2)");
		C.AddPhones(tx, "+79961355770", 1);

		/*std::cout << "Enter a new email: ";
		std::cin >> new_email;
		std::cout << "Enter client name: ";
		std::cin >> new_name;*/
		c.prepare("UpInfoClients", "UPDATE Clients SET email=" "'" +new_email + "' WHERE name_client = '" + new_name + "'" );
		//C.UpdateInfoClients(tx);
		
		c.prepare("DeletePhoneClients", "DELETE FROM Phones WHERE id_client='1'");
		//C.DeletePhoneClients(tx);

		c.prepare("DeleteClients", "DELETE FROM Clients WHERE id_client='1'");
		//C.DeleteClients(tx);

		std::string FindViaName, FindViaLName, FindViaEmail, FindViaPhone;

		/*std::cout << "Enter client name: ";
		std::cin >> FindViaName;*/
		c.prepare("FindClients", "SELECT * FROM Clients WHERE name_client LIKE '%" + FindViaName + "%'");
		//C.FindClients(tx);

		/*std::cout << "Enter client last name: ";
		std::cin >> FindViaLName;
		c.prepare("FindClients", "SELECT * FROM Clients WHERE name_client LIKE '%" + FindViaLName + "%'");
		C.FindClients(tx);*/

		/*std::cout << "Enter client email: ";
		std::cin >> FindViaEmail;
		c.prepare("FindClients", "SELECT * FROM Clients WHERE name_client LIKE '%" + FindViaEmail + "%'");
		C.FindClients(tx);*/

		/*std::cout << "Enter client phone: ";
		std::cin >> FindViaPhone;
		c.prepare("FindClients", "SELECT * FROM Clients c "
					"INNER JOIN Phones p ON c.id_client = p.id_client "
					"WHERE name_client LIKE '%" + FindViaPhone + "%'");

		C.FindClients(tx);*/

		tx.commit();

	}catch (pqxx::sql_error e)
	{
		std::cout << "SQL error: " << e.what() << std::endl;
	}
	catch (std::exception ex) {
		std::cout << "GENERAL error: " << ex.what() << std::endl;
	}
	return 0;
}