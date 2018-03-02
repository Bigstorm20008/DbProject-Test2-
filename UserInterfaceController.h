#pragma once

#include "OdbcConnection.h"

class UserInterfaceController
{
public:
	UserInterfaceController(OdbcConnection* databaseConnection);
	~UserInterfaceController();
	std::vector<std::vector<SqlBinding*>*>* getAllClient();
	std::vector<std::vector<SqlBinding*>*>* getAllEmployees();
private:
	OdbcConnection* m_odbcConnection;
};

