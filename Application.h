#pragma once

#include "MainApplicationWindow.h"
#include "DataBase.h"
#include "DatabaseController.h"

class Application
{
public:
	Application();
	~Application();
	int run();
private:
	MainApplicationWindow* m_mainView;
	DataBase* m_dataBase;
	DatabaseController* m_databaseController;
	
};

