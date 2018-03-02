#include "UserInterface.h"


UserInterface::UserInterface(HWND parentForInterface, UserInterfaceController* userInterfaceController)
{
	m_userInterfaceController = userInterfaceController;
}


UserInterface::~UserInterface()
{
}
