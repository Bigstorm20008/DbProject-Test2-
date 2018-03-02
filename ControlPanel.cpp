#include "ControlPanel.h"


ControlPanel::ControlPanel(HWND parent, UserInterfaceController* controller) : Window(L"ControlPanelWindow", L"")
{
	m_userInterfaceController = controller;
	m_parentOfControlPanel = parent;
	RECT parentRC;
	GetClientRect(parent, &parentRC);
	int xPos = parentRC.left;
	int yPos = parentRC.top;
	int controlPanelWidth = parentRC.right - parentRC.left;

	this->createWindow(parent, WS_CHILD | WS_VISIBLE, xPos, yPos, controlPanelWidth, controlPanelHeight);

	RECT controlPanelRC;
	GetClientRect(getHandle(), &controlPanelRC);
	int timeWndWidth = 100;
	int timeWndHeight = 20;
	xPos = controlPanelRC.right - timeWndWidth - offsetsBetweenWindow;
	yPos = controlPanelRC.bottom - offsetsBetweenWindow - timeWndHeight;
	
	m_timeWnd = CreateWindow(L"STATIC",
		                     L"",
		                     WS_CHILD | WS_VISIBLE|SS_RIGHT,
		                     xPos, yPos,
		                     timeWndWidth, timeWndHeight,
		                     this->getHandle(),
		                     NULL,
		                     reinterpret_cast<HINSTANCE>(GetWindowLongPtr(NULL, GWLP_HINSTANCE)),
		                     NULL);
	
	SetTimer(this->getHandle(), IDT_ONE_SEC, 1000, (TIMERPROC)NULL);
	setCurrentTime();
}


ControlPanel::~ControlPanel()
{
	DestroyWindow(this->getHandle());
}
void ControlPanel::setCurrentTime()
{
	TCHAR buffer[20] = {};
	time_t seconds = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	TCHAR* format = TEXT("%H:%M:%S");
	_tcsftime(buffer, 20, format, &timeinfo);
	SetWindowText(m_timeWnd, buffer);
}

LRESULT ControlPanel::RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
		case WM_TIMER:
		{
			switch (wParam)
			{
				case IDT_ONE_SEC:
				{					
					setCurrentTime();
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case WM_CTLCOLORSTATIC:
		{
			if ((HWND)lParam == m_timeWnd)
			{
				HDC hdcStatic = (HDC)wParam;
				SetBkMode(hdcStatic, TRANSPARENT);
				return (INT_PTR)CreateSolidBrush(RGB(230, 241, 255));
			}
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(230,241,255)));		
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			KillTimer(hWnd, IDT_ONE_SEC);
			DestroyWindow(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
