#pragma once
#include <Windows.h>
#include <tchar.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <memory>



class SqlBinding
{
public:
	SqlBinding();
	~SqlBinding();

	void allocateBinding(SQLHANDLE hStmthandle, int columnNumber);
	TCHAR* getColumnName();
	TCHAR* getDescription() const;
private:
	TCHAR* m_Description;
	SQLLEN m_MaxDescriptionLenght;
	TCHAR m_columnName[SQL_MAXIMUM_COLUMN_NAME_LENGTH];
	SQLLEN m_realLenght;
	SQLSMALLINT m_isNullable;

	SQLSMALLINT getColumnAtributeLenght(SQLHANDLE statementHandle, int columnNumber, SQLUSMALLINT fieldIdentifier);
	void getAtribute(SQLHANDLE statementHandle, int columnNumber, SQLUSMALLINT fieldIdentifier);

	
};

