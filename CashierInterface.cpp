#include "CashierInterface.h"


CashierInterface::CashierInterface(HWND parentForInterface, UserInterfaceController* userInterfaceController) : UserInterface(parentForInterface, userInterfaceController)
{
	m_controlPanel = new CashierControlPanel(parentForInterface,m_userInterfaceController);
}


CashierInterface::~CashierInterface()
{
	if (m_controlPanel)
	{
		delete m_controlPanel;
		m_controlPanel = nullptr;
	}
}

void CashierInterface::activate()
{

}
 void CashierInterface::destroy()
{

}
 void CashierInterface::disable()
{

}
