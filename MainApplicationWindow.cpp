#include "MainApplicationWindow.h"


MainApplicationWindow::MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName)
	: Window(szClassName, szWindowName)
{
	createWindow(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 30, 1000, 600);
	update(NULL);
}


MainApplicationWindow::~MainApplicationWindow()
{
	
}

void MainApplicationWindow::update(Subject* theChangedSubject)
{
	
}

LRESULT MainApplicationWindow::RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		break;
	}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}