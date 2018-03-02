#include "Application.h"


Application::Application()
{
	m_dataBase = new DataBase;
	m_databaseController = new DatabaseController(m_dataBase);
	m_mainView = new MainApplicationWindow(L"MainApplicationWindow", L"Test Database Project", m_databaseController);

}


Application::~Application()
{
	if (m_mainView)
	{
		delete m_mainView;
		m_mainView = nullptr;
	}
	if (m_dataBase)
	{
		delete m_dataBase;
		m_dataBase = nullptr;
	}
	if (m_databaseController)
	{
		delete m_databaseController;
		m_databaseController = nullptr;
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
