#include "MiniginPCH.h"
#include "Subject.h"
#include <iostream>

Subject::~Subject()
{

}

void Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);

}

void Subject::RemoveObserver(Observer* observer)
{
	for (size_t i = 0; i < m_Observers.size(); ++i)
	{
		if (observer == m_Observers[i])
		{
			m_Observers.erase(m_Observers.begin() + i);
			break;
		}
	}

}

void Subject::Notify(Event event)
{
	for (size_t i = 0; i < m_Observers.size(); ++i)
	{
		m_Observers[i]->onNotify(event);
	
	}
}
