#pragma once
#include "Window.h"

#include "EditControlTemplate.h"
#include "DatabaseController.h"

class AuthenticationForm
	:public Window
{
public:
	AuthenticationForm(HWND parent, TCHAR* szClassName, TCHAR* szWindowName, DatabaseController* controller);
	~AuthenticationForm();
private:
	DatabaseController* m_databaseController;
	void createControls();
	BOOL verifyData() const;
	EditControlTemplate* m_UserName;
	EditControlTemplate* m_Password;
	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

