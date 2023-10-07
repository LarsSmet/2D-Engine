#pragma once
#include "Event.h"

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void onNotify(Event event) = 0;
};

