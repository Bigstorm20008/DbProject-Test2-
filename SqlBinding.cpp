#include "SqlBinding.h"


SqlBinding::SqlBinding()
{
	m_Description = nullptr;
	m_MaxDescriptionLenght = 0;
	m_realLenght = 0;
	m_isNullable = NULL;
}


SqlBinding::~SqlBinding()
{
	if (m_Description)
	{
		delete[]m_Description;
		m_Description = nullptr;
	}

}

SQLSMALLINT SqlBinding::getColumnAtributeLenght(SQLHANDLE statementHandle, int columnNumber, SQLUSMALLINT fieldIdentifier)
{
	SQLSMALLINT lenght = 0;
	SQLRETURN retcode = SQLColAttribute(statementHandle,                    
		                                columnNumber,  
										fieldIdentifier, 
		                                NULL,
		                                NULL,
										&lenght,
										NULL);
	return lenght;
}

void SqlBinding::getAtribute(SQLHANDLE statementHandle, int columnNumber, SQLUSMALLINT fieldIdentifier)
{
	switch (fieldIdentifier)
	{
		case SQL_DESC_NULLABLE:
		{
			m_isNullable = 0;
			SQLColAttribute(statementHandle,
				            columnNumber,
				            fieldIdentifier,
				            NULL,
				            NULL,
				            NULL,
							&m_isNullable);
			
			break;
		}
		case SQL_DESC_LABEL:
		{
			SQLColAttribute(statementHandle,
				            columnNumber,
				            fieldIdentifier,
				            &m_columnName,
							sizeof(m_columnName),
							NULL,
				            NULL);
			break;
		}
		default:
		{
			break;
		}
	}
}

void SqlBinding::allocateBinding(SQLHANDLE hStmthandle,int columnNumber)
{
	getAtribute(hStmthandle, columnNumber, SQL_DESC_NULLABLE);
	getAtribute(hStmthandle, columnNumber, SQL_DESC_LABEL);
	
	SQLColAttribute(hStmthandle,                //statetment handle
		columnNumber,                          //number of row in dataset
		SQL_DESC_DISPLAY_SIZE,          //maximum number of characters required to display data
		NULL,                           //is not required if SQL_DESC_DISPLAY_SIZE
		NULL,                           //is not required if SQL_DESC_DISPLAY_SIZE
		NULL,                           //is not required if SQL_DESC_DISPLAY_SIZE
		&m_realLenght);       //here save lenght in characters

	size_t len = (m_realLenght+sizeof(TCHAR));          //Compute lenght in characters for save data
	m_Description = new TCHAR[len];
	memset(m_Description, 0, len*sizeof(TCHAR));
	SQLRETURN retcode = SQLBindCol(hStmthandle,                   //statetment handle
		columnNumber,                             //number of row in dataset
		SQL_C_TCHAR,                       //type from convert data
		m_Description,        //here save data from dataset
		len*sizeof(TCHAR),                 //size pThisBinding->pDescription in bytes
		&m_realLenght);     //here save actual size in characters when called SQLFetc
	retcode = 0;
}

TCHAR* SqlBinding::getColumnName()
{
	return m_columnName;
}

TCHAR* SqlBinding::getDescription() const
{
	return m_Description;
}
