class Subject;

#pragma once
#include "Subject.h"

class Observer
{
public:
	virtual ~Observer();
	virtual void update(Subject* theChangedSubject) = 0;
protected:
	Observer();
};

