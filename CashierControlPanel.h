#pragma once
#include "ControlPanel.h"
#include "ClientView.h"
#include "EmployeeView.h"
#include "Constants.h"
class CashierControlPanel 
	     : public ControlPanel
{
public:
	CashierControlPanel(HWND parent, UserInterfaceController* controller);
	~CashierControlPanel();
private:
	View* m_view;
	ClientView* m_clientView;
	EmployeeView* m_employeesView;

	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

