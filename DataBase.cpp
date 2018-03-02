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
		std::wstring sqlCommand = { L"EXEC sp_helpuser ?" };
		TCHAR* parameterArray[] = { (TCHAR*)m_connectedUser->m_username.c_str() };
		if (m_odbcConnection->executePrepearedQuery((TCHAR*)sqlCommand.c_str(), parameterArray))
		{
			std::vector<std::vector<SqlBinding*>*>* res = m_odbcConnection->getQueryResult();
			for (auto& elem : *res)
			{
				for (auto& rowElem : *elem)
				{
					if (_tcscmp(rowElem->getColumnName(), L"RoleName") == 0)
					{
						m_connectedUser->m_roleInDatabase.assign(rowElem->getDescription());
						break;
					}
				}
				break;
			}
		}
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

std::wstring* DataBase::getUserRole() const
{
	return &m_connectedUser->m_roleInDatabase;
}
