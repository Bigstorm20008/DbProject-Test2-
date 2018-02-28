#pragma once

#include<iostream>
#include <list>
#include <vector>
#include "SqlBinding.h"

class OdbcConnection
{
public:
	OdbcConnection();
	~OdbcConnection();

	BOOL openConnection(TCHAR* dataSourcheName, TCHAR* login, TCHAR* password);
	void closeConnection(void);
	BOOL sendQueryToDatabase(SQLWCHAR* sqlCommand);
	BOOL executePrepearedQuery(SQLTCHAR* sqlCommand, SQLTCHAR** parametrArray);
	std::vector<std::vector<SqlBinding*>*>* getQueryResult() const;
private:
	SQLHENV m_EnviromentHandle;     
	SQLHDBC m_DbConnectionHandle;   
	SQLHSTMT m_StatementHandle;     
	SQLHDESC m_DescriptorHandle;    

	std::vector<std::vector<SqlBinding*>*>* m_queryResult;
	inline void freeResources();
	inline void freeQueryResult();
	inline void initHandles(void);
	inline void showError(TCHAR* infoAboutError, SQLHANDLE handle, SQLSMALLINT type);
	inline BOOL getDataFromDataSource();
	inline std::vector<SqlBinding*>* allocateBindings(SQLSMALLINT numCols);
};

