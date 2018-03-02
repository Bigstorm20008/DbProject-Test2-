#include "UserInterfaceFactory.h"


UserInterfaceFactory::UserInterfaceFactory(HWND parentForInterface,UserInterfaceController* controller)
{
	m_parentForInterface = parentForInterface;
	m_userIntefaceController = controller;
}


UserInterfaceFactory::~UserInterfaceFactory()  
{
}

UserInterface* UserInterfaceFactory::createUserInterfaceFor(std::wstring* roleName)
{
	if (_tcscmp(roleName->c_str(), L"CashDesk") == 0)
	{
		return new CashierInterface(m_parentForInterface,m_userIntefaceController);
	}
	else
	{
		return nullptr;
	}
}

