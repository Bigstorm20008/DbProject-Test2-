#pragma once
#include <Windows.h>
#include <tchar.h>

#include "View.h"
#include "UserInterfaceController.h"
class UserInterface
{
public:
	UserInterface(HWND parentForInterface, UserInterfaceController* userInterfaceController);
	virtual~UserInterface();
	virtual void activate() = 0;
	virtual void destroy() = 0;	
	virtual void disable() = 0;
protected:
	UserInterfaceController* m_userInterfaceController;
};

