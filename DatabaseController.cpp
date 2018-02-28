#include "DatabaseController.h"


DatabaseController::DatabaseController(DataBase* database_model)
{
	m_database_model = database_model;
}


DatabaseController::~DatabaseController()
{
}

void DatabaseController::attachView(Observer* view)
{
	m_database_model->attach(view);
}

OdbcConnection* DatabaseController::getDatabaseConnection() const
{
	return m_database_model->getConnectionHandle();
}

bool DatabaseController::connect(std::wstring username, std::wstring password)
{
	return m_database_model->connectUser(username,password);
}

bool DatabaseController::checkConnectionState() const
{
	return m_database_model->isConnected();
}
