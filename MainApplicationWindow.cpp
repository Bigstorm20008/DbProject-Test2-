#include "MainApplicationWindow.h"


MainApplicationWindow::MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName, DatabaseController* controller)
	: Window(szClassName, szWindowName)
{
	m_databaseController = controller;
	m_databaseController->attachView(this);
	createWindow(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 30, 1000, 600);
	update(NULL);
	m_databaseController->connect(L"", L"");
}


MainApplicationWindow::~MainApplicationWindow()
{
	DestroyWindow(this->getHandle());
}

void MainApplicationWindow::update(Subject* theChangedSubject)
{
	if (m_databaseController->checkConnectionState())
	{
		MessageBox(this->getHandle(), L"Database connected", L"", MB_OK);
	}
	else
	{
		MessageBox(this->getHandle(), L"Database not connected", L"", MB_OK);
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