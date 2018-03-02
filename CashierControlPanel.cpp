#include "CashierControlPanel.h"


CashierControlPanel::CashierControlPanel(HWND parent, UserInterfaceController* controller) : ControlPanel(parent, controller)
{
	m_view = nullptr;
	m_clientView = nullptr;
	m_employeesView = nullptr;
	CreateWindow(L"BUTTON",
			     L"Клиенты",
		         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		         10, 10,
		         100, 40,
		         this->getHandle(),
		         (HMENU)ID_CLIENTS_BUTTON,
		         reinterpret_cast<HINSTANCE>(GetWindowLongPtr(NULL, GWLP_HINSTANCE)),
		         NULL);
	CreateWindow(L"BUTTON",
		         L"Касса",
		         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		         120, 10,
		         100, 40,
		         this->getHandle(),
		         (HMENU)ID_CASH_BUTTON,
		         reinterpret_cast<HINSTANCE>(GetWindowLongPtr(NULL, GWLP_HINSTANCE)),
		         NULL);
	CreateWindow(L"BUTTON",
		         L"Работники",
		         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		         230, 10,
		         100, 40,
		         this->getHandle(),
		         (HMENU)ID_EMPLOYEES_BUTTON,
		         reinterpret_cast<HINSTANCE>(GetWindowLongPtr(NULL, GWLP_HINSTANCE)),
		         NULL);
}


CashierControlPanel::~CashierControlPanel()
{
	if (m_clientView)
	{
		delete m_clientView;
		m_clientView = nullptr;
	}
	if (m_employeesView)
	{
		delete m_employeesView;
		m_employeesView = nullptr;
	}
	m_view = nullptr;
}

LRESULT CashierControlPanel::RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case ID_CLIENTS_BUTTON:
			{
				
				if (!m_clientView)
				{
					m_clientView = new ClientView(m_parentOfControlPanel);
				}
				if (m_view)
				{
					m_view->hide();
				}
				
				m_view = m_clientView;
				m_view->activate(m_userInterfaceController);
				m_view->show();
				break;
			}
			case ID_EMPLOYEES_BUTTON:
			{
				if (!m_employeesView)
				{
					m_employeesView = new EmployeeView(m_parentOfControlPanel);
				}
				if (m_view)
				{
					m_view->hide();
				}
				m_view = m_employeesView;
				m_view->activate(m_userInterfaceController);
				m_view->show();
				break;
			}
			default:
			{
				break;
			}
			break;
		}
		break;
	}
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
			FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(230, 241, 255)));
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
