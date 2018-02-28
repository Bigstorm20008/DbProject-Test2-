class Observer;

#pragma once
#include "Observer.h"
#include <vector>
class Subject
{
public:	
	virtual ~Subject();
	virtual void attach(Observer*);
	//virtual void detach(Observer*);
	virtual void notify();
protected:
	Subject();
private:
	(std::vector<Observer*>)* m_Observers;
};

