#pragma once

#include <Windows.h>
#include "View.h"
#include "ImageTemplate.h"
#include "ListView.h"
class ClientView 
	: public View
{
public:
	ClientView(HWND parent);
	~ClientView();
	virtual void activate(UserInterfaceController* controller);
	virtual void hide();
	virtual void show();
private:
	HWND m_parentForView;
	ImageTemplate* m_clientImage;
	ListView* m_clientsList;
};

