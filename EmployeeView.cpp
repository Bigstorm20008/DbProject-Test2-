#include "EmployeeView.h"


EmployeeView::EmployeeView(HWND parent)
{
	m_parentForView = parent;
}


EmployeeView::~EmployeeView()
{
	if (m_clientImage)
	{
		delete m_clientImage;
		m_clientImage = nullptr;
	}
	if (m_clientsList)
	{
		delete m_clientsList;
		m_clientsList = nullptr;
	}
}

void EmployeeView::activate(UserInterfaceController* controller)
{
	if (!m_clientImage)
	{
		m_clientImage = new ImageTemplate(10, 70, 320, 280, m_parentForView, NULL);
		m_clientImage->loadDefaultImage();
	}
	if (!m_clientsList)
	{
		m_clientsList = new ListView(m_parentForView, 340, 70, 400, 400);
	}
	m_clientsList->fillList(controller->getAllEmployees());
}
void EmployeeView::hide()
{
	ShowWindow(m_clientsList->getHandleOfList(), SW_HIDE);
	ShowWindow(m_clientImage->getHandle(), SW_HIDE);
}

void EmployeeView::show()
{
	ShowWindow(m_clientsList->getHandleOfList(), SW_NORMAL);
	ShowWindow(m_clientImage->getHandle(), SW_NORMAL);
}


