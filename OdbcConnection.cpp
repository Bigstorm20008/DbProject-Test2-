#include "OdbcConnection.h"


OdbcConnection::OdbcConnection()
{
	m_queryResult = new std::vector<std::vector<SqlBinding*>*>;
}


OdbcConnection::~OdbcConnection()
{
	if (m_queryResult)
	{
		freeQueryResult();
		delete m_queryResult;
		m_queryResult = nullptr;
	}
}

void OdbcConnection::initHandles(void)
{
	//Allocate an enviroment handle
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_EnviromentHandle);
	//ODBC 3 support
	SQLSetEnvAttr(m_EnviromentHandle, SQL_ATTR_ODBC_VERSION, (void*)(SQL_OV_ODBC3), SQL_IS_INTEGER);
	//Allocate a connection handle
	SQLAllocHandle(SQL_HANDLE_DBC, m_EnviromentHandle, &m_DbConnectionHandle);

}

BOOL OdbcConnection::openConnection(TCHAR* dataSourcheName, TCHAR* login, TCHAR* password)
{
	initHandles();
	//При попытке подключения к базе данных изменим вид курсора
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCursor);

	//Подключимся к базе данных
	SQLRETURN retCode;
	retCode = SQLConnect(m_DbConnectionHandle, dataSourcheName, SQL_NTS, login, SQL_NTS, password, SQL_NTS);
	switch (retCode)
	{
	case SQL_SUCCESS:	
	{
		return TRUE;
		break;
	}
	case SQL_SUCCESS_WITH_INFO:
	{
		showError(L"Информация о подключении", m_DbConnectionHandle, SQL_HANDLE_DBC);
		return TRUE;
		break;
	}
	case SQL_ERROR:
	{
		showError(L"Ошибка при подключении к базе данных", m_DbConnectionHandle, SQL_HANDLE_DBC);
		closeConnection();
		return FALSE;
		break;
	}
	default:
		break;
	}
	return 0;
}

void OdbcConnection::closeConnection(void)
{
	if (m_StatementHandle)
		freeResources();
	SQLDisconnect(m_DbConnectionHandle);
	if (m_DbConnectionHandle)
		SQLFreeHandle(SQL_HANDLE_DBC, m_DbConnectionHandle);
	if (m_EnviromentHandle)
		SQLFreeHandle(SQL_HANDLE_ENV, m_EnviromentHandle);

	m_StatementHandle = nullptr;
	m_DbConnectionHandle = nullptr;
	m_EnviromentHandle = nullptr;
}
void OdbcConnection::showError(TCHAR* infoAboutError, SQLHANDLE handle, SQLSMALLINT type)
{
	setlocale(LC_ALL, "");
	SQLSMALLINT  i = 0;
	SQLINTEGER   native;
	TCHAR     state[6];
	TCHAR     text[SQL_MAX_MESSAGE_LENGTH];
	SQLSMALLINT  len;
	SQLRETURN    ret;
	std::wcout << infoAboutError << std::endl;
	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
			sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
		{
			std::wcout << state << "||" << i << "||" << native << "||" << text;
			std::cout << std::endl;
		}
	} while (ret == SQL_SUCCESS);
}

BOOL OdbcConnection::sendQueryToDatabase(SQLWCHAR* sqlCommand)
{
	freeResources();
	SQLRETURN retCode;
	retCode = SQLAllocHandle(SQL_HANDLE_STMT, m_DbConnectionHandle, &m_StatementHandle);
	if (retCode == SQL_ERROR)
	{
		showError(TEXT("SQLAllocHandle error(statement handle)"), m_DbConnectionHandle, SQL_HANDLE_DBC);
		return FALSE;
	}
	size_t len = _tcslen(sqlCommand) + 1;
	retCode = SQLExecDirect(m_StatementHandle, sqlCommand, len);
	if (retCode == SQL_ERROR)
	{
		showError(TEXT("SQLExecDirect error"), m_StatementHandle, SQL_HANDLE_STMT);
		return FALSE;
	}
	if (getDataFromDataSource())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL OdbcConnection::executePrepearedQuery(SQLTCHAR* sqlCommand, SQLTCHAR** parametrArray)
{
	freeResources();
	SQLAllocHandle(SQL_HANDLE_STMT, m_DbConnectionHandle, &m_StatementHandle);
	SQLRETURN retcode = SQLPrepare(m_StatementHandle, sqlCommand, SQL_NTS);
	if (retcode == SQL_ERROR)
	{
		showError(L"Ошибка подготовки запроса", m_StatementHandle, SQL_HANDLE_STMT);
		return FALSE;
	}
	SQLSMALLINT   DataType, DecimalDigits, Nullable;
	SQLUINTEGER   ParamSize;
	SQLLEN iNts = SQL_NTS;
	SQLLEN null = SQL_NULL_DATA;
	SQLSMALLINT numParams;
	SQLNumParams(m_StatementHandle, &numParams);

	if (numParams)
	{
		for (int i = 0; i < numParams; i++)
		{
			if (parametrArray[i])
			{
				SQLDescribeParam(m_StatementHandle, i + 1, &DataType, &ParamSize, &DecimalDigits, &Nullable);
				SQLBindParameter(m_StatementHandle, i + 1, SQL_PARAM_INPUT, SQL_C_TCHAR, DataType, ParamSize,
					DecimalDigits, parametrArray[i], (ParamSize)*sizeof(SQLTCHAR),
					&iNts);
			}
			else
			{
				SQLDescribeParam(m_StatementHandle, i + 1, &DataType, &ParamSize, &DecimalDigits, &Nullable);
				SQLBindParameter(m_StatementHandle, i + 1, SQL_PARAM_INPUT, SQL_C_TCHAR, DataType, ParamSize,
					DecimalDigits, parametrArray[i], (ParamSize)*sizeof(SQLTCHAR),
					&null);
			}
		}

	}
	retcode = SQLExecute(m_StatementHandle);
	if (retcode == SQL_ERROR)
	{
		showError(TEXT("Ошибка выполнения запроса"), m_StatementHandle, SQL_HANDLE_STMT);
		return FALSE;
	}
	if (getDataFromDataSource())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL OdbcConnection::getDataFromDataSource()
{
	SQLRETURN retcode;       
	SQLSMALLINT numCols = 0;   
	retcode = SQLNumResultCols(m_StatementHandle, &numCols);
	if (retcode == SQL_ERROR)
	{
		showError(TEXT("SQLNumResultCols error"), m_StatementHandle, SQL_HANDLE_STMT);
		return FALSE;
	}
	if (numCols)
	{
		/*std::vector<SqlBinding*>* thisRow = allocateBindings(numCols);
		while (SQL_SUCCEEDED(retcode = SQLFetch(m_StatementHandle)))
		{
			
			m_queryResult->push_back(thisRow);
			thisRow = allocateBindings(numCols);
		}*/
		retcode = SQL_SUCCESS;
		do
		{
			std::vector<SqlBinding*>* thisRow = allocateBindings(numCols);
			retcode = SQLFetch(m_StatementHandle);
			m_queryResult->push_back(thisRow);
		} while (retcode == SQL_SUCCESS);
		return TRUE;
	}
	else
	{
		SQLLEN rowCount = 0;
		SQLRowCount(m_StatementHandle, &rowCount);

		if (rowCount > 0)
		{
			std::wcout << rowCount << " affected!" << std::endl;
			return TRUE;
		}
	}
	return FALSE;
}


std::vector<SqlBinding*>* OdbcConnection::allocateBindings(SQLSMALLINT numCols)
{
	std::vector<SqlBinding*>* thisRow = new std::vector<SqlBinding*>;
	thisRow->reserve(numCols - 1);
	for (int i = 1; i <= numCols; ++i)
	{
		SqlBinding* thisBinding = new SqlBinding;
		thisBinding->allocateBinding(m_StatementHandle, i);
		thisRow->push_back(thisBinding);
	}
	return thisRow;
}

std::vector<std::vector<SqlBinding*>*>* OdbcConnection::getQueryResult() const
{
	return m_queryResult;
}

void OdbcConnection::freeQueryResult()
{
	for (auto& elem : *m_queryResult)
	{
		for (auto& vectorElem : *elem)
		{
			delete vectorElem;
			vectorElem = nullptr;
		}
		delete elem;
		elem = nullptr;
	}
	m_queryResult->clear();
}

void OdbcConnection::freeResources()
{
	freeQueryResult();
	SQLFreeStmt(m_StatementHandle, SQL_CLOSE);
	SQLFreeStmt(m_StatementHandle, SQL_UNBIND);
	SQLFreeStmt(m_StatementHandle, SQL_RESET_PARAMS);

	SQLFreeHandle(SQL_HANDLE_STMT, m_StatementHandle);
	m_StatementHandle = SQL_NULL_HSTMT;
}
