#include "DataBase.h"


DataBase::DataBase()
{
	m_databaseState = disconnected;
	m_connectedUser = new DatabaseUser;
	m_odbcConnection = new OdbcConnection;
}


DataBase::~DataBase()
{
	if (m_odbcConnection)
	{
		m_odbcConnection->closeConnection();
		delete m_odbcConnection;
		m_odbcConnection = nullptr;
	}
	if (m_connectedUser)
	{
		delete m_connectedUser;
		m_connectedUser = nullptr;
	}
	
}

bool DataBase::isConnected() const
{
	if (m_databaseState == connected)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DataBase::connectUser(std::wstring userName, std::wstring password)
{
	if (m_odbcConnection->openConnection(L"Malinka", (TCHAR*)userName.c_str(), (TCHAR*)password.c_str()))
	{
		m_connectedUser->m_username.assign(userName);
		m_databaseState = connected;
		notify();
		return true;
	}
	else
	{
		return false;
	}
}

OdbcConnection* DataBase::getConnectionHandle() const
{
	return m_odbcConnection;
}
