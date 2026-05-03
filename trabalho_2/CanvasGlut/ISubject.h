#pragma once
#include "IObserver.h"

// manages the list of observers
class ISubject
{
public:
	virtual ~ISubject() = default;

	virtual void attach(IObserver *observer) = 0;

	virtual void detach(IObserver* observer) = 0;

	virtual void notify() = 0;
};