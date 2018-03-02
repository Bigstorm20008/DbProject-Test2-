#pragma once

#include "Window.h"
#include "Observer.h"
#include "DatabaseController.h"
#include "AuthenticationForm.h"
#include "UserInterface.h"
#include "UserInterfaceFactory.h"
#include "UserInterfaceController.h"

class MainApplicationWindow :
	public Window, public Observer 
{
public:

	MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName, DatabaseController* controller);
	~MainApplicationWindow();
private:
	DatabaseController* m_databaseController;
	AuthenticationForm* m_AuthenticationForm;
	UserInterface* m_userInterface;
	UserInterfaceController* m_userInterfaceController;

	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void update(Subject* theChangedSubject);
};

