#pragma once
#include "Window.h"
#include "Observer.h"

class MainApplicationWindow :
	public Window, public Observer 
{
public:
	MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName);
	~MainApplicationWindow();
private:
	
	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void update(Subject* theChangedSubject);
};

