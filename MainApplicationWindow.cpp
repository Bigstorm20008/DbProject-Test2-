#include "MainApplicationWindow.h"


MainApplicationWindow::MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName, DatabaseController* controller)
	: Window(szClassName, szWindowName)
{
	m_databaseController = controller;
	m_databaseController->attachView(this);
	createWindow(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 30, 1000, 600);
	update(NULL);
}


MainApplicationWindow::~MainApplicationWindow()
{
	if (m_AuthenticationForm)
	{
		delete m_AuthenticationForm;
		m_AuthenticationForm = nullptr;
	}
	if (m_userInterface)
	{
		delete m_userInterface;
		m_userInterface = nullptr;
	}
	if (m_userInterfaceController)
	{
		delete m_userInterfaceController;
		m_userInterfaceController = nullptr;
	}
	DestroyWindow(this->getHandle());
}

void MainApplicationWindow::update(Subject* theChangedSubject)
{
	if (m_databaseController->checkConnectionState())
	{
		if (m_AuthenticationForm)
		{
			delete m_AuthenticationForm;
			m_AuthenticationForm = nullptr;
		}
		m_userInterfaceController = new UserInterfaceController(m_databaseController->getDatabaseConnection());
		UserInterfaceFactory factory(this->getHandle(), m_userInterfaceController);
		m_userInterface = factory.createUserInterfaceFor(m_databaseController->getUserRole());
	}
	else
	{
		if (m_userInterface)
		{
			delete m_userInterface;
			m_userInterface = nullptr;
		}
		if (m_userInterfaceController)
		{
			delete m_userInterfaceController;
			m_userInterfaceController = nullptr;
		}
		m_AuthenticationForm = new AuthenticationForm(this->getHandle(), L"AuthenticationWindow", L"Аутентификация", m_databaseController);
	}
}

LRESULT MainApplicationWindow::RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}