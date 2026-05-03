#pragma once
#include <string>

// Class called by the Subject to send updates
class IObserver
{
public:
	virtual ~IObserver() = default;

	virtual void listen(std::string message) = 0;
};