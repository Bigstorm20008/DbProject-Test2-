#pragma once
#include "UserInterface.h"
#include "CashierControlPanel.h"
#include "ClientView.h"
#include "EmployeeView.h"

class CashierInterface :
	public UserInterface
{
public:
	CashierInterface(HWND parentForInterface, UserInterfaceController* userInterfaceController);
	~CashierInterface();
	virtual void activate();
	virtual void destroy();
	virtual void disable();
private:
	CashierControlPanel* m_controlPanel;
};

