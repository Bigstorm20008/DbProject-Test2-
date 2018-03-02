#pragma once
#include <Windows.h>
#include "UserInterface.h"
#include "UserInterfaceController.h"
#include "CashierInterface.h"
class UserInterfaceFactory
{
public:
	UserInterfaceFactory(HWND parentForInterface,UserInterfaceController* controller);
	~UserInterfaceFactory();
	UserInterface* createUserInterfaceFor(std::wstring* roleName);
private:
	HWND m_parentForInterface;
	UserInterfaceController* m_userIntefaceController;
};

