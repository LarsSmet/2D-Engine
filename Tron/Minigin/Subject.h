#pragma once
#include "Observer.h"

class Subject
{
public:

	virtual ~Subject();

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:

	void Notify(Event event);



protected:

	
	//i expect that there won't be a lot of observers per subject
	std::vector<Observer*> m_Observers;

};

