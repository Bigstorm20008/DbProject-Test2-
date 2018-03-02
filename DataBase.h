#pragma once
#include "DatabaseUser.h"
#include "OdbcConnection.h"
#include "Subject.h"

class DataBase 
	: public Subject
{
public:
	DataBase();
	~DataBase();
	OdbcConnection* getConnectionHandle() const;
	bool isConnected() const;
	bool connectUser(std::wstring userName, std::wstring password);
	std::wstring* getUserRole() const;
private:
	enum DatabaseState {disconnected, connected} m_databaseState;
	OdbcConnection* m_odbcConnection;
	DatabaseUser* m_connectedUser;
};

