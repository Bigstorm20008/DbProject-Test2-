#pragma once

#include "DataBase.h"

class DatabaseController
{
public:
	DatabaseController(DataBase* database_model);
	~DatabaseController();
	bool connect(std::wstring username, std::wstring password);
	bool checkConnectionState() const;
	void attachView(Observer*);
	OdbcConnection* getDatabaseConnection() const;
private:
	DataBase* m_database_model;
};

