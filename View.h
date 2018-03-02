#pragma once
#include "UserInterfaceController.h"
class View
{
public:
	virtual void activate(UserInterfaceController* controller) = 0;
	virtual void hide() = 0;
	virtual void show() = 0;
	View();
	~View();
private:
	
};

