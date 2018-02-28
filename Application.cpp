#include "Application.h"


Application::Application()
{
	m_mainView = new MainApplicationWindow(L"MainApplicationWindow", L"Test Database Project");
}


Application::~Application()
{
	if (m_mainView)
	{
		delete m_mainView;
		m_mainView = nullptr;
	}
}

int Application::run()
{
	MSG msg;  
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);   
		DispatchMessage(&msg);    
	}
	return static_cast<int>(msg.wParam);
}
