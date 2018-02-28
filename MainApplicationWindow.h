#pragma once
#include "Window.h"
#include "Observer.h"
#include "DatabaseController.h"
class MainApplicationWindow :
	public Window, public Observer 
{
public:

	MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName, DatabaseController* controller);
	~MainApplicationWindow();
private:
	DatabaseController* m_databaseController;
	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void update(Subject* theChangedSubject);
};

