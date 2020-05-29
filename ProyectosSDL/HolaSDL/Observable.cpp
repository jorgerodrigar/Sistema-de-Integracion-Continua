#include "Observable.h"



Observable::Observable():numOfObservers_(0)
{
	
}


Observable::~Observable()
{
}

void Observable::removeObserver(Observer * o)
{
	std::vector<Observer*>::iterator it = std::find(observers_.begin(),
		observers_.end(), o);
	if (it != observers_.end())
		observers_.erase(it);
}

void Observable::send(Mensaje* msg)
{
	for (Observer* o : observers_) {
		o->receive(msg);
	}
}


