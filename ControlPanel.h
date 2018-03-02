#pragma once


#include <ctime>

#include "Constants.h"
#include "Window.h"
#include "View.h"
#include "UserInterfaceController.h"
class ControlPanel 
	 : public Window
{
public:
	ControlPanel(HWND parent, UserInterfaceController* controller);
	~ControlPanel();
protected:
	UserInterfaceController* m_userInterfaceController;
	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void setCurrentTime();
	HWND m_timeWnd;
	HWND m_parentOfControlPanel;
};

