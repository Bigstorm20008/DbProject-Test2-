#include "Subject.h"


Subject::Subject()
{
	m_Observers = new std::vector<Observer*>;
}


Subject::~Subject()
{
	if (m_Observers)
	{
		m_Observers->clear();
		delete m_Observers;
		m_Observers = nullptr;
	}
}

void Subject::attach(Observer* observer)
{
	m_Observers->push_back(observer);
}
/*void Subject::detach(Observer* observer)
{
	m_Observers->(observer);
}*/
void Subject::notify()
{
	for (auto& elem : *m_Observers)
	{
		elem->update(this);
	}
}
