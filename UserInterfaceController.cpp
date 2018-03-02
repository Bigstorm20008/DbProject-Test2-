#include "UserInterfaceController.h"


UserInterfaceController::UserInterfaceController(OdbcConnection* databaseConnection)
{
	m_odbcConnection = databaseConnection;
}


UserInterfaceController::~UserInterfaceController()
{
}

std::vector<std::vector<SqlBinding*>*>* UserInterfaceController::getAllClient()
{
	std::wstring sqlCommand = { L"SELECT [Nickname],[Фамилия],[Имя],[Отчество] FROM [dbo].[Clients]" };
	if (m_odbcConnection->sendQueryToDatabase((TCHAR*)sqlCommand.c_str()))
	{
		return m_odbcConnection->getQueryResult();
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::vector<SqlBinding*>*>* UserInterfaceController::getAllEmployees()
{
	std::wstring sqlCommand = { L"SELECT [Lastname],[Firstname],[Patronymicname],[Posts].Должность FROM [dbo].[Employees] JOIN [Posts] on Employees.PostID = Posts.PostID" };
	if (m_odbcConnection->sendQueryToDatabase((TCHAR*)sqlCommand.c_str()))
	{
		return m_odbcConnection->getQueryResult();
	}
	else
	{
		return nullptr;
	}
}
