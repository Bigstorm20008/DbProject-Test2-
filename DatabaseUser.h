#pragma once
class DataBase;
#include <string>
class DatabaseUser
{
public:
	friend DataBase;
	DatabaseUser();
	~DatabaseUser();
private:
	std::wstring m_username;
	std::wstring m_roleInDatabase;
};

