#include "AuthenticationForm.h"


AuthenticationForm::AuthenticationForm(HWND parent, TCHAR* szClassName, TCHAR* szWindowName, DatabaseController* controller)
	: Window(szClassName, szWindowName)
{
	m_databaseController = controller;
	RECT parentRC;
	GetClientRect(parent, &parentRC);
	int width = 300;
	int height = 200;
	int xPos = (parentRC.right - parentRC.left) / 2 - width / 2;
	int yPos = (parentRC.bottom - parentRC.top) / 2 - height / 2;
	createWindow(parent, WS_CHILD | WS_VISIBLE |WS_BORDER|WS_TABSTOP,xPos,yPos,width,height);

	createControls();
}


AuthenticationForm::~AuthenticationForm()
{
	if (m_UserName)
	{
		delete m_UserName;
		m_UserName = nullptr;
	}
	if (m_Password)
	{
		delete m_Password;
		m_Password = nullptr;
	}
	DestroyWindow(this->getHandle());
}
void AuthenticationForm::createControls()
{
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		                     DEFAULT_CHARSET,
		                     0, 0, 0, VARIABLE_PITCH,
		                     L"Time New Romans");

	RECT parentRC;
	GetClientRect(this->getHandle(), &parentRC);
	int btnWidth = 90;
	int btnHeight = 25;
	int xPos = parentRC.right - btnWidth - 5;
	int yPos = parentRC.bottom - btnHeight - 5;

	HWND btn = CreateWindow(TEXT("BUTTON"),
		                    TEXT("Продолжить"),
		                    WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                    xPos, yPos,
		                    btnWidth, btnHeight,
		                    this->getHandle(),
		                    (HMENU)ID_CONTINUE_AUTENTIFICATION_BTN,
		                    (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                    NULL);
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	xPos -= btnWidth + 5;
	btn = CreateWindow(TEXT("BUTTON"),
		               TEXT("Отмена"),
		               WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		               xPos, yPos,
		               btnWidth, btnHeight,
		               this->getHandle(),
		               (HMENU)ID_CANCEL_AUXILIARY_BTN,
		               (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		               NULL);
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	xPos = parentRC.left;
	yPos = parentRC.top + windowCaptionHeight + offsetsBetweenWindow;
	int staticTextWidth = parentRC.right - parentRC.left;
	int staticTextHeight = 40;
	HWND staticText = CreateWindow(TEXT("STATIC"),
		                           TEXT("Для продолжения необходимо ввести имя пользователя и пароль"),
		                           WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
		                           xPos, yPos,
		                           staticTextWidth, staticTextHeight,
		                           this->getHandle(),
		                           (HMENU)NULL,
		                           (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                           NULL);

	int editWidth = 200;
	int editHeight = 20;
	xPos = (parentRC.right - parentRC.left) / 2 - editWidth / 2;
	yPos += staticTextHeight + 4 * offsetsBetweenWindow;
	m_UserName = new EditControlTemplate(this->getHandle(), xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP);
	m_UserName->createDescriptionForEdit(L"Имя пользователя");
	m_UserName->setFocusOnEdit();
	m_UserName->setFontForEdit(hFont);
	m_UserName->setNewTextForEdit(TEXT("Zhmenka"));


	yPos += editHeight + descriptionForControlHeight + offsetsBetweenWindow;
	m_Password = new EditControlTemplate(this->getHandle(), xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | WS_TABSTOP);
	m_Password->createDescriptionForEdit(L"Пароль");
	m_Password->setFontForEdit(hFont);
	m_Password->setNewTextForEdit(TEXT("47dim9175rty"));
	

	
	
}

BOOL AuthenticationForm::verifyData() const
{
	TCHAR* username = m_UserName->getTextFromEdit();
	if (_tcscmp(username, L"") == 0)
	{
		MessageBox(this->getHandle(), L"Укажите имя пользователя", L"Ошибка при подключении", MB_OK);
		return FALSE;
	}
	TCHAR* password = m_Password->getTextFromEdit();
	if (_tcscmp(password, L"") == 0)
	{
		MessageBox(this->getHandle(), L"Введите пароль", L"Ошибка при подключении", MB_OK);
		return FALSE;
	}
	return TRUE;
}


LRESULT AuthenticationForm::RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
										DEFAULT_CHARSET,
										0, 0, 0, VARIABLE_PITCH,
										L"Time New Romans");
			SelectObject(hdcStatic, hFont);
			SetBkMode(hdcStatic, TRANSPARENT);
			return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_CONTINUE_AUTENTIFICATION_BTN:
			{	
				if (verifyData())
				{
					if (!m_databaseController->connect(m_UserName->getTextFromEdit(), m_Password->getTextFromEdit()))
					{
						MessageBox(hWnd, L"Неверное имя пользователя или пароль", L"Ошибка подключения", MB_OK);
					}
				}
				break;
			}
			case ID_CANCEL_AUXILIARY_BTN:
			{
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				PostQuitMessage(0);
				break;
			}
			}
			break;
		}
		case WM_DESTROY:
		{
			DestroyWindow(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
